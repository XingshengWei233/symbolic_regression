#include "TreePopulation.h"
#include <iostream>
#include <algorithm> 
#include <random>
#include <string>
#include <queue>
using namespace std;

TreePopulation::TreePopulation(int popSize)
{
    this->popSize = popSize;
    this->treeVec.reserve(this->popSize);
    generate();
}

TreePopulation::~TreePopulation()
{
}

void TreePopulation::generate()
{
    for (int i = 0; i < this->popSize; i++)
    {
        vector<float> tree = generateTree();
        this->treeVec.push_back(tree);
    }
    
}

vector<float> TreePopulation::generateTree()
{   
    vector<float> tree(256);
    tree[0] = 0;
    for (int i = 1; i < this->L / 2; i++)
    {
        tree[i] = assignNode();
    }
    for (int i = this->L / 2; i < this->L; i++)
    {
        tree[i] = assignLeaf();
    }
    return tree;
}


void TreePopulation::reproduce(int nChildren, int nMutation){
    // select parent can be improved by priority distribution
    for (int i=0; i < nChildren; i++){
        vector<float>& parent_0 = this->treeVec[rand() % this->popSize];
        vector<float>& parent_1 = this->treeVec[rand() % this->popSize];

        cout<< "parent_0:" << endl;
        printTree(parent_0);
        cout<< "parent_1:" << endl;
        printTree(parent_1);

        vector<float> newTree = crossover(parent_0, parent_1);

        cout<< "child:" << endl;
        printTree(newTree);

        mutate(newTree, nMutation);

        cout<< "mutated_child:" << endl;
        printTree(newTree);

        this->treeVec.push_back(newTree);
    }
}



void TreePopulation::mutate(vector<float>& tree, int nMutation)
{
    for (int i=0; i < nMutation; i++){
        int mutateIndex = rand() % this->L;
        if (tree[mutateIndex] < 0){
            if (mutateIndex < this->L / 2){
                tree[mutateIndex] = assignNode();
            }
            else{
                tree[mutateIndex] = assignLeaf();
            }
        }
        else{
            normal_distribution<float> distribution(0, 0.5);
            float increment = distribution(this->generator);
            tree[mutateIndex] += increment;
        }
    }

}

vector<float> TreePopulation::crossover(vector<float>& parent0, vector<float>& parent1)
{   
    // swap parent_0 and parent_1 by 50% chance
    if (rand() % 2 == 0){
        swap(parent0, parent1);
    }
    //copy parent_0 to new tree
    vector<float> newTree(this->L);
    for (int i = 0; i < this->L; i++)
    {
        newTree[i] = parent0[i];
    }
    //select a subtree root
    int subTreeRoot = rand() % this->L;
    cout << "subTreeRoot:" << subTreeRoot << endl;
    //use bfs to traverse subtree to replace with parent_1
    queue<int> bfsQueue;
    bfsQueue.push(subTreeRoot);
    while (bfsQueue.empty() == false){
        int i = bfsQueue.front();
        bfsQueue.pop();
        newTree[i] = parent1[i];
        if (i * 2 < this->L){
            bfsQueue.push(i * 2);
        }
        if (i * 2 + 1 < this->L){
            bfsQueue.push(i * 2 + 1);
        }
    }
    return newTree;
}


void TreePopulation::select()
{
    while (this->treeVec.size() > this->popSize){
        cout << "poped" << endl;
        this->treeVec.pop_back();
    }
}

float TreePopulation::assignNode()
{ // with possibel sub-nodes
    float r = rand() / static_cast<float>(RAND_MAX);
    int maxConstant = this->maxConstant;
    if (r < this->probConstantNode)
    {   
        return (rand() % maxConstant); // generate a constant from -1 standing for x (0 children)
    }
    else
    {   
        return (rand() % 7) - 7; // generate a constant from 0 to 99 (0 children)
    }
}

