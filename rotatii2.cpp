#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("rotatii2.in","r");
FILE *g = fopen("rotatii2.out","w");

const int NMAX = 1e6;
const int LEN = 1e4;

char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while('0' <= buff[ind] && buff[ind] <= '9'){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int n;
int sons[NMAX + 5][2];
pair<int,int> father[NMAX + 5];

void solve(int n,vector<pair<int,int> > &op,bool reversed){
    int root = -1;
    for(int i = 1;i <= n;i++){
        if(father[i].first == 0){
            root = i;
        }
    }

    while(root){
        while(sons[root][0] != 0){
            if(reversed == false){
                op.push_back({1,root});
            }
            else{
                op.push_back({2,sons[root][0]});
            }
            int l = sons[root][0];
            int r = sons[root][1];
            sons[root][0] = sons[l][1];
            sons[l][1] = root;
            sons[father[root].first][father[root].second] = l;
            father[l] = father[root];
            father[sons[root][0]] = {root,0};
            father[root] = {l,1};
            root = l;
        }
        root = sons[root][1];
    }
}

int main(){

    n = i32();

    for(int i = 1;i <= n;i++){
        for(int j = 0;j < 2;j++){
            sons[i][j] = i32();
            father[sons[i][j]] = {i,j};
        }
    }

    vector<pair<int,int> > op1;

    solve(n,op1,false);

    for(int i = 1;i <= n;i++){
        father[i] = {0,0};
    }

    for(int i = 1;i <= n;i++){
        for(int j = 0;j < 2;j++){
            sons[i][j] = i32();
            father[sons[i][j]] = {i,j};
        }
    }

    vector<pair<int,int> > op2;

    solve(n,op2,true);
    reverse(op2.begin(),op2.end());

    fprintf(g,"%d\n",int(op1.size() + op2.size()));

    for(auto it:op1){
        fprintf(g,"%d %d\n",it.first,it.second);
    }

    for(auto it:op2){
        fprintf(g,"%d %d\n",it.first,it.second);
    }

    fclose(f);
    fclose(g);

    return 0;
}
