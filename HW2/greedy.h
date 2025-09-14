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
    int curr_city, next_city;
    double min_city_dis, temp_dis;

    sol_t best_sol;
    double best_dis;

    // iteration
    int total_iter = 0;

    // processing
    void init();
    inline double calcDis(pos_t a, pos_t b);

};


/* ---- Implementation ---- */

Greedy::Greedy(Test& test): test(test){

    city_ids = test.getCityIds();
    city_pos = test.getCityPosVec();

}

void Greedy::solve(){

    init();

    for(int iter=1; iter<total_iter; iter++){

        next_city = -1;
        min_city_dis = 1e9;

        for(int id : city_ids){

            temp_dis = 1e9;
            if(!visited[id]){
                temp_dis = calcDis(city_pos[curr_city], city_pos[id]);
            }

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

        // output current progress
        cout << "Progress: " << iter << " / " << total_iter << "\r";

    }

    // Complete the tour by returning to the starting city
    curr_dis += calcDis(city_pos[curr_city], city_pos[curr_sol[0]]);

    // Update best solution
    best_sol = curr_sol;
    best_dis = curr_dis;

}

void Greedy::init(){

    curr_sol.clear();
    curr_sol.push_back(city_ids[0]);
    visited.assign(city_ids.size() + 1, false);

    curr_city = city_ids[0];
    visited[curr_city] = true;

    next_city = -1;
    curr_dis = 0.0;

    best_sol.clear();
    best_dis = 1e9;

    total_iter = city_ids.size();

}

inline double Greedy::calcDis(pos_t a, pos_t b) { 

    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); 

}