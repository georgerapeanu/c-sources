#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

FILE *f = fopen("dreptunghiuri.in","r");
FILE *g = fopen("dreptunghiuri.ok","w");

int n,m;
map<pair<pair<long long,long long>,long long>,int> v;

int main(){
    fscanf(f,"%d %d",&n,&m);

    long long ans = 0;

    for(int x = 0;x < n;x++){
        for(int y = 0;y < m;y++){
            for(int xx = x;xx < n;xx++){
                for(int yy = 0;yy < m;yy++){
                    if(x == xx && y >= yy){
                        continue;
                    }
                    pair<pair<long long,long long>,long long> target = {{x + xx,y + yy},1LL * (xx - x) * (xx - x) + 1LL * (yy - y) * (yy - y)};
                    ans += v[target];
                    v[target]++;
                }
            }
        }
    }

    fprintf(g,"%lld\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
