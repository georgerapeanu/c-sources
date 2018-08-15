#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

struct point_data_t{
    int x,y;

    bool operator < (const point_data_t &other)const{
        if(x != other.x){
            return x < other.x;
        }
        return y < other.y;
    }

    bool operator == (const point_data_t &other)const{
        return x == other.x && y == other.y;
    }

    long long sqr_dist(const point_data_t &other)const{
        return 1LL * (x - other.x) * (x - other.x) + 1LL * (y - other.y) * (y - other.y);
    }
};

long long det(point_data_t a, point_data_t b, point_data_t c){
    return 1LL * a.x * (b.y - c.y) + 1LL * b.x * (c.y - a.y) + 1LL * c.x * (a.y - b.y);
}

vector<point_data_t> get_convex_hull(vector<point_data_t> &V){
    vector<point_data_t> convex_hull;

    sort(V.begin(), V.end());

    for(int i = 0;i < (int)V.size();i++){
        point_data_t it = V[i];
        while((int)convex_hull.size() >= 2 && det(convex_hull[(int)convex_hull.size() - 2],convex_hull[(int)convex_hull.size() - 1],it) < 0LL){
            convex_hull.pop_back();
        }
        convex_hull.push_back(it);
    }

    reverse(V.begin(),V.end());

    for(int i = 1;i < (int)V.size();i++){
        point_data_t it = V[i];
        while((int)convex_hull.size() >= 2 && det(convex_hull[(int)convex_hull.size() - 2],convex_hull[(int)convex_hull.size() - 1],it) < 0LL){
            convex_hull.pop_back();
        }
        convex_hull.push_back(it);
    }

    convex_hull.pop_back();
    vector<point_data_t> real_convex_hull;

    for(int i = 0; i < (int)convex_hull.size();i++){
        point_data_t ant = convex_hull[i == 0 ? ((int)convex_hull.size() - 1) : i - 1];
        point_data_t curr = convex_hull[i];
        point_data_t nxt = convex_hull[i == ((int)convex_hull.size() - 1) ? 0 : i + 1];
        if(det(ant, curr, nxt) != 0LL){
            real_convex_hull.push_back(convex_hull[i]);
            ant = curr;
        }
    }

    return real_convex_hull;
}

double unghi(point_data_t a,point_data_t b,point_data_t c){
    b.x -= a.x;
    b.y -= a.y;
    c.x -= a.x;
    c.y -= a.y;
    double u = atan2(b.y,b.x) - atan2(c.y,c.x);
    return u;
}

vector< pair<double,int> > get_transform(vector<point_data_t> &A){
    vector< pair<double,int> > trans;
    for(int i = 0;i < (int)A.size();i++){
        trans.push_back({A[i].sqr_dist(A[(i + 1) % ((int)A.size())]),0});
        trans.push_back({unghi(A[i],A[(i + 1) % ((int)A.size())],A[(i + 2) % ((int)A.size())]),1});
    }
    return trans;
}

string isomorphic(vector<point_data_t> &A, vector<point_data_t> &B){
    if(A.size() != B.size()){
        return "NO";
    }
    vector< pair<double,int> > transA = get_transform(A);
    vector< pair<double,int> > transB = get_transform(B);

    int sz = transA.size();
    for(int i = sz;i < 2 * sz;i++){
        transA.push_back(transA[i - sz]);
    }

    vector<int> Fail;
    Fail.resize(transB.size());
    Fail[0] = -1;

    for(int i = 1;i < (int)transB.size();i++){
        int k = Fail[i - 1];
        while(k >= 0 && transB
              [k + 1] != transB[i]){
            k = Fail[k];
        }
        Fail[i] = k + (transB[k + 1] == transB[i]);
    }

    int ind = -1;

    for(int i = 0;i < (int)transA.size();i++){
        while(ind != -1 && transB[ind + 1] != transA[i]){
            ind = Fail[ind];
        }
        ind = ind + (transB[ind + 1] == transA[i]);
        if(ind == (int)B.size() - 1){
            return "YES";
        }
    }

    return "NO";

}
int N,M;
vector<point_data_t> A;
vector<point_data_t> B;

int main() {

    cin >> N >> M;
    A.resize(N);
    B.resize(M);

    for(int i = 0;i < N;i++){
        cin >> A[i].x >> A[i].y;
    }

    for(int i = 0;i < M;i++){
        cin >> B[i].x >> B[i].y;
    }

    A = get_convex_hull(A);
    B = get_convex_hull(B);

//    cout << "\n\n\n";for(auto it:A)cout << it.x << " " << it.y << "\n";cout << "\n\n\n";
//    cout << "\n\n\n";for(auto it:B)cout << it.x << " " << it.y << "\n";cout << "\n\n\n";

    cout << isomorphic(A,B);

    return 0;
}
