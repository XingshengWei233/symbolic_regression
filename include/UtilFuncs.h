#pragma once
#include <iostream>
#include <vector>
using namespace std;


float evaluateOnce(vector<float>& tree, float x);
float treeLoss(vector<float>& tree, 
        vector<int>& dataIndices, float *datax, float *datay);
void loadData(string loadDir, float *datax, float *datay);