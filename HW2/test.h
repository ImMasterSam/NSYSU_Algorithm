#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
using sol_t = vector<int>;          // {city1, city2, ...}

const double EPS = 1e-3;

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

    Test(const string& name, const string& filePath, const string& outputFile, const string& ansPath = "")
    : name(name), filePath(filePath), outputFile(outputFile), ansPath(ansPath) {

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
    const string outputFile;
    const string ansPath;

    // city data
    vector<int> city_ids;
    unordered_map<int, city_t> city_datas;

    // answer
    double ans_dis;
    sol_t ans;

    // loading functions
    void loadCities();
    void loadAns();

};

/* ---- Implementation ---- */

// verify solution
bool Test::verifySol(const sol_t& sol, const double best_dis, bool output) const {

    if(output){
        ofstream fout("ans/" + outputFile + ".txt");

        if(!fout.is_open()){
            cerr << "Error: Cannot open output file " << outputFile << endl;
            exit(-1);
        }

        fout << "distance: " << best_dis << endl;
        for(int id : sol){
            fout << id << endl;
        }
        fout.close();
    }

    if(!ans.empty()){
        
        // Check solution size
        if(sol.size() != ans.size()){
            cerr << "\033[91mSolution size mismatch: expected " << ans.size() << ", got " << sol.size() << ".\033[m" << endl;
            return false;
        }
        
        // Check if the solution reach the optima
        if(best_dis - ans_dis > EPS){
            cout << "\033[91mUnable to reach minimum distance!\033[m" << endl;
            cout << "Minimum distance: ";
            cout << "\033[92m" << ans_dis << "\033[m, Your distance: \033[93m" << best_dis << "\033[m" << endl;
            return false;
        }
        else{
            cout << "\033[92mReach minimum distance!\033[m" << endl;
            return true;
        }


    } else {
        cout << "\033[90mNo answer file provided.\033[m" << endl;
        return false;
    }

    cerr << "\033[91Unknown error in verifying solution.\033[m" << endl;
    return false;

}

// load cities' info from files
void Test::loadCities() {
    
    ifstream fin(filePath);

    if(!fin.is_open()){
        cerr << "Error: Cannot open data file " << filePath << endl;
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

    // Read the answer distance from the header
    char* header_cstr = (char*) header.c_str();
    char* token = strtok(header_cstr, " ");
    token = strtok(NULL, " ");                      // Skip "distance:"
    if(token != nullptr){
        ans_dis = stod(string(token));
    }

    while(fin >> city_id){
        ans.push_back(city_id);
    }

}

