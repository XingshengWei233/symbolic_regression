#pragma once
#include <iostream>
#include <vector>
#include <random>
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
    void mutate(vector<float>& tree, int nMutation);
    vector<float> crossover(vector<float>& parent_0, vector<float>& parent_1);
    void insertSelect();
    vector<float> generatePriority();
    vector<int> priority2indices(vector<float> priority);
    void writeAllLoss(vector<int>& dataIndex, float *datax, float *datay);
    void writeTreeLoss(vector<float>& tree, 
        vector<int>& dataIndex, float *datax, float *datay);
    float assignNode();
    float assignLeaf();
    float evaluateOnce(vector<float>& tree, float x);
    string expression(vector<float>& tree);
    void printTree(vector<float>& tree);
    void sortTrees();
    void reproduce(int nChildren, int nMutation);
    void select();
    default_random_engine generator;
};
