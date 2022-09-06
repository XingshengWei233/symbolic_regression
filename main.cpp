#include "Genome.h"
#include <iostream>
#include <cmath>//math operators
#include <cstdlib>//generate random number
#include <time.h>//generate random number
#include <string>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;


void loadData(string loadDir, float *datax, float *datay){
    ifstream infile;
    infile.open(loadDir);
    string s;
    int i = 0;
    while (getline(infile, s))
    {
        string s1 = s.substr(0, 7);
        string s2 = s.substr(8);
        datax[i] = stof(s1);
        datay[i] = stof(s2);
        i++;
    }
    infile.close();   
}


int main(int argc, char **argv)
{
    // Parameters:
    float datax[1000];
    float datay[1000];

    // load data:
    loadData("data/data.txt", datax, datay);

    // for (int i=0; i<1000; i++){
    //     cout<<datax[i]<<endl;
    // }
    Genome genome();
    cout << "111" << endl;

    return 0;
}