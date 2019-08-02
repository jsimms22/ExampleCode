#include <iostream>

using namespace std;

int main() {
    int imax = 5;

    double**** array = new double***[imax];
    for(int i = 0; i <imax; i++){
        array[i] = new double**[imax];
        for(int j = 0; j < imax; j++){
            array[i][j] = new double*[imax];
            for(int k = 0; k < imax; k++){
                array[i][j][k] = new double[imax];
            }
        }
    }

}
