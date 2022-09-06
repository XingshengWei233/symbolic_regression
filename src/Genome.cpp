#include "Genome.h"
#include <iostream>
#include <random>
using namespace std;



Genome::Genome(){
    
}


Genome::~Genome(){

}

void Genome::generate(){
    for (int i = 0; i < this->L / 2; i++){
        this->nodes[i] = assignNode();
    }
    for (int i = this->L / 2; i < this->L; i++){
        this->nodes[i] = assignLeaf();
    }
    
}

float Genome::assignNode(){
    int maxConstant = this->maxConstant;
    int oprt = (rand() % 10);//decide operater, +-* / or trig
    if (oprt >= 0 && oprt < 1) {
        return -1; //generate a constant from -1 standing for x (0 children)
    }
    if (oprt >= 1 && oprt < 4) {
        return (rand() % maxConstant); //generate a constant from 0 to 9 (0 children)
    }
    if (oprt >= 4 && oprt < 6) {
        return (rand() % 2) - 3; //generate a constant from -3 to -2 standing for sin, cos (1 children)
    }
    if (oprt >= 6 && oprt < 10) {
        return (rand() % 4) - 7; //generate a constant from -7 to -4 standing for plus, minus, times, devide (2 children)
    }
}

float Genome::assignLeaf(){
    float r = rand() / static_cast<float>(RAND_MAX);
    int maxConstant = this->maxConstant;
    if (r < 0.2) {
        return -1; //generate a constant from -1 standing for x (0 children)
    }
    if (r >= 0.2) {
        return (rand() % maxConstant); //generate a constant from 0 to 99 (0 children)
    }
}

vector<short> subTree(short index) {
    // return a list of subtree index
    vector<short> arr(2);
    arr[0] = 0;
    arr[1] = index;
    for (short n = 2; n <= 8; n++) {
        for (short i = pow(2, n - 1); i <= pow(2, n) - 1; i++) {

            short arri = ((index - 1) * pow(2, n - 1) + i);
            if (arri > 255) {
                break;
            }
            arr.push_back(arri);
        }
    }
    return arr;
}

float Genome::evaluation(float x, vector<float> tree){
    vector<float> biTree(256);
    for (short i = 0; i < 256; i++) {
        biTree[i] = tree[i];
    }
    for (short i = 128; i > 0; i--) {
        if (biTree[i] == -7) {
            biTree[i] = biTree[2 * i] + biTree[2 * i + 1];
            biTree[2 * i] = 0; biTree[2 * i + 1] = 0;
        }
        if (biTree[i] == -6) {
            biTree[i] = biTree[2 * i] - biTree[2 * i + 1];
            biTree[2 * i] = 0; biTree[2 * i + 1] = 0;
        }
        if (biTree[i] == -5) {
            biTree[i] = biTree[2 * i] * biTree[2 * i + 1];
            biTree[2 * i] = 0; biTree[2 * i + 1] = 0;
        }
        if (biTree[i] == -4) {
            if (biTree[2 * i + 1] == 0) {
                biTree[2 * i + 1] = 1;
            }
            biTree[i] = biTree[2 * i] / biTree[2 * i + 1];
            biTree[2 * i] = 0; biTree[2 * i + 1] = 0;
        }
        if (biTree[i] == -3) {
            biTree[i] = sin(biTree[2 * i]);
            biTree[2 * i] = 0;
        }
        if (biTree[i] == -2) {
            biTree[i] = cos(biTree[2 * i]);
            biTree[2 * i] = 0;
        }
        if (biTree[i] == -1) {
            biTree[i] = x;
        }
    }
    return biTree[1];
}