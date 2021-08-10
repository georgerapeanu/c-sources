#include <cstdio>
#include <vector>
#include <deque>
#include <algorithm>
#include <set>

using namespace std;

const int NMAX = 1e5;

int n;
int p[NMAX + 5];
pair<int,int> v[NMAX + 5];
bool used[NMAX + 5];

set<int> taken;

int main(){
    
    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&p[i]);
        v[i] = {p[i],i};
    }

    sort(v + 1,v + 1 + n);
    reverse(v + 1,v + 1 + n);

    int root = v[1].second;
    used[root] = true;
    taken.insert(root);

    int l = 1;
    int r = n;
    

    for(int i = 2;i <= n;i++){
        while(used[l]){
            l++;
        }
        while(used[r]){
            r--;
        }
        int value_l;
        int value_r;
        int b_value_l;
        int b_value_r;
        if(l < root){
            value_l = p[*taken.lower_bound(l)];
            b_value_l = p[l - 1];
        }else{
            value_l = n;
            b_value_l = n;
        }

        if(r > root){
            value_r = p[*prev(taken.lower_bound(r))];
            b_value_r = p[r + 1];
        }else{
            value_r = n;
            b_value_r = n;
        }
        int pos = v[i].second;
        if(pos > *taken.begin() && pos < *taken.rbegin()){
            continue;
        }
        if(b_value_l <= value_r && p[l] > p[pos]){
            break;
        }
        if(b_value_r <= value_l && p[r] > p[pos]){
            break;
        }
        used[pos] = true;
        taken.insert(pos);
    }

    deque<int> _taken;

    for(auto it:taken){
        _taken.push_back(it);
    }

    l = 1;
    r = n;
    int to_l = _taken.front();
    int to_r = _taken.back();


    deque<int> ans;

    while(l <= r && to_l != -1 && to_r != -1){
        if(used[l] && used[r]){
            if(p[l] < p[r]){
                ans.push_front(p[l]);
                l++;
                _taken.pop_front();
                if(_taken.size()){
                    to_l = _taken.front();
                }else{
                    to_l = -1;
                }
            }else{
                ans.push_front(p[r]);
                r--;
                _taken.pop_back();
                if(_taken.size()){
                    to_r = _taken.back();
                }else{
                    to_r = -1;
                }
            }
        }else if(used[l]){
            if(p[to_l] <= p[to_r]){
                ans.push_front(p[l]);
                l++;
                _taken.pop_front();
                if(_taken.size()){
                    to_l = _taken.front();
                }else{
                    to_l = -1;
                }
            }else{
                ans.push_back(p[r]);
                r--;
            }
        }else if(used[r]){
            if(p[to_l] < p[to_r]){
                ans.push_back(p[l]);
                l++;
            }else{
                ans.push_front(p[r]);
                r--;
                _taken.pop_back();
                if(_taken.size()){
                    to_r = _taken.back();
                }else{
                    to_r = -1;
                }
            }
        }else{
            if(p[l] > p[r]){
                ans.push_back(p[l]);
                l++;
            }else{
                ans.push_back(p[r]);
                r--;
            }
        }
    }

    while(l <= r){
        if(p[l] > p[r]){
            ans.push_back(p[l]);
            l++;
        }else{
            ans.push_back(p[r]);
            r--;
        }
    }

    for(auto it:ans){
        printf("%d ",it);
    }

    return 0; 
}
