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

    Test(const string& name, const string& filePath, const string& outputPath, const string& ansPath = "")
    : name(name), filePath(filePath), outputPath(outputPath), ansPath(ansPath) {

        loadCities();
        loadAns();

    }

    bool verifySol(const sol_t& sol, const double best_dis, bool output = true) const;

    // Accessors
    vector<int> getCityIds() const { return city_ids; }
    unordered_map<int, city_t> getCityData() const { return city_datas; }
    vector<pos_t> getCityPosVec() const {
        vector<pos_t> data;
        data.resize(city_ids.size() + 1);
        for(int id : city_ids){
            data[id] = city_datas.at(id).pos;
        }
        return data;
    }

private:
    
    // files
    const string filePath;
    const string outputPath;
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

// verify solution
bool Test::verifySol(const sol_t& sol, const double best_dis, bool output) const {

    if(output){
        ofstream fout(outputPath);
        fout << "distance: " << best_dis << endl;
        for(int id : sol){
            fout << id << endl;
        }
        fout.close();
    }

    if(!ans.empty()){
        
        if(sol.size() != ans.size()){
            cerr << "Solution size mismatch: expected " << ans.size() << ", got " << sol.size() << "." << endl;
            return false;
        }
        for(size_t i = 0; i < sol.size(); i++){
            if(sol[i] != ans[i]){
                cout << "Wrong answer: city id mismatch at position " << i << "." << endl;
                return false;
            }
        }
        cout << "Correct answer!" << endl;
        return true;

    } else {
        cout << "No answer file provided." << endl;
        return false;
    }

}

// load cities' info from files
void Test::loadCities() {
    
    ifstream fin(filePath);

    if(!fin.is_open()){
        cerr << "Error: Cannot open file " << filePath << endl;
        exit(-1);
    }

    city_ids.clear();
    city_datas.clear();

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
        cerr << "Error: Cannot open answer file " << ansPath << endl;
        exit(-1);
    }

    ans.clear();

    int city_id;

    // skip the first line (header)
    string header;
    getline(fin, header);

    while(fin >> city_id){
        ans.push_back(city_id);
    }

}

