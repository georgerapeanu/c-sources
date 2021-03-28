#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;

int n;
int v[NMAX + 5];
pair<int,int> values[NMAX + 5];
int nxt[NMAX + 5];
int ant[NMAX + 5];
bool taken[NMAX + 5];

int digit_sum(int value){
    int sum = 0;

    while(value){
        sum += value % 10;
        value /= 10;
    }

    return sum;
}

int main(){
  
    freopen("stergeri.in","r",stdin);
    freopen("stergeri.out","w",stdout);

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
        values[i] = {digit_sum(v[i]),i};
    }

    sort(values + 1,values + 1 + n);
    reverse(values + 1,values + 1 + n);

    for(int i = 1;i <= n;i++){
        ant[i] = i - 1;
        nxt[i - 1] = i;
    }
    nxt[n] = 0;
    ant[0] = n;

    int l = n + 1;
    int r = 0;

    int cnt_pasi = 0;
    int max_delete = 0;

    for(int i = 1;i <= n;i++){
        if(taken[values[i].second] == false){
            l = min(l,values[i].second);
            r = max(r,values[i].second);
        }
        if(i == n || values[i].first != values[i + 1].first){
            if(l <= r){
                cnt_pasi++;
                int local_delete = 0;

                for(int nod = l;nod <= r && nod != 0;nod = nxt[nod]){
                    taken[nod] = true;
                    local_delete++;
                    ant[nxt[nod]] = ant[nod];
                    nxt[ant[nod]] = nxt[nod];
                }

                max_delete = max(max_delete,local_delete);
            }
            l = n + 1;
            r = 0;
        }
    }

    printf("%d %d\n",cnt_pasi,max_delete);

    return 0;
}
