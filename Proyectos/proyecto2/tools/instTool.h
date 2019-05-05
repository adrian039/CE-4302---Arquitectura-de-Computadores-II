
#ifndef INSTTOOL_H
#define INSTTOOL_H

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include "../instMem.h"
#include "../config.h"

class InstTool
{
  public:
    InstTool(InstMem *instMem_);
};

#endif