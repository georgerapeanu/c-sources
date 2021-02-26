#include <bits/stdc++.h>

using namespace std;

struct point_t{
    long long x,y;
    bool operator <= (const point_t &other)const{
        return y  * other.x <= other.y * x;
    }
    bool operator < (const point_t &other)const{
        return y  * other.x < other.y * x;
    }
};

const int NMAX = 2e5;

int n;
point_t v[NMAX + 5];
int st[NMAX + 5];
int len;

int main(){
    
    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        v[i].x = i;
        scanf("%lld",&v[i].y);
    }
    
    reverse(v + 1,v + 1 + n);

    for(int i = 1;i <= n;i++){
        while(len > 0 && v[st[len]] <= v[i]){
            len--;
        }
        st[++len] = i;
    }

    int ans = len;

    for(int i = len;i >= 1;i--){
        ///erase i

        point_t val;

        if(i == len){
            val.x = 1;
            val.y = 0;
        }else{
            val = v[st[i + 1]];
        }
        int bonus_length = -1;

        for(int j = st[i] - 1;j > st[i - 1];j--){
            if(val < v[j]){
                val = v[j];
                bonus_length++;
            }
        }
        ans = max(ans,bonus_length + len);
    }

    printf("%d\n",ans);

    return 0;
}
