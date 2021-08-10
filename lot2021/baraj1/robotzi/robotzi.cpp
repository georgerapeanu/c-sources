#include <bits/stdc++.h>

using namespace std;

int main(){

    printf("X N X -> Minor\n");
    printf("X Y X -> Major\n");

    printf("? N ? -> 15\n");
    printf("? Y ? -> 13\n");///Y biased

    for(int l = 1;l <= 28;l++){
        for(int m = 1;m <= 28;m++){
            for(int r = 1;r <= 28;r++){
                if(m <= 13){
                    if(max(l,r) <= m){
                        if(max(l,r) - 1 < 1){
                            printf("%d %d %d -> Major\n",l,m,r);
                        }else{
                            printf("%d %d %d -> %d\n",l,m,r,max(l,r) - 1);
                        }
                    }else if(min(l,r) > m){
                        printf("%d %d %d -> %d\n",l,m,r,min(l,r));
                    }
                }else{
                    if(max(l,r) <= m){
                        printf("%d %d %d -> %d\n",l,m,r,max(l,r));
                    }else if(min(l,r) > m){
                        if(min(l,r) + 1 > 28){
                            printf("%d %d %d -> Minor\n",l,m,r);
                        }else{
                            printf("%d %d %d -> %d\n",l,m,r,min(l,r) + 1);
                        }
                    }
                }
            }
        }
    }

    for(int m = 1;m <= 28;m++){
        for(int r = 1;r <= 28;r++){
            if(m > r){
                if(m <= 13){
                    printf("X %d %d -> %d\n",m,r,r);
                    printf("%d %d X -> %d\n",r,m,r);
                }             
            }else if(m < r){
                if(m > 13){
                    printf("X %d %d -> %d\n",m,r,r);
                    printf("%d %d X -> %d\n",r,m,r);
                }
            }else{
                if(m <= 13){
                    if(m - 1 < 1){
                        printf("X %d %d -> Major\n",m,r);
                        printf("%d %d X -> Major\n",r,m);
                    }else{
                        printf("X %d %d -> %d\n",m,r,m - 1);
                        printf("%d %d X -> %d\n",r,m,m - 1);
                    }
                }
                else{
                    if(m + 1 > 28){
                        printf("X %d %d -> Minor\n",m,r);
                        printf("%d %d X -> Minor\n",r,m);
                    }else{
                        printf("X %d %d -> %d\n",m,r,m + 1);
                        printf("%d %d X -> %d\n",r,m,m + 1);
                    }
                }
            }
        }
    }



    for(int i = 1;i <= 28;i++){
        printf("? %d ? -> %d\n",i,i);
    }
    printf("? Y ? -> Y\n");
    printf("? N ? -> N\n");

    return 0;
}
