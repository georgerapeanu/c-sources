#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("shoebox.in","r");
FILE *g = fopen("shoebox.out","w");

int t;
int n;
pair<int,int> v[1005];

int aib[1005];
int rev_aib[1005];

void update(int aib[],int pos,int val){
    for(;pos <= 1000;pos += (-pos) & pos){
        aib[pos] = max(aib[pos],val);
    }
}

int query(int aib[],int pos){
    int ans = 0;
    for(;pos;pos -= (-pos) & pos){
        ans = max(aib[pos],ans);
    }
    return ans;
}

int main(){

    fscanf(f,"%d",&t);
    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d %d",&v[i].first,&v[i].second);
        if(v[i].first > v[i].second){
            swap(v[i].first,v[i].second);
        }
    }

    sort(v + 1,v + 1 + n);

    int ans1 = 0;
    int ans2 = 0;

    for(int i = 1;i <= n;i++){
        int t1 = query(aib,v[i].second) + 1;
        int t2 = query(rev_aib,1000 - v[i].second) + 1;
        ans1 = max(ans1,t1);
        ans2 = max(ans2,t2);
        update(aib,v[i].second,t1);
        update(rev_aib,1000 - v[i].second + 1,t2);
    }

    fprintf(g,"%d\n",(t == 1 ? ans1:ans2));

    fclose(f);
    fclose(g);

    return 0;
}
