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
