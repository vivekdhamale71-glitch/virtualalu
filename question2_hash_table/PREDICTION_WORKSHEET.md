# Hand-Prediction Worksheet (Question 2)

**PRN:** 202501100156 | **Scenario:** Mango varieties | **S:** 156
**Hash:** h(key) = key mod 29 | **Collisions:** linear probing | **m:** 29

**How this was prepared:** an AI assistant worked these values out by
arithmetic, without running any code. It was written and committed before the
hashing code existed. If your course needs a prediction in your own hand, redo
it on paper (see the blank sheet at the end).

## Rules

1. Home index = key mod 29.
2. If the home slot is empty, put the key there.
3. If it holds a different key, that is a collision. Try (index + 1) mod 29
   until an empty slot is found.
4. If a slot on the way already holds the same key, it is a duplicate. Do not
   insert it again.

## Dataset: v[i] = (156 + 13i) mod 100

56, 69, 82, 95, 8, 21, 34, 47, 60, 73, 86, 99, 12, 25, 38, 51, 64, 77, 90, 3

## Step-by-step prediction

| Step | Key | Working | Home | Collision handling | Final slot | Probes |
|---:|---:|---|---:|---|---:|---:|
| 1 | 56 | 56 - 1×29 = 27 | 27 | none | 27 | 1 |
| 2 | 69 | 69 - 2×29 = 11 | 11 | none | 11 | 1 |
| 3 | 82 | 82 - 2×29 = 24 | 24 | none | 24 | 1 |
| 4 | 95 | 95 - 3×29 = 8 | 8 | none | 8 | 1 |
| 5 | 8 | 8 - 0×29 = 8 | 8 | 8 holds 95, go to 9 | 9 | 2 |
| 6 | 21 | 21 - 0×29 = 21 | 21 | none | 21 | 1 |
| 7 | 34 | 34 - 1×29 = 5 | 5 | none | 5 | 1 |
| 8 | 47 | 47 - 1×29 = 18 | 18 | none | 18 | 1 |
| 9 | 60 | 60 - 2×29 = 2 | 2 | none | 2 | 1 |
| 10 | 73 | 73 - 2×29 = 15 | 15 | none | 15 | 1 |
| 11 | 86 | 86 - 2×29 = 28 | 28 | none | 28 | 1 |
| 12 | 99 | 99 - 3×29 = 12 | 12 | none | 12 | 1 |
| 13 | 12 | 12 - 0×29 = 12 | 12 | 12 holds 99, go to 13 | 13 | 2 |
| 14 | 25 | 25 - 0×29 = 25 | 25 | none | 25 | 1 |
| 15 | 38 | 38 - 1×29 = 9 | 9 | 9 holds 8, go to 10 | 10 | 2 |
| 16 | 51 | 51 - 1×29 = 22 | 22 | none | 22 | 1 |
| 17 | 64 | 64 - 2×29 = 6 | 6 | none | 6 | 1 |
| 18 | 77 | 77 - 2×29 = 19 | 19 | none | 19 | 1 |
| 19 | 90 | 90 - 3×29 = 3 | 3 | none | 3 | 1 |
| 20 | 3 | 3 - 0×29 = 3 | 3 | 3 holds 90, go to 4 | 4 | 2 |

## Table state after each step (occupied slots as slot:key)

| After step | Occupied slots |
|---:|---|
| 1 | 27:56 |
| 2 | 11:69, 27:56 |
| 3 | 11:69, 24:82, 27:56 |
| 4 | 8:95, 11:69, 24:82, 27:56 |
| 5 | 8:95, 9:8, 11:69, 24:82, 27:56 |
| 6 | 8:95, 9:8, 11:69, 21:21, 24:82, 27:56 |
| 7 | 5:34, 8:95, 9:8, 11:69, 21:21, 24:82, 27:56 |
| 8 | 5:34, 8:95, 9:8, 11:69, 18:47, 21:21, 24:82, 27:56 |
| 9 | 2:60, 5:34, 8:95, 9:8, 11:69, 18:47, 21:21, 24:82, 27:56 |
| 10 | 2:60, 5:34, 8:95, 9:8, 11:69, 15:73, 18:47, 21:21, 24:82, 27:56 |
| 11 | 2:60, 5:34, 8:95, 9:8, 11:69, 15:73, 18:47, 21:21, 24:82, 27:56, 28:86 |
| 12 | 2:60, 5:34, 8:95, 9:8, 11:69, 12:99, 15:73, 18:47, 21:21, 24:82, 27:56, 28:86 |
| 13 | 2:60, 5:34, 8:95, 9:8, 11:69, 12:99, 13:12, 15:73, 18:47, 21:21, 24:82, 27:56, 28:86 |
| 14 | 2:60, 5:34, 8:95, 9:8, 11:69, 12:99, 13:12, 15:73, 18:47, 21:21, 24:82, 25:25, 27:56, 28:86 |
| 15 | 2:60, 5:34, 8:95, 9:8, 10:38, 11:69, 12:99, 13:12, 15:73, 18:47, 21:21, 24:82, 25:25, 27:56, 28:86 |
| 16 | 2:60, 5:34, 8:95, 9:8, 10:38, 11:69, 12:99, 13:12, 15:73, 18:47, 21:21, 22:51, 24:82, 25:25, 27:56, 28:86 |
| 17 | 2:60, 5:34, 6:64, 8:95, 9:8, 10:38, 11:69, 12:99, 13:12, 15:73, 18:47, 21:21, 22:51, 24:82, 25:25, 27:56, 28:86 |
| 18 | 2:60, 5:34, 6:64, 8:95, 9:8, 10:38, 11:69, 12:99, 13:12, 15:73, 18:47, 19:77, 21:21, 22:51, 24:82, 25:25, 27:56, 28:86 |
| 19 | 2:60, 3:90, 5:34, 6:64, 8:95, 9:8, 10:38, 11:69, 12:99, 13:12, 15:73, 18:47, 19:77, 21:21, 22:51, 24:82, 25:25, 27:56, 28:86 |
| 20 | 2:60, 3:90, 4:3, 5:34, 6:64, 8:95, 9:8, 10:38, 11:69, 12:99, 13:12, 15:73, 18:47, 19:77, 21:21, 22:51, 24:82, 25:25, 27:56, 28:86 |

## Predicted summary

- Keys inserted: 20
- Keys that collided: 4 (8, 12, 38, 3)
- Extra probes: 4 (one for each of those keys)
- Total probes: 24
- Empty slots: 0, 1, 7, 14, 16, 17, 20, 23, 26 (9 slots)
- Duplicates in the dataset: none. gcd(13, 100) = 1, so 13i mod 100 is
  different for every i from 0 to 19.

## Blank sheet for your own prediction

Copy this onto paper and fill it in without looking at the table above.

| Step | Key | key mod 29 | Occupied slots tried | Final slot |
|---:|---:|---|---|---|
| 1 | 56 | | | |
| 2 | 69 | | | |
| 3 | 82 | | | |
| 4 | 95 | | | |
| 5 | 8 | | | |
| 6 | 21 | | | |
| 7 | 34 | | | |
| 8 | 47 | | | |
| 9 | 60 | | | |
| 10 | 73 | | | |
| 11 | 86 | | | |
| 12 | 99 | | | |
| 13 | 12 | | | |
| 14 | 25 | | | |
| 15 | 38 | | | |
| 16 | 51 | | | |
| 17 | 64 | | | |
| 18 | 77 | | | |
| 19 | 90 | | | |
| 20 | 3 | | | |
