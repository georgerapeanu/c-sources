///we variate the line bg
///now we have to sides:a side and c side
///we want to see if there is a line between the n/3 and n/3 + 1point in a side that is good for c side also
///so we need a structure that supports add,remove and query on the element on the kth position,where k is the same for all queries
///we can do this pretty naively,because on one side we only add and on the other we only remove(except at the initialization)
///a bit of more case work and that's it

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

FILE *f = fopen("tri.in","r");
FILE *g = fopen("tri.out","w");

const int NMAX = 1e4;
const double eps = 1e-9;

int n;
pair<int,int> vertex[4];
pair<int,int> point[NMAX + 5];

int order_a[NMAX + 5];
int order_b[NMAX + 5];
int order_c[NMAX + 5];

int inv_a[NMAX + 5];
int inv_b[NMAX + 5];
int inv_c[NMAX + 5];

long long det(pair<int,int> a,pair<int,int> b,pair<int,int> c){
    return 1LL * a.first * (b.second - c.second) + 1LL * b.first * (c.second - a.second) + 1LL * c.first * (a.second - b.second);
}

bool cmp(int a,int b){
    return det(vertex[0],point[a],point[b]) > 0;
}

///linear beause of monotonicity,otherwise quadratic
///assume that initially all are inactive
///0-indexed
class MonotoneGetKth{
public:
    vector<int> active;
    int target_k;
    int wh;
    int cnt_left;
    int sz;

    void go_next(){
        if(sz < target_k){
            return ;
        }
        
        while(cnt_left < target_k){
            wh++;
            cnt_left += active[wh];
        }
        
        while(cnt_left > target_k || active[wh] == 0){///possible source of bugs
            cnt_left -= active[wh];
            wh--;
        }
    }

public:

    MonotoneGetKth(const int &n,const int &target_k){
        this->active = vector<int>(n,0);
        this->target_k = target_k;
        this->cnt_left = 0;
        this->sz = 0;
        this->wh = -1;
    }

    void add(int pos){
        active[pos] = 1;
        sz++;
        cnt_left += (pos <= wh);
        go_next();
    }

    void rem(int pos){
        active[pos] = 0;
        sz--;
        cnt_left -= (pos <= wh);
        go_next();
    }

    int get_kth_ind(){
        return sz >= target_k ? wh:-1;
    }

    int get_sz(){
        return sz;
    }

};

double sect(double l,double r,double ll,double rr){
    if(r < ll || rr < l){
        return false;
    }
    return true;
}

pair<double,double> get_pos(int from,int to,int orig,int target){
    double a = point[to].second - point[from].second;
    double b = point[from].first - point[to].first;
    double c = 1LL * point[to].first * point[from].second - 1LL * point[to].second * point[from].first;

    double aa = point[target].second - point[orig].second;
    double bb = point[orig].first - point[target].first;
    double cc = 1LL * point[target].first * point[orig].second - 1LL * point[target].second * point[orig].first;

    double x = (cc * b - c * bb) / (a * bb - aa * b);
    x = max(x,eps);
    double y = (c - a * x) / b;

    return {x,y};
}

bool taken[NMAX + 5];

void print_sol(MonotoneGetKth &a,MonotoneGetKth &c,pair<double,double> G){
    fprintf(g,"%.10f %.10f\n",G.first,G.second);
    for(int i = 1;i <= c.wh;i++){
        if(c.active[i]){
            fprintf(g,"%d %d ",point[order_c[i]].first,point[order_c[i]].second);
            taken[order_c[i]] = true;
        }
    }
    
    fprintf(g,"\n");

    for(int i = 1;i <= a.wh;i++){
        if(a.active[i]){
            fprintf(g,"%d %d ",point[order_a[i]].first,point[order_a[i]].second);
            taken[order_a[i]] = true;
        }
    }

    fprintf(g,"\n");

    for(int i = 1;i <= n;i++){
        if(taken[i] == false){
            fprintf(g,"%d %d ",point[i].first,point[i].second);
        }
    }

    fprintf(g,"\n");

    exit(0);
}

