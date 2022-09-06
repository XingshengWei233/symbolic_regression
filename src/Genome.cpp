#include "Genome.h"
#include <iostream>
#include <random>
#include <string>
using namespace std;
// -1:  x
// -2: cos
// -3: sin
// -4: /
// -5: *
// -6: -
// -7: +

Genome::Genome()
{
    this->nodes.reserve(this->L);
    this->probConstantNode = 0.2;
    this->probConstantLeaf = 0.8;
    generate();
}

Genome::~Genome()
{
}

float Genome::assignNode()
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

float Genome::assignLeaf()
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

void Genome::generate()
{
    for (int i = 0; i < this->L / 2; i++)
    {
        this->nodes[i] = assignNode();
    }
    for (int i = this->L / 2; i < this->L; i++)
    {
        this->nodes[i] = assignLeaf();
    }
    // this->loss
}

void Genome::print()
{
    cout << "loss:" << this->loss << " rank:" << this->rank << endl;
    cout << "nodes:" << endl;
    for (int i = 0; i < this->L; i++)
    {
        cout << this->nodes[i] << " ";
    }
    cout << endl;
}

float Genome::evaluate(float x)
{ // change to a buffer tree
    vector<float> newTree(this->L);
    for (int i = 0; i < this->L; i++)
    {
        newTree[i] = this->nodes[i];
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

string Genome::expression()
{
    string stringTree[256];
    for (short i = 255; i > 0; i--)
    {
        if (this->nodes[i] == -7)
        { //+
            stringTree[i] = "(" + stringTree[2 * i] + " + " + stringTree[2 * i + 1] + ")";
            ;
        }
        if (this->nodes[i] == -6)
        { //-
            stringTree[i] = "(" + stringTree[2 * i] + " - " + stringTree[2 * i + 1] + ")";
        }
        if (this->nodes[i] == -5)
        { //*
            stringTree[i] = "(" + stringTree[2 * i] + " * " + stringTree[2 * i + 1] + ")";
        }
        if (this->nodes[i] == -4)
        { // divide
            stringTree[i] = "(" + stringTree[2 * i] + " / " + stringTree[2 * i + 1] + ")";
        }
        if (this->nodes[i] == -3)
        { // sin
            stringTree[i] = "sin(" + stringTree[2 * i] + ")";
        }
        if (this->nodes[i] == -2)
        { // cos
            stringTree[i] = "cos(" + stringTree[2 * i] + ")";
        }
        if (this->nodes[i] == -1)
        { // x
            stringTree[i] = "x";
        }
        if (this->nodes[i] > -1)
        {
            float num = this->nodes[i];
            string strNum = to_string(num);
            strNum = strNum.substr(0, strNum.size() - 4);
            stringTree[i] = strNum;
        }
    }
    return stringTree[1];
}