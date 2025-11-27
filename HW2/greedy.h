#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include "test.h"
using namespace std;

/* ---- Definition ---- */

class Greedy{

public:

    Greedy(Test& test);

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
    vector<bool> visited;

    sol_t best_sol;
    double best_dis;

    // iteration
    int total_iter = 0;

    // processing
    void init();
    void startPoint(const int& start_id);
    inline double calcDis(const pos_t& a, const pos_t& b) const;

};


/* ---- Implementation ---- */

Greedy::Greedy(Test& test): test(test){

    city_ids = test.getCityIds();
    city_pos = test.getCityPosVec();

}

void Greedy::solve(){

    init();

    for(int iter=0; iter<total_iter; iter++){

        startPoint(city_ids[iter]);

        // Update best solution
        if(curr_dis < best_dis){
            best_sol = curr_sol;
            best_dis = curr_dis;
        }

        // output current progress
        cout << "Progress: " << iter << " / " << total_iter << "\r";

    }

}

void Greedy::init(){

    curr_sol.clear();
    visited.assign(city_ids.size() + 1, false);

    curr_dis = 0.0;

    best_sol.clear();
    best_dis = 1e9;

    total_iter = city_ids.size();

}

void Greedy::startPoint(const int& start_id){

    curr_sol.clear();
    curr_sol.push_back(start_id);

    visited.assign(city_ids.size() + 1, false);
    visited[start_id] = true;

    int curr_city = start_id;
    int next_city = -1;
    double min_city_dis = 1e9, temp_dis = 1e9;

    curr_dis = 0.0;

    for(int city=1; city<city_ids.size(); city++){

        next_city = -1;
        min_city_dis = 1e9;

        for(int id : city_ids){

            if(visited[id]) continue;
            
            temp_dis = calcDis(city_pos[curr_city], city_pos[id]);

            if(temp_dis < min_city_dis){
                min_city_dis = temp_dis;
                next_city = id;
            }

        }

        // Update current solution
        visited[next_city] = true;
        curr_dis += min_city_dis;

        curr_city = next_city;
        curr_sol.push_back(curr_city);

    }

    // Complete the tour by returning to the starting city
    curr_dis += calcDis(city_pos[curr_city], city_pos[curr_sol[0]]);

}

inline double Greedy::calcDis(const pos_t& a, const pos_t& b) const { 

    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); 

}