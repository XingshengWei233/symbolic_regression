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
// print out variation
// visulizer



int main(int argc, char **argv)
{
    srand((unsigned)time(NULL)); // give different seeds for random number

    // Parameters:
    
    const int popSize = 20;
    const int nIndices = 100;
    const int nChildren = 4;
    const int nMutation = 2;
    // const int nWorker = 6;
    int maxIteration = 10000;
    int indicesRenewInterval = 100;
    float datax[1000];
    float datay[1000];
    vector<int> trueIndices(1000);
    iota(trueIndices.begin(), trueIndices.end(), 0);

    // load data:
    loadData("data/data.txt", datax, datay);

    // generate population
    TreePopulation symPop(popSize);
    DataPopulation dataPop(popSize, nIndices);
    vector<int> indices = 
            dataPop.priority2indices(dataPop.priorityVec[0]);
    symPop.writeLoss(indices, datax, datay);
    symPop.sortTrees();
    
    float trueLoss = treeLoss(symPop.treeVec[0], trueIndices, datax, datay);
    


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
        cout << "iteration: " << i << "  ";
        cout << symPop.treeVec[0][0] << "  " << dataPop.priorityVec[0][0] << endl;
        // cout << endl;
        // for (int i = 0; i < 10; i++){
        //     symPop.printTree(symPop.treeVec[i]);
        // }

        // cout << endl;
        // for (int i = 0; i < 10; i++){
        //     dataPop.printPriority(dataPop.priorityVec[i]);
        // }

        // cout << endl;
        
    }
    cout << "start loss: " << trueLoss << endl;
    trueLoss = treeLoss(symPop.treeVec[0], trueIndices, datax, datay);
    cout << "end loss: " << trueLoss << endl;
    
    // cout << "popSize: " << symPop.treeVec.size() << endl;

    
    //renew dataIndex = dataPop.dataIndex[0]

    
    // cout << "popSize: " << symPop.treeVec.size() << endl;

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

    cout << endl;
    cout << "end of program" << endl;

    return 0;
}