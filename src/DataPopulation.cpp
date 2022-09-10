#include "DataPopulation.h"
#include <iostream>
#include <algorithm> 
#include <vector>
#include <random>
#include <string>
#include <queue>

using namespace std;

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


vector<float> DataPopulation::generatePriority()
{
    vector<float> priority(this->L);
    for (int i = 0; i < this->L; i++)
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

vector<int> DataPopulation::priority2indices(vector<float> priority){
    vector<int> indices;
    vector<float>::iterator max = max_element(priority.begin(), priority.end());
    int arg_max = distance(max, priority.begin());
    return indices;
}

void DataPopulation::mutate(vector<float>& tree, int nMutation);


vector<float> DataPopulation::crossover(vector<float>& parent_0, vector<float>& parent_1);

float evaluateOnce(vector<float>& tree, float x);