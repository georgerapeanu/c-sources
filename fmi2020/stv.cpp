#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("stv.in","r");
FILE *g = fopen("stv.out","w");

int n;
int m;
vector<int> pref[105];

bool active[105];
int votes[105];

int main(){

    fscanf(f,"%d",&n);
    fscanf(f,"%d",&m);

    for(int i = 1;i <= m;i++){
        active[i] = 1;
    }

    for(int i = 1;i <= n;i++){
        int len;
        fscanf(f,"%d",&len);

        while(len--){
            int val;
            fscanf(f,"%d",&val);
            pref[i].push_back(val);
        }
        reverse(pref[i].begin(),pref[i].end());
    }

    vector<int> ans;

    for(int i = 1;i <= m;i++){
        for(int j = 1;j <= m;j++){
            votes[j] = 0;
        }
        for(int j = 1;j <= n;j++){
            while(pref[j].empty() == false && active[pref[j].back()] == 0){
                pref[j].pop_back();
            }
            if(pref[j].empty() == false){
                votes[pref[j].back()]++;
            }
        }
        int bst = -1;
        for(int j = 1;j <= m;j++){
            if(active[j] && (bst == -1 || votes[j] <= votes[bst])){
                bst = j;
            }
        }
        active[bst] = 0;
        ans.push_back(bst);
    }

    reverse(ans.begin(),ans.end());

    for(auto it:ans){
        fprintf(g,"%d ",it);
    }

    fclose(f);
    fclose(g);

    return 0;  
}

