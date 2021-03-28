#include <bits/stdc++.h>

using namespace std;

int q;
int u,v;


int main(){

    scanf("%d",&q);

    while(q--){
        scanf("%d %d",&u,&v);
        if(u > v){
            printf("NO\n");
            continue;
        }

        bool ok = true;

        for(int h = 30;h >= 0;h--){
            if((v >> h) & 1){
                if((u >> h) & 1){
                    u ^= (1 << h);
                    v ^= (1 << h);
                }else{
                    break;
                }
            }
        }

        int delta_cnt = 0;

        for(int h = 30;h >= 0;h--){
            delta_cnt += ((u >> h) & 1) - ((v >> h) & 1);
        }

        if(delta_cnt < 0){
            printf("NO\n");
            continue;
        }

        bool found = false;
        for(int h = 30;h >= 0;h--){
            if((u >> h) & 1){
                if(found && delta_cnt > 0){
                    delta_cnt--;
                    u ^= (1 << h);
                }
                if(found == false){
                    u += (1 << h);
                }
                found = true;
            }
        }
        
        ok = true;
        for(int h = 30;h >= 0;h--){
            if((v >> h) & 1){
                bool found = false;
                for(int h2 = h;h2 >= 0;h2--){
                    if((u >> h2) & 1){
                        u ^= (1 << h2);
                        found = true;
                        break;
                    }
                }
                if(found == false){
                    ok = false;
                    break;
                }
                v ^= (1 << h);
            }
        }


        printf(ok ? "YES\n":"NO\n");
    }

    return 0;
}
