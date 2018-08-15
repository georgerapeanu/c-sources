#include <iostream>

using namespace std;

int N;
int A[100006];
int even,odd;
int on_time;
int ans;

int main(){
    cin >> N;
    cin >> A[N + 1];
    for(int i = 1;i <= N;i++){
        cin >> A[i];
    }

    for(int i = 0;i <= N;i++){
        if(i % 2 == 0){
            even += (A[i + 1] - A[i]);
        }
        else{
            odd += (A[i + 1] - A[i]);
        }
    }

    for(int i = 0;i <= N;i++){
        even -= (i % 2 == 0) * (A[i + 1] - A[i]);
        odd -= (i % 2 == 1) * (A[i + 1] - A[i]);
        if(A[i] == A[i + 1] - 1){
            ;
        }
        else if(i % 2 == 0){
            ans = max(ans,on_time + A[i + 1] - A[i] - 1 + odd);
        }
        else{
            ans = max(ans,on_time + A[i + 1] - A[i] - 1 + odd);
        }
        on_time += (i % 2 == 0) * (A[i + 1] - A[i]);
    }

    ans = max(ans,on_time);

    cout << ans;

    return 0;
}
