#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("cadouri.in","r");
FILE *g = fopen("cadouri.out","w");

const int NMAX = 5e6;

int n,k;
pair<int,int> v[NMAX + 5];

int solve(pair<int,int> v[],int st,int dr,long long k){

    int lst = st - 1;

    for(int i = st;i < dr;i++){
        if(v[i] < v[dr]){
            swap(v[++lst],v[i]);
        }
    }

    swap(v[++lst],v[dr]);

    long long sum = 0;

    for(int i = st;i < lst;i++){
        sum += v[i].second;
    }

    if(sum < k && k <= sum + v[lst].second){
        return v[lst].first;
    }else if(k <= sum){
        return solve(v,st,lst - 1,k);
    }else{
        return solve(v,lst + 1,dr,k - sum - v[lst].second);
    }
}

int main(){

    long long m1,m2;
    unsigned int c1,c2;

    fscanf(f,"%d %d %d %d %d %lld",&n,&m1,&c1,&m2,&c2,&k);

    for(int i = 1;i <= n;i++){
        c1 = 5 * c1 + 1;
        c2 = 5 * c2 + 3;
        v[i].second = ((m2 * c2) >> 32) + 1;
        v[i].first = ((m1 * c1) >> 32) + 1;
    }

    fprintf(g,"%d\n",solve(v,1,n,k));

    fclose(f);
    fclose(g);

    return 0;
}
