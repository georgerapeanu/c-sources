#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e5;
const int BUCK = 700;

class AIB{

    int n;
    vector<int> aib;

public:

    AIB(int n){
        this->n = n;
        this->aib = vector<int>(n + 1,0);
    }

    void update(int pos,int val){
        pos++;//because reminders->position
        for(;pos <= n;pos += (-pos) & pos){
            aib[pos] += val;
        }
    }

    int query(int pos){
        pos++;
        int ans = 0;
        for(;pos;pos -= (-pos) & pos){
            ans += aib[pos];
        }
        return ans;
    }

};

int t;
int a[NMAX + 5];
int ans[BUCK + 5][BUCK + 5];

int main() {

    scanf("%d",&t);

    while(t--){
        int t,x,y;
        
        scanf("%d %d %d",&t,&x,&y);

        if(t == 1){
            a[x] += y;
            for(int k = 1;k <= BUCK;k++){
                ans[k][x % k] += y;
            }
        }
        else{
            if(x <= BUCK){
                printf("%d\n",ans[x][y]);
            }
            else{
                int ans = 0;
                for(int i = y;i <= NMAX;i += x){
                    ans += a[i];
                }
                printf("%d\n",ans);
            }
        }
    }
   
    return 0;
}
