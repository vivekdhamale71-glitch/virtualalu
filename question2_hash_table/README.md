# Question 2: Hash Table of Mango Varieties

## Personalisation (PRN 202501100156)

| Item | Rule | Value |
|---|---|---|
| Scenario | PRN mod 3 = 2 | Mango varieties |
| Seed S | last four digits (0156) | 156 |
| Dataset | v[i] = (156 + 13i) mod 100, i = 0..19 | see below |
| Hash function | PRN is even | Division method |
| Collision strategy | PRN is even | Linear probing |

Dataset: 56, 69, 82, 95, 8, 21, 34, 47, 60, 73, 86, 99, 12, 25, 38, 51, 64, 77,
90, 3

## Compile and run

From the repository root, with g++ (tested with g++ 15.2.0 on Linux):

    g++ -std=c++17 -Wall -Wextra -Wpedantic -o question2_hash_table/mango question2_hash_table/mango_hash_table.cpp
    ./question2_hash_table/mango

The program takes no input. To save the output:

    ./question2_hash_table/mango > question2_hash_table/actual_output.txt

## Hash function: division method

    h(key) = key mod 29

The remainder is always 0 to 28, so it is a valid slot. Example:
56 mod 29 = 27. Mid-square hashing is for odd PRNs, so it is not used.

## Collision strategy: linear probing

If the home slot holds another key, try the next slot, one at a time:

    index = (home + step) mod 29,   step = 0, 1, 2, ... 28

- `mod 29` wraps from slot 28 back to slot 0.
- At most 29 slots are tried, so a full table cannot cause an endless loop.
- An empty slot is marked -1, which is never a real key (keys are 0 to 99).

## Duplicate values

While probing, if a slot already holds the same key, the program reports a
duplicate and does not store it again. This works because nothing is ever
deleted: an earlier copy is always met before the first empty slot. (Adding
deletion would need a separate "deleted" marker.)

This dataset has **no duplicates**, because 13 and 100 share no common factor.
To show the check anyway, the program inserts 38 again after the final table.
38 is a good test because it is not in its home slot.

## Assumptions

- **Table size m = 29.** The assignment gives no size. 29 is the smallest prime
  that keeps the load factor for 20 keys at or below 0.70 (20/29 = 0.69). A
  prime helps the division method spread keys with common patterns, and the nine
  spare slots keep probe runs short.
- Each value is a **mango variety code** from 0 to 99. No variety names are
  invented. The value is also the key.
- The program only inserts and displays; search and delete were not requested.

## Result

20 keys stored, 4 collided (8, 12, 38, 3), 24 probes in total.

## Quick viva notes

- **Why linear probing needs `% m`:** to continue from the last slot to slot 0.
- **Weakness:** primary clustering. Filled slots join into runs, and any key that
  lands in a run must walk to its end. Here, slots 8 to 13 form one run.
- **Why 38 collided:** key 8 had been moved into slot 9, which is 38's home.
- **Cost:** insertion is O(1) on average at moderate load, O(m) in the worst case.

## Files

| File | Contents |
|---|---|
| `mango_hash_table.cpp` | the program |
| `actual_output.txt` | saved output of one run |
| `PREDICTION_WORKSHEET.md` | prediction made before the hashing code |
| `TRACE_MATCH_REPORT.md` | prediction compared with the output |
| `DEBUG_JOURNAL.md` | dated journal and deliberate bug tests |
| `GIT_LOG.txt` | `git log --stat` export with timestamps |
