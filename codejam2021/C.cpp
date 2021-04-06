#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int t;
int n,c;
int v[105];
vector<pair<int,int> > to_reverse;

int main(){
    scanf("%d",&t);
    for(int test = 1;test <= t;test++){
        scanf("%d %d",&n,&c);
        
        c -= (n - 1);

        to_reverse.clear();

        for(int i = 1;i < n;i++){
            if(c >= (n - i)){
                to_reverse.push_back({i,n});
                c -= (n - i);
            }else if(c > 0){
                to_reverse.push_back({i,i + c});
                c = 0;
            }
        }
        
        for(int i = 1;i <= n;i++){
            v[i] = i;
        }

        reverse(to_reverse.begin(),to_reverse.end());

        for(auto it:to_reverse){
            reverse(v + it.first,v + it.second + 1);
        }

        printf("Case #%d: ",test);

        if(c != 0){
            printf("IMPOSSIBLE\n");
        }else{
            for(int i = 1;i <= n;i++){
                printf("%d ",v[i]);
            }
            printf("\n");
        }
    }
    
    return 0;
}
