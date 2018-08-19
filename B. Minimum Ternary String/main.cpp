#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct data{
    int num0;
    int num1;
    int num2;
};

string S;
vector<data> V;

int main(){
    cin >> S;
    data last = {0,0,0};

    for(auto it:S){
        last.num0 += (it == '0');
        last.num1 += (it == '1');
        last.num2 += (it == '2');

        if(last.num2){
            V.push_back(last);
            last = {0,0,0};
        }
    }

    V.push_back(last);

    for(int i = 1;i < (int)V.size();i++){
        V[0].num1 += V[i].num1;
        V[i].num1 = 0;
    }

    for(auto it:V){
        while(it.num0--){
            cout << 0;
        }
        while(it.num1--){
            cout << 1;
        }
        while(it.num2--){
            cout << 2;
        }
    }

    return 0;
}
