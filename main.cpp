#include "Genome.h"
#include "Population.h"
#include <iostream>
#include <cmath>   //math operators
#include <cstdlib> //generate random number
#include <time.h>  //generate random number
#include <string>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

void loadData(string loadDir, float *datax, float *datay)
{
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
    srand((unsigned)time(NULL)); // give different seeds for random number

    // Parameters:
    float datax[1000];
    float datay[1000];
    const int popSize = 10;
    const int nWorker = 6;
    // load data:
    loadData("data/data.txt", datax, datay);
    int dataIndex[10] = {1, 32, 93, 402, 542, 135, 351, 643, 984, 234};

    // generate population
    Genome geno;
    geno.print();
    Population symPop(popSize);
    cout << "symPop.genomeVec.size()" << symPop.genomeVec.size() << endl;
    for (int i = 0; i < 10; i++){
        symPop.genomeVec[i].print();
    }
    // vector<Genome> tree = symPop.genomeVec[0];

    // for (int i = 0; i < 1000; i++)
    // {
    //     cout << "x: " << datax[i] << " y: " << geno.evaluate(datax[i]) << endl;
    // }
    // cout << "expression: " << geno.expression() << endl;

    cout << "end of program" << endl;

    return 0;
}