#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 2e5;
const int inf = 1 << 28;

struct dfs_ret_t{
    int id;///id of the son
    int last_sum;///biggest sum in a node with degree = 3
    int fahrest_len;///distance to fahrest node
    int fahrest_node;///fahrest node
    int last_node;///last_node with degree = 3
    int last_len; ///distance to last node with degree = 3
    int first_node;///the first node which contributes to the sum
    int second_node;///the second node which contributes to the sum

    dfs_ret_t(int id,int last_sum,int fahrest_len,int fahrest_node,int last_node,int last_len,int first_node,int second_node){
        this->id = id;
        this->last_sum = last_sum;
        this->fahrest_len = fahrest_len;
        this->fahrest_node = fahrest_node;
        this->last_len = last_len;
        this->last_node = last_node;
        this->first_node = first_node;
        this->second_node = second_node;
    }
};

int n;
vector<int> graph[NMAX + 5];
bool viz[NMAX + 5];

dfs_ret_t dfs(int nod){
    viz[nod] = true;

    dfs_ret_t ans(nod,-inf,0,nod,0,-inf,0,0);

    vector<dfs_ret_t> tmp;

    for(auto it:graph[nod]){
        if(!viz[it]){
            tmp.push_back(dfs(it));
        }
    }

    if(graph[nod].size() >= 3){
        int d1 = -1,fst = 0;
        int d2 = -1,snd = 0;
        for(auto it:tmp){
            if(it.fahrest_len + 1 > d1){
                d2 = d1;
                snd = fst;
                d1 = it.fahrest_len + 1;
                fst = it.fahrest_node;
            }
            else if(it.fahrest_len + 1 > d2){
                d2 = it.fahrest_len + 1;
                snd = it.fahrest_node;
            }
        }
        ans.last_sum = d1 + d2;
        ans.first_node = fst;
        ans.second_node = snd;
        ans.last_node = nod;
        ans.last_len = 0;
    }

    for(auto it:tmp){
        if(ans.fahrest_len < it.fahrest_len + 1){
            ans.fahrest_len = it.fahrest_len + 1;
            ans.fahrest_node = it.fahrest_node;
        }
    }

    for(auto it:tmp){
        if(it.last_len + 1 > ans.last_len || (it.last_len + 1 == ans.last_len && it.last_sum >= ans.last_sum)){
            ans.last_len = it.last_len + 1;
            ans.last_node = it.last_node;
            ans.last_sum = it.last_sum;
            ans.first_node = it.first_node;
            ans.second_node = it.second_node;
        }
    }

    return ans;
}

int main(){

    scanf("%d",&n);

    for(int i = 1; i < n; i++){
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs_ret_t a = dfs(1);
    memset(viz,0,sizeof(viz));
    dfs_ret_t b = dfs(a.last_node);
    memset(viz,0,sizeof(viz));
    a = dfs(b.last_node);

//    printf("\n\n\n\n%d %d\n\n\n\n",a.last_node,b.last_node);
//    printf("\n\n\n\n%d %d\n\n\n\n",b.first_node,b.second_node);

    printf("%d %d\n",a.first_node,b.first_node);
    printf("%d %d\n",a.second_node,b.second_node);

    return 0;
}