float TreePopulation::assignLeaf()
{ // without possible sub_nodes
    float r = rand() / static_cast<float>(RAND_MAX);
    int maxConstant = this->maxConstant;
    if (r < probConstantLeaf)
    {
        return (rand() % maxConstant); // generate a constant from -1 standing for x (0 children)
    }
    else
    {
        return -1; // generate a constant from 0 to 99 (0 children)
    }
}



void TreePopulation::printTree(vector<float>& tree)
{
    cout << "expression: " << expression(tree) << endl;
    cout << "score: " << tree[0] << endl << " tree: ";
    for (int i = 1; i < this->L; i++)
    {
        cout << tree[i] << " ";
    }
    cout << endl;
}

void TreePopulation::writeAllLoss(vector<int>& dataIndex, float *datax, float *datay){
    for (int i = 0; i < this->treeVec.size(); i++){
        writeTreeLoss(this->treeVec[i], dataIndex, datax, datay);
    }
}

void TreePopulation::writeTreeLoss(vector<float>& tree, 
    vector<int>& dataIndex, float *datax, float *datay){
    //write Mean square loss to the 0th index of tree
    float sum = 0;
    for (int i = 0; i < dataIndex.size(); i++){
        float yPred = evaluateOnce(tree, datax[dataIndex[i]]);
        float squareLoss = pow((datay[dataIndex[i]] - yPred), 2);
        sum += squareLoss;
    }
    tree[0] = sum / dataIndex.size();
}

float TreePopulation::evaluateOnce(vector<float>& tree, float x)
{ 
    vector<float> newTree(this->L);
    for (int i = 0; i < this->L; i++)
    {
        newTree[i] = tree[i];
    }
    for (int i = 127; i > 0; i--)
    {
        if (newTree[i] == -7)
        {
            newTree[i] = newTree[2 * i] + newTree[2 * i + 1];
        }
        if (newTree[i] == -6)
        {
            newTree[i] = newTree[2 * i] - newTree[2 * i + 1];
        }
        if (newTree[i] == -5)
        {
            newTree[i] = newTree[2 * i] * newTree[2 * i + 1];
        }
        if (newTree[i] == -4)
        {
            if (newTree[2 * i + 1] == 0)
            {
                newTree[2 * i + 1] = 1;
            }
            newTree[i] = newTree[2 * i] / newTree[2 * i + 1];
        }
        if (newTree[i] == -3)
        {
            newTree[i] = sin(newTree[2 * i]);
        }
        if (newTree[i] == -2)
        {
            newTree[i] = cos(newTree[2 * i]);
        }
        if (newTree[i] == -1)
        {
            newTree[i] = x;
        }
    }
    return newTree[1];
}

void TreePopulation::sortTrees(){
    sort(this->treeVec.begin(), this->treeVec.end());
}
string TreePopulation::expression(vector<float>& tree)
{
    string stringTree[256];
    for (short i = 255; i > 0; i--)
    {
        if (tree[i] == -7)
        { //+
            stringTree[i] = "(" + stringTree[2 * i] + " + " + stringTree[2 * i + 1] + ")";
            ;
        }
        if (tree[i] == -6)
        { //-
            stringTree[i] = "(" + stringTree[2 * i] + " - " + stringTree[2 * i + 1] + ")";
        }
        if (tree[i] == -5)
        { //*
            stringTree[i] = "(" + stringTree[2 * i] + " * " + stringTree[2 * i + 1] + ")";
        }
        if (tree[i] == -4)
        { // divide
            stringTree[i] = "(" + stringTree[2 * i] + " / " + stringTree[2 * i + 1] + ")";
        }
        if (tree[i] == -3)
        { // sin
            stringTree[i] = "sin(" + stringTree[2 * i] + ")";
        }
        if (tree[i] == -2)
        { // cos
            stringTree[i] = "cos(" + stringTree[2 * i] + ")";
        }
        if (tree[i] == -1)
        { // x
            stringTree[i] = "x";
        }
        if (tree[i] > -1)
        {
            float num = tree[i];
            string strNum = to_string(num);
            strNum = strNum.substr(0, strNum.size() - 4);
            stringTree[i] = strNum;
        }
    }
    return stringTree[1];
}