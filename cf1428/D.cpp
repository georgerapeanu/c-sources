#include <bits/stdc++.h>

using namespace std;

int n;
int a[100005];
vector<int> available;
vector<int> available2;
int height[100005];

vector<pair<int,int> > cells;

int main(){

    cin >> n;

    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }

    int lst = 0;

    for(int i = n;i;i--){
        if(a[i] == 0){
            continue;
        }
        else if(a[i] == 1){
            lst++;
            height[i] = lst;
            cells.push_back({i,height[i]});
            available.push_back(i);
        }
        else if(a[i] == 2){
            if(available.empty()){
                cout << "-1\n";
                return 0;
            }
            int tmp = available.back();
            available.pop_back();
            cells.push_back({i,height[tmp]});
            available2.push_back(i);
        }
        else{
            int tmp;
            if(available2.size()){
                tmp = available2.back();
                available2.pop_back();
            }
            else if(available.size()){
                tmp = available.back();
                available.pop_back();
            }
            else{
                cout << "-1\n";
                return 0;
            }
            lst++;
            cells.push_back({i,lst});
            cells.push_back({tmp,lst});
            available2.push_back(i);
        }
    }

    cout << (int)cells.size() << "\n";
    for(auto it:cells){
        swap(it.first,it.second);
        it.first = n + 1 - it.first;
        cout << it.first << " " << it.second << "\n";
    }

    return 0;
}
