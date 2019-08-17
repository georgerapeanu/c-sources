#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("aimin.in","r");
FILE *g = fopen("aimin.out","w");

const int NMAX = 2e5;
const int LMAX = 1e8;


int n;
int len;
int st[NMAX + 5];
int height[NMAX + 5];

int main(){

    fscanf(f,"%d",&n);
    
    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&height[i]);
    }

    st[len = 1] = height[1];

    for(int i = 2;i <= n;i++){
        while(len >= 2 && st[len - 1] < max(st[len],height[i]) + 2){
            len--;
        }
        st[++len] = height[i];
        st[len - 1] = 1 + max(height[i],st[len - 1]);
    }

    fprintf(g,"%d\n",st[1]);

    fclose(f);
    fclose(g);

    return 0;
}
