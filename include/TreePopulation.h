#pragma once
#include <iostream>
#include <vector>
#include <random>
using namespace std;

class TreePopulation
{
private:
    /* data */
public:
    TreePopulation(int popSize);
    ~TreePopulation();
    const int L = 256;
    const float maxConstant = 10;
    const float probConstantNode = 0.2;
    const float probConstantLeaf = 0.8;
    int popSize;
    vector<vector<float>> treeVec; // use 0th position to store fitness
    void generate();
    void mutate(vector<float>& tree, int nMutation);
    vector<float> crossover(vector<float>& parent_0, vector<float>& parent_1);
    vector<float> generateTree();
    void writeLoss(vector<int>& dataIndex, float *datax, float *datay);
    float assignNode();
    float assignLeaf();
    string expression(vector<float>& tree);
    void printTree(vector<float>& tree);
    void sortTrees();
    void reproduce(int nChildren, int nMutation);
    void select();
    default_random_engine generator;
};

// Population::Population(int nGenome)
// {
// }

// Population::~Population()
// {
// }
