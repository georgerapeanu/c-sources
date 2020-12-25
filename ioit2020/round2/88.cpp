#include <cstdio>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>


using namespace std;

int n,l;
vector<int> power;
vector<int> x,e;

vector<int> ans;
int best;

vector<int> cf = {1,2,3,4,5,6,7,8,9};

void btr(int pas,int sum){
    if(pas >= (int)power.size()){
        if(sum > best){
            best = sum;
            ans = power;
        }
        return ;
    }

    if(best > (l - pas) * 9 + sum){
        return ;
    }

    if(power[pas]){
        btr(pas + 1,sum + power[pas]);
        return;
    }



    for(auto j:cf){
        if(j > pas){
            continue;
        }
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

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(cf.begin(),cf.end(),gen);

    btr(0,0);

    for(auto it:ans)printf("%d ",it);

    return 0;
}
