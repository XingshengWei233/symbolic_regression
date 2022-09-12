#include <iostream>
#include <vector>
#include <cmath>
using namespace std;



float evaluateOnce(vector<float>& tree, float x){
    int L = tree.size();
    vector<float> newTree(L);
    for (int i = 0; i < L; i++)
    {
        newTree[i] = tree[i];
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

float treeLoss(vector<float>& tree, 
        vector<int>& dataIndices, float *datax, float *datay){
    float sum = 0;
    for (int i = 0; i < dataIndices.size(); i++){
        float yPred = evaluateOnce(tree, datax[dataIndices[i]]);
        float squareLoss = pow((datay[dataIndices[i]] - yPred), 2);
        sum += squareLoss;
    }
    return sum / dataIndices.size();
}