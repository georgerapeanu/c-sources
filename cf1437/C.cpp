#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int a[205];
int c[405];
int v[405];

void reset(){
    memset(c,0,sizeof(c));
    memset(v,0,sizeof(v));
}

int ins(int pos){

    pos++;
    v[pos]++;
    int l_cost = 0;
    int r_cost = 0;

    vector<int> undo;

    for(int i = pos;;i++){
        if(v[i] - c[i] + c[i - 1] > 1){
            r_cost += (c[i] < 0 ? -1:1);
            c[i]++;
            undo.push_back(i);
        }
        else{
            break;
        }
    }

    while(undo.empty() == false){
        c[undo.back()]--;
        undo.pop_back();
    }

    for(int i = pos;;i--){
        if(v[i] - c[i] + c[i - 1] > 1){
            if(i - 1 == 1){
                l_cost = 1e9;
                break;
            }
            l_cost += (c[i - 1] > 0 ? -1:1);
            c[i - 1]--;
            undo.push_back(i - 1);
        }
        else{
            break;
        }
    }
    while(undo.empty() == false){
        c[undo.back()]++;
        undo.pop_back();
    }
    
    if(l_cost > r_cost){
        for(int i = pos;;i++){
            if(v[i] - c[i] + c[i - 1] > 1){
                c[i]++;
            }
            else{
                break;
            }
        }
        return r_cost;
    }
    else{
        for(int i = pos;;i--){
            if(v[i] - c[i] + c[i - 1] > 1){
                c[i - 1]--;
            }
            else{
                break;
            }
        }
        return l_cost;
    }
}

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
        }

        sort(a + 1,a + 1 + n);

        reset();
        int ans = 0;

        for(int i = 1;i <= n;i++){
            ans += ins(a[i]);
        }
        printf("%d\n",ans);
    }

    return 0;
}
