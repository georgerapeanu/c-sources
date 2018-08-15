#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("amiba.in","r");
FILE *g = fopen("amiba.out","w");

int play(vector<int> &other,vector<int> &boss){
    int other_idx = 0,ans = 0;

    for(auto it:boss){
        while(other_idx < (int)other.size() && it > other[other_idx]){
            other_idx++;
        }
        if(other_idx == (int)other.size()){
            break;
        }
        ans++;
        other_idx++;
    }
    return ans;
}

void fill_rest(vector< pair<int,int> > &ans,vector<int> &boss,vector<int> &skinny,vector<int> &junior){
    vector<bool> used(3 * N,false);
    for(auto it:ans){
        if(it.first != -1){
            used[it.first] = 1;
        }
        if(it.second != -1){
            used[it.second] = 1;
        }
    }

    int junior_idx = 0;
    int skinny_idx = 0;

    for(auto &it:ans){
        if(it.first == -1){
            while(used[skinny[skinny_idx++]]);
            it.first = skinny[skinny_idx++];
        }
        if(it.second == -1){
            while(used[junior[junior_idx++]]);
            it.second = junior[junior_idx++];
        }
    }
}

vector<int> tmp;
vector<int> ord;

bool cmp(int a,int b){
    return tmp[a] < tmp[b];
}

void prep(vector<int> &boss,int N){
    tmp = boss;
    ord.resize(N);
    for(int i = 0;i < N;i++){
        ord[i] = i;
    }
    sort(ord.begin(),ord.end(),cmp);
}

void reorder(vector< pair<int,int> > &ans,int N){
    vector< pair<int,int> > V(N);
    for(int i = 0;i < N;i++){
        V[ord[i]] = ans[i];
    }
    ans = V;
}

int T,N,A,B;

int main(){

    fscanf(f,"%d",&T);

    while(T--){
        fscanf(f,"%d %d %d",&N,&A,&B);

        vector<int> boss(N,0);
        vector<int> skinny(N,0);
        vector<int> junior(N,0);
        vector< pair<int,int> > ans(N,{-1,-1});

        for(int i = 0;i < N;i++){
            fscanf(f,"%d",&boss[i]);
        }

        for(int i = 0;i < N;i++){
            fscanf(f,"%d",&skinny[i]);
        }

        for(int i = 0;i < N;i++){
            fscanf(f,"%d",&junior[i]);
        }

        prep(boss,N);

        if(A <= 2 * B){

        }
        else{

        }

        reorder(áns,N)
    }

    fclose(f);
    fclose(g);

    return 0;
}
