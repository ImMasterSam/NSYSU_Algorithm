#pragma once
using namespace std;

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
using sol_t = vector<int>;          // {city1, city2, ...}

// {x, y}
struct pos_t{
    int x;
    int y;
};

// {city1_id, {x, y}}
struct city_t{
    int id;
    pos_t pos;
};


/* ---- Definition ---- */

class Test{

public:

    const string name;

    Test(const string& name, const string& filePath, const string& ansPath = "")
    : name(name), filePath(filePath), ansPath(ansPath) {

        loadCities();
        loadAns();

    }

    // Accessors
    sol_t getAns() const { return ans; }
    vector<int> getCityIds() const { return city_ids; }
    unordered_map<int, city_t> getCityData() const { return city_datas; }

private:
    
    // files
    const string filePath;
    const string ansPath;

    // city data
    vector<int> city_ids;
    unordered_map<int, city_t> city_datas;
    sol_t ans;

    // loading functions
    void loadCities();
    void loadAns();

};

/* ---- Implementation ---- */

// load cities' info from files
void Test::loadCities() {
    
    ifstream fin(filePath);

    if(!fin.is_open()){
        cerr << "Error: Cannot open file " << filePath << endl;
        exit(-1);
    }

    int city_id, x, y;
    while(fin >> city_id >> x >> y){
        city_ids.push_back(city_id);
        city_datas[city_id] = {city_id, {x, y}};
    }

}

// load answer from files
void Test::loadAns() {
    if(ansPath.empty()) return;

    ifstream fin(ansPath);

    if(!fin.is_open()){
        cerr << "Error: Cannot open file " << ansPath << endl;
        exit(-1);
    }

    int city_id;
    while(fin >> city_id){
        ans.push_back(city_id);
    }

}

