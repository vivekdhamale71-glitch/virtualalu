# Trace-Match Report (Question 2)

**PRN:** 202501100156 | h(key) = key mod 29 | linear probing

## What was compared

- **Prediction:** `PREDICTION_WORKSHEET.md`, worked out by an AI
  assistant and committed in 6f24800 at 2026-11-27 00:08:09 +0530, before any hashing code
  existed.
- **Actual:** `actual_output.txt`, from the finished program. The duplicate demo
  at the end is left out of the comparison because it is not part of the dataset.

## Method

Shell tools (`awk`, `sed`) pulled the values out of both files into the same
format, and `diff` compared them:

1. For each of the 20 insertions: key, home index, final slot, probe count.
2. After each of the 20 insertions: the full list of occupied slots.

## Results

| Check | Predicted | Actual | Match |
|---|---|---|---|
| 20 steps (key, home, slot, probes) | worksheet | program | Yes, `diff` empty |
| 20 table states | worksheet | program | Yes, `diff` empty |
| Keys stored | 20 | 20 | Yes |
| Keys that collided | 4 | 4 | Yes |
| Total probes | 24 | 24 | Yes |
| Empty slots | 0, 1, 7, 14, 16, 17, 20, 23, 26 | same | Yes |
| Duplicates in dataset | none | none reported | Yes |

## Collisions

| Key | Home | Slot held | Predicted slot | Actual slot |
|---:|---:|---:|---:|---:|
| 8 | 8 | 95 | 9 | 9 |
| 12 | 12 | 99 | 13 | 13 |
| 38 | 9 | 8 | 10 | 10 |
| 3 | 3 | 90 | 4 | 4 |

38 collides because key 8 had been pushed from slot 8 into 38's home slot, 9.
These two keys have different home indices.

## Mismatches

**There were no mismatches**, so there is none to explain.

## Limit of this check

The same assistant made the prediction and wrote the program. The commit order
shows the prediction came first, but this is not an independent check by a
second person. If you must predict by hand yourself, use the blank sheet in the
worksheet.