///need 2/vertex because we need the next one too
int main(){

    for(int i = 1;i <= 3;i++){
        fscanf(f,"%d %d",&vertex[i].first,&vertex[i].second);
    }

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d %d",&point[i].first,&point[i].second);
        order_a[i] = i;
        order_b[i] = i;
        order_c[i] = i;
    }

    vertex[0] = vertex[1];
    sort(order_a + 1,order_a + 1 + n,cmp);

    vertex[0] = vertex[2];
    sort(order_b + 1,order_b + 1 + n,cmp);

    vertex[0] = vertex[3];
    sort(order_c + 1,order_c + 1 + n,cmp);
    reverse(order_c + 1,order_c + 1 + n);

    for(int i = 1;i <= n;i++){
        inv_a[order_a[i]] = i;
        inv_b[order_b[i]] = i;
        inv_c[order_c[i]] = i;
    }

    order_a[n + 1] = order_b[n + 1] = order_c[n + 1] = n + 1;
    order_a[n + 2] = order_b[n + 2] = order_c[n + 2] = n + 2;

    point[n + 1] = vertex[1];
    point[n + 2] = vertex[3];
    point[n + 3] = vertex[2];
    
    MonotoneGetKth a_curr(n + 5,n / 3);
    MonotoneGetKth a_nxt(n + 5,n / 3 + 1);
    MonotoneGetKth c_curr(n + 5,n / 3);
    MonotoneGetKth c_nxt(n + 5,n / 3 + 1);

    for(int i = 1;i <= n;i++){
        a_curr.add(i);
        a_nxt.add(i);
    }

    c_nxt.add(n + 1);///add A to c list
    a_nxt.add(n + 2);///add C to a list

    int target_point_cnt = n / 3;

    for(int i = 1;i <= n;i++){
        int c_fst,c_snd;
        int a_fst,a_snd;

        ///try to do it with point on A side
        c_fst = c_curr.get_kth_ind();
        c_snd = c_nxt.get_kth_ind();
        a_fst = a_curr.get_kth_ind();
        a_snd = a_nxt.get_kth_ind();

        if(1 < i && i < n && (!(a_fst == -1 || a_snd == -1 || c_fst == -1 || c_snd == -1))){
            double l = get_pos(n + 3,order_b[i],n + 2,order_c[c_fst]).first;
            double r = get_pos(n + 3,order_b[i],n + 2,order_c[c_snd]).first;
            double ll = get_pos(n + 3,order_b[i],n + 1,order_a[a_fst]).first;
            double rr = get_pos(n + 3,order_b[i],n + 1,order_a[a_snd]).first;
            if(sect(l,r,ll,rr)){
                print_sol(a_curr,c_curr,max(get_pos(n + 3,order_b[i],n + 2,order_c[c_fst]),get_pos(n + 3,order_b[i],n + 1,order_a[a_fst])));
            }
        }
       
        ///del point from A
        a_curr.rem(inv_a[order_b[i]]);
        a_nxt.rem(inv_a[order_b[i]]);


        ///try to do it with point on neither of those 
        if(1 < i && i < n && (!(a_fst == -1 || a_snd == -1 || c_fst == -1 || c_snd == -1))){
            double l = get_pos(n + 3,order_b[i],n + 2,order_c[c_fst]).first;
            double r = get_pos(n + 3,order_b[i],n + 2,order_c[c_snd]).first;
            double ll = get_pos(n + 3,order_b[i],n + 1,order_a[a_fst]).first;
            double rr = get_pos(n + 3,order_b[i],n + 1,order_a[a_snd]).first;
            if(sect(l,r,ll,rr) && max(l,ll) <= point[order_b[i]].first){
                print_sol(a_curr,c_curr,max(get_pos(n + 3,order_b[i],n + 2,order_c[c_fst]),get_pos(n + 3,order_b[i],n + 1,order_a[a_fst])));
            }
        }
        
        ///add point to C
        c_curr.add(inv_c[order_b[i]]);
        c_nxt.add(inv_c[order_b[i]]);

        ///try to do it with point on C side
        c_fst = c_curr.get_kth_ind();
        c_snd = c_nxt.get_kth_ind();
        a_fst = a_curr.get_kth_ind();
        a_snd = a_nxt.get_kth_ind();
    
        if(1 < i && i < n && (!(a_fst == -1 || a_snd == -1 || c_fst == -1 || c_snd == -1))){
            double l = get_pos(n + 3,order_b[i],n + 2,order_c[c_fst]).first;
            double r = get_pos(n + 3,order_b[i],n + 2,order_c[c_snd]).first;
            double ll = get_pos(n + 3,order_b[i],n + 1,order_a[a_fst]).first;
            double rr = get_pos(n + 3,order_b[i],n + 1,order_a[a_snd]).first;
            if(sect(l,r,ll,rr)){
                print_sol(a_curr,c_curr,max(get_pos(n + 3,order_b[i],n + 2,order_c[c_fst]),get_pos(n + 3,order_b[i],n + 1,order_a[a_fst])));
            }
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
