#include <cstdio>
#include <vector>

using namespace std;

const int NMAX = 1e3;
const int MMAX = 1e4;

int n,m;
vector<int> graph[NMAX + 5];
int match[NMAX + 5];
int gr[NMAX + 5];
bool near[NMAX + 5];

int main(){

    scanf("%d %d",&n,&m);

    while(m--){
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    for(int i = 1;i <= n;i++){
        if((int)graph[i].size() * 2 + 1 >= n){
            for(int i = 1;i <= n;i++){
                match[i] = -1;
                gr[i] = graph[i].size();
                near[i] = false;
            }

            near[i] = true;
            for(auto it:graph[i]){
                near[it] = true;
            }

            int solved = 1 + (int)graph[i].size();

            while(1){
                int node = -1;

                for(auto it:graph[i]){
                    if((node == - 1 || gr[it] < gr[node]) && (gr[it] > 1) && match[it] == -1){
                        node = it;
                    }
                }
                
                if(node == -1){
                    break;
                }
                for(auto it:graph[node]){
                    if(it != i && !near[it] && match[it] == -1){
                        match[node] = it;
                        match[it] = node;
                        solved++;
                        break;
                    }
                }

                if(match[node] == -1){
                    gr[node] = 0;
                }
            }
            printf("\n"); 
            if(solved == n){
                printf("Yes\n");
                printf("%d %d\n",i,(int)graph[i].size());
                for(auto it:graph[i]){
                    printf("%d %d\n",it,match[it]);
                }
                return 0;
            }
        }
    }

    printf("No\n");

    return 0;
}
