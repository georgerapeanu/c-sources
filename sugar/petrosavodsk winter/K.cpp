#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int VMAX = 1e9;

int n;
bool orig[NMAX + 5];
bool changeable[NMAX + 5];
int gr[NMAX + 5];
int remap[NMAX + 5];
pair<int,int> edges[NMAX + 5];

int main(){

    freopen("in","r",stdin);
    freopen("out","w",stdout);

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        int val;
        scanf("%d",&val);    
        changeable[i] = val;
        orig[i] = val;
        remap[i] = i;
    }

    int xo = n;

    for(int i = 1;i < n;i++){
        scanf("%d %d",&edges[i].first,&edges[i].second);
        gr[edges[i].first]++;
        gr[edges[i].second]++;
        xo ^= edges[i].first;
        xo ^= edges[i].second;
    }

    if(xo == 0){
        printf("%d\n",n);
        for(int i = 1;i < n;i++){
            printf("%d %d\n",remap[edges[i].first],remap[edges[i].second]);
        }
        return 0;
    }

    bool found = false;

    for(int i = 1;i <= n;i++){
        changeable[i] &= (gr[i] % 2 == 1);
        if(changeable[i] == true && ((xo ^ i) > n || (xo ^ i) == i)){
               remap[i] = (xo ^ i);
               found = true;
               break;
        }
        else if(changeable[i] == true && (xo ^ i) <= n && (xo ^ i) > 0 && orig[xo ^ i] == true && gr[xo ^ i] % 2 == 0){
            remap[xo ^ i] ^= 1 << 25;
            remap[i] = (xo ^ i);
            found = true;
            break;
        }
    }

    if(found){
        printf("%d\n",n);
        for(int i = 1;i < n;i++){
            printf("%d %d\n",remap[edges[i].first],remap[edges[i].second]);
        }
        return 0;
    }

    int x = -1,y = -1,z = -1;

    for(int i = 1;i <= n;i++){
        if(changeable[i] == true){
            if(x == -1){
                x = i;
            }
            else if(y == -1){
                y = i;
            }
            else if(z == -1){
                z = i;
            }
        }
    }

    if((xo ^ x ^ y) == 0){
        swap(y,z);
    }

    if(y != -1){
        remap[x] = (1 << 28);
        remap[y] = (1 << 28) ^ (xo ^ x ^ y);
        printf("%d\n",n);
        for(int i = 1;i < n;i++){
            printf("%d %d\n",remap[edges[i].first],remap[edges[i].second]);
        }
    }
    else{
        printf("-1\n");
    }


    return 0;
}

