#pragma once
#include <iostream>
#include "Genome.h"
using namespace std;

class Population
{
private:
    /* data */
public:
    Population(int nGenome);
    ~Population();
    void mutate(Genome *ptr_genome);
    void crossover(Genome *ptr_genome0, Genome *ptr_genome1);
    void insertSelect();
};

Population::Population(int nGenome)
{
}

Population::~Population()
{
}
