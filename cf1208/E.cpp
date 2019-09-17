#include <bits/stdc++.h>

using namespace std;

int n,w;
long long smen[int(1e6) + 5];
int a[(int)1e6 + 5];
int main() {
    
    scanf("%d %d",&n,&w);

    for(int i = 1;i <= n;i++){
        int l,ma = 0;

        scanf("%d",&l);
        for(int i = 1;i <= l;i++){
            scanf("%d",&a[i]);
            ma = max(ma,a[i]);
        }

        ///preffix of l
        deque<int> dq;
        int st = 1,dr = 0;
        for(int i = 1;i <= l;i++){
            while(dr < i){
                dr++;
                while(dq.empty() == false && a[dq.back()] < a[dr]){
                    dq.pop_back();
                }
                dq.push_back(dr);
            }
            while(st < l - (w - i)){
                if(dq.front() == st){
                    dq.pop_front();
                }
                st++;
            }
            if(a[dq.front()] >= 0 || ((i > l || i <= w - l) == false)){
                smen[i] += a[dq.front()];
                smen[i + 1] -= a[dq.front()];
            }
        }

        ///suffix of l(kinda)
        int suff_ma = 0;
        for(int i = w;i > w - l && i > l;i--){
            suff_ma = max(suff_ma,a[i - w + l]);
            if(suff_ma >= 0 || ((i > l || i <= w - l) == false)){
                smen[i] += suff_ma;
                smen[i + 1] -= suff_ma;
            }
        }

        ///the rest
        if(1 + l <= w - l){
            smen[1 + l] += ma;
            smen[w - l + 1] -= ma;
        }
    }

    for(int i = 1;i <= w;i++){
        smen[i] += smen[i - 1];
        printf("%lld ",smen[i]);
    }


    return 0;
}
