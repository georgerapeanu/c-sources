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

int main(){

    int n;

    cin >> n;

    while(n--){
        color_t a,b;
        cin >> a.r >> a.g >> a.b;
        cin >> b.r >> b.g >> b.b;
        cout << a.round_dist(b) << endl;
    }

    return 0;
}
