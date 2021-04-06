#include <bits/stdc++.h>

using namespace std;

const int n = 100;
const int q = 10000;

const double eps = 1e-5;

const bool HOME = false;

const int ST = 50;
const int DR = q - 700;

string s[n + 5];

int t;
int p;

double skill[n + 5];
double diff[q + 5];

double real_skill[n + 5];
double real_diff[q + 5];

double area_skill[n + 5];

int order[q + 5];

double eval(double x){
    return 1 / (1 + exp(-x));
}

double skill_probability(double x){
    return double(1) / 6 * log((1 + exp(x + 3)) / (1 + exp(x - 3)));
}

double get_expected_answers(double x,int cheater){
    double ans = 0;

    for(int i = 1;i <= n;i++){
        if(cheater == i){
            continue;
        }
        ans += eval(real_skill[i] - x);
    }

    return ans;
}

void get_queries_difficulties(int cheater){
    for(int j = 0;j < q;j++){
        double l = -3 -eps;
        double r = 3 + eps;
        
        int real_answers = 0;

        for(int i = 1;i <= n;i++){
            real_answers += (s[i][j] - '0') * (i != cheater);
        }

        while(r - l > eps){
            double mid = (l + r) / 2;

            if(get_expected_answers(mid,cheater) < real_answers){
                r = mid;
            }else{
                l = mid;
            }
        }
        real_diff[j] = l; 
    }
}

bool cmp(int a,int b){
    return real_diff[a] < real_diff[b];
}

int run_test(){
   
    for(int i = 1;i <= n;i++){
        double current_probability = 0;

        for(int j = 0;j < q;j++){
            current_probability += s[i][j] - '0';
        }

        current_probability /= q;

        double l = -3 - eps;
        double r = 3 + eps;

        while(r - l > eps){
            double mid = (l + r) / 2;

            if(skill_probability(mid) < current_probability){
                l = mid;
            }else{
                r = mid;
            }
        }
        real_skill[i] = r;
        area_skill[i] = log((1 + exp(real_skill[i] + 3)) / (1 + exp(real_skill[i] - 3)));
    }

    get_queries_difficulties(-1);

/*
    fprintf(stderr,"debug info\n");

    for(int i = 1;i <= n;i++){
        fprintf(stderr,"%.2f ",abs(skill[i] - real_skill[i]));
    }
    fprintf(stderr,"\n");
    */
    double biggest_diff = 0;
    double lowest_diff = 10;
    for(int j = 0;j < q;j++){
        //fprintf(stderr,"%.2f ",abs(diff[j] - real_diff[j]));
        biggest_diff = max(biggest_diff,abs(diff[j] - real_diff[j]));
        lowest_diff = min(lowest_diff,abs(diff[j] - real_diff[j]));
    }
    //fprintf(stderr,"\n");

    fprintf(stderr,"biggest_diff is %2f %2f\n",lowest_diff,biggest_diff);

    int best;
    double best_cost = 1;

    for(int j = 0;j < q;j++){
        order[j] = j;
    }
    
    sort(order,order + q,cmp);

    for(int i = 1;i <= n;i++){
        long double probability = 0;
        for(int j = 0;j < q;j++){
            if(ST <= j && j < DR){
    //        if(-2.4 <= real_diff[order[j]] && real_diff[order[j]] <= 2.3){
                continue;
            }
            if(s[i][order[j]] == '1'){
                probability += log(eval(real_skill[i] - real_diff[order[j]]));
            }else{
                probability += log(1 - eval(real_skill[i] - real_diff[order[j]]));
            }
        }
        if(probability < best_cost){
            best_cost = probability;
            best = i;
        }
    }

    return best;
}

void stress_test(){

    t = 50;
    p = 86;

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    uniform_real_distribution<double> distrib(-3.0,3.0);
    uniform_int_distribution<int> player(1,n);

    int ans = 0;

    for(int test = 1;test <= t;test++){
        printf("doing %d\n",test);
        for(int i = 1;i <= n;i++){
            skill[i] = distrib(gen);
        }
        for(int i = 0;i < q;i++){
            diff[i] = distrib(gen);
        }

        int cheater = player(gen);

        for(int i = 1;i <= n;i++){
            s[i] = string(q,'0');
            for(int j = 0;j < q;j++){
                if(i == cheater && (gen() % 2 == 1)){
                    s[i][j] = '1';
                }else{
                    double tmp = eval(skill[i] - diff[j]);
                    discrete_distribution<int> win({1 - tmp,tmp});
                    s[i][j] = '0' + win(gen);
                }
            }
        }
        printf("running now with cheater %d:\n",cheater);
        ans += (run_test() == cheater);
    }

    printf("accuracy %.10f\n",double(ans) / t);
    exit(0);
}

void real_solve(){
    cin >> t;
    cin >> p;

    for(int test = 1;test <= t;test++){
        for(int i = 1;i <= n;i++){
            cin >> s[i];
        }
        cout << "Case #" << test << ": " << run_test() << "\n";
    }
}

int main(){
    if(HOME){
        stress_test();
    }else{
        real_solve();
    }
    return 0;
}


