#include <iostream>
#include <cstdlib>

// This code explores how to use a pointer to iterate an entire 2_D dynamically allocated 
// matrix without anything other than the array's pointer and array sizes

using namespace std;

int main() {
  srand(time(NULL));
  int rowmax = 3;
  int columnmax = 2;
  int i; 
  int j;

  int** array = new int*[rowmax];
  for(i = 0; i < rowmax; i++) {
    array[i] = new int[columnmax];
  }

  for(i = 0; i < rowmax; i++){
    for(j = 0; j < columnmax; j++) {
      array[i][j] = rand() % 9 + 1;
    }
  }

  cout << "printing array's values\n" << "\n";

  for(i = 0; i < rowmax; i++) {
    cout << array[i][0] << " " << array[i][1] << "\n";
  }

  cout << "\nprinting array's addresses via array notation\n\n";
  
  for(i = 0; i < rowmax; i++) {
    cout << &array[i][0] << " " << &array[i][1] << "\n";
  }

  cout << "\ntrying to print array's addresses via pointer notation\n\n";

  for(i = 0; i < rowmax; i++) {
      cout << array + (i+1)*sizeof(int) << " ";
      array++;
      cout << array + (i+1)*sizeof(int) << "\n";
      array--;
  }
  
  cout << "\ntrying something new\n\n";

  int* a_ptr;
  for(i = 0; i < rowmax; i++) {
    a_ptr = *array + (i*2)*sizeof(int);
    cout << a_ptr << " ";
    a_ptr++;
    cout << a_ptr << "\n";
    a_ptr--;
  }

  cout << "\nusing a_ptr method to print array's values\n\n";

  for(i = 0; i < rowmax; i++) {
    a_ptr = *array + (i*2)*sizeof(int);
    cout << *a_ptr << " ";
    a_ptr++;
    cout << *a_ptr << "\n";
    a_ptr--;
  }

  delete[] array;

  return 0;
}
