#include <iostream>
#include <omp.h>

using namespace std;

void multiply(double** matr1, double** matr2, double** result, int size, int threads) {
#pragma omp parallel for shared(matr1, matr2, result) num_threads(threads)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                result[i][j] += matr1[i][k] * matr2[k][j];
            }
        }
    }
    
}

int main() {
    double** matr1, ** matr2, ** result;
    int size=1000;
    double start_time, end_time;
    int threads;
    cout << "Input nuber of threads ";
    cin >> threads;

    matr1 = new double* [size];
    for (int i = 0; i < size; ++i) {
        matr1[i] = new double[size];
        for(int j=0; j< size; j++)
            matr1[i][j] = rand()%100;
    }

    matr2 = new double* [size];
    for (int i = 0; i < size; ++i) {
        matr2[i] = new double[size];
        for (int j=0; j < size; j++)
            matr2[i][j] = rand() % 100;
    }

    result = new double* [size];
    for (int i = 0; i < size; ++i) {
        result[i] = new double[size];
        for (int j = 0; j < size; j++)
            result[i][j] = 0;
    }

     
        start_time = omp_get_wtime(); // Начальное время
        multiply(matr1, matr2, result, size, threads);
        
        end_time = omp_get_wtime(); // Конечное время
        cout << end_time - start_time;
        cout << endl;

        delete[] matr1;
        delete[] matr2;
        delete[] result;

	return 0;
}