#include <bits/stdc++.h>

using namespace std;

struct data_t{
    int i,j,k;
};

vector<int> v;
vector<data_t> ans;

void add_ans(int i,int j,int k){
    ans.push_back({i,j,k});
    int xo = v[i] ^ v[j] ^ v[k];
    v[i] = v[j] = v[k] = xo;
}

int main(){
    
    int n;

    scanf("%d",&n);

    int xo = 0;

    for(int i = 1;i <= n;i++){
        int val;
        scanf("%d",&val);
        v.push_back(val);
        xo ^= val;
    }

    if(xo != 0 && n % 2 == 0){
        printf("NO\n");
        return 0;
    }

    printf("YES\n");

    printf("%d\n",2 * int((n - 1) / 2));

    for(int i = 2;i + 1 <= n;i += 2){
        printf("1 %d %d\n",i,i + 1);
    }
    for(int i = 2;i + 1 <= n;i += 2){
        printf("1 %d %d\n",i,i + 1);
    }

    return 0;
}
