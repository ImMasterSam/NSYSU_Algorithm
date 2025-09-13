#include <iostream>
#include "test.h"
#include "exhaustive.h"
using namespace std;

Test tests[] = {
    Test("Test Case 1", "dt1/point.txt", "ans/ans_dt1.txt", "dt1/ans.txt"),
    Test("Test Case 2", "dt2/point.txt", "ans/ans_dt2.txt", "dt2/ans.txt"),
    Test("Test Case 3", "dt3/point.txt", "ans/ans_dt3.txt")
};

int main(){
    
    for(Test& test : tests){
        cout << "===== " << test.name << " =====" << endl;

        sol_t city_ids = test.getCityIds();
        unordered_map<int, city_t> city_datas = test.getCityData();

        cout << "Number of cities: " << city_ids.size() << endl;

        Exhaustive solver(test);
        solver.solve();
        sol_t best_sol = solver.getBestSol();
        double best_dis = solver.getBestDis();

        cout << "Best distance: " << best_dis << endl;
        test.verifySol(best_sol, best_dis, true);

        cout << endl;

    }

    return 0;
}