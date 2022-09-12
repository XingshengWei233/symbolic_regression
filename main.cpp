#include "TreePopulation.h"
#include "DataPopulation.h"
#include "UtilFuncs.h"
#include <iostream>
#include <cmath>   //math operators
#include <cstdlib> //generate random number
#include <time.h>  //generate random number
#include <string>

#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
 
//TODO:
// debug main algorithm
// visulizer
// move load data to util funcs



int main(int argc, char **argv)
{
    srand((unsigned)time(NULL)); // give different seeds for random number

    // Parameters:
    
    const int popSize = 10;
    const int nIndices = 50;
    const int nChildren = 5;
    const int nMutation = 2;
    const int nWorker = 6;
    int iteration = 0;
    int maxIteration = 100;
    int indicesRenewInterval = 10;
    float datax[1000];
    float datay[1000];
    // load data:
    loadData("data/data.txt", datax, datay);

    // generate population
    TreePopulation symPop(popSize);
    DataPopulation dataPop(popSize, nIndices);
    vector<int> indices = 
            dataPop.priority2indices(dataPop.priorityVec[0]);
    symPop.writeLoss(indices, datax, datay);
    symPop.sortTrees();
    
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
        cout << endl;
        for (int i = 0; i < 10; i++){
            symPop.printTree(symPop.treeVec[i]);
        }
        cout << endl;
        for (int i = 0; i < 10; i++){
            dataPop.printPriority(dataPop.priorityVec[i]);
        }
    }
    // for (int i = 0; i < 10; i++){
    //     dataPop.printPriority(dataPop.priorityVec[i]);
    // }
    

    
    cout << "popSize: " << symPop.treeVec.size() << endl;

    
    //renew dataIndex = dataPop.dataIndex[0]

    
    cout << "popSize: " << symPop.treeVec.size() << endl;

    //if iteration % 100 ==0
    //dataPop.reproduce();
    //dataPop.writeAllLoss();
    //dataPop.sortPriorities();
    //dataPop.select();

    // for (int i = 0; i < 1000; i++)
    // {
    //     cout << "x: " << datax[i] << " y: " << symPop.evaluateOnce(symPop.treeVec[0], datax[i]) << endl;
    // }
    // cout << "expression: " << symPop.expression(0) << endl;

    
    cout << "end of program" << endl;

    return 0;
}