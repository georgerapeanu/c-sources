#include <bits/stdc++.h>

using namespace std;

int num_for_2[10];

pair<int,int> A[20],B[20];
int N,M;

int common(pair<int,int> a,pair<int,int> b){
    if(a.first == b.first) return a.first;
    if(a.first == b.second) return a.first;
    if(a.second == b.second) return a.second;
    if(a.second == b.first) return a.second;
    return -1;
}

int solve(pair<int,int> A[],pair<int,int> B[],int N,int M){
    vector<int> cf;

    for(int fst = 1;fst <= N;fst++){
        vector<int> digits;
        for(int snd = 1;snd <= M;snd++){
            if(A[fst] != B[snd]){
                if(common(A[fst],B[snd]) != -1){
                    digits.push_back(common(A[fst],B[snd]));
                }
            }
        }
        sort(digits.begin(),digits.end());
        digits.resize(unique(digits.begin(),digits.end()) - digits.begin());
        if(digits.size() == 0){
            ;
        }
        else if(digits.size() == 1){
            cf.push_back(digits[0]);
        }
        else{
            return -1;
        }
    }

    sort(cf.begin(),cf.end());
    cf.resize(unique(cf.begin(),cf.end()) - cf.begin());

    if(cf.size() != 1){
        return 0;
    }
    else{
        return cf[0];
    }
}

int main(){

    cin >> N >> M;

    for(int i = 1;i <= N;i++){
        cin >> A[i].first >> A[i].second;
        if(A[i].second < A[i].first){
            swap(A[i].first,A[i].second);
        }
    }

    for(int i = 1;i <= M;i++){
        cin >> B[i].first >> B[i].second;
        if(B[i].second < B[i].first){
            swap(B[i].first,B[i].second);
        }
    }

    int a = solve(A,B,N,M);
    int b = solve(B,A,M,N);

    if(a == -1 || b == -1)cout << -1;
    else if(a > 0 && b > 0 && a != b) cout << -1;
    else cout << max(a,b);

    return 0;
}
