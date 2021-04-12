#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int MMAX = 1e5;

int c;
int n,m;
bool infected[NMAX + 5];
bool current[NMAX + 5];
int stuff[NMAX + 5];
vector<pair<int,int> > meets;
vector<int> graph[NMAX + 5];
int cnt_meets[NMAX + 5];
int answer[NMAX + 5];

int main(){
    scanf("%d",&c);
    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        int value;
        scanf("%d",&value);
        infected[i] = value;
        current[i] = value;
    }

    for(int i = 1;i <= m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        meets.push_back({x,y});
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    for(int i = m - 1;i >= 0;i--){
        int x = meets[i].first;
        int y = meets[i].second;
        if(current[x] == 0){
            current[y] = 0;
        }else if(current[y] == 0){
            current[x] = 0;
        }
    }

    if(c == 1){
        for(int i = 1;i <= n;i++){
            printf("%d",current[i]);
        }
        printf("\n");
    }else{
    
        for(int i = 1;i <= n;i++){
            answer[i] = 0;
            if(current[i] == 0){
                answer[i] = 1;
            }else{
                if(graph[i].empty()){
                    answer[i] = 0;
                    continue;
                }else if(current[graph[i][0]] == 1){
                    answer[i] = 1;
                    continue;
                }
                current[i] = 0;
                for(int j = 1;j <= n;j++){
                    stuff[j] = current[j];
                    cnt_meets[j] = graph[j].size();
                }
                for(auto it:meets){
                    int x = it.first;
                    int y = it.second;
                    if(stuff[x] || stuff[y]){
                        stuff[x] = stuff[y] = 1;
                    }
                    cnt_meets[x]--;
                    cnt_meets[y]--;
                    if(cnt_meets[x] == 0 && stuff[x] != infected[x]){
                        break;
                    }
                    if(cnt_meets[y] == 0 && stuff[y] != infected[y]){
                        break;
                    }
                }
                bool ok = true;
                for(int j = 1;j <= n;j++){
                    ok &= (infected[j] == stuff[j]);
                }
                if(ok){
                    answer[i] = 1;
                }else{
                    answer[i] = 0;
                }
                current[i] = 1;
            }
        }

        for(int i = 1;i <= n;i++){
            printf("%d",(answer[i] == 1));
        }
        printf("\n");
        
    }

    return 0;
}
