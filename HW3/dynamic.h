#pragma once

#include <iostream>
#include <bitset>
#include <algorithm>
#include <cmath>
#include "test.h"
using namespace std;

/* ---- Definition ---- */

class DynamicProgramming{

public:

    DynamicProgramming(Test& test);

    void solve();

    // Accessors
    sol_t getBestSol() const { return best_sol; }
    double getBestDis() const { return best_dis; }

private:

    // datas
    Test test;
    vector<int> city_ids;
    vector<pos_t> city_pos;

    // solutions
    sol_t curr_sol;
    double curr_dis;

    sol_t best_sol;
    double best_dis;

    // variables
    const double INF = 1e9;
    vector<int> bits__id;
    vector<vector<double>> dp_table; 

    // iteration
    int total_iter = 0;

    // processing
    void init();
    void startPoint(const int& start_id);
    inline double calcDis(const pos_t& a, const pos_t& b) const;

};


/* ---- Implementation ---- */

DynamicProgramming::DynamicProgramming(Test& test): test(test){

    city_ids = test.getCityIds();
    city_pos = test.getCityPosVec();

}

void DynamicProgramming::solve(){

    init();

    startPoint(0);
    best_sol = curr_sol;
    best_dis = curr_dis;

}

void DynamicProgramming::init(){

    curr_sol.clear();
    curr_dis = 0.0;

    best_sol.clear();
    best_dis = 1e9;

    bits__id.resize(city_ids.size() - 1);

    total_iter = city_ids.size();

}

void DynamicProgramming::startPoint(const int& start_id){

    // initialize bits_id
    for(int i=0, j=0; i<city_ids.size(); i++){

        if(i == start_id)
            continue;
        
        bits__id[j++] = i;

    }

    // Variables
    int start_city = city_ids[start_id];
    int total_states = (1 << bits__id.size());
    dp_table.assign(total_states, vector<double>(city_ids.size(), INF));

    // First state initialization
    for(int visit=0; visit<city_ids.size(); visit++){

        int visit_city = city_ids[visit];
        dp_table[0][visit] = calcDis(city_pos[start_city], city_pos[visit_city]);

    }

    int visit_city, last_city, last_id, prev_state;
    double dis;

    // DP state transition using bottom method
    for(int state=1; state<total_states; state++){

        for(int visit=0; visit<city_ids.size(); visit++){

            for(int b=0; b<bits__id.size(); b++){

                if((state & (1 << b))){

                    // Get city ids
                    visit_city = city_ids[visit];
                    last_id = bits__id[b];
                    last_city = city_ids[last_id];
                    
                    // Update dp table from previous state
                    prev_state = (state ^ (1 << b));
                    dis = calcDis(city_pos[last_city], city_pos[visit_city]);
                    dp_table[state][visit] = min(dp_table[state][visit], dp_table[prev_state][last_id] + dis);

                }

            }

        }

        cout << "Progress: " << state << " / " << total_states << "\r";

    }

    curr_sol = city_ids;
    curr_dis = dp_table[total_states-1][start_id];

}

inline double DynamicProgramming::calcDis(const pos_t& a, const pos_t& b) const { 

    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); 

}