#ifndef __DP_H__
#define __DP_H__

#include <set>
#include <vector>
using Clause = std::set<int>;
using Cnf = std::vector<Clause>;

class DP 
{
   public:
   /**
    * @brief find unit clause and apply first rule
    * @return true if first rule was applied
    */ 
   bool first_rule(Cnf& F);

   bool second_rule(Cnf& F);

   void third_rule(Cnf& F);
   /**
    * @brief search for unit clause
    * @return literal in unit clause <0 if ~p
    */
   int find_literal_in_unit_clause(Cnf& F);

   unsigned remove_literal_from_all_clauses(Cnf& F, int p);

   unsigned remove_clauses_contain_literal(Cnf& F, int p);

   void collect_pure_literal(Cnf& F, std::set<int>& );
   
   int get_random_literal(Cnf& F);

   void mv_clauses_containing_literal(Cnf& F, int p, Cnf& F_pos, Cnf& F_neg);

   void clause_union(Clause& a, Clause& b, Clause& c);

   void cross_product(Cnf& a, Cnf&b, Cnf& c);

   bool have_empty_clause(Cnf& c);

   bool is_clause_empty(Cnf& c);
public:
   DP();

   /**
    * @brief Use DP procedure to check
    * if formula F is satisfiably
    */
   void print_Cnf(const Cnf& F);
   bool is_satisfiable(const Cnf& F); 
};
#endif // __DP_H__