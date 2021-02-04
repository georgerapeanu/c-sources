#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n,l;
vector<int> power;
vector<int> x,e;

int main(){

    scanf("%d %d",&n,&l);

    x = vector<int>(n,0);
    e = vector<int>(n,0);
    power = vector<int>(l,0);

    for(auto &it:x){
        scanf("%d",&it);
    }
    for(auto &it:e){
        scanf("%d",&it);
    }

    for(int i = 0; i < n;i++){
        power[x[i]] = e[i];
    }

    for(int i = 0;i < l;i++){
        if(power[i] != 0){
            continue;
        }
        for(int j = 1;j <= i && j <= 9;j++){
            if((power[i - j] % j == 0) || (j % power[i - j] == 0)){
                power[i] = j;
            }
        }
    }

    for(auto it:power){
        printf("%d ",it);
    }

    return 0;
}
