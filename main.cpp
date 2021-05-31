#include "dp.h"
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>



int main() 
{
    std::string s;
    std::cin >> s;

    std::fstream f(s);

    Cnf formula;    
    DP dp;
    f >> formula;
    std::cout << dp.is_satisfiable(formula) << std::endl;
}