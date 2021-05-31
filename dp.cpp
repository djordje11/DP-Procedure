#include "dp.h"
#include <algorithm>
#include <cmath>
#include <iostream>
DP::DP() 
{
}

void DP::print_Cnf(const Cnf& F) 
{
    std::cout << "********************************" << std::endl;
    std::for_each(F.begin(), F.end(), [](auto it ){
        std::for_each(it.begin(), it.end(), [](auto jt){
            std::cout << jt << " " ;
        });
        std::cout << std::endl;
    });
    std::cout << "********************************" << std::endl;
}

int DP::find_literal_in_unit_clause(Cnf& F) 
{
    auto it = std::find_if(F.cbegin(), F.cend(), 
        [](auto C){
            return C.size() == 1;
        }
    );
    return it == F.cend() ? 0 : *(it->begin()) ; 
}


unsigned DP::remove_literal_from_all_clauses(Cnf& F, int p) 
{
    unsigned n = 0;

    for(auto it = F.begin(); it != F.end(); ++it)
    {
        auto jt = it->find(p);
        if(jt != it->end())
        {
            it->erase(jt);
            ++n;
        }
    }
    return n;
}

unsigned DP::remove_clauses_contain_literal(Cnf& F, int p) 
{
    unsigned n = 0;
    for(auto it = F.begin(); it != F.end(); ) 
    {
        auto jt = it->find(p);
        if(jt != it->end())
        {
            it = F.erase(it); 
            n++;
        }
        else 
            ++it;
    }
    return n;
}

bool DP::first_rule(Cnf& F) 
{
    int p = find_literal_in_unit_clause(F);

    if(p == 0)
        return false;

    remove_literal_from_all_clauses(F, -p);

    remove_clauses_contain_literal(F, p);

    return true;
}

void DP::collect_pure_literal(Cnf& F, std::set<int>& pures) 
{
    std::set<int> not_pures;

  //  pures.empty(); 

    for(auto it = F.begin(); it != F.end(); ++it)
    {
        for(auto jt = it->begin(); jt != it->end(); ++jt)
        {
            int el_abs = std::abs(*jt);
            if(not_pures.count(el_abs))
                continue;

            int el = *jt * -1;
            if(pures.count(el))
            {
                pures.erase(el);
                not_pures.insert(el_abs);
                continue;
            }
            else
                pures.insert(el*-1);
        }
    }
}

bool DP::second_rule(Cnf& F) 
{
    std::set<int> pures;

    collect_pure_literal(F, pures);

    if(!pures.size())
        return false;
    std::for_each(pures.cbegin(), pures.cend(), [this,&F](auto it){
        remove_clauses_contain_literal(F, it);
    });

    return true;
}

int DP::get_random_literal(Cnf& F) 
{
    auto it = F.begin();
    while(it != F.end())
    {
        if(it->size())
            return *it->begin();
        ++it;
    }
    return 0;
}

void DP::mv_clauses_containing_literal(Cnf& F, int p, Cnf& F_pos, Cnf& F_neg) 
{
   // F_pos.clear();
  //  F_neg.clear();
    for(auto it = F.begin(); it != F.end(); )
    {
        auto jt = it->find(p);
        auto zt = it->find(-1 * p);

        if(jt != it->end() && zt != it->end())
        {
            it = F.erase(it);
            continue;
        }
        if(jt != it->end())
        {
            it->erase(jt);
            F_pos.push_back(std::move(*it));
            it = F.erase(it);
            continue;
        }
        if(zt != it->end())
        {
            it->erase(zt); 
            F_neg.push_back(std::move(*it));
            it = F.erase(it);
            continue;
        }
        ++it;
    }
}

void DP::clause_union(Clause& a, Clause& b, Clause& c) 
{
    std::for_each(b.begin(), b.end(), [&c](auto it) {
        c.insert(it);
    });
    std::for_each(a.begin(), a.end(), [&c](auto it) {
        c.insert(it);
    });
}

void DP::cross_product(Cnf& a, Cnf&b, Cnf& c) 
{
    for(auto it = a.begin(); it != a.end(); ++it)
    {
       for(auto jt = b.begin(); jt != b.end(); ++jt)
       {
           Clause cl;
           clause_union(*it, *jt, cl);
           c.push_back(std::move(cl));
       } 
    }

}

void DP::third_rule(Cnf& F) 
{
    int rand_literal = get_random_literal(F); 
    Cnf F_pos, F_neg;
    mv_clauses_containing_literal(F, rand_literal, F_pos, F_neg);
    cross_product(F_pos, F_neg, F);
}

bool DP::have_empty_clause(Cnf& c) 
{
    return std::any_of(c.begin(), c.end(), [](auto it) { return it.size() == 0;});
}

bool DP::is_clause_empty(Cnf& c) 
{
    return c.size() == 0;
}


bool DP::is_satisfiable(const Cnf& F) 
{
    Cnf formula = F;

    while(1) 
    {
        if(have_empty_clause(formula))
            return false;
        if(is_clause_empty(formula))
            return true;
        if(first_rule(formula))
            continue;
        if(second_rule(formula))
            continue; 
        third_rule(formula);

    }
}
