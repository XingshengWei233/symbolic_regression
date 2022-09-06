#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Genome
{
    // A 8 layer heap that saves symbols and constants
private:
    /* data */
public:
    Genome();
    ~Genome();
    const int L = 256;
    const float maxConstant = 10;
    // int nodes[256];
    vector<float> nodes;
    int rank;
    int val;
    void generate();
    float assignNode();
    float assignLeaf();
    float evaluation();
};

// Genome::Genome(/* args */)
// {
// }

// Genome::~Genome()
// {
// }
