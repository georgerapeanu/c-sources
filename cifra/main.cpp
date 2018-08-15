#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream f("cifra.in");
ofstream g("cifra.out");

int T;
string N;
vector<int> cycle = {0,1,5,2,8,3,9,2,8,7,7,8,4,7,3,8,4,1,5,4,4,5,9,6,2,7,3,6,2,1,1,2,8,1,7,2,8,5,9,8,8,9,3,0,6,1,7,0,6,5,5,6,2,5,1,6,2,9,3,2,2,3,7,4,0,5,1,4,0,9,9,0,6,9,5,0,6,3,7,6,6,7,1,8,4,9,5,8,4,3,3,4,0,3,9,4,0,7,1,0};

int main(){

    f >> T;

    while(T--){
        f >> N;
        int num = N.back() - '0';
        if(N.size() > 1){
            num += 10 * (N[(int)N.size() - 2] - '0');
        }
        g << cycle[num] << "\n";
    }

    f.close();
    g.close();

    return 0;
}
