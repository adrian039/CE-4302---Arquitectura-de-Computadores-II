#include <string>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <functional>
#include <bitset>
#include <sstream>
#include <pthread.h>
#include "config.h"

int main(){
    std::bitset<24> b;
            b = (std::bitset<24>)21072;
            std::string instruction = b.to_string();
    std::string data="10111";
    std::istringstream buffer(data);
    int value;
    buffer >> value;
    int result = 0;
    int m = 1;
    int datA = 0, datB = 0;
    for (int i = 0; value > 0; i++)
    {
        if (value % 10 == 1)
        {
            result += m;
        }
        value /= 10;
        m <<= 1;
    }
    std::cout<<instruction<<std::endl;
    return result;
    // freopen(instFile, "rb", stdin);
    // std::string line;
    // while (getline(std::cin, line))
    // {
    //     std::cout << line << std::endl;
    // }
}