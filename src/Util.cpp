#include "Util.h"
#include "Mask.h"
#include <iostream>
#include <vector>
#include <cmath>
using std::vector;
using std::pow;
using std::exp;
bool hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}
