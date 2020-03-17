#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("rufe.in","r");
FILE *g = fopen("rufe.out","w");

long long n,m,a,b;
long long k;

long long cnt_upper(long long n,long long m,long long a,long long b,long long d){
    long long fst_row = max(1LL,a - d);
    long long fst_col = min(m,b + d - (a - fst_row));
    long long mid_row = max(fst_row,min(a,a - (b + d - m)));
    long long mid_col = min(m,b + d - (a - mid_row));

    //printf("deb %lld%lld%lld%d\n",fst_row,fst_col,mid_row,mid_col);

    return 1LL * (mid_col + fst_col) * (mid_row - fst_row + 1) / 2 + 1LL * (a - mid_row) * m;
}

long long cnt_less(long long n,long long m,long long a,long long b,long long d){
    long long ans = 0;

    ///calculating prefix to the right
    //calculating upper
    ans += cnt_upper(n,m,a,b,d);
   // printf("1 %lld\n",ans);
    //calculating low
    ans += cnt_upper(n,m,n - a + 1,b,d);
    //printf("2 %lld\n",ans);
    //subtract mid because of calculating it twice
    ans -= (min(m,b + d));
    //printf("3 %lld\n",ans);
    ///calculating prefix to left
    //calculating upper
    ans -= 1LL * (m) * (a - max(a - d,1LL) + 1) - cnt_upper(n,m,a,m - b + 1,d);
    //printf("4 %lld\n",ans);
    //calculating low
    ans -= 1LL * (m) * (min(a + d,n) - a + 1) - cnt_upper(n,m,n - a + 1,m - b + 1,d);
    //printf("5 %lld\n",ans);
    //add mid back because of calculating it twice
    ans += (max(1LL,b - d) - 1);
    //printf("6 %lld\n",ans);

    return ans;
}

int main(){

    fscanf(f,"%lld%lld%lld%lld%lld",&n,&m,&a,&b,&k);

    long long st = 0,dr = n + m + 2;

    while(dr - st > 1){
        long long mid = (st + dr) / 2;

        if(1LL * n * m - (cnt_less(n,m,a,b,mid)) >= k){
            st = mid;
        }
        else{
            dr = mid;
        }
    }

    fprintf(g,"%lld\n",dr);

    fclose(f);
    fclose(g);

    return 0;
}
