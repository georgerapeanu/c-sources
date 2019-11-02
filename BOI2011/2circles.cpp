#include <cstdio>
#include <algorithm>
#include <deque>
#include <cmath>

using namespace std;

const int NMAX = 5e4;
int n;
pair<int,int> p[NMAX + 5];
pair<double,double> np[NMAX + 5];
pair<double,double> vec[NMAX + 5];
pair<double,double> gr;
pair<int,int> origin;

struct line_t {
    double a,b,c;

    line_t() {
        a = b = c = 0;
    }

    line_t(pair<double,double> p1,pair<double,double> p2) {
        a = -(p2.second - p1.second);
        b = -(p1.first - p2.first);
        c = -(p2.first * p1.second - p1.first * p2.second);
///        printf("%.4f %.4f spatiu %.4f %.4f dreapta %.4f %.4f %.4f \n",p1.first,p1.second,p2.first,p2.second,a,b,c);
    }
};

double sqr_dist(pair<double,double> p1,pair<double,double> p2) {
    return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}

double det(pair<double,double> a,pair<double,double> b,pair<double,double> c) {
    return a.first * (b.second - c.second) + b.first * (c.second - a.second) + c.first * (a.second - b.second);
}

pair<double,double> sect(line_t a,line_t b) {
    if((a.a * b.b == b.a * a.b))return {-1e7,-1e7};
    pair<double,double> ans;
    ans.first = (b.c * a.b - a.c * b.b) / (a.a * b.b - b.a * a.b);
    ans.second = (b.c * a.a - a.c * b.a) / (a.b * b.a - b.b * a.a);
    printf("d1 %.4f %.4f %.4f d2 %.4f %.4f %.4f sect %.4f %.4f\n",a.a,a.b,a.c,b.a,b.b,b.c,ans.first,ans.second);
    return ans;
}

bool above(line_t a,pair<double,double> b) {
    if(b.first == -1e7 && b.second == -1e7)return false;
    printf("abouve %.4f %.4f %.4f point %.4f %4.f ans %.4f\n",a.a,a.b,a.c,b.first,b.second,a.a * b.first + a.b * b.second + a.c);
    return a.a * b.first + a.b * b.second + a.c >= 0;
}

void init() {
    for(int i = 1; i <= n; i++) {
        vec[i].first = p[i % n + 1].first - p[i].first;
        vec[i].second = p[i % n + 1].second - p[i].second;
        swap(vec[i].first,vec[i].second);
        vec[i].first *= -1;
        double len = sqrt(vec[i].first * vec[i].first + vec[i].second * vec[i].second);
        vec[i].first = (vec[i].first / len);
        vec[i].second = (vec[i].second / len);
        if((gr.first - p[i].first) * vec[i].first + (gr.second - p[i].second) * vec[i].second < 0) {
            vec[i].first *= -1;
            vec[i].second *= -1;
        }
    }
}


bool ok(double r) {
    deque<line_t> v;
    for(int i = 1; i <= n; i++) {
        pair<double,double> p1 = p[i];
        pair<double,double> p2 = p[i % n + 1];

///        line_t base(p1,p2);

        p1.first += r * vec[i].first;
        p1.second += r * vec[i].second;

        p2.first += r * vec[i].first;
        p2.second += r * vec[i].second;

        line_t tmp(p1,p2);

        if(base.a * gr.first + base.b * gr.second + base.c < 0) {
            base.a *= -1;
            base.b *= -1;
            base.c *= -1;
        }

        if(base.a != tmp.a || base.b != tmp.b) {
            tmp.a *= -1;
            tmp.b *= -1;
            tmp.c *= -1;
        }

        while(v.size() > 1 && above(v.back(),sect(v[(int)v.size() - 2],tmp))) {
            v.pop_back();
        }
        printf("tmps is %.4f %.4f %.4f\n",tmp.a,tmp.b,tmp.c);
        v.push_back(tmp);
    }

    //for(auto it:v)printf("%.4f %.4f %.4f\n",it.a,it.b,it.c);
    while(v.size() > 2 && above(v.back(),sect(v[(int)v.size() - 2],v[0]))) {
        v.pop_back();
    }

    while(v.size() > 2 && above(v[0],sect(v.back(),v[1]))) {
        v.pop_front();
    }

    if((int)v.size() < 3) {
        return false;
    }

    int n = v.size();

    for(int i = 1; i <= n; i++) {
        np[i] = sect(v[(i == 1 ? n - 1:i - 2)],v[i - 1]);
    }


    for(int i = 1; i <= n; i++) {
        printf("%.4f %.4f\n",np[i].first,np[i].second);
    }

    int lst = 1;

    for(int i = 1; i <= n; i++) {
        while(sqr_dist(np[i],np[lst]) < sqr_dist(np[i],np[lst % n + 1])) {
            lst = lst % n + 1;
        }
//        printf("%d %d %.4f\n",i,lst,sqr_dist(np[i],np[lst % n + 1]));
        if(sqr_dist(np[i],np[lst]) >= 4 * r * r) {
            return true;
        }
    }

    return false;
}

int main() {

    scanf("%d",&n);

    pair<double,double> lst = {-1e7,-1e7},fst = {1e7,1e7};

    for(int i = 1; i <= n; i++) {
        scanf("%d %d",&p[i].first,&p[i].second);
        origin.first = min(origin.first,p[i].first);
        origin.second = min(origin.second,p[i].second);
        gr.first += p[i].first;
        gr.second += p[i].second;
        fst.first = min(fst.first,1.0 * p[i].first);
        fst.second = min(fst.second,1.0 * p[i].second);
        lst.first = max(lst.first,1.0 * p[i].first);
        lst.second = max(lst.second,1.0 * p[i].second);
    }

    gr.first /= n;
    gr.second /= n;

    init();

    double st = 0,dr = 1e7;

    dr = min(lst.first - fst.first,lst.second - fst.second) / 2;

    printf("%d\n",ok(1427));
    return 0;

    while(dr - st > 1e-4) {
        double mid = (st + dr) / 2;

        if(ok(mid)) {
            st = mid;
        }
        else {
            dr = mid;
        }
    }

    printf("%.4f\n",st);

    return 0;
}
