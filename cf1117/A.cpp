#include <cstdio>

using namespace std;

int main(){
    int ans = -1;
    int ans_val = -1;

    int n;

    scanf("%d",&n);

    int curr = -1;
    int curr_val = -1;

    for(int i = 1;i <= n;i++){
        int x;
        scanf("%d",&x);
        if(x == curr_val){
            curr++;
        }
        else{
            curr = 1;
            curr_val = x;
        }

        if(ans_val < curr_val){
            ans_val = curr_val;
            ans = curr;
        }
        else if(ans_val == curr_val && ans < curr){
            ans = curr;
        }
    }

    printf("%d",ans);
}
