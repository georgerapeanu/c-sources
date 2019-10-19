#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const int NMAX = 1e5;

int t;
int n;
int x[NMAX + 5];
int typ[NMAX + 5];
int val[NMAX + 5];

struct node_t{
    int total_sum;
    int best_pref_sum;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.total_sum = this->total_sum + other.total_sum;
        ans.best_pref_sum = max(this->best_pref_sum,this->total_sum + other.best_pref_sum);
        return ans;
    }

}aint[4 * NMAX + 5];

void init(int nod,int st,int dr){
    aint[nod] = {0,0};
    
    if(st == dr){
        return ;
    }
    
    int mid = (st + dr) / 2;

    init(nod * 2,st,mid);
    init(nod * 2 + 1,mid + 1,dr);
}

void update(int nod,int st,int dr,int pos,int val){
    if(dr < pos || st > pos){
        return ;
    }

    if(st == dr){
        aint[nod].total_sum += val;
        aint[nod].best_pref_sum += val;
        return ;
    }

    int mid = (st + dr) / 2;
    
    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

node_t query(int nod,int st,int dr){
    return aint[nod];
}

int main(){
    
    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&x[i]);
        }
    
        int cnt_elf = 0;

        for(int i = 1;i <= n;i++){
            scanf("%d",&typ[i]);
            cnt_elf += (typ[i] == 0);
        }
        
        for(int i = 1;i <= n;i++){
            scanf("%d",&val[i]);
        }

        init(1,1,n);
        set<pair<int,int> > disp_elfs;

        int posl = 1;

        for(int i = 1;i <= n;i++){
            if(typ[i] == 0){
                update(1,1,n,val[i],1);
            }
            else{
                update(1,1,n,val[i],-1);
            }
            cnt_elf -= (typ[i] == 0);
            if(cnt_elf > 0){
                printf("-1 ");
                continue;
            }
            if(query(1,1,n).best_pref_sum > 0){
                printf("-1 ");
                continue;
            }
            while(posl <= i){
                if(typ[posl] == 0){
                    disp_elfs.insert({val[posl],x[posl]});
                    posl++;
                    continue;
                }
                else{
                    pair<int,int> tmp = {-1,-1};
                    if(disp_elfs.lower_bound({val[posl],0}) != disp_elfs.end()){
                        tmp = *disp_elfs.lower_bound({val[posl],0});
                        disp_elfs.erase(tmp);
                        update(1,1,n,tmp.first,-1);
                    }
                    update(1,1,n,val[posl],1);
                    if(query(1,1,n).best_pref_sum <= 0){
                        posl++;
                        continue;
                    }
                    update(1,1,n,val[posl],-1);
                    if(tmp.first != -1){
                        update(1,1,n,tmp.first,1);
                        disp_elfs.insert(tmp);
                    }
                    break;
                }
            }
            printf("%d ",2 * x[i] - x[min(i,posl)]);
        }

        printf("\n");

    }


    return 0;
}
