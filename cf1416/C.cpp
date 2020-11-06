#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int n;

vector<vector<int> > buckets;

int main(){

    scanf("%d",&n);

    vector<int> a;

    for(int i = 1;i <= n;i++){
        int val;
        scanf("%d",&val);
        a.push_back(val);
    }

    buckets.push_back(a);
    int ans = 0;
    long long inv = 0;

    for(int h = 30;h >= 0;h--){
        long long inv0 = 0;
        long long inv1 = 0;
        vector<vector<int> > new_buckets;

        for(auto it:buckets){
            vector<int> tmp0,tmp1;
            int cnt0 = 0;
            int cnt1 = 0;
            for(auto it2:it){
                if((it2 >> h) & 1){
                    tmp1.push_back(it2);
                    cnt1++;
                    inv1 += cnt0;
                }
                else{
                    tmp0.push_back(it2);
                    cnt0++;
                    inv0 += cnt1;
                }
            }
            if(tmp0.size()){
                new_buckets.push_back(tmp0);
            }
            if(tmp1.size()){
                new_buckets.push_back(tmp1);
            }
        }

        if(inv1 < inv0){
            ans |= (1 << h);
            inv += inv1;
        }
        else{
            inv += inv0;
        }
        buckets.swap(new_buckets);
    }

    printf("%lld %d",inv,ans);


    return 0;
}
