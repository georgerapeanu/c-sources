#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n;
long long x;
long long v[1005];

///max sum is n * 1e12
///number of sums is 2^n
///2^n should be < n * 1e12
///so n <= 46

vector<pair<long long,int> > a,b;

void get_sums(vector<long long> &aa,vector<pair<long long,int> > &a){
    for(int conf = 0;conf < (1 << ((int)aa.size()));conf++){
        long long sum = 0;
        for(int i = 0;i < (int)aa.size();i++){
            if((conf >> i) & 1){
                sum += aa[i];
            }
        }
        a.push_back({sum,conf});
    }
}

int main(){

    scanf("%d %lld",&n,&x);

    for(int i = 1;i <= n;i++){
        scanf("%lld",&v[i]);
    }

    vector<long long> aa,bb;

    for(int i = 1;i <= n / 2;i++){
        aa.push_back(v[i]);
    }

    for(int i = n / 2 + 1;i <= n;i++){
        bb.push_back(v[i]);
    }


    get_sums(aa,a);
    get_sums(bb,b);

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    int j = (int)b.size() - 1;

    for(int i = 0;i < (int)a.size();i++){
        while(j >= 0 && b[j].first + a[i].first > x){
            j--;
        }

        if(j < 0){
            break;
        }

        if(a[i].first + b[j].first == x){
            vector<long long> ans;
            for(int t = 0;t < (int)aa.size();t++){
                if((a[i].second >> t) & 1){
                    ans.push_back(aa[t]);
                }
            }
            for(int t = 0;t < (int)bb.size();t++){
                if((b[j].second >> t) & 1){
                    ans.push_back(bb[t]);
                }
            }
            sort(ans.begin(),ans.end());
            printf("%d\n",(int)ans.size());
            for(auto it:ans)printf("%lld ",it);
            return 0;
        }
    }

    printf("-1");

    return 0;
}
