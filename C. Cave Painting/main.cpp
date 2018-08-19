#include <iostream>
#include <unordered_set>
using namespace std;
unordered_set<long long> R;
long long N,K;
int main()
{
    cin >> N >> K;
    for(long long i = 1;i <= K;i++){
        if(R.count(N % i)){
            cout << "No";
            return 0;
        }
        R.insert(N % i);
    }
    cout << "Yes";
    return 0;
}
