#include <iostream>
#include <cmath>//math operators
#include <cstdlib>//generate random number
#include <time.h>//generate random number
#include <string>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>    // std::sort
using namespace std;
vector<float> datax(1000);
vector<float> datay(1000);
string interpret(vector<float> newtree);
const float maxConstant = 10;
const short treeLen = 256;
//randomly return a operator, x or a constant
int assignNode() {
    short constantMax = maxConstant;
    int oprt = (rand() % 10);//decide operater, +-* / or trig
    if (oprt >= 0 && oprt < 1) {
        return -1; //generate a constant from -1 standing for x (0 children)
    }
    if (oprt >= 1 && oprt < 4) {
        return (rand() % constantMax); //generate a constant from 0 to 9 (0 children)
    }
    if (oprt >= 4 && oprt < 6) {
        return (rand() % 2) - 3; //generate a constant from -3 to -2 standing for sin, cos (1 children)
    }
    if (oprt >= 6 && oprt < 10) {
        return (rand() % 4) - 7; //generate a constant from -7 to -4 standing for plus, minus, times, devide (2 children)
    }
}

//randomly return x or a constant
int assignTerminal() {
    short constantMax = maxConstant;
    int oprt = (rand() % 4);//decide operater, constant or x
    if (oprt >= 0 && oprt < 1) {
        return -1; //generate a constant from -1 standing for x (0 children)
    }
    if (oprt >= 1 && oprt < 4) {
        return (rand() % constantMax); //generate a constant from 0 to 99 (0 children)
    }
}

//return a tree with 8 layers (length of 32)
vector<float> generateTree() {
    int nodeMaxValue = 100;
    static vector<float> tree(256);
    tree[0] = 0;
    tree[1] = assignNode();
    for (short i = 2; i < 128; i++) { //propagate the branches
        if (tree[i / 2] >= -1) {
            tree[i] = 0; //parent is constant or x, has no children
        }
        if (tree[i / 2] >= -3 && tree[i / 2] < -1 && i % 2 == 0) {
            tree[i] = assignNode(); //parent is cos or sin, has 1 children
        }
        if (tree[i / 2] >= -3 && tree[i / 2] < -1 && i % 2 == 1) {
            tree[i] = 0;
        }
        if (tree[i / 2] >= -7 && tree[i / 2] < -3) {
            tree[i] = assignNode(); //parent is + - * /, has 2 children
        }
    }
    for (short i = 128; i < 256; i++) { //propagate the branches
        if (tree[i / 2] >= -1) {
            tree[i] = 0; //parent is constant or x, has no children
        }
        if (tree[i / 2] >= -3 && tree[i / 2] < -1 && i % 2 == 0) {
            tree[i] = assignTerminal(); //parent is cos or sin, has 1 children
        }
        if (tree[i / 2] >= -3 && tree[i / 2] < -1 && i % 2 == 1) {
            tree[i] = 0;
        }
        if (tree[i / 2] >= -7 && tree[i / 2] < -3) {
            tree[i] = assignTerminal(); //parent is + - * /, has 2 children
        }
    }
    return tree;
}

