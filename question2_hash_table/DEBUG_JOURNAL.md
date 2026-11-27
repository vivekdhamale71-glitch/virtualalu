# Debugging and Development Journal: Question 2 Hash Table

For the team. Entries are in time order, times are IST (+05:30), and only things
that actually happened are recorded. The work was done by an AI
assistant at the request of the owner of PRN 202501100156.

**Build command used throughout** (run from the repository root; `<out>` was a
temporary folder outside the repository):

    g++ -std=c++17 -Wall -Wextra -Wpedantic -o <out>/mango question2_hash_table/mango_hash_table.cpp

## 2026-11-27

### Before the first commit: setup

- Looked at the file listing, `run.sh` and the git log.
- Commands that would have printed older project files and the assignment PDFs
  were rejected by the repository owner, who asked that their files not be read.
  All work is in the new folder `question2_hash_table/`, based on the written
  task description. The assignment PDFs were not checked.
- `git fetch`: local `main` and `origin/main` were level (0 ahead, 0 behind).
- Worked out the values: PRN mod 3 = 2 (mango), S = 156, division method,
  linear probing. Chose m = 29.

### 00:07:43: commit d0246d8, program skeleton

- Added the header comment and dataset generation.
- Compiled with no warnings. All 20 printed values matched the hand calculation.
- Pushed at 00:07:45.

### 00:08:09: commit 6f24800, hand-prediction worksheet

- Predicted every home index, collision and table state by arithmetic, before
  any hashing code existed.
- The push was scheduled at least 5 minutes after the previous one.

### Between commits 2 and 3: division hash

- Added `M = 29`, `hashKey()` and printing of the indices while the push of
  commit 2 was waiting.
- Compiled with no warnings. All 20 indices matched the worksheet.
- Held back the commit so that each push carries one commit.
- Pushed commit 6f24800 at 00:12:53.
- Saved a copy of this hash-only version outside the repository.
- A command to commit this milestone was rejected by the repository owner, so
  commits and pushes were put on hold.

### About 00:14: linear probing, duplicate check, final table

- Added `insertKey()`, `printOccupied()`, `printFinalTable()`, the summary and
  the duplicate check demo.
- Compiled with no warnings and ran with exit code 0. Output saved in
  `actual_output.txt`.
- Compared it with the worksheet using `diff`: no differences in 20 steps or
  20 table states. See `TRACE_MATCH_REPORT.md`.

**Development errors so far:** no compile errors, warnings or wrong results.

## Deliberate fault-injection tests (about 00:14)

**These bugs were put in on purpose, at the owner's request. They did not occur
during development.** Each was added to a temporary copy of the finished
program. The program in this folder never contained them. Flags were
`-std=c++17 -Wall -Wextra -Wpedantic -g`; test A also used
`-fsanitize=address,undefined`. None of the buggy copies produced a compiler
warning.

To repeat a test, copy the program, make the change shown, replace `main()`
where a test input is given, then compile and run.

### Test A: no wrap-around

Change in `insertKey()`:

    - int index = (home + step) % M;
    + int index = home + step;

**A1, the real dataset:** exit code 0, output identical to the correct program
(checked with `cmp`). No key probes past slot 28, so the bug stays hidden.

**A2, test input:** insert 28, then 57 (both have home index 28).

    Correct program (exit 0):
    Insert 57: home index = 57 mod 29 = 28
        collision: slot 28 holds 28, move to the next slot
        stored in slot 0 after 2 probe(s)
        Table: 0:57, 28:28

    Buggy copy (exit 1), first lines of the error:
    ERROR: AddressSanitizer: stack-buffer-overflow
    READ of size 4 ...
        #0 ... in insertKey(int*, int, int&) bugA_A.cpp:84

- **Cause:** the second probe reads `table[29]`; valid slots are 0 to 28.
- **Fix:** keep `% M`.
- **Lesson:** a correct run on one dataset does not test wrap-around.

### Test B: no duplicate check

Change: delete the whole `if (table[index] == key) { ... }` block.
Input: unchanged `main()`, which inserts 38 a second time at the end.

    Correct program:
        collision: slot 9 holds 8, move to the next slot
        duplicate: 38 is already in slot 10, not stored again

    Buggy copy (exit 0, no error message):
        collision: slot 9 holds 8, move to the next slot
        collision: slot 10 holds 38, move to the next slot
        collision: slot 11 holds 69, move to the next slot
        collision: slot 12 holds 99, move to the next slot
        collision: slot 13 holds 12, move to the next slot
        stored in slot 14 after 6 probe(s)

- **Result:** 38 is in both slot 10 and slot 14.
- **Fix:** while probing, stop if the slot already holds the same key. Checking
  only the home slot is not enough, because 38 is not in its home slot.

### Test C: no limit on the probe loop

Change in `insertKey()`:

    - for (int step = 0; step < M; step++) {
    + for (int step = 0; ; step++) {

Input: replace `main()` so it inserts keys 0 to 28 (table full), then 29. Each
version ran under `timeout 2`.

    Correct program (exit 0):
        table full: 29 was not stored
    returned after 29 probes

    Buggy copy: exit 124 (stopped by timeout). It never returned.

- **Cause:** there is no empty slot or matching key to end the loop.
- **Fix:** allow at most M probes.

## Commits and pushes after the hold

The owner asked for the remaining commits to be made and pushed. Commit times
below are later than the times the work was done, because commits were on hold.
Before each push, `git fetch` showed no new commits on the remote.

| Commit | Committed | Pushed | Contents |
|---|---|---|---|
| 0cf7167 | 00:17:59 | 00:18:01 | division hash (staged from the saved copy) |
| 50186a2 | 00:23:07 | 00:23:09 | linear probing, duplicate check, final table |
| 45c1087 | 00:28:15 | 00:28:17 | program output, trace-match report |

Before commit 45c1087, the assistant's product name was removed from the
worksheet, trace report and this journal at the owner's request. They still say
that an AI assistant did the work. No predicted values changed.

The README and this journal go in the next commit, followed by the
`git log --stat` export. Pushes stay at least 5 minutes apart.

## 2026-11-27 about 05:28: explanations added to the terminal output

- At the owner's request, the program now also prints the personal values, the
  table size reason, the collision paths of keys 8 and 38, and a wrap-around
  demo (test keys 28 and 57, separate table). The seed is now calculated from
  the PRN in the code.
- Compiled with no warnings. A run with
  `-fsanitize=address,undefined` exited with code 0.
- Saved the new `actual_output.txt` and repeated the trace comparison: still no
  differences in 20 steps and 20 table states. Insertion logic was not changed.
