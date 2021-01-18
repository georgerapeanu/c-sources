#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e6;
const int QMAX = 1e6;

vector<pair<int,int> > queries[NMAX + 5];
int n,q;
int v[NMAX + 5];
int ans[QMAX + 5];
int w[NMAX + 5];

int aint[2 * NMAX + 5];

void update(int p,int val){
    p += n;
    aint[p] = max(aint[p],val);
    for(;p > 1;p >>= 1){
        aint[p >> 1] = max(aint[p],aint[p ^ 1]);
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

int main(){
    
    scanf("%d %d",&n,&q);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    for(int i = 1;i <= q;i++){
        int l,r;
        scanf("%d %d %d",&l,&r,&w[i]);
        queries[r].push_back({l,i});
    }

    vector<int> st;

    for(int i = 1;i <= n;i++){
        while(st.empty() == false && v[st.back()] <= v[i]){
            st.pop_back();
        }
        if(st.empty() == false){
            update(st.back(),v[st.back()] + v[i]);
        }       
        st.push_back(i);
        for(auto it:queries[i]){
            ans[it.second] = query(it.first,i);
        }
    }

    for(int i = 1;i <= q;i++){
        printf("%d\n",(ans[i] <= w[i]));
    }

    return 0;
}