vector<short> subTree(short index) {
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

//take 2 trees as input to cross over 
vector<float> crossover(vector<float> tree1, vector<float> tree2) {
    static vector<float> newTree(256);
    short loca = (rand() % 255) + 1; // location of where the mutation to occur random from 1 to 255
    //cout << "crossover: " << endl;
    int count = 0;
    //if the location of any of the trees has value of 0, change a location randomly until the location is not 0
    while (tree1[loca] == 0 || tree2[loca] == 0) {
        //loca = (rand() % 255) + 1;
        loca = loca - 1;
        //cout << count << endl;
        count++;
    }
    //cout << endl;

    bool a = (rand() % 2) == 1; // generate 0 or 1 randomly
    if (a == 1) {
        //copy the input tree1 to the newTree
        for (short i = 0; i < 256; i++) {
            newTree[i] = tree1[i];
        }

        //change the subtree to the subtree of tree2
        short i = 0;
        vector<short> subIndeces;
        subIndeces = subTree(loca);
        for (short i = 0; i < subIndeces.size(); i++) {//erase all childrens in loca's subtree
            newTree[subIndeces[i]] = tree2[subIndeces[i]];
        }
    }
    if (a == 0) {
        //copy the input tree2 to the newTree
        for (short i = 0; i < 256; i++) {
            newTree[i] = tree2[i];
        }

        //change the subtree to the subtree of tree1
        short i = 0;
        vector<short> subIndeces;
        subIndeces = subTree(loca);
        for (short i = 0; i < subIndeces.size(); i++) {//erase all childrens in loca's subtree
            newTree[subIndeces[i]] = tree1[subIndeces[i]];
        }
    }
    return newTree;
}

vector<float> mutate(vector<float> tree) {
    vector<float> newtree(tree);
    int indi = rand() % 256;
    //for (int i=0;i<256;i++){
    while (newtree[indi] == 0) {
        //indi = rand() % 256;
        indi--;
    }
    if (newtree[indi] = -1) { // when index stands for x
        newtree[indi] = assignTerminal();
    }
    if (newtree[indi] > -1) { // when index stands for constant
        float a = static_cast<float>(rand() % 110);
        if (a >= 100) {
            newtree[indi] = -1;
        }
        else{
            newtree[indi] += a/100-0.5;
        }
    }
    if (newtree[indi] == -2 || newtree[indi] == -3) { // cos
        newtree[indi] = (rand() % 2) - 3;
    }
    if (newtree[indi] >= -7 && newtree[indi] <= -4) { // +-/*
        newtree[indi] = (rand() % 4) - 7;
    }
    //}


    return newtree;
}

//evaluate tree with a x value, return a y value trough tree
float evaluate(float x, vector<float> tree) {
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

float get_se(vector<float> tree) {
    const float dataLen = 1000;
    float y[1000];
    float err[1000];
    for (int i = 0; i < dataLen; i++) { //calculate y error of each x

        y[i] = evaluate(datax[i], tree);
        err[i] = y[i] - datay[i];
    }
    float se = 0; //calculate squared error
    for (short i = 0; i < dataLen; i++) {
        se = se + err[i] * err[i];
    }
    return se;
}

string interpret(vector<float> tree) {
    string stringTree[257];
    for (short i = 0; i < 257; i++) {
        stringTree[i] = "void";
    }
    for (short i = 256; i > 0; i--) {
        if (tree[i] == -7) { //+
            stringTree[i] = "(" + stringTree[2 * i] + "+" + stringTree[2 * i + 1] + ")";
            //biTree[2 * i] = 0; biTree[2 * i + 1] = 0;
        }
        if (tree[i] == -6) { //-
            stringTree[i] = "(" + stringTree[2 * i] + "-" + stringTree[2 * i + 1] + ")";
            //biTree[2 * i] = 0; biTree[2 * i + 1] = 0;
        }
        if (tree[i] == -5) { //*
            stringTree[i] = "(" + stringTree[2 * i] + "*" + stringTree[2 * i + 1] + ")";
            //biTree[2 * i] = 0; biTree[2 * i + 1] = 0;
        }
        if (tree[i] == -4) { //divide
            stringTree[i] = "(" + stringTree[2 * i] + "/" + stringTree[2 * i + 1] + ")";
            //biTree[2 * i] = 0; biTree[2 * i + 1] = 0;
        }
        if (tree[i] == -3) { //sin
            stringTree[i] = "sin(" + stringTree[2 * i] + ")";
            //biTree[2 * i] = 0;
        }
        if (tree[i] == -2) { //cos
            stringTree[i] = "cos(" + stringTree[2 * i] + ")";
            //biTree[2 * i] = 0;
        }
        if (tree[i] == -1) { //x
            stringTree[i] = "x";
        }
        if (tree[i] > -1) {
            stringTree[i] = to_string(tree[i]);
        }
    }
    return stringTree[1];
}

int main()
{
    srand((unsigned)time(NULL));//give different seeds for random number


    ifstream infile;
    ofstream learnCurve;
    ofstream movieData;
    infile.open("data.txt");   //���ļ����������ļ��������� 
    learnCurve.open("learnCurve.txt");
    movieData.open("movieData.txt");
    //assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

    string s;
    short i = 0;
    while (getline(infile, s))
    {
        string s1 = s.substr(0, 7);
        string s2 = s.substr(8);
        float x, y;
        datax[i] = stof(s1);
        datay[i] = stof(s2);
        i++;

    }
    infile.close();          //�ر��ļ������� 
    const short dataLen = 1000;


    //generate a data set as a simple problem
    /*for (short i = 0; i < 1000; i++) {
        datax[i] = i;
    }
    for (short i = 0; i < 1000; i++) {
        datay[i] = datax[i]*cos(i);
    }*/

    //genetic

    const short nPop = 10;
    const int iteration = 10001;
    bool enableCrossover = 1;

    //generate initial population
    vector<vector<float> > population(0);
    for (short i = 0; i < nPop; i++) {
        vector<float>tree = generateTree();
        tree[0] = get_se(tree);
        population.push_back(tree);
    }
    sort(population.begin(), population.end());

    for (int k = 0; k < iteration; k++) {
        //randomly select parents
        vector<float> parent1 = population[(rand() % nPop)];
        vector<float> parent2 = population[(rand() % nPop)];
        vector<float> child;
        if (enableCrossover == 1) {
            child = crossover(parent1, parent2);
        }
        if (enableCrossover == 0) {
            child = parent1;
        }
        child = mutate(child);
        child[0] = get_se(child);

        //sort child into the population, and delete the worst tree
        if (child[0] < population[nPop - 1][0]) {
            short count = nPop - 2;
            while (population[count][0] > child[0] && count >= 0) {

                population[count + 1] = population[count];
                //cout << "iteration: " << k << ", seBest: " << population[0][0] << ", count: " << count << ", population[count][0]: " << population[count][0] << ", child[0]: " << child[0] << endl;
                count--;
                if (count < 0) {
                    break;
                }
            }
            if (count < nPop - 1) {
                population[count + 1] = child;
            }
        }


        //print parents
        /*
        cout << "parent1: " << endl;
        for (short j = 0; j < treeLen; j++) {
            cout << parent1[j] << ", ";
        }
        cout << endl;
        cout << "parent2: " << endl;
        for (short j = 0; j < treeLen; j++) {
            cout << parent2[j] << ", ";
        }
        cout << endl;
        //print child
        cout << "child: " << endl;
        for (short j = 0; j < treeLen; j++) {
            cout << child[j] << ", ";
        }
        cout << endl;*/
        if (k % 100 == 0) {
            cout << "iteration: " << k << ", seBest: " << population[0][0] << endl;
            //
        }
        learnCurve << k << ", " ;
        for (short i = 0; i < nPop; i++) {
            learnCurve << population[i][0] << ", ";
        }
        learnCurve << endl;
        float yReg[dataLen];
        if (k % 100 == 0) {
            movieData << k << ", ";
            for (short i = 0; i < dataLen; i++) {
                yReg[i] = evaluate(datax[i], population[0]);
                movieData << yReg[i] <<", ";
            }
            movieData << endl;
            //
        }
    }


    //print population
    /*
    cout << "population: " << endl;
    for (short i = 0; i < nPop; i++) {
        for (short j = 0; j < treeLen; j++) {
            cout << population[i][j] << ", ";
        }
        cout << endl;
    }*/
    //print best se
    cout << "seBest: " << population[0][0] << endl;









    //hill climber
    /*
    vector<vector<float> > population(0);
    float bestHCFitness = 100000;
    vector<float> bestTreeHC;
    for (int j = 0; j < 10; j++) {
        for (i = 0; i < 100; i++) {
            vector<float> tree = generateTree();
            //cout << "tree" << interpret(tree) << endl;
            //cout << "se" << get_se(tree) << endl;
            population.push_back(tree);
        }
        //float bestHCFitness = 100000;
        //vector<float> bestTreeHC;
        for (int count = 0; count < 100; count++) {
            if (get_se(population[count]) < bestHCFitness) {
                bestTreeHC = population[count];
                bestHCFitness = get_se(population[count]);
            }
        }
        //for (int j = 0; j<100; j++){
        vector<vector<float> > populationHC(0);
        for (int k = 0; k < 1; k++) {
            populationHC.push_back(mutate(bestTreeHC));
        }
        for (const auto& tree : populationHC) {
            if (get_se(tree) < bestHCFitness) {
                bestTreeHC = tree;
                bestHCFitness = get_se(tree);
            }
        }
    }

    cout << "HC: " << bestHCFitness << endl;
    cout << "HC expression: " << interpret(bestTreeHC) << endl;*/

    //test datax datay read 
    /*for (int i = 0; i < dataLen; i++) {
        cout << "datax: " << datax[i] << ", datay: " << datay[i] << endl;
    }*/

    //test generateTree() and get_se(tree)
    /*
    //test generateTree()
    vector<float> tree = generateTree();
    cout << "tree: " << endl;
    for (int i = 0; i < treeLen; i++) {
        cout << tree[i] << ", ";
    }
    cout << endl;
    //test get se
    cout << "se: " << get_se(tree) << endl;
    */

    //test subTree()
    /*
    vector<short> sub1 = subTree(7);
    for (short i = 0; i < sub1.size(); i++) {
        cout << sub1[i] << ", ";
    }*/

    //test crossover()
    /*
    vector<float> tree1 = generateTree();
    vector<float> tree2 = generateTree();

    cout << "tree1: " << endl;
    for (short i = 0; i < treeLen; i++) {
        cout << tree1[i] << ", ";
    }
    cout << endl;

    cout << "tree2: " << endl;
    for (short i = 0; i < treeLen; i++) {
        cout << tree2[i] << ", ";
    }
    cout << endl;

    vector<float> child = crossover(tree1, tree2);

    cout << "tree1: " << endl;
    for (short i = 0; i < treeLen; i++) {
        cout << tree1[i] << ", ";
    }
    cout << endl;

    cout << "tree2: " << endl;
    for (short i = 0; i < treeLen; i++) {
        cout << tree2[i] << ", ";
    }
    cout << endl;

    cout << "child: " << endl;
    for (short i = 0; i < treeLen; i++) {
        cout << child[i] << ", ";
    }
    cout << endl;
    */

    //test mutation()
        /*
        vector<float> tree1 = generateTree();

        cout << "tree1: " << endl;
        for (short i = 0; i < treeLen; i++) {
            cout << tree1[i] << ", ";
        }
        cout << endl;

        vector<float> child = mutate(tree1);

        cout << "tree1: " << endl;
        for (short i = 0; i < treeLen; i++) {
            cout << tree1[i] << ", ";
        }
        cout << endl;

        cout << "child: " << endl;
        for (short i = 0; i < treeLen; i++) {
            cout << child[i] << ", ";
        }
        cout << endl;*/
    learnCurve.close();
    movieData.close();
    return 0;
}

