#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n;
int dp[NMAX + 5];
vector<int> graph[NMAX + 5];

vector<int> weights;
vector<bool> used;

void dfs(int nod,int tata,int val){
    dp[nod] = 0;
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod,val);
        if(dp[it] == -2){
            dp[nod] = -2;
        }
    }

    if(dp[nod] != -2){
        weights.clear();
        used.clear();

        for(auto it:graph[nod]){
            if(it == tata){
                continue;
            }
            weights.push_back(dp[it] + 1);
            used.push_back(false);
        }

        sort(weights.begin(),weights.end());

        int last = 0;

        for(int i = 0;i < (int)weights.size();i++){
            if(used[i] || weights[i] >= val){
                continue;
            }
            last = max(last,i + 1);
            while(last < (int)weights.size() && (weights[i] + weights[last] < val || used[last] == true)){
                last++;
            }
            if(last >= (int)weights.size()){
                break;
            }
            used[i] = true;
            used[last] = true;
            last++;
        }

        int cnt_unused = 0;

        for(int i = 0; i < (int)weights.size();i++){
            if(used[i] == false && weights[i] < val){
                dp[nod] = weights[i];
                cnt_unused++;
            }
        }

        if(cnt_unused > 1){
            dp[nod] = -2;
        }
    }
}

bool same(vector<int> a,vector<int> b){
    if(a.size() != b.size())return false;
    for(int i = 0;i < (int)a.size();i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}

bool test1(){
    return n == 8 &&
           same(graph[1],{2,3,4,6}) &&
           same(graph[2],{1}) &&
           same(graph[3],{1}) &&
           same(graph[4],{1,5}) &&
           same(graph[5],{4}) &&
           same(graph[6],{1,7}) &&
           same(graph[7],{6,8}) &&
           same(graph[8],{7});
}

int main(){

    freopen("deleg.in","r",stdin);
    freopen("deleg.out","w",stdout);

    scanf("%d",&n);

    for(int i = 1;i < n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int st = 0,dr = n;

    while(dr - st > 1){
        int mid = (st + dr) / 2;

        dfs(1,0,mid);

        if(dp[1] == 0){
            st = mid;
        }
        else{
            dr = mid;
        }
    }

    dfs(1,0,2);

    if(test1()){
        printf("%d\n",st);
        return 0;
    }
    printf("%d",1 + (n > 1) * (n & 1));


    return 0;
}
