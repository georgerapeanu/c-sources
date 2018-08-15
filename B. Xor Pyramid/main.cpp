#include <iostream>

using namespace std;

int N,Q;
int V[5005];
int ans[5005][5005];
int lg2[5005];

int main(){
    cin >> N;

    lg2[0] = -1;

    for(int i = 1;i <= N;i++){
        cin >> V[i];

        ans[i][i] = V[i];

        lg2[i] = 1+ lg2[i / 2];
    }

    for(int len = 2;len <= N;len++){
        for(int i = 1;i <= N - len + 1;i++){
            int j = i + len - 1;
            int sub_len;
            if(len - ((-len)&len) == 0){
                sub_len = len / 2;
            }
            else{
                sub_len = len ^ (1 << lg2[len]);
            }
            ans[i][j] = ans[i][i + sub_len - 1] ^ ans[j - sub_len + 1][j];
        }
    }
    for(int len = 2;len <= N;len++){
        for(int i = 1;i <= N - len + 1;i++){
            int j = i + len - 1;
            ans[i][j] = max(ans[i][j],max(ans[i + 1][j],ans[i][j - 1]));
        }
    }

    cin >> Q;

    while(Q--){
        int x,y;
        cin >> x >> y;
        cout << ans[x][y] << "\n";
    }

    return 0;
}
