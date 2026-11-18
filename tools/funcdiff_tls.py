"""Find the immediate values that x64 code uses only as TLS offsets."""

from collections import defaultdict
from functools import lru_cache

import capstone
from capstone import x86 as X86

_GPR_NAMES = {
    alias: group[0]
    for group in (
        ("rax", "eax", "ax", "ah", "al"),
        ("rbx", "ebx", "bx", "bh", "bl"),
        ("rcx", "ecx", "cx", "ch", "cl"),
        ("rdx", "edx", "dx", "dh", "dl"),
        ("rsi", "esi", "si", "sil"),
        ("rdi", "edi", "di", "dil"),
        ("rbp", "ebp", "bp", "bpl"),
        ("rsp", "esp", "sp", "spl"),
        *((f"r{n}", f"r{n}d", f"r{n}w", f"r{n}b") for n in range(8, 16)),
    )
    for alias in group
}
_ARG_REGS = {"rcx", "rdx", "r8", "r9"}
_CALL_WRITES = _ARG_REGS | {"rax", "r10", "r11"}


def exact_tls_offsets(insns):
    """Find immediate definitions whose only use is a named TLS address."""
    if not any(op.type == X86.X86_OP_MEM and op.mem.segment == X86.X86_REG_GS
               for ins in insns for op in ins.operands):
        return set()

    def register(ins, operand):
        return _GPR_NAMES.get(ins.reg_name(operand))

    def memory(op):
        return op.type == X86.X86_OP_MEM

    def mov_load(ins):
        return (ins.mnemonic == "mov" and len(ins.operands) == 2
                and ins.operands[0].type == X86.X86_OP_REG and ins.operands[0].size == 8
                and memory(ins.operands[1]))

    def tebs_tls_pointer(ins):
        return (mov_load(ins) and ins.operands[1].mem.segment == X86.X86_REG_GS
                and ins.operands[1].mem.disp == 0x58
                and not (ins.operands[1].mem.base or ins.operands[1].mem.index))

    if any(ins.mnemonic == "jmp" and ins.operands[0].type != X86.X86_OP_IMM for ins in insns):
        return set()  # The control flow of a computed jump is not known here.

    address_index = {ins.address: i for i, ins in enumerate(insns)}
    predecessors = defaultdict(set)
    successors = defaultdict(set)
    reads, writes = [], []
    for i, ins in enumerate(insns):
        rd, wr = ins.regs_access()
        reads.append({register(ins, r) for r in rd} - {None})
        writes.append({register(ins, r) for r in wr} - {None})
        if ins.mnemonic == "jmp" and ins.operands[0].imm not in address_index:
            reads[-1].update(_ARG_REGS)
        if ins.group(capstone.CS_GRP_CALL):
            reads[-1].update(_ARG_REGS)
            writes[-1].update(_CALL_WRITES)
        if ins.group(capstone.CS_GRP_RET):
            reads[-1].add("rax")

        if ins.mnemonic != "jmp" and not ins.group(capstone.CS_GRP_RET) and i + 1 < len(insns):
            successors[i].add(i + 1)
        if ((ins.group(capstone.CS_GRP_JUMP) or ins.mnemonic.startswith("loop"))
                and ins.operands and ins.operands[0].type == X86.X86_OP_IMM):
            target = address_index.get(ins.operands[0].imm)
            if target is not None:
                successors[i].add(target)
        for target in successors[i]:
            predecessors[target].add(i)

    # Each path must reach the same definition. A path from the function
    # entry without a definition also makes the value unknown.
    @lru_cache(None)
    def reaching(index, reg):
        pending = list(predecessors[index])
        seen = set()
        result = None
        while pending:
            i = pending.pop()
            if i in seen:
                continue
            seen.add(i)
            if reg in writes[i]:
                if result is not None and i != result:
                    return None
                result = i
            elif i == 0 or not predecessors[i]:
                return None
            else:
                pending.extend(predecessors[i])
        return result

    # The first entry of the thread storage vector is the exe TLS block.
    def tls_vector_access(i, mem, ins):
        if not mem.base or mem.index or mem.segment or mem.disp:
            return False
        vector_load = reaching(i, register(ins, mem.base))
        return vector_load is not None and tebs_tls_pointer(insns[vector_load])

    def tls_base(i, reg):
        slot_load = reaching(i, reg)
        if slot_load is None or not mov_load(insns[slot_load]):
            return False
        slot = insns[slot_load]
        return tls_vector_access(slot_load, slot.operands[1].mem, slot)

    uses = defaultdict(set)

    def add_use(index, offset):
        definition = reaching(index, offset)
        if definition is None:
            return
        ins = insns[definition]
        if ins.mnemonic != "mov" or len(ins.operands) != 2:
            return
        dst, src = ins.operands
        if dst.type == X86.X86_OP_REG and dst.size >= 4 and src.type == X86.X86_OP_IMM:
            uses[definition].add(index)

    for i, ins in enumerate(insns):
        direct_reads = {
            register(ins, op.reg) for op in ins.operands
            if op.type == X86.X86_OP_REG and op.access & capstone.CS_AC_READ
        }
        for op in ins.operands:
            if memory(op) and op.mem.base and op.mem.index and op.mem.scale == 1 and not op.mem.segment:
                a, b = register(ins, op.mem.base), register(ins, op.mem.index)
                if not a or not b or a == b:
                    continue
                for base, offset in ((a, b), (b, a)):
                    if offset not in direct_reads and tls_base(i, base):
                        add_use(i, offset)
        if ins.mnemonic == "add" and len(ins.operands) == 2:
            dst, src = ins.operands
            if dst.type != X86.X86_OP_REG or dst.size != 8 or src.size != 8:
                continue
            a = register(ins, dst.reg)
            if not a:
                continue
            if src.type == X86.X86_OP_REG:
                b = register(ins, src.reg)
                if not b or a == b:
                    continue
                for base, offset in ((a, b), (b, a)):
                    if tls_base(i, base):
                        add_use(i, offset)
            elif memory(src) and tls_vector_access(i, src.mem, ins):
                add_use(i, a)

    # Restrict the match to definitions whose other uses cannot give the immediate a second meaning.
    def only_tls_uses(definition, locations):
        ins = insns[definition]
        reg = register(ins, ins.operands[0].reg)
        pending = list(successors[definition])
        seen = set()
        while pending:
            i = pending.pop()
            if i in seen:
                continue
            seen.add(i)
            if reg in reads[i] and i not in locations:
                return False
            if reg not in writes[i]:
                pending.extend(successors[i])
        return True

    return {definition for definition, locations in uses.items() if only_tls_uses(definition, locations)}
