#include "instTool.h"

using namespace std;
InstTool::InstTool(InstMem *instMem_)
{
    cout<<"perra"<<endl;
    freopen(instFile, "rb", stdin);
   string line;
   while(getline(cin, line))
       cout << line << endl;
}