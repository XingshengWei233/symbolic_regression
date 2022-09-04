#pragma once
#include <iostream>
using namespace std;

class Genome
{
    // A 8 layer heap that saves symbols and constants
private:
    /* data */
public:
    Genome(/* args */);
    ~Genome();
    int nodes[256];
    void evaluation();
};

Genome::Genome(/* args */)
{
}

Genome::~Genome()
{
}
