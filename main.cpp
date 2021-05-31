#include "dp.h"
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
int main()
{
    DP dp;
    Cnf c = {{1, 2,-4, 3} , {-1, 4}, {4, 5}, {-9}, {9, 11, 13}, {-11}, {-13}, {1, 2, 3, 78}, {-11, -1, 2, 5}};
    Cnf a = 
            {{1, 2}}, b = {{1, 2}, {1, -2}, {-1, 2}};
    ;
    Cnf r = {{-1}};
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

    std::cout << dp.is_satisfiable(c) << std::endl;
    std::cout << dp.is_satisfiable(a) << std::endl;
    std::cout << dp.is_satisfiable(b) << std::endl;
    std::cout << dp.is_satisfiable(r) << std::endl;


    return 1;
    dp.mv_clauses_containing_literal(c, 1, a, b);
    std::cout << c.size() << " Velicina" << std::endl;
    dp.print_Cnf(c);
    dp.print_Cnf(a);
    dp.print_Cnf(b);

    dp.cross_product(a, b, c);
    dp.print_Cnf(c);
}