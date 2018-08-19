#include <iostream>

using namespace std;
int V[5005];
int N;
int main()
{
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> V[i];
    }
    bool ok = 0;
    for(int i = 1;i <= N;i++){
        if(V[V[V[i]]] == i){
            cout << "YES";
            ok = 1;
            break;
        }
    }
    if(!ok)cout << "NO";
    return 0;
}
