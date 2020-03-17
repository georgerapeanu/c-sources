#include <cstdio>
#include <algorithm>
#include <unordered_map>

using namespace std;

FILE *f = fopen("avarcolaci.in","r");
FILE *g = fopen("avarcolaci.ok","w");

int t;
int n;

int main(){
    fscanf(f,"%d",&t);


    for(int test = 1;test <= t;test++){
        fscanf(f,"%d",&n);
        unordered_map<int,int> tmp;
        for(int i = 1;i <= 2 * n;i++){
            int a;
            fscanf(f,"%d",&a);
            tmp[a]++;
        }
        for(auto it:tmp){
            if(it.second > n){
                fprintf(g,"%d\n",it.first);
                goto done;
            }
        }
        fprintf(g,"Mozart\n");
        done:;
    }

    fclose(f);
    fclose(g);

    return 0;
}
