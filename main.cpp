#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

#define NUM_THREADS 10
#define MATRIX_SIZE 3

int counter = 0;
//atomic<int> counter(0);
mutex mtx;


void multiplication(int fila,int columna,int(matrix_1)[MATRIX_SIZE][MATRIX_SIZE],int(matrix_2)[MATRIX_SIZE][MATRIX_SIZE],int(&matrixresult)[MATRIX_SIZE][MATRIX_SIZE]){
  int mult = 0;
  for(int i = 0; i < MATRIX_SIZE; i++){
    mult += matrix_1[fila][i]*matrix_2[i][columna];
  }
  matrixresult[fila][columna] = mult;
}


int main(int argc, char *argv[]) {
    cout << "===========================================================" << endl;
    cout << "\tThreads" << endl;
    cout << "===========================================================" << endl << endl;

    int matrix1[MATRIX_SIZE][MATRIX_SIZE] = {{1,2,3},{4,5,6},{7,8,9}};
    int matrix2[MATRIX_SIZE][MATRIX_SIZE] = {{9,8,7},{6,5,4},{3,2,1}};
    int matrixresult[MATRIX_SIZE][MATRIX_SIZE];
    thread threads[MATRIX_SIZE*MATRIX_SIZE];

    for(int i = 0; i < MATRIX_SIZE;i++){
      for(int j = 0; j < MATRIX_SIZE;j++){
        threads[counter] = thread(multiplication,i,j,matrix1,matrix2,std::ref(matrixresult));
        counter += 1;
      }
    }
    // We have to wait for the threads, otherwise the main thread may finish first

    for(int y = 0; y < MATRIX_SIZE*MATRIX_SIZE;y++){
      threads[y].join();
    }

    for(int i = 0; i < MATRIX_SIZE; i++){
      for(int j = 0; j < MATRIX_SIZE; j++){
        cout << matrixresult[i][j]<<" ";
      }
      cout << endl;
    }

    return 0;
}

// TODO
// Multiplicación de matrices en paralelo
