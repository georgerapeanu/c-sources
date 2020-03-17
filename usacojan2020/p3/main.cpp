#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("falling.in","r");
FILE *g = fopen("falling.out","w");

struct frac_t{
    long long a,b;

    bool operator < (const frac_t &other){
        return a * other.b < b * other.a;
    }

    bool operator <= (const frac_t &other){
        return a * other.b < b * other.a;
    }
};

const int NMAX = 2e5;

int n;
pair<int,int> eq[NMAX + 5];
frac_t sect[NMAX + 5];

int main(){

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&eq[i].second);
        eq[i].first = -i;
    }

    sort(eq + 1,eq + 1 + n,[&](pair<int,int> a,pair<int,int> b){if(a.second != b.second)return a.second < b.second;return a < b;});

    int len = 0;

    for(int i = 1;i <= n;i++){
        while(len > 1 && frac_t(eq[len].second - eq[i].second,eq[i].first - eq[len].first) <= sect[len]){
            add_edge(frac_t(eq[len].second - eq[i].second,eq[i].first - eq[len].first),-eq[len].first,-eq[i].first);
            len--;
        }
        if(len){
            add_edge(frac_t(eq[len].second - eq[i].second,eq[i].first - eq[len].first),-eq[len].first,-eq[i].first);
        }
        eq[++len] = eq[i];
        sect[len] = (len == 1 {1e9,1}:{eq[len - 1].second - eq[len].second,eq[len].first - eq[len - 1].first});
    }

    fclose(f);
    fclose(g);

    return 0;
}
