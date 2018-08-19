#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f = fopen("becuri.in","r");
FILE *g = fopen("becuri.out","w");
int N,M;
int L[505];
int C[505];
int V[505][505];
int nrL,nrC;
vector<pair<vector<int>,vector<int> > > SOL;
bool eval(){
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            if((V[i][j] ^ L[i] ^ C[j]) != 0){
                return 0;
            }
        }
    }
    return 1;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            fscanf(f,"%d",&V[i][j]);
        }
    }
    L[1] = 0;
    nrL = 0;
    nrC = 0;
    for(int j = 1;j <= M;j++){
        C[j] = V[1][j];
        nrC += C[j];
    }
    for(int i = 2;i <= N;i++){
        L[i] = V[i][1] ^ C[1];
        nrL += L[i];
    }
    if(eval()){
        if(nrL % 2 == nrC % 2){
            vector<int> LL,CC;
            while(nrL < nrC){
                nrL++;
                LL.push_back(1);
            }
            while(nrC < nrL){
                nrC++;
                CC.push_back(1);
            }
            for(int i = 1;i <= N;i++){
                if(L[i]){
                    LL.push_back(i);
                }
            }
            for(int i = 1;i <= M;i++){
                if(C[i]){
                    CC.push_back(i);
                }
            }
            SOL.push_back({LL,CC});
        }
    }
    L[1] = 1;
    nrL = 1;
    nrC = 0;
    for(int j = 1;j <= M;j++){
        C[j] = V[1][j] ^ 1;
        nrC += C[j];
    }
    for(int i = 2;i <= N;i++){
        L[i] = V[i][1] ^ C[1];
        nrL += L[i];
    }
    if(eval()){
        if(nrL % 2 == nrC % 2){
            vector<int> LL,CC;
            while(nrL < nrC){
                nrL++;
                LL.push_back(1);
            }
            while(nrC < nrL){
                nrC++;
                CC.push_back(1);
            }
            for(int i = 1;i <= N;i++){
                if(L[i]){
                    LL.push_back(i);
                }
            }
            for(int i = 1;i <= M;i++){
                if(C[i]){
                    CC.push_back(i);
                }
            }
            SOL.push_back({LL,CC});
        }
    }
    if(SOL.size() == 0){
        fprintf(g,"-1");
        return 0;
    }
    else if(SOL.size() == 2){
        if(SOL[0].first.size() > SOL[1].first.size()){
            swap(SOL[0],SOL[1]);
        }
    }
    fprintf(g,"%d\n",SOL[0].first.size());
    for(int i = 0;i < (int)SOL[0].first.size();i++){
        fprintf(g,"%d %d\n",SOL[0].first[i],SOL[0].second[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
