#include <bits/stdc++.h>

using namespace std;

int trans[33][33][33];
string sym[34];

void add_trans(vector<int> l,vector<int> m,vector<int> r,int ans){
    for(auto _l:l){
        for(auto _m:m){
            for(auto _r:r){
                trans[_l][_m][_r] = ans;
            }
        }
    }
}

void print_trans(){
    for(int i = 0;i <= 30;i++){
        for(int j = 1;j <= 30;j++){
            for(int k = 0;k <= 30;k++){
                cout << sym[i] << " " << sym[j] << " " << sym[k] << " -> " << sym[trans[i][j][k]] << "\n";
            }
        }
    }
}

void simulate(){
    vector<int> v = {29,29,29};

    while(true){
        vector<int> nv(v.size());

        for(int i = 0;i < (int)v.size();i++){
            int l = (i > 0 ? v[i - 1]:0);
            int r = (i + 1 < (int)v.size() ? v[i + 1]:0);
            int m = v[i];
            nv[i] = trans[l][m][r];
            if(nv[i] > 30){
                cout << sym[nv[i]] << "\n";            
                break;
            }
        }
        v = nv;
    }
}

int main(){

    for(int i = 1;i <= 28;i++){
        string s;
        if(i < 10){
            s = string(1,i + '0');
        }else{
            s = string(2,'0');
            s[0] = (i / 10) + '0';
            s[1] = (i % 10) + '0';
        }
        sym[i] = s;
    }
    sym[0] = "X";
    sym[29] = "Y";
    sym[30] = "N";
    sym[31] = "Minor";
    sym[32] = "Major";

    for(int i = 0;i <= 32;i++){
        for(int j = 1;j <= 32;j++){
            for(int k = 0;k <= 32;k++){
                trans[i][j][k] = j;
            }
        }
    }

    add_trans({0,1},{2},{0,1,2,29,30},1);
    add_trans({30},{29},{0,1,2,29,30},2);
    add_trans({0,1,2,29,30},{30},{29},2);
    add_trans({0,1},{29,2},{0,1},32);
    add_trans({0,1},{30},{0,1},31);
   
    print_trans();
    simulate();

    return 0;
}
