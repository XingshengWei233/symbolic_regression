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
    int loss;
    float probConstantNode;
    float probConstantLeaf;
    void generate();
    float assignNode();
    float assignLeaf();
    float evaluate(float x);
    string expression();
    void print();
};

// Genome::Genome(/* args */)
// {
// }

// Genome::~Genome()
// {
// }
