#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <map>

using namespace std;

const int XMAX = 1e5;

map<pair<pair<int,int>,pair<int,int> >,int> memo;
int my_query(int x,int y,int xx,int yy){
    if(memo.count({{x,y},{xx,yy}}) == 0){
        int ans;
        cout << "? " << x << " " << y << " " << xx << " " << yy << endl;
        cin >> ans;
        memo[{{x,y},{xx,yy}}] = ans;
    }
    return memo[{{x,y},{xx,yy}}];
}
/*
vector<pair<int,int> > v = {{1,2},{4,5},{6,2}};
int my_query(int x,int y,int xx,int yy){
    int ans = 0;
    for(auto it:v){
        ans += (1LL * x * yy + 1LL * xx * it.second + 1LL * it.first * y > 1LL * xx * y + 1LL * yy * it.first + 1LL * x * it.second);
    }
    return ans;
}
*/

int ask_up(int x){
    return my_query(x,0,x,1);
}

int ask_down(int x){
    return my_query(x,1,x,0);
}

int ask_lower_left(int x,int y){
    int tmp;
    if(y > XMAX / 2){
        tmp = my_query(x + 1,0,x,y);
    }
    else{
        tmp =  my_query(x,y,x - 1,XMAX + 1);
    }
    return tmp;
}

void answer(vector<pair<int,int> > &ans){
    cout << "! ";
    for(auto it:ans)cout << it.first << " " << it.second << " ";
    cout << endl;
    exit(0);
}

void divide_x(int l,int r,int val_l,int val_r,vector<pair<int,int> > &xs){
    if(val_l == val_r){
        xs.push_back({r,val_r});
        return ;
    }
    int mid = (l + r) / 2;
    int tmp = ask_up(mid);
    divide_x(l,mid,val_l,tmp,xs);
    if(tmp != val_r){
        tmp = ask_up(mid + 1);
    }
    divide_x(mid + 1,r,tmp,val_r,xs);
}

void divide_y(int x,int l,int r,int val_l,int val_r,vector<pair<int,int> > &ys){
    if(val_l == val_r){
        ys.push_back({r,val_r});
        return ;
    }
    int mid = (l + r) / 2;
   
    int tmp = ask_lower_left(x,mid);
    divide_y(x,l,mid,val_l,tmp,ys);
    if(tmp != val_r){
        tmp = ask_lower_left(x,mid + 1);
    }
    divide_y(x,mid + 1,r,tmp,val_r,ys);
}

int n;

int main(){
    
    cin >> n;
//    n = (int)v.size();

    vector<pair<int,int> > xs;
    divide_x(0,XMAX + 1,0,n,xs);
        
    sort(xs.begin(),xs.end());

    vector<int> x;
    vector<int> sum_x;
    
    for(int i = 0;i < (int)xs.size();i++){
        if(i + 1 >= (int)xs.size() || xs[i].second != xs[i + 1].second){
            if(xs[i].second == n){
                continue;
            }
            x.push_back(xs[i].first);
            sum_x.push_back(xs[i].second);
        }
    }

    vector<pair<int,int> > ans;
    for(int i = 0;i < (int)x.size();i++){
        int val_l = sum_x[i];
        int val_r = ask_down(x[i]);
        vector<pair<int,int> > ys;
        divide_y(x[i],0,XMAX + 1,val_l,n - val_r,ys);
        sort(ys.begin(),ys.end());
        for(int j = 0;j < (int)ys.size();j++){
            if((j + 1 >= (int)ys.size() && ys[j].first <= XMAX) || (j + 1 < (int)ys.size() && ys[j].second != ys[j + 1].second)){
                ans.push_back({x[i],ys[j].first});
            }
        }
    }
    
    sort(ans.begin(),ans.end());
    answer(ans);

    return 0;
}
