#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int N;
int X[2001];
int Y[2001];

struct state{
    int lst,lvl;
    vector<int> peeps;
    bool operator < (const state &other)const{
        if(lst != other.lst){
            return lst < other.lst;
        }
        if(lvl != other.lvl){
            return lvl < other.lvl;
        }
        return peeps < other.peeps;
    }
    void afis(){
        cerr << lst << " " << lvl << "\n";
        for(auto it:peeps){
            cerr << it << " ";
        }
        cerr << "\n\n";
    }
};

map<state,int> viz;
queue<state> Q;

void fix(state &a){
    for(int i = 0;i < (int)a.peeps.size();i++){
        if(Y[a.peeps[i]] == a.lvl){
            a.peeps.erase(a.peeps.begin() + i);
            i--;
        }
    }
    while(a.peeps.size() < 4 && a.lst < N && X[a.lst + 1] == a.lvl){
        a.lst++;
        a.peeps.push_back(a.lst);
    }
}

int main(){

    scanf("%d",&N);

    for(int i = 1;i <= N;i++){
        scanf("%d %d",&X[i],&Y[i]);
    }

    state start;
    start.lst = 0;
    start.lvl = 1;

    fix(start);

    viz[start] = 2 * N;
    Q.push(start);
    while(!Q.empty()){
        state nod = Q.front();
        ///nod.afis();
        Q.pop();
        if(nod.lvl > 1){
            state a = nod;
            a.lvl--;
            fix(a);
            if(!viz.count(a)){
                viz[a] = viz[nod] + 1;
                Q.push(a);
                if(a.lst == N && a.peeps.empty()){
                    printf("%d\n",viz[a]);
                    return 0;
                }
            }
        }
        if(nod.lvl < 9){
            state a = nod;
            a.lvl++;
            fix(a);
            if(!viz.count(a)){
                viz[a] = viz[nod] + 1;
                Q.push(a);
                if(a.lst == N && a.peeps.empty()){
                    printf("%d\n",viz[a]);
                    return 0;
                }
            }
        }
    }

    return 0;
}
