#include <iostream>
#include "test.h"
#include "exhaustive.h"
using namespace std;

string test_name = "Custom Test";
string data_path = "";
string output_path = "";
string ans_path = "";
bool plot = false;

Test tests[] = {
    Test("Test Case 1", "data/dt1/point.txt", "ans/ans_dt1.txt", "data/dt1/ans.txt"),
    Test("Test Case 2", "data/dt2/point.txt", "ans/ans_dt2.txt", "data/dt2/ans.txt"),
    Test("Test Case 3", "data/dt3/point.txt", "ans/ans_dt3.txt")
};

void handleArgs(int argc, char* argv[]){
    
    int index = 0;
    while(index < argc - 1){

        index++;
        if(argv[index][0] != '-') continue;

        const char opt = argv[index][1];

        switch(opt){

            // Data input path
            case 'i':
                index++;
                if(index < argc && argv[index][0] != '-')
                    data_path = argv[index];
                else{
                    cerr << "Error: Missing argument for -i" << endl;
                    exit(-1);
                }
                break;

            // Output path
            case 'o':
                index++;
                if(index < argc && argv[index][0] != '-')
                    output_path = argv[index];
                else{
                    cerr << "Error: Missing argument for -o" << endl;
                    exit(-1);
                }
                break;

            // Answer path
            case 'a':
                index++;
                if(index < argc && argv[index][0] != '-')
                    ans_path = argv[index];
                else{
                    cerr << "Error: Missing argument for -a" << endl;
                    exit(-1);
                }
                break;

            // Test name
            case 'n':
                index++;
                if(index < argc && argv[index][0] != '-')
                    test_name = argv[index];
                else{
                    cerr << "Error: Missing argument for -n" << endl;
                    exit(-1);
                }
                break;

            // Plot flag
            case 'p':
                plot = true;
                break;

        }

    }

}

int main(int argc, char* argv[]){

    handleArgs(argc, argv);

    Test test = Test(test_name, data_path, output_path, ans_path);

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

    return 0;
}