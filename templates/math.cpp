#include<vector>
#include<iostream>

template <class T>
void matrix_mult(int lda, std::vector<T>& A, std::vector<T>& B, std::vector<T>& C)
// This routine performs a dgemm operation
// C := C + A * B
// where A, B, and C are lda-by-lda matrices stored in row-major format.
// On exit, A and B maintain their input values. 
{
    T sum = 0;
    for (int i = 0; i < lda; i++) {
        for (int j = 0; j < lda; j++) {
            for (int k = 0; k < lda; k++){
                C[j+i*lda] += A[k+i*lda] * B[j+k*lda];
            }         
        }
    }
}

int main()
{
    std::vector<int> A = {1,1,
                          1,1};

    std::vector<int> B = {1,1,
                          1,1};

    std::vector<int> C = {0,0,
                          0,0};

    matrix_mult(2,A,B,C);

    std::cout << "Printing vector of integers\n";
    for (auto i : C) {
        std::cout << i << ' ';
    }

    std::vector<double> Ad = {1.5f,1.5f,
                              1.5f,1.5f};

    std::vector<double> Bd = {1.5f,1.5f,
                              1.5f,1.5f};

    std::vector<double> Cd = {0.0f,0.0f,
                              0.0f,0.0f};

    matrix_mult(2,Ad,Bd,Cd);

    std::cout << "\nPrinting vector of doubles\n";
    for (auto i : Cd) {
        std::cout << i << ' ';
    }
}