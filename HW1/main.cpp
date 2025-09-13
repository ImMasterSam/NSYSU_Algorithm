#include <iostream>
#include "test.h"
using namespace std;

const Test tests[] = {
    Test("Test Case 1", "dt1/point.txt", "dt1/ans.txt"),
    Test("Test Case 2", "dt2/point.txt", "dt2/ans.txt"),
    Test("Test Case 3", "dt3/point.txt"),
};

int main(){
    
    for(const Test& test : tests){
        cout << "Running " << test.name << " ..." << endl;

        sol_t city_ids = test.getCityIds();
        unordered_map<int, city_t> city_datas = test.getCityData();

        cout << "  Number of cities: " << city_ids.size() << endl;
        
        for(int id : city_ids){
            city_t city = city_datas[id];
            cout << "    City " << city.id << ": (" << city.pos.x << ", " << city.pos.y << ")" << endl;
        }

    }

    return 0;
}