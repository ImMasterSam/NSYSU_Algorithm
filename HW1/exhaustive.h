#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include "test.h"
using namespace std;

/* ---- Definition ---- */

class Exhaustive{

public:

    Exhaustive(Test& test);

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
    sol_t best_sol;
    double curr_dis;
    double best_dis;

    // iteration
    int iter = 0;
    int total_iter = 1;

    // processing
    void init();
    double calcDis(sol_t sol);

};


/* ---- Implementation ---- */

Exhaustive::Exhaustive(Test& test): test(test){

    city_ids = test.getCityIds();
    city_pos = test.getCityPosVec();

}

void Exhaustive::solve(){

    init();

    do{

        curr_dis = calcDis(curr_sol);

        // update best solution
        if(curr_dis < best_dis){
            best_dis = curr_dis;
            best_sol = curr_sol;
        }

        // output current progress
        iter++;
        int progress = ((double)iter / total_iter) * 100;
        if(iter % 50000 == 0){
            cout << "Progress: " << progress << "%" << "\r";
        }

    }while(next_permutation(curr_sol.begin(), curr_sol.end()));

}

void Exhaustive::init(){

    curr_sol = city_ids;
    sort(curr_sol.begin(), curr_sol.end());

    best_sol = curr_sol;
    best_dis = 1e9;

    iter = 0;
    total_iter = 1;
    for(size_t i=2; i<=city_ids.size(); i++) total_iter *= i;

}

double Exhaustive::calcDis(sol_t sol){

    double dis = 0.0;

    for(size_t i=0; i<sol.size(); i++){

        pos_t c1 = city_pos[sol[i]];
        pos_t c2 = city_pos[sol[(i+1) % sol.size()]];

        double d = sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
        dis += d;

    }

    return dis;

}