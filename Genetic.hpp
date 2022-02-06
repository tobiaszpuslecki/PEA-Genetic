#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <random>

using namespace std;

class Genetic
{
private:
    int dimension;
    int bestLength = INT_MAX;
    int stopCriteria;
    double executionTime;
    double foundInTime = 0.0;
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;
    vector<vector<int> > matrix;
    vector<int> bestPath;
    vector<int> currentPath;

    int iterations; // liczba iteracji
    int populationSize; // rozmiar populacji
    double crossFactor; // współczynnik krzyżowania
    double mutationFactor; // współczynnik mutacji
    int swapsInMutation; // ilość zamian w mutacji
    int crossMethodVariant; //metoda krzyżowania
    int mutationMethodVariant; //metoda mutacji

    
    vector<vector<int> > parents;
    vector<vector<int> > children;
    vector<vector<int> > population;
    
    void generatePopulation();
    vector<int> generateRandomPermutation();
    void chooseParents();
    double getRandomDouble();
    int calculateMaxCompletionTime(vector<int> v);
    void cross(int crossMethodVariant);
    void mutate(vector<int>& child);
    void generateNewPopulation();

    int alghoritm();

public:
    Genetic();
    Genetic(const vector<vector<int> >& matrix_);
    int calculate(int stopCriteria_, int populationSize_, double mutationFactor_, double crossFactor_, int crossMethodVariant_, int mutationMethodVariant_);
    double getExecutionTime();
};
