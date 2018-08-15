#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("copaci.in","r");
FILE *g = fopen("copaci.out","w");

int N;
pair<int,int> P[100005];
long long B,A,I;

int gcd(int a,int b){
    if(!b){
        return a;
    }
    return gcd(b,a % b);
}

long long det(pair<int,int> a,pair<int,int> b,pair<int,int> c){
    return (1LL * a.first * b.second + 1LL * b.first * c.second + 1LL * c.first * a.second) -
           (1LL * a.first * c.second + 1LL * b.first * a.second + 1LL * c.first * b.second);
}

int main(){
    fscanf(f,"%d",&N);

    for(int i = 1;i <= N;i++){
        fscanf(f,"%d %d",&P[i].first,&P[i].second);
    }

    B = - N;

    for(int i = 1;i <= N;i++){
        B += gcd(abs(P[i].first - P[i % N + 1].first),abs(P[i].second - P[i % N + 1].second)) + 1;
    }

    for(int i = 2;i < N;i++){
        A += det(P[1],P[i],P[i + 1]);
    }

    I = (A + 2 - B) / 2;

    fprintf(g,"%lld",I);

    fclose(f);
    fclose(g);

    return 0;
}
