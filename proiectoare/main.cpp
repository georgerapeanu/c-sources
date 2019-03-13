#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

FILE *f = fopen("proiectoare.in","r");
FILE *g = fopen("proiectoare.out","w");

const int NMAX = 1e5;
const int KMAX = 1e5;

struct segm_t{
    int x,y;
    int id;
    bool operator < (const segm_t &other)const{
        if(x != other.x){
            return x < other.x;
        }
        return y < other.y;
    }
};
int n,q,k;
segm_t segm[NMAX + 5];

segm_t sta[NMAX + 5];
int len;

int father[NMAX + 5];

vector<int> graph[NMAX + 5];

int fahrest[NMAX + 5];

vector<int> chestii;

void dfs(int nod){
    chestii.push_back(nod);

    fahrest[nod] = segm[chestii[max(0,(int)chestii.size() - k)]].y;

    for(auto it:graph[nod]){
        dfs(it);
    }

    chestii.pop_back();
}

int ans[NMAX + 5];

int main(){

    fscanf(f,"%d %d %d",&n,&q,&k);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d %d",&segm[i].x,&segm[i].y);
        segm[i].id = i;
    }

    sort(segm + 1,segm + 1 + n);


    for(int i = n;i;i--){
        while(len > 0 && sta[len].y <= segm[i].y){
            len--;
        }

        sta[++len] = segm[i];

        int st = 0,dr = len;

        while(dr - st > 1){
            int mid = (st + dr) / 2;
            if(sta[mid].x <= segm[i].y){
                dr = mid;
            }
            else{
                st = mid;
            }
        }

        father[segm[i].id] = sta[dr].id;
    }

    for(int i = 1;i <= n;i++){
        if(father[i] != i){
            graph[father[i]].push_back(i);
        }
    }

    for(int i = 1;i <= n;i++){
        if(father[i] == i){
            dfs(i);
        }
    }





    fclose(f);
    fclose(g);

    return 0;
}
