# Handoff: lift-lobbydaemon-v2b2-wco (session 1 of 4)

## What I changed

Function: `WindowConsole::Open` (CG 0x17090, LG 0x2b880, SCD 0x26c70, POD 0x346e0). One source file has the code for all 4 exes.

1. Inlined `WinMsgHandler::WinMsgHandler`: the code keeps the `SystemEvent` pointer in a local.
   `CreateEventW` stores through the local. The code does not read `_initEvent` again.
   The null case is an explicit `else initEvent = nullptr` branch.
   Evidence: the original has `mov s4, rax` / `jmp` / `mov s4, s3` and `mov qword ptr [s4], rax` after `CreateEventW`.
2. The module check and the console check are 2 separate `if` statements.
3. The 2 `Daemon::Instance->Name()` calls are in the argument list of `Initialize`.
   Evidence: the original loads the vtable of the console before the Name calls and loads `this` again after them.
   Note: the batch lead tried form 3 alone (p11) with no change. This session tries it together with forms 1 and 2.

## Not done (if the build shows that the diff stays)

`WindowConsole::Open` can stay DIFF for these causes. The driver build gives the result.

- Early `return false` after `AlertSender::Write`: the original puts `xor al, al; jmp` in place. The lift shares one `xor al, al` at the end. No source form is known. Cause: block layout.
- Zero register: the original zeroes `_consoleWindow` with `eax` and makes a new zero register (`s3`) after the Name calls. The lift keeps one callee-saved zero register (`s4`) through the function. Cause: register allocation and constant CSE.
- Store order of the inlined `Thread` constructor: the original stores `_id`, `_run`, `_maxFrozenSeconds`, `_lastExecuted`, `_threadManager`. The lift stores in member order. `Thread::Thread` is in `Thread.h` and other exes inline it. I did not change it, because a change can break a MATCH in other exes. A next session can test a body form of `Thread()` with assignments in the original order and check all 5 exes.
- LG only: the original sets `xor r8d, r8d` before `ThreadManager::StartThread`. The other 3 exes do not. Cause: LTCG constant propagation per exe.

## Files changed

- `src/Server/BloodLib/source/WindowConsole.cpp`
- `Docs/Plan/handoffs/lift-lobbydaemon-v2b2-wco.md`

# Handoff: lift-lobbydaemon-v2b2-wco (session 2 of 4)

## What I changed

Function: `WindowConsole::Open` (CG 0x17090, LG 0x2b880, SCD 0x26c70, POD 0x346e0).

1. The console check reads `_consoleWindow.console` into a local `console` and tests the local.
   The `Initialize` call still uses `_consoleWindow.console` as `this`.
   Evidence: the original has `mov s4, qword ptr [s0 + 0xc0]; test s4, s4; je L; mov s4, qword ptr [s4]`.
   The base lift has `cmp qword ptr [s0 + 0xc0], s4` (compare with the zero register).
   This form is new. It adds to the session 1 forms. The driver build gives the result.

## Checks that I did

- `Thread::Thread` store order: the original `PipeConsole::PipeConsole`, `Log::Log` and the inlined `IoWorker` ctor
  store `_id`, `_run`, `_lastExecuted`, `_threadManager` in the same order as `WinMsgHandler` in `WindowConsole::Open`.
  `PipeConsole::PipeConsole` is MATCH in the baseline with the present `Thread()` form.
  Thus the store order comes from instruction scheduling, not from source order. I did not change `Thread.h`.
- Constant evidence: the triage hint "0xc0 vs 0x30" comes from the reload of `_initEvent` (`[s5 + 0x30]`) after `CreateEventW`.
  The session 1 local `initEvent` form targets it.

## Not done (if the build shows that the diff stays)

`WindowConsole::Open` (all 4 exes). Causes and evidence:

- Zero register: the original makes the zero register (`xor s3d, s3d`) after the `Name` calls and uses `cmp qword ptr [s0 + 0xb8], 0`.
  The lift keeps one callee-saved zero register from the `_consoleWindow` reset to the end. Cause: register allocation and constant CSE
  (the same class as `EventNotiJob::finalize` and `JobManager::Execute` in the lessons stop list).
- Early `return false` block (`xor al, al; jmp L` at insn 20): block layout. No source form is known.
- LG 0x2b880 only: the original sets `xor r8d, r8d` before `ThreadManager::StartThread`. CG, SCD and POD do not.
  The source is shared, so one form cannot give both. Cause: LTCG constant propagation per exe.
- Forms tried in total: session 1 forms 1 to 3, the batch lead test p11, and form 1 of this session.

## Files changed (session 2)

- `src/Server/BloodLib/source/WindowConsole.cpp`
- `Docs/Plan/handoffs/lift-lobbydaemon-v2b2-wco.md`
