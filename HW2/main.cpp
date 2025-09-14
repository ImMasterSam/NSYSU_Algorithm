#include <iostream>
#include "test.h"
#include "greedy.h"
using namespace std;

const string point_dir = "data/";
const string ans_dir = "ans/";

Test tests[] = {
    Test("Test Case 1", point_dir + "dt1/point.txt", ans_dir + "ans_dt1.txt", point_dir + "dt1/ans.txt"),
    Test("Test Case 2", point_dir + "dt2/point.txt", ans_dir + "ans_dt2.txt", point_dir + "dt2/ans.txt"),
    Test("Test Case 3", point_dir + "dt3/point.txt", ans_dir + "ans_dt3.txt")
};

int main(){
    
    for(Test& test : tests){
        cout << "===== " << test.name << " =====" << endl;

        sol_t city_ids = test.getCityIds();
        unordered_map<int, city_t> city_datas = test.getCityData();

        cout << "Number of cities: " << city_ids.size() << endl;

        Greedy solver(test);
        solver.solve();
        sol_t best_sol = solver.getBestSol();
        double best_dis = solver.getBestDis();

        cout << "Best distance: " << best_dis << endl;
        test.verifySol(best_sol, best_dis, true);

        cout << endl;

    }

    return 0;
}