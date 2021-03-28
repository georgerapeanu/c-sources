#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n;
queue<int> to_delete;
int nxt[NMAX + 5];
int v[NMAX + 5];
bool taken[NMAX + 5];
vector<int> ans;

int gcd(int a,int b){
    if(!b){
        return a;
    }
    return gcd(b,a % b);
}


int main(){

    scanf("%d",&t);

    while(t--){
        while(!to_delete.empty()){
            to_delete.pop();
        }
        ans.clear();
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&v[i]);
            taken[i] = false;
        }

        for(int i = 1;i <= n;i++){
            nxt[i] = (i % n) + 1;
            if(gcd(v[i],v[nxt[i]]) == 1){
                to_delete.push(i);
            }
        }

        while(to_delete.empty() == false){
            int nod = to_delete.front();
            to_delete.pop();
            if(taken[nod]){
                continue;
            }
            taken[nxt[nod]] = true;
            ans.push_back(nxt[nod]);
            if(nod == nxt[nod]){
                break;
            }
            nxt[nod] = nxt[nxt[nod]];
            if(gcd(v[nod],v[nxt[nod]]) == 1){
                to_delete.push(nod);
            }
        }

        printf("%d ",(int)ans.size());
        for(auto it:ans){
            printf("%d ",it);
        }
        printf("\n");
        
    }

    return 0;
}
