#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <math.h>
#include <fstream>

struct AnswWithActCounter {
    long double answer;
    int counter;
};
struct NumAndProb {
    double num;
    double prob;
};

struct BanchMark {
    std::string pModel = "Intel(R) Core(TM) i7-4700MQ";
    std::string task;
    std::string opType = "double";
    std::string opt = "None";
    std::vector<int> insCount;
    std::string timer = "std::chrono::high_resolution_clock::now";
    std::vector<double>time;
    std::vector<double>lNum;
    double avTime;
    std::vector<double>absError;
    std::vector<double>relError;
    std::vector<double> taskPerf;   //nanosec
    double taskPerfAv;
    double variance;
    double meanSquareDeviation;

};

AnswWithActCounter Exp(double power);

AnswWithActCounter Sin(double angle);
AnswWithActCounter Sh(double angle);

AnswWithActCounter Cos(double angle);

void runFunc(AnswWithActCounter(*mathFunc)(double angle), int expCount, std::string opName);

void SaveToCVS(BanchMark& bnchmrk);