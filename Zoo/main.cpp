#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f = fopen("zoo.in","r");
FILE *g = fopen("zoo.out","w");
const int NMAX = 16000;
const int MMAX = 100000;
struct event{
    int x;
    int Y1,Y2;
    int where;
    int type;
    bool operator < (const event &other)const{
        if(x != other.x){
            return x < other.x;
        }
        return type < other.type;
    }
};
int N;
int M;
int AIB[NMAX + 9];
int X[NMAX + 5];
int Y[NMAX + 5];
int X1[MMAX + 5];
int Y1[MMAX + 5];
int X2[MMAX + 5];
int Y2[MMAX + 5];
int R[MMAX + 5];
vector<event> V;
vector<int> tmp;
int sz = 0;
void u(int pos){
    for(;pos <= sz;pos += (-pos) & pos){
        AIB[pos]++;
    }
}
int q(int pos){
    int rez = 0;
    for(;pos;pos -= (pos) & -pos){
        rez += AIB[pos];
    }
    return rez;
}
const int LEN = 131072;
int ind = LEN - 1;
char buff[LEN];
int i32(){
    int rez = 0,sgn = 1;
    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    if(buff[ind] == '-'){
        sgn = -1;
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    while(buff[ind] >= '0' && buff[ind] <= '9'){
        rez = rez * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return rez * sgn;
}
int main(){
    N = i32();
    for(int i = 1;i <= N;i++){
        X[i] = i32();
        Y[i] = i32();
        tmp.push_back(Y[i]);
    }
    M = i32();
    for(int i = 1;i <= M;i++){
        X1[i] = i32();
        Y1[i] = i32();
        X2[i] = i32();
        Y2[i] = i32();
    }
    tmp.push_back(2000000001);
    tmp.push_back(-2000000001);
    sort(tmp.begin(),tmp.end());
    tmp.resize(unique(tmp.begin(),tmp.end()) - tmp.begin());
    sz = tmp.size();
    for(int i = 1;i <= N;i++){
        Y[i] = lower_bound(tmp.begin(),tmp.end(),Y[i]) - tmp.begin() + 1;
        V.push_back({X[i],Y[i],0,0,0});
    }
    for(int i = 1;i <= M;i++){
        int tmpY2 = Y2[i];
        Y1[i] = lower_bound(tmp.begin(),tmp.end(),Y1[i]) - tmp.begin() + 1;
        Y2[i] = lower_bound(tmp.begin(),tmp.end(),Y2[i]) - tmp.begin() + 1;
        if(tmp[Y2[i] - 1] != tmpY2){
            Y2[i]--;
        }
        V.push_back({X1[i],Y1[i],Y2[i],i,-1});
        V.push_back({X2[i],Y1[i],Y2[i],i,1});
    }
    sort(V.begin(),V.end());
    for(auto it:V){
        if(it.type == 0){
            u(it.Y1);
        }
        else{
            if(it.Y2 < it.Y1){
                continue;
            }
            R[it.where] += (q(it.Y2) - (it.Y1 > 0 ? q(it.Y1 - 1) : 0)) * it.type;
        }
    }
    for(int i = 1;i <= M;i++){
        fprintf(g,"%d\n",R[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
