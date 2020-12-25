#include <bits/stdc++.h>

using namespace std;

int n,q;
int cnt[50];
long long tmp[50];

long long get_cost(int x,int y,int cnt){
    if(x >= y){
        return 0;
    }
    return ((1LL << (y - x)) - 1) * cnt;
}

int main(){

    scanf("%d %d",&n,&q);

    for(int i = 0;i < n;i++){
        scanf("%d",&cnt[i]);
    }

    while(q--){
        int t,x,y;
        scanf("%d %d %d",&t,&x,&y);

        if(t == 1){
            cnt[x] = y;
        }
        else{
            for(int i = 0;i < n;i++){
                tmp[i] = cnt[i];
            }

            long long small = 0;
            long long ans = 0;
            long long cnt_small = 0;

            for(int i = 0;i <= x;i++){
                small += (1LL << i) * tmp[i];
                cnt_small += tmp[i];
                y -= tmp[i];
            }

            if(y <= 0){
                printf("0\n");
                continue;
            }

            int bit = -1;

            for(int i = x + 1;i < n;i++){
                if(y >= (1LL << (i - x)) * tmp[i]){
                    y -= (1LL << (i - x)) * tmp[i];
                    tmp[x] += (1LL << (i - x)) * tmp[i];
                    cnt_small += (1LL << (i - x)) * tmp[i];
                    small += (1LL << i) * tmp[i];
                    ans += get_cost(x,i,tmp[i]);
                    tmp[i] = 0;
                }
                else{
                    bit = i;
                    break;
                }
            }
            
            if(bit == -1){
                if(small - cnt_small >= y){
                    ans += y;
                    y = 0;
                }
                else{
                    ans = -1;
                }
            }
            else{
                long long base_ans = ans;
                ans = 1e18;
                if(small - cnt_small >= y){
                    ans = min(ans,base_ans + y);
                }
                base_ans += 1;
                tmp[bit]--;
                tmp[bit - 1] += 2;
                if(bit - 1 <= x){
                    cnt_small += 2;
                    small += (1LL << (bit - 1)) * 2;
                }
                for(int i = bit - 1;i > x;i--){
                    int aux = y / (1LL << (i - x));
                    y -= aux * (1LL << (i - x));
                    base_ans += get_cost(x,i,aux);
                    tmp[i] -= aux;
                    tmp[x] += aux * (1LL << (i - x));
                    cnt_small += aux * (1LL << (i - x));
                    small += aux * (1LL << i);
                    if(y > 0){
                        if(y <= small - cnt_small){
                            ans = min(ans,base_ans + y);
                        }
                        base_ans++;
                        tmp[i]--;
                        tmp[i - 1] += 2;
                        if(i - 1 <= x){
                            cnt_small += 2;
                            small += (1LL << (i - 1)) * 2;
                        }
                    }
                    else{
                        break;
                    }
                }
                if(y <= small - cnt_small){
                    ans = min(ans,base_ans + y);
                }
            }
            printf("%lld\n",ans);

        }
    }

    return 0;
}
