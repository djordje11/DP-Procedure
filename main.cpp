#include "dp.h"
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
int main()
{
    DP dp;
    Cnf c = {{1, 2,-4, 3} , {-1, 4}, {4, 5}, {-9}, {9, 11, 13}, {-11}, {-13}, {1, 2, 3, 78}, {-11, -1, 2, 5}};
    Cnf a, b;
    std::cout << dp.find_literal_in_unit_clause(c) << std::endl;


 //   std::set<int> mapa;
//
 //   dp.second_rule(c);
 //   std::cout << "novi: " << std::endl;
 //   std::for_each(c.begin(), c.end(), [](auto it ){
 //       std::for_each(it.begin(), it.end(), [](auto jt){
 //           std::cout << jt << " " ;
 //       });
 //       std::cout << std::endl;
 //   });
 //   
    dp.mv_clauses_containing_literal(c, 1, a, b);
    dp.print_Cnf(c);
    dp.print_Cnf(a);
    dp.print_Cnf(b);

}