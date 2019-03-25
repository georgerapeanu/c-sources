#include <bits/stdc++.h>

using namespace std;

struct color_t{
    int r,g,b;

    double dist(color_t &other){
        return sqrt((this -> r - other.r) * (this->r - other.r) +
                    (this->b - other.b) * (this->b - other.b) + 
                    (this->g - other.g) * (this->g - other.g)
                );
    }

    int round_dist(color_t &other){
        return (int)this->dist(other);
    }
};

int n,m;

vector<vector<color_t> > v;

int main(){


    cin >> n >> m;

    v = vector<vector<color_t> >(n + 4,vector<color_t>(m + 4,{0,0,0}));

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> v[i][j].r >> v[i][j].g >> v[i][j].b;
            if(j > 1){
                cout << v[i][j].round_dist(v[i][j - 1]) << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
