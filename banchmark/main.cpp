#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <vector>
#include <ctime>
#include "Auxiliary.h"


void Test() {
    std::ofstream myfile;
    myfile.open("Statistics.csv", std::ios_base::out);
    myfile.close();
    int expCount;
    std::cout << "\n Enter the number of experiments: ";
    std::cin >> expCount;
    runFunc(Sin, expCount, "Sin");
    runFunc(Cos, expCount, "Cos");
    runFunc(Exp, expCount, "Exp");
    
}

int main()
{
    srand(time(0));
    Test();
    //std::cout<<Exp(50).answer;
    //std::cout << Sin(234).answer;
    return 0;
}