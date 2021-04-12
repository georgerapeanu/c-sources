#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

FILE *f = fopen("arbsat.in","r");
FILE *g = fopen("arbsat.out","w");

const int NMAX = 1e5;

int t;
int n;
vector<int> events[NMAX + 5];
pair<int,int> points[NMAX + 5];

int last_x[NMAX + 5];

class SegmentTree{
    int n;
    vector<int> aint;

public:
    SegmentTree(int n){
        this->n = n;
        aint = vector<int>(2 * n + 5);
    }

    void update(int pos,int value){
        for(aint[pos += n] = value;pos > 1;pos >>= 1){
            aint[pos >> 1] = max(aint[pos],aint[pos ^ 1]);
        }
    }

    int query(int l,int r){
        r++;
        int ans = 0;
        for(l += n,r += n;l < r;l >>= 1,r >>= 1){
            if(l & 1){
                ans = max(ans,aint[l++]);
            }
            if(r & 1){
                ans = max(ans,aint[--r]);
            }
        }

        return ans;
    }
};

int main(){

    fscanf(f,"%d",&t);


    while(t--){
        fscanf(f,"%d",&n);

        map<int,int> to_norm_x;
        map<int,int> to_norm_y;
        
        SegmentTree aint(n);

        for(int i = 1;i <= n;i++){
            fscanf(f,"%d %d",&points[i].first,&points[i].second);
            to_norm_x[points[i].first] = 0;
            to_norm_y[points[i].second] = 0;
            last_x[i] = 0;
            events[i].clear();
        }

        int lst_x = 0;
        int lst_y = 0;

        for(auto &it:to_norm_x){
            it.second = ++lst_x;
        }
        
        for(auto &it:to_norm_y){
            it.second = ++lst_y;
        }

        for(int i = 1;i <= n;i++){
            points[i].first = to_norm_x[points[i].first];
            points[i].second = to_norm_y[points[i].second];
            events[points[i].first].push_back(points[i].second);
        }

        bool ok = true;

        for(int i = 1;i <= n && ok;i++){
            sort(events[i].begin(),events[i].end());
            for(int j = 0;j < (int)events[i].size() && ok;j++){
                int l = (j == 0 ? 1 : events[i][j - 1] + 1);
                int r = (j == (int)events[i].size() - 1 ? lst_y:events[i][j + 1] - 1);
                int last = (last_x[events[i][j]] == 0 ? 1:last_x[events[i][j]] + 1);
                if(aint.query(l,r) >= last){
                    ok = false;
                }
            }
            for(auto it:events[i]){
                aint.update(it,i);
                last_x[it] = i;
            }
        }

        if(ok){
            fprintf(g,"1\n");
        }else{
            fprintf(g,"0\n");
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
