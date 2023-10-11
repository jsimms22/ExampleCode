#include <iostream>

using namespace std;

int main() {
    int imax = 5;

    double*** array = new double**[imax];
    for(int i = 0; i <imax; i++){
        array[i] = new double*[imax];
        for(int j = 0; j < imax; j++){
            array[i][j] = new double[imax];
        }
    }

}
