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

int main() {
    int v[N];
    makeDataset(v);

    cout << "PRN 202501100156 | Mango Varieties | Seed S = " << SEED << "\n\n";
    printDataset(v);
    return 0;
}
