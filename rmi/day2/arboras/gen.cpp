#include <bits/stdc++.h>

using namespace std;

FILE *g = fopen("arboras.in","w");

int main(){
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    int n = gen() % 10 + 2;

    fprintf(g,"%d\n",n);
    
    for(int i = 1;i < n;i++){
        fprintf(g,"%d ",int(gen() % i));
    }
    fprintf(g,"\n");
    
    for(int i = 1;i < n;i++){
        fprintf(g,"%d ",int(gen() % 4));
    }
    fprintf(g,"\n");

    int q = gen() % 20;

    fprintf(g,"%d\n",q);

    for(int i = 1;i <= q;i++){
        fprintf(g,"%d %d\n",int(gen() % (n - 1)) + 1,int(gen() % 4) + 1);
    }


    return 0;
}
