#include <iostream>
using namespace std;
long long N,K,ans;
long long a[100005];
int main()
{
    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cout.tie(0);
    cin >> N >> K;
    ans = 1;
    for(int i = 1;i <= K;i++){
        cin >> a[i];
        if((N / a[ans]) * a[ans] < (N / a[i]) * a[i]){
            ans = i;
        }
    }
    cout << ans << " " << (N / a[ans]);
    return 0;
}
