#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "TreePopulation.h"
using namespace std;

class DataPopulation
{
private:
    /* data */
public:
    DataPopulation(int popSize, int nIndices);
    ~DataPopulation();
    const int L = 1000;
    int nIndices;
    int popSize;
    vector<vector<float>> priorityVec; // use 0th position to store fitness
    void generate();
    void mutate(vector<float> &tree, int nMutation);
    vector<float> crossover(vector<float> &parent0, vector<float> &parent1);
    vector<float> generatePriority();
    vector<int> priority2indices(vector<float> priority);
    void writeLoss(vector<float> &tree, float *datax, float *datay);
    void printPriority(vector<float> &priority);
    void sortPriority();
    void reproduce(int nChildren, int nMutation);
    void select();
    default_random_engine generator;
    // TreePopulation *ptr_treePop;
    // void addTreePop(TreePopulation *ptr_treePop);
};
