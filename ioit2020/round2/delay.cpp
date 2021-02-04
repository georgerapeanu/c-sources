#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n;

vector<int> s;
vector<int> d;
vector<int> o;

int main(){

    scanf("%d",&n);
    s = vector<int>(n + 1,0);
    d = vector<int>(n + 1,0);
    o = vector<int>(n + 1,0);
    
    for(int i = 1;i <= n;i++){
        scanf("%d",&s[i]);
    }
    for(int i = 1;i <= n;i++){
        scanf("%d",&d[i]);
    }

    int lst = 1;

    for(int i = 1;i <= n;i++){
        while(i - lst > d[i]){
            lst++;
        }
        o[i] = s[lst];
    }

    for(int i = 1;i <= n;i++){
        printf("%d ",o[i]);
    }

    return 0;
}
