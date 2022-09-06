#pragma once
#include <iostream>
#include <vector>
#include "Genome.h"
using namespace std;

class Population
{
private:
    /* data */
public:
    Population(int popSize);
    ~Population();
    int popSize;
    void mutate(Genome *ptr_genome);
    void crossover(Genome *ptr_genome0, Genome *ptr_genome1);
    void insertSelect();
    vector<Genome> genomeVec;
};

// Population::Population(int nGenome)
// {
// }

// Population::~Population()
// {
// }
