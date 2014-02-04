#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

using namespace std;

int readInput(int* currentRow);
int dumpOutput(int* currentRow);
int writeOutput(int* currentRow);

int calculateRow(int* currentRow, int* nextRow);
int calculateCell(int first, int second, int third, int* cell);

const int iterations = 500000;
const int rowSize = 165;
const int rule[8] = {
  0, // 000
  1, // 001
  1, // 010
  1, // 011
  0, // 100
  1, // 101
  1, // 110
  0  // 111
};
const int sleepTime = 20000;

int main() {
  int* currentRow = (int*) malloc(rowSize * sizeof(int));
  int* nextRow = (int*) malloc(rowSize * sizeof(int));
  readInput(currentRow);
  for (int i = 0; i < iterations; i++) {
    calculateRow(currentRow, nextRow);
    for (int j = 0; j < rowSize; j++) {
      currentRow[j] = nextRow[j];
    }
    writeOutput(currentRow);
    usleep(sleepTime);
  }
  free(currentRow);
  free(nextRow);
}

int readInput(int* row) {
  cout << "Please input the initial condition of " << rowSize << " integers, 1 || 0\n";
  for (int i = 0; i < rowSize; i++) {
    cout << "x";
  }
  cout << "\n";

  char tmp;
  for (int i = 0; i < rowSize; i++) {
    tmp = getchar();
    if (tmp == '0') {
      row[i] = 0;
    } else {
      row[i] = 1;
    }
  }
}

int dumpOutput(int* row) {
  for (int i = 0; i < rowSize; i++) {
    cout << row[i];
  }
  cout << "\n\n";
}

int writeOutput(int* row) {
  for (int i = 0; i < rowSize; i++) {
    if (row[i] == 0) {
      cout << ' ';
    } else {
      cout << 'O';
    }
  }
  cout << "\n";
}

int calculateRow(int* currentRow, int* nextRow) {
  calculateCell(0, currentRow[0], currentRow[1], &nextRow[0]);
  for (int i = 1; i < rowSize - 1; i++) {
    calculateCell(currentRow[i - 1], currentRow[i], currentRow[i + 1], &nextRow[i]);
  }
  calculateCell(currentRow[rowSize - 2], currentRow[rowSize - 1], 0, &nextRow[rowSize - 1]);
}

int calculateCell(int first, int second, int third, int* cell) {
  unsigned int key = 0;
  key = key | first;
  key = key << 1;
  key = key | second;
  key = key << 1;
  key = key | third;
  *cell = rule[key];
}
