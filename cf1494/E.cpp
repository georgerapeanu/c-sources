#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int n,m;
map<pair<int,int>,int> edges;
set<int> graph[NMAX + 5];
int cnt_edges;
int cnt_equal_edges;

void add(int a,int b,int c){
    edges[{a,b}] = c;
    graph[a].insert(b);
    if(graph[b].count(a)){
        cnt_edges++;
        if(edges[{b,a}] == edges[{a,b}]){
            cnt_equal_edges++;    
        }
    }
}

void remove(int a,int b){
    if(graph[b].count(a)){
        cnt_edges--;
        if(edges[{b,a}] == edges[{a,b}]){
            cnt_equal_edges--;
        }
    }
    edges.erase({a,b});
    graph[a].erase(b);
}


int main(){

    scanf("%d %d\n",&n,&m);

    while(m--){
        char c;
        int u,v;
        char w;
        scanf("%c ",&c);
        if(c == '+'){
            scanf("%d %d %c\n",&u,&v,&w);
            add(u,v,w);
        }else if(c == '-'){
            scanf("%d %d\n",&u,&v);
            remove(u,v);
        }else{
            int k;
            scanf("%d\n",&k);
            k--;
            if(cnt_equal_edges || (cnt_edges && k % 2 == 0)){
                printf("YES\n");
            }else{
                printf("NO\n");
            }
        }
    }

    return 0;
}
