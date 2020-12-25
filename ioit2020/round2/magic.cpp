#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n,l;
vector<int> power;
vector<int> x,e;

vector<int> ans;
int best;
int cnt;

void btr(int pas,int sum){
    if(pas >= (int)power.size()){
        if(sum > best){
            best = sum;
            ans = power;
        }
        cnt++;
        return ;
    }

    if(power[pas]){
        btr(pas + 1,sum + power[pas]);
        return;
    }

    for(int j = min(pas,9);j >= 1;j--){
        if(power[pas - j] % j == 0 || j % power[pas - j] == 0){
            power[pas] = j;
            btr(pas + 1,sum + j);
            power[pas] = 0;
        }
    }
}

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

    for(int i = 0;i < n;i++){
        power[x[i]] = e[i];
    }

    for(int i = 1;i < 10;i++){
        power[0] = i;
        btr(0,0);
    }
    fprintf(stderr,"deb %d %d\n",cnt,best);

    for(auto it:ans)printf("%d ",it);

    return 0;
}
