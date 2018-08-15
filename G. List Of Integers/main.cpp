#include <cstdio>
#include <vector>
using namespace std;
int T;
vector<int> D;
void get_div(int x){
    D.clear();
    for(int i = 2;1LL * i * i <= x;i++){
        if(x % i == 0){
            D.push_back(i);
            while(x % i == 0){
                x /= i;
            }
        }
    }
    if(x != 1){
        D.push_back(x);
    }
}
int get_less(int x){
    int rez = 0;
    for(int conf = 0;conf < (1 << D.size());conf++){
        int tmp = 1,sgn = 1;
        for(int i = 0;i < (int)D.size();i++){
            if((conf >> i) & 1){
                tmp *= D[i];
                sgn *= -1;
            }
        }
        rez += (x / tmp) * sgn;
    }
    return rez;
}
int main(){
    scanf("%d",&T);
    while(T--){
        int x,p,k;
        scanf("%d %d %d",&x,&p,&k);
        get_div(p);
        int tmp = get_less(x);
        int st = x,dr = 1e9;
        while(dr - st > 1){
            int mid = (st + dr) / 2;
            if(get_less(mid) - tmp >= k){
                dr = mid;
            }
            else{
                st = mid;
            }
        }
        printf("%d\n",dr);
    }
    return 0;
}
