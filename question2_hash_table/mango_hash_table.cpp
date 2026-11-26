/*
 * Question 2 : Hash Table
 *
 * PRN                : 202501100156
 * Scenario           : PRN mod 3 = 2          -> Mango varieties
 * Seed S             : last four digits       -> 0156 = 156
 * Dataset            : v[i] = (S + 13*i) mod 100, i = 0..19
 * Hash function      : PRN is even            -> Division method (key mod m)
 * Collision strategy : PRN is even            -> Linear probing
 * Table size m       : 29 (assumption, see README)
 *
 * Each value is treated as a mango variety code from 0 to 99.
 */

#include <iostream>
using namespace std;

const int SEED = 156;
const int N = 20;   // number of values in the dataset
const int M = 29;   // table size: prime, load factor 20/29 = 0.69
const int EMPTY = -1; // marks a free slot (real codes are 0..99)

// Fill v[] using the formula given in the assignment.
void makeDataset(int v[]) {
    for (int i = 0; i < N; i++) {
        v[i] = (SEED + 13 * i) % 100;
    }
}

void printDataset(const int v[]) {
    cout << "Dataset (mango variety codes):\n";
    for (int i = 0; i < N; i++) {
        cout << "  v[" << i << "] = " << v[i] << "\n";
    }
}

// Division method: the remainder is always from 0 to M-1.
// Keys are never negative here (they are 0..99).
int hashKey(int key) {
    return key % M;
}

void printHashIndices(const int v[]) {
    cout << "\nHash indices: h(key) = key mod " << M << "\n";
    for (int i = 0; i < N; i++) {
        cout << "  " << v[i] << " mod " << M << " = " << hashKey(v[i]) << "\n";
    }
}

void initTable(int table[]) {
    for (int i = 0; i < M; i++) {
        table[i] = EMPTY;
    }
}

// One-line view of the table: only the occupied slots, as slot:key.
void printOccupied(const int table[]) {
    cout << "    Table: ";
    bool first = true;
    for (int i = 0; i < M; i++) {
        if (table[i] != EMPTY) {
            if (!first) cout << ", ";
            cout << i << ":" << table[i];
            first = false;
        }
    }
    cout << "\n";
}

// Insert using linear probing.
// probes receives the number of slots that were looked at.
// Returns true if stored, false if it is a duplicate or the table is full.
bool insertKey(int table[], int key, int &probes) {
    int home = hashKey(key);
    probes = 0;
    cout << "Insert " << key << ": home index = " << key << " mod " << M
         << " = " << home << "\n";

    // At most M tries, so a full table cannot cause an endless loop.
    for (int step = 0; step < M; step++) {
        int index = (home + step) % M;   // % M wraps from the end to slot 0
        probes++;

        if (table[index] == EMPTY) {
            table[index] = key;
            cout << "    stored in slot " << index << " after " << probes
                 << " probe(s)\n";
            return true;
        }
        if (table[index] == key) {
            cout << "    duplicate: " << key << " is already in slot " << index
                 << ", not stored again\n";
            return false;
        }
        cout << "    collision: slot " << index << " holds " << table[index]
             << ", move to the next slot\n";
    }

    cout << "    table full: " << key << " was not stored\n";
    return false;
}

void printFinalTable(const int table[]) {
    cout << "\nFinal hash table\n";
    cout << "  Slot  Key\n";
    for (int i = 0; i < M; i++) {
        cout << "  " << i << (i < 10 ? "     " : "    ");
        if (table[i] == EMPTY) cout << "-";
        else cout << table[i];
        cout << "\n";
    }
}

int main() {
    int v[N];
    makeDataset(v);

    cout << "PRN 202501100156 | Mango Varieties | Seed S = " << SEED << "\n\n";
    printDataset(v);
    printHashIndices(v);

    int table[M];
    initTable(table);

    int stored = 0, collided = 0, totalProbes = 0;

    cout << "\nInsertion with linear probing\n";
    for (int i = 0; i < N; i++) {
        int probes;
        if (insertKey(table, v[i], probes)) {
            stored++;
            if (probes > 1) collided++;
        }
        totalProbes += probes;
        printOccupied(table);
    }

    printFinalTable(table);

    cout << "\nSummary\n";
    cout << "  Keys stored        : " << stored << "\n";
    cout << "  Keys that collided : " << collided << "\n";
    cout << "  Total probes       : " << totalProbes << "\n";
    cout << "  Load factor        : " << stored << "/" << M << "\n";

    // The dataset has no repeated values, so try one again to show the check.
    // 38 is useful because it was moved away from its home slot.
    cout << "\nDuplicate check demo (not part of the dataset)\n";
    int probes;
    insertKey(table, 38, probes);
    printOccupied(table);

    return 0;
}
