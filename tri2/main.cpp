#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
FILE *f = fopen("tri2.in","r");
FILE *g = fopen("tri2.out","w");
int N,M;
vector<int> pts;
int ordX[1005];
int PordX[1005];
int AIB[1005];
pair<int,int> P[1005];
int Ans[1005][1005];
set<int> OX,OY;
void u(int x,int val){
    for(;x <= N;x += (-x) & x){
        AIB[x] += val;
    }
}
int q(int x){
    int rez = 0;
    for(;x;x -= (-x) & x){
        rez += AIB[x];
    }
    return rez;
}
bool cmpX(int a,int b){
    return P[a] < P[b];
}
int pivot;
bool cmpA(int a,int b){
    int xA = P[a].first - P[pivot].first;
    int xB = P[b].first - P[pivot].first;
    int yA = P[a].second - P[pivot].second;
    int yB = P[b].second - P[pivot].second;
    return 1LL * yA * xB < 1LL * yB * xA;
}
int main(){
    fscanf(f,"%d",&N);
    assert(3 <= N && N <= 1000);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d %d",&P[i].first,&P[i].second);
        ordX[i] = i;
        OX.insert(P[i].first);
        OY.insert(P[i].second);
        assert(0 <= P[i].first && P[i].first <= 2e9);
        assert(0 <= P[i].second && P[i].second <= 2e9);
    }
    assert(OX.size() == N && OY.size() == N);
    sort(ordX + 1,ordX + 1 + N,cmpX);
    for(int i = 1;i <= N;i++){
        PordX[ordX[i]] = i;
    }
    for(int i = 1;i <= N;i++){
        pts.clear();
        for(int j = 1;j <= N;j++){
            if(PordX[i] < PordX[j]){
                pts.push_back(j);
            }
        }
        pivot = i;
        sort(pts.begin(),pts.end(),cmpA);
        memset(AIB,0,sizeof(AIB));
        for(auto it:pts){
            Ans[i][it] = q(PordX[it]);
            u(PordX[it],1);
        }
    }
    fscanf(f,"%d",&M);
    while(M--){
        vector<int> tmp(3);
        fscanf(f,"%d %d %d",&tmp[0],&tmp[1],&tmp[2]);
        sort(tmp.begin(),tmp.end(),cmpX);
        int rez = Ans[tmp[0]][tmp[1]] + Ans[tmp[1]][tmp[2]] - Ans[tmp[0]][tmp[2]];
        rez = (rez >= 0 ? rez : -rez - 1);
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
