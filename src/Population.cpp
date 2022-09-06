#include "Population.h"
#include <iostream>
using namespace std;

Population::Population(int popSize){
    this->popSize = popSize;
    this->genomeVec.reserve(this->popSize);
    generate();
}


Population::~Population(){

}

void Population::generate(){
    for (int i = 0; i < this->popSize; i++){
        Genome geno;
        this->genomeVec.push_back(geno);
    }
}

void Population::mutate(Genome& genome){

}

void Population::crossover(Genome& ptr_genome0, Genome& ptr_genome1){

}

void Population::insertSelect(){

}