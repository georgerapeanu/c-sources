#include <bits/stdc++.h>

using namespace std;

int t;
int d,k;

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&d,&k);

        int z = (((long double)d) / k) / sqrt(2);

        int x = z * k;
        int y = z * k;

        if(1LL * x * x + 1LL * (y + k) * (y + k) <= 1LL * d * d){
            printf("Ashish\n");
        }
        else{
            printf("Utkarsh\n");
        }
    }

    return 0;
}
