#include <cstdio>
#include <vector>
#include <cstdlib>
using namespace std;
long long p,k;
vector<long long> tmp;
int pas;
void solve(long long p){
    if(0 <= p && p < k){
        tmp.push_back(p);
        return ;
    }
    if(pas > 1e6){
        printf("-1");
        exit(0);
    }
    long long q1 = (k - p) / k;
    if(q1 * k + p < k && q1 * k + p >= 0){
        tmp.push_back(q1 * k + p);
        pas++;
        solve(q1);
        pas--;
        return ;
    }
    q1++;
    if(q1 * k + p < k && q1 * k + p >= 0){
        tmp.push_back(q1 * k + p);
        pas++;
        solve(q1);
        pas--;
        return ;
    }
    q1 -= 2;
    if(q1 * k + p < k && q1 * k + p >= 0){
        tmp.push_back(q1 * k + p);
        pas++;
        solve(q1);
        pas--;
        return;
    }
}
int main()
{
    scanf("%I64d %I64d",&p,&k);
    solve(p);
    printf("%d\n",(int)tmp.size());
    for(auto it:tmp){
        printf("%I64d ",it);
    }
    return 0;
}
