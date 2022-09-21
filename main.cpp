#include "TreePopulation.h"
#include "DataPopulation.h"
#include "UtilFuncs.h"
#include <iostream>
#include <cmath>   //math operators
#include <cstdlib> //generate random number
#include <time.h>  //generate random number
#include <string>
#include <fstream>

#include <cassert>
#include <vector>
#include <algorithm>
#include "gnuplot-iostream.h"


using namespace std;
 
//TODO:
// print out variation
// visulizer
// multithread
//seperate parameters



int main(int argc, char **argv)
{
    srand((unsigned)time(NULL)); // give different seeds for random number

    // Parameters:
    
    const int popSize = 50;
    const int nIndices = 125;
    const int nChildren = 4;
    const int nMutation = 2;
    // const int nWorker = 6;
    int maxIteration = 100000;
    int indicesRenewInterval = 100;

    int evalInterval = 100;
    int videoInterval = 1000;
    float datax[1000];
    float datay[1000];
    vector<int> trueIndices(1000);
    iota(trueIndices.begin(), trueIndices.end(), 0);

    // load data:
    loadData("data/data.txt", datax, datay);
    ofstream learnCurve;
    ofstream movieData;
    learnCurve.open("learnCurve.txt");
    movieData.open("movieData.txt");

    // generate population
    TreePopulation symPop(popSize);
    DataPopulation dataPop(popSize, nIndices);
    vector<int> indices = 
            dataPop.priority2indices(dataPop.priorityVec[0]);
    symPop.writeLoss(indices, datax, datay);
    symPop.sortTrees();
    
    float trueLoss = treeLoss(symPop.treeVec[0], trueIndices, datax, datay);
    
    // Gnuplot gp;

    for (int i = 0; i<maxIteration; i++){
        //reproduce, including mutation and creossover
        symPop.reproduce(nChildren, nMutation);
        //select tree
        symPop.writeLoss(indices, datax, datay);
        symPop.sortTrees();
        symPop.select();
        //update dataPop
        if (i % indicesRenewInterval == 0){
            dataPop.reproduce(nChildren, nMutation);
            dataPop.writeLoss(symPop.treeVec[0], datax, datay);
            dataPop.sortPriority();
            dataPop.select();
            indices = dataPop.priority2indices(dataPop.priorityVec[0]);
            
        }
        

        if (i % evalInterval == 0){
            trueLoss = treeLoss(symPop.treeVec[0], trueIndices, datax, datay);
            cout << "iteration: " << i << ",  ";
            cout << symPop.treeVec[0][0] << ",  " << dataPop.priorityVec[0][0] << ",  ";
            cout << trueLoss << endl;
            cout << symPop.expression(symPop.treeVec[0]) << endl;
            learnCurve << i << ",  ";
            learnCurve << symPop.treeVec[0][0] << ",  " << dataPop.priorityVec[0][0] << ",  ";
            learnCurve << trueLoss << endl;
        }

        if (i % videoInterval == 0){
            for (int i = 0; i<1000; i++){
                movieData << evaluateOnce(symPop.treeVec[0], i) << ",  ";
            }
            movieData << endl;
            
        }
        
    }
    // cout << "start loss: " << trueLoss << endl;
    // trueLoss = treeLoss(symPop.treeVec[0], trueIndices, datax, datay);
    // cout << "end loss: " << trueLoss << endl;
    


    cout << endl;
    cout << "end of program" << endl;
    learnCurve.close();
    movieData.close();
    return 0;
}