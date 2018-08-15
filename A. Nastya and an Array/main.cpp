#include <iostream>
#include <algorithm>

using namespace std;

int N;
int V[100005];

int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> V[i];
        if(!V[i]){
            i--;
            N--;
        }
    }
    sort(V + 1,V + 1 + N);
    cout << unique(V + 1,V + 1 + N) - (V + 1);
    return 0;
}
