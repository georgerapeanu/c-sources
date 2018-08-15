#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int N;
vector<int> G[305];
int label[305];
unsigned long long min_leafs_for_label[305];
int link[305];
int longest[305];
int num_sons_per_label[305];
int num_sons[305];

int furthest(int nod,int tata){
    longest[nod] = 1;
    link[nod] = 0;
    int far = nod;
    for(auto it:G[nod]){
        if(it != tata){
            int tmp = furthest(it,nod);
            if(longest[nod] < longest[it] + 1){
                longest[nod] = longest[it] + 1;
                link[nod] = it;
                far = tmp;
            }
        }
    }
    return far;
}

vector<int> get_diameter(int nod){
    vector<int> ans;
    while(nod){
        ans.push_back(nod);
        nod = link[nod];
    }
    return ans;
}

pair<int,unsigned long long> propagate_labes(vector<int> diameter){
    memset(label,0,sizeof(label));
    memset(num_sons_per_label,0,sizeof(num_sons_per_label));
    memset(num_sons,0,sizeof(num_sons));
    memset(min_leafs_for_label,0,sizeof(min_leafs_for_label));

    queue<int> Q;
    if(diameter.size() & 1){
        Q.push(diameter[diameter.size() / 2]);
        label[ diameter[diameter.size() / 2] ] = 1;
    }
    else{
        Q.push(diameter[diameter.size() / 2]);
        Q.push(diameter[diameter.size() / 2 - 1]);
        label[ diameter[diameter.size() / 2] ] = 1;        label[ diameter[diameter.size() / 2 - 1] ] = 1;
    }

    while(!Q.empty()){
        int nod = Q.front();
        Q.pop();
        for(auto it:G[nod]){
            if(!label[it]){
                label[it] = label[nod] + 1;
                num_sons[nod]++;
                Q.push(it);
            }
        }
    }

    int max_label = 0;

    for(int i = 1;i <= N;i++){
        num_sons_per_label[ label[i] ] = max(num_sons_per_label[ label[i] ] , num_sons[i]);
        max_label = max(max_label,label[i]);
    }

    min_leafs_for_label[max_label] = 1;
    for(int i = max_label - 1;i >= 0;i--){
        min_leafs_for_label[i] = (unsigned long long)min_leafs_for_label[i + 1] * num_sons_per_label[i];
    }
    return {diameter.size() / 2 + diameter.size() % 2,(unsigned long long)min_leafs_for_label[1] * ( (unsigned long long)((diameter.size()) % 2 == 0) + 1)};
}

int main(){

    cin >> N;

    for(int i = 1;i < N;i++){
        int x,y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    pair<int,unsigned long long> ans = {1 << 30,-1};

    int a = furthest(1,0);
    int b = furthest(a,0);
    ans = propagate_labes(get_diameter(a));

    int diameter_size = get_diameter(a).size();

    for(int i = 1;i <= N;i++){

        stack<int> S;
        S.push(i);

        while(1){
            G[S.top()].push_back(N + 1);
            G[N + 1].push_back(S.top());
            S.push(++N);
            int a = furthest(1,0);
            int b = furthest(a,0);
            ans = min(ans,propagate_labes(get_diameter(a)));
            if(get_diameter(a).size() > diameter_size){
                break;
            }
        }
        while(S.size() > 1){
            int x = S.top();S.pop();
            G[S.top()].pop_back();
            G[x].pop_back();
            N--;
        }
        int a = furthest(1,0);
        int b = furthest(a,0);
        ans = min( ans , propagate_labes(get_diameter(a)) );
    }

    cout << ans.first << " " << ans.second;

    return 0;
}
