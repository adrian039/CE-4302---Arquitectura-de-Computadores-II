#include <stdio.h>
    #include <stdio.h>
    #include <iostream>
    #include <string.h>
    #include <bitset>
    #include <vector>
    #include <map>
    #include <stdlib.h>
    #include <algorithm>
    #include <cstdlib>
    #include <fstream>
    #include <sstream>

int main(){
    std::string pHex="AB1FFFF";
    unsigned int x = strtoul(pHex.c_str(), NULL, 16);
	std::cout<<x<<std::endl;
    return 0;
}