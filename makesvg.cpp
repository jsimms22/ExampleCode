#include <iostream>
#include <fstream>  //to read or write files
#include <cmath>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>


using namespace std;

int main()
{
    srand(time(0)); //initialize random number generator

    ofstream output;            //rename 'output' for multiple files or {}

    output.open("another.svg"); //if the file does not exist, it will create it
                                //if it does it will rewrite everything
                                //basic rule if you open, close it
    
    //prints line into console with 'cout', change to 'output' to stick in file

    output << "<svg xmlns='http://www.w3.org/2000/svg' width='600' height='600' inversion='1.1'>" <<endl;

    int maxR = 300, minR = 10;

    for (int i = 0; i < 10; i++)
    {
    double r = 300 - ((maxR - minR) / 9 * i);
    int red = rand() % 256;

    output << "<circle cx='300' cy='300' r='" << r << "' fill='rgb(" << red << ",0,0)' />"
    <<endl;
    }

    output << "</svg>"<< endl;

    output.close();             //only name it when you open it
}
