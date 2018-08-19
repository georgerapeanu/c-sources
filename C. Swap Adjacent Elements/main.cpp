#include <iostream>

using namespace std;
int pos[200005];
int S[2000005];
int N;
string a;
int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        int x;
        cin >> x;
        pos[x] = i;
    }
    cin >> a;
    a = " " + a;
    a = a + "0";
    for(int i = 1;i <= N;i++){
        S[i] = S[i - 1] + (a[i] == '1');
    }
    for(int i = 1;i <= N;i++){
        int st = min(i,pos[i]);
        int dr = max(i,pos[i]);
        if(dr - st == S[dr - 1] - S[st - 1]){
            ;
        }
        else{
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}
