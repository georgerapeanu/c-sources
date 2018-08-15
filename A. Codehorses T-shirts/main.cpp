#include <iostream>
#include <algorithm>

using namespace std;

int N;
string A[105];
string B[105];
int total;

int change(string &a,string &b){
    int ans = 0;
    for(int i = 0;i < (int)a.size();i++){
        ans += (a[i] != b[i]);
    }
    return ans;
}

bool cmp(string a,string b){
    if(a.size() != b.size()){
        return a.size() < b.size();
    }
    return a < b;
}

int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> A[i];
    }
    for(int j = 1;j <= N;j++){
        cin >> B[j];
    }



    sort(A + 1,A + 1 + N,cmp);
    sort(B + 1,B + 1 + N,cmp);

    int last = 1;

    for(int i = 1;i <= N;i++){
        if(A[i].size() != A[i + 1].size()){
            int S = 0,M = 0,L = 0;
            for(int j = last;j <= i;j++){
                S += (A[j].back() == 'S');
                M += (A[j].back() == 'M');
                L += (A[j].back() == 'L');
                S -= (B[j].back() == 'S');
                M -= (B[j].back() == 'M');
                L -= (B[j].back() == 'L');
            }
            total += abs(S) + abs(M) + abs(L);
            last = i + 1;
        }
    }

    cout << total / 2;

    return 0;
}
