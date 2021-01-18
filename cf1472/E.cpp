#include <bits/stdc++.h>

using namespace std;

struct photo_t{
    int h,w;
    int id;

    bool operator < (const photo_t &other)const{
        if(h != other.h){
            return h < other.h;
        }
        if(w != other.w){
            return w < other.w;
        }
        return id < other.id;
    }
};

const int NMAX = 2e5;

int t;
int n;
int ans[NMAX + 5];
photo_t photos[NMAX + 5];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);
        for(int i = 1;i <= n;i++){
            scanf("%d %d",&photos[i].h,&photos[i].w);
            if(photos[i].h > photos[i].w){
                swap(photos[i].h,photos[i].w);
            }
            photos[i].id = i;
        }

        sort(photos + 1,photos + 1 + n);
    
        int small_w = 1e9,id = -1;
        int last_processed = 0;

        for(int i = 1;i <= n;i++){
            while(photos[last_processed + 1].h < photos[i].h){
                last_processed++;
                if(small_w > photos[last_processed].w){
                    small_w = photos[last_processed].w;
                    id = photos[last_processed].id;
                }
            }
            ans[photos[i].id] = (photos[i].w <= small_w ? -1:id);
        }
        
        for(int i = 1;i <= n;i++){
            printf("%d ",ans[i]);
        }
        printf("\n");
    }

    return 0;
}
