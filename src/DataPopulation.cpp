#include "DataPopulation.h"
#include "UtilFuncs.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <string>
#include <queue>

using namespace std;

// TODO:
// seperate loss calculation to another class maybe

DataPopulation::DataPopulation(int popSize, int nIndices)
{
    this->popSize = popSize;
    this->nIndices = nIndices;
    this->priorityVec.reserve(this->popSize);
    generate();
}

DataPopulation::~DataPopulation()
{
}

// void DataPopulation::addTreePop(TreePopulation *ptr_treePop)
// {
//     this->ptr_treePop = ptr_treePop;
// }

vector<float> DataPopulation::generatePriority()
{
    // first element reserved for loss
    vector<float> priority(this->L + 1);
    priority[0] = 0;
    for (int i = 1; i < this->L + 1; i++)
    {
        priority[i] = rand() / static_cast<float>(RAND_MAX);
    }
    return priority;
}

void DataPopulation::generate()
{
    for (int i = 0; i < this->popSize; i++)
    {
        vector<float> priority = generatePriority();
        this->priorityVec.push_back(priority);
    }
}

vector<int> DataPopulation::priority2indices(vector<float> priority)
{
    vector<int> indices(this->nIndices);
    for (int i = 0; i < this->nIndices; i++)
    {
        vector<float>::iterator max = max_element(priority.begin() + 1, priority.end());
        int arg_max = distance(priority.begin(), max);
        indices[i] = arg_max;
        priority[arg_max] = -1e99;
    }

    return indices;
}

void DataPopulation::reproduce(int nChildren, int nMutation)
{
    // select parent can be improved by priority distribution
    for (int i = 0; i < nChildren; i++)
    {
        vector<float> &parent_0 = this->priorityVec[rand() % this->popSize];
        vector<float> &parent_1 = this->priorityVec[rand() % this->popSize];

        cout << "parent_0:" << endl;
        // printTree(parent_0);
        cout << "parent_1:" << endl;
        // printTree(parent_1);

        vector<float> newTree = crossover(parent_0, parent_1);

        cout << "child:" << endl;
        // printTree(newTree);

        mutate(newTree, nMutation);

        cout << "mutated_child:" << endl;
        // printTree(newTree);

        this->priorityVec.push_back(newTree);
    }
}

void DataPopulation::mutate(vector<float> &priority, int nMutation)
{
    for (int i = 0; i < nMutation; i++)
    {
        int mutateIndex = rand() % this->L;
        normal_distribution<float> distribution(0, 0.1);
        float increment = distribution(this->generator);
        priority[mutateIndex] += increment;
    }
}

vector<float> DataPopulation::crossover(vector<float> &parent0, vector<float> &parent1)
{
    // swap parent_0 and parent_1 by 50% chance
    if (rand() % 2 == 0)
    {
        swap(parent0, parent1);
    }
    int crossBegin = rand() % this->L;
    int crossEnd = rand() % this->L;
    if (crossBegin > crossEnd)
    {
        swap(crossBegin, crossEnd);
    }
    // copy to new priority
    vector<float> newPriority(this->nIndices);
    for (int i = 0; i < this->L; i++)
    {
        if (i >= crossBegin && i < crossEnd)
        {
            newPriority[i] = parent1[i];
        }
        else
        {
            newPriority[i] = parent0[i];
        }
    }

    return newPriority;
}

void DataPopulation::select()
{
    while (this->priorityVec.size() > this->popSize)
    {
        cout << "poped" << endl;
        this->priorityVec.pop_back();
    }
}


void DataPopulation::printPriority(vector<float> &priority)
{
    vector<int> indices = priority2indices(priority);
    cout << "indices: " << endl;
    for (int i = 1; i < this->nIndices; i++)
    {
        cout << indices[i] << " ";
    }
    cout << endl
         << "loss: " << priority[0] << endl;
    cout << "priority: " << endl;
    for (int i = 1; i < this->L; i++)
    {
        cout << priority[i] << " ";
    }
    cout << endl;
}

void DataPopulation::writeLoss(vector<int> &dataIndex, float *datax, float *datay){
    for (int i = 0; i < this->priorityVec.size(); i++){
        this->priorityVec[i][0] = treeLoss(this->priorityVec[i], dataIndex, datax, datay);
    }
}