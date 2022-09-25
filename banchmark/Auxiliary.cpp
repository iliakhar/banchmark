#pragma once
#include "Auxiliary.h"

//1 + 1 + 4 * power
AnswWithActCounter Exp(double power) {
    long double answ(1), powerToPower(power);
    long double prev(2),counter(1);
    int actCounter(6);
    long double fact(1);
    while (answ - prev > 0.01 or answ - prev < -0.01) {
        prev = answ;
        answ += powerToPower / fact;
        powerToPower *= power;
        counter++;
        fact *= counter;
        actCounter += 16;
    }
    return { answ , actCounter };
}

AnswWithActCounter Sin(double angle) {
    angle *= 3.1415926535 / 180;
    long double answ(0), angleToPower(angle);
    long double prev(2), powerOfNegOne(1), counter(1);
    int actCounter(10);
    long double fact(1);
    while (answ - prev > 0.001 or answ - prev < -0.001) {
        prev = answ;
        answ += (powerOfNegOne * angleToPower) / fact;
        counter += 2;
        powerOfNegOne *= -1;
        fact *= counter * (counter - 1);
        angleToPower *= angle * angle;
        actCounter += 22;
    }
    return { answ , actCounter };
}

AnswWithActCounter Sh(double angle) {
    angle *= 3.1415926535 / 180;
    long double answ(0), angleToPower(angle);
    long double prev(2), counter(1);
    int actCounter(9);
    long double fact(1);
    while (answ - prev > 0.001 or answ - prev < -0.001) {
        prev = answ;
        answ += (angleToPower) / fact;
        counter += 2;
        fact *= counter * (counter - 1);
        angleToPower *= angle * angle;
        actCounter += 20;
    }
    return { answ , actCounter };
}

AnswWithActCounter Cos(double angle) {
    angle *= 3.1415926535 / 180;
    long double answ(1), angleToPower(angle);
    long double prev(2), powerOfNegOne(-1), counter(2);
    int actCounter(12);
    long double fact(2);
    angleToPower *= angleToPower;
    while (answ - prev > 0.001 or answ - prev < -0.001) {
        prev = answ;
        answ += (powerOfNegOne * angleToPower) / fact;
        counter += 2;
        powerOfNegOne *= -1;
        fact *= counter * (counter - 1);
        angleToPower *= angle * angle;
        actCounter += 23;
    }
    return { answ , actCounter };
}

template<typename T>
void WriteVecToCVS(std::string vecName, std::vector<T>& vec, std::ofstream& myfile) {
    myfile << vecName << ";";
    for (int i(0); i < vec.size(); i++)
        myfile << vec[i] << ";";
    myfile << "\n";
}

void SaveToCVS(BanchMark& bnchmrk) {
    std::ofstream myfile;
    std::ofstream gistfile;
    myfile.open("Statistics.csv", std::ios_base::app);
    gistfile.open("banchPyth\\banchPyth\\forGist.txt", std::ios_base::app);
    myfile << "PModel;" << bnchmrk.pModel << "\n";
    myfile << "Task;" << bnchmrk.task << "\n";
    myfile << "OpType;" << bnchmrk.opType << "\n";
    myfile << "Opt;" << bnchmrk.opt << "\n";
    WriteVecToCVS("InsCount",bnchmrk.insCount, myfile);
    myfile << "Timer;" << bnchmrk.timer<< "\n";
    WriteVecToCVS("Time",bnchmrk.time, myfile);
    WriteVecToCVS("Lnum", bnchmrk.lNum, myfile);
    myfile << "AvTime;" << bnchmrk.avTime << "\n";
    WriteVecToCVS("AbsError", bnchmrk.absError, myfile);
    WriteVecToCVS("RelError", bnchmrk.relError, myfile);
    WriteVecToCVS("TaskPerf", bnchmrk.taskPerf, myfile);
    myfile << "TaskPerfAv;" << bnchmrk.taskPerfAv << "\n";
    myfile << "Variance;" << bnchmrk.variance << "\n";
    myfile << "MeanSquareDeviation;" << bnchmrk.meanSquareDeviation << "\n";
    myfile << "\n";

    gistfile << bnchmrk.task << " " << bnchmrk.taskPerfAv << "\n";

    myfile.close();
    gistfile.close();
}

void runFunc(AnswWithActCounter(*mathFunc)(double angle), int expCount, std::string opName) {
    
    /*long */double funcTime, totalTime = 0, totalInsCount = 0;
    BanchMark bnchmrk;
    bnchmrk.time.reserve(expCount);
    bnchmrk.lNum.reserve(expCount);
    bnchmrk.absError.resize(expCount);
    bnchmrk.relError.resize(expCount);
    bnchmrk.taskPerf.resize(expCount);
    bnchmrk.task = opName;
    bnchmrk.taskPerfAv = 0;
    double p = 1.0 / expCount;
    std::chrono::steady_clock::time_point startTimer, stopTimer;
    for (int i(0); i <= expCount; i++) {
        AnswWithActCounter answ;
        startTimer = std::chrono::high_resolution_clock::now();
        if(opName == "Exp")
            answ = mathFunc(rand() % 50);
        else
            answ = mathFunc(rand()%180);
        stopTimer = std::chrono::high_resolution_clock::now();
        if (i != 0) {
            
            funcTime = /*(long double)*/std::chrono::duration_cast<std::chrono::nanoseconds>(stopTimer - startTimer).count();// / 1000000000;
            bnchmrk.taskPerf[i-1] = answ.counter / funcTime;
            bnchmrk.taskPerfAv += p / bnchmrk.taskPerf[i - 1];
            bnchmrk.time.push_back(funcTime);
            bnchmrk.lNum.push_back(i-1);
            bnchmrk.insCount.push_back(answ.counter);
            totalTime += bnchmrk.time[i-1];
            totalInsCount += bnchmrk.insCount[i-1];
        }
        
       
    }
    //bnchmrk.taskPerfAv = totalInsCount / totalTime;
    bnchmrk.taskPerfAv = 1 / bnchmrk.taskPerfAv;
    double mathExpect(0), mathExpectPow2(0);
    for (int i(0); i < expCount; i++) {
        mathExpect += bnchmrk.time[i];
        mathExpectPow2 += bnchmrk.time[i] * bnchmrk.time[i];
    }
    
    mathExpect /= expCount;
    bnchmrk.avTime = mathExpect;
    mathExpectPow2 /= expCount;
    bnchmrk.variance = mathExpectPow2 - mathExpect*mathExpect;
    bnchmrk.meanSquareDeviation = sqrt(bnchmrk.variance);
    for (int i(0); i < expCount; i++) {
        bnchmrk.absError[i] = std::abs(bnchmrk.time[i] - mathExpect);
        bnchmrk.relError[i] = (bnchmrk.absError[i] / bnchmrk.time[i]) * 100;
    }
    SaveToCVS(bnchmrk);
}