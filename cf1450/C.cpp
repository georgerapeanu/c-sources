#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;

    cin >> t;

    while(t--){
        int n;
        cin >> n;
        vector<string> v(n);

        for(int i = 0;i < n;i++){
            cin >> v[i];
        }

        vector<vector<int> > fr(3,vector<int>(2,0));

        int k = 0;

        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(v[i][j] == 'O'){
                    fr[(i + j) % 3][0]++;
                    k++;
                }
                else if(v[i][j] == 'X'){
                    fr[(i + j) % 3][1]++;
                    k++;
                }
            }
        }

        vector<int> perm = {0,1,2};

        int bst = 0;
        
        for(int i = 1;i < 3;i++){
            if(fr[i][0] + fr[i][1] > fr[bst][0] + fr[bst][1]){
                bst = i;
            }
        }
        swap(perm[bst],perm[2]);

        if(fr[perm[0]][1] + fr[perm[1]][0] > k / 3){
            swap(perm[0],perm[1]);            
        }

        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(v[i][j] == '.'){
                    continue;
                }
                if((i + j) % 3 == perm[0]){
                    v[i][j] = 'O';
                }
                else if((i + j) % 3 == perm[1]){
                    v[i][j] = 'X';
                }
            }
        }
        for(int i = 0;i < n;i++){
            cout << v[i] << "\n";
        }
    }

    return 0;
}
