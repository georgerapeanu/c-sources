#include <bits/stdc++.h>

using namespace std;

struct point_t {
    int x,y,z;
    int id;

    point_t(int x = 0,int y = 0,int z = 0,int id = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->id = id;
    }

    bool operator < (const point_t &other)const {
        if(x != other.x)return x < other.x;
        if(y != other.y) return y < other.y;
        if(z != other.z)return z < other.z;
        return id < other.id;
    }
};

int n;
vector<point_t> points;
bool taken[50000 + 5];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        point_t tmp;
        scanf("%d %d %d",&tmp.x,&tmp.y,&tmp.z);
        tmp.id = i;
        points.push_back(tmp);
    }

    sort(points.begin(),points.end());

    for(int i = 0; i < (int)points.size(); i++) {
        if(i > 0 && points[i].x == points[i - 1].x && points[i].y == points[i - 1].y && taken[points[i - 1].id] == false) {
            taken[points[i - 1].id] = true;
            taken[points[i].id] = true;
            printf("%d %d\n",points[i - 1].id,points[i].id);
        }
    }

    vector<point_t> tmp;

    for(auto it:points) {
        if(taken[it.id] == false) {
            tmp.push_back(it);
        }
    }

    points = tmp;

    for(int i = 0; i < (int)points.size(); i++) {
        if(i > 0 && points[i].x == points[i - 1].x && taken[points[i - 1].id] == false) {
            taken[points[i - 1].id] = true;
            taken[points[i].id] = true;
            printf("%d %d\n",points[i - 1].id,points[i].id);
        }
    }

    tmp.clear();

    for(auto it:points) {
        if(taken[it.id] == false) {
            tmp.push_back(it);
        }
    }

    points = tmp;

    for(int i = 0; i < (int)points.size(); i++) {
        if(i > 0 && taken[points[i - 1].id] == false) {
            taken[points[i - 1].id] = true;
            taken[points[i].id] = true;
            printf("%d %d\n",points[i - 1].id,points[i].id);
        }
    }

    return 0;
}
