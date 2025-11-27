#pragma once

#include <iostream>
#include <bitset>
#include <algorithm>
#include <cmath>
#include "test.h"
using namespace std;

/* ---- Definition ---- */

class AntColonyOptimization{

public:

    AntColonyOptimization(Test& test);

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
    sol_t best_sol;
    double best_dis;

    // variables
    const double INF = 1e9;
    const int start_id = 0;      // default starting from city_ids[0]

    int start_city, total_states;

    vector<int> bits__id;
    vector<vector<double>> dp_table; 
    vector<vector<pair<int, int>>> prev_table;

    // iteration
    int percentage = 0, new_percentage = 0;
    int total_iter = 0;

    // processing
    void init();
    sol_t reconstructSol(int state, int last_id) const;
    inline double calcDis(const pos_t& a, const pos_t& b) const;

};


/* ---- Implementation ---- */

AntColonyOptimization::AntColonyOptimization(Test& test): test(test){

    city_ids = test.getCityIds();
    city_pos = test.getCityPosVec();

}

void AntColonyOptimization::solve(){

    init();

    // initialize bits_id
    for(int i=0, j=0; i<city_ids.size(); i++){

        if(i == start_id)
            continue;
        
        bits__id[j++] = i;

    }

    // Variables
    int visit_city, last_city, last_id, prev_state;
    double dis, temp_dis;

    // First state initialization
    for(int visit=0; visit<city_ids.size(); visit++){

        visit_city = city_ids[visit];
        dp_table[0][visit] = calcDis(city_pos[start_city], city_pos[visit_city]);

    }

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
                    temp_dis = dp_table[prev_state][last_id] + dis;

                    if(temp_dis < dp_table[state][visit]){

                        dp_table[state][visit] = temp_dis;
                        prev_table[state][visit] = {prev_state, last_id};

                    }

                }

            }

        }

        new_percentage = (state * 100) / total_states;
        if(percentage != new_percentage){
            percentage = new_percentage;
            cout << "Progress: " << percentage << " %\r";
        }

    }

    best_sol = reconstructSol(total_states-1, start_id);
    best_dis = dp_table[total_states-1][start_id];

}

void AntColonyOptimization::init(){

    best_sol.clear();
    best_dis = 1e9;

    bits__id.resize(city_ids.size() - 1);
    
    start_city = city_ids[start_id];
    total_states = (1 << bits__id.size());
    dp_table.assign(total_states, vector<double>(city_ids.size(), INF));
    prev_table.assign(total_states, vector<pair<int, int>>(city_ids.size(), {-1, -1}));

    total_iter = city_ids.size();

}

sol_t AntColonyOptimization::reconstructSol(int state, int last_id) const {

    sol_t sol;
    sol.push_back(city_ids[last_id]);

    int prev_state, prev_id;

    while(state != 0){

        prev_state = prev_table[state][last_id].first;
        prev_id = prev_table[state][last_id].second;

        sol.push_back(city_ids[prev_id]);
        state = prev_state;
        last_id = prev_id;

    }

    return sol;

}

inline double AntColonyOptimization::calcDis(const pos_t& a, const pos_t& b) const { 

    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); 

}