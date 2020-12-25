#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

string v;
void init(int n, const char s[]) {
    
    for(int i = 0;i < n;i++){
        v += s[i];
    }

    return;
}

int query(int i, int k) {
    
    if(i + (1 << k) - 1 >= (int)v.size()){
        return 0;
    }

    for(int pos = 0;pos < (1 << k);pos++){
        int rev_pos = 0;
        for(int i = 0;i < k;i++){
            rev_pos = rev_pos * 2 + ((pos >> i) & 1);
        }
        if(v[i + pos] != v[i + rev_pos]){
            return 0;
        }
    }

    return 1;
}

FILE *f = fopen("brperm.in","r");
FILE *g = fopen("brperm.out","w");

char s[500005];

int main(){
    
    int n,q;
    fscanf(f,"%d\n",&n);
    fgets(s,500005,f);

    fscanf(f,"%d",&q);

    init(n,s);

    for(int i = 1;i <= q;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        fprintf(g,"%d\n",query(x,y));
    }

    fclose(f);
    fclose(g);

    return 0;
}
