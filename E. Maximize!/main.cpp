#include <cstdio>
#include <algorithm>
using namespace std;
int last;
long long sum,cnt;
double bestans = (-1e9);
vector<int> V;
int N;
int main()
{
    scanf("%d",&N);
    V.push_back(0);
    while(N--){
        int t,x;
        scanf("%d",&t);
        if(t == 1){
            scanf("%d",&x);
            last = x;
            V.push_back(x);
        while(cnt < (int)V.size() - 2 && 1LL * (sum + V.back()) * (cnt + 2) > 1LL * (sum + V.back() + V[cnt + 1]) * (cnt + 1)){sum += V[++cnt];}bestans = max(bestans,V.back() - (double)(sum + V.back())/(cnt + 1));
        }else{printf("%.8f\n",bestans);}
    }
    return 0;
}
