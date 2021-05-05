#include <bits/stdc++.h>

const int MAX_N = 100000;

bool show_best = false;
bool show_distinct = false;

// Print the usage of the program
void print_usage() {
    fprintf(stderr, "Usage: <program> [OPTIONS] N Q\n");
    fprintf(stderr, "where N is the size of the permutation\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "   --show-best      Show the generated 'best' vector for the given perm\n");
    fprintf(stderr, "   --show-distinct  Show the number of distinct answers\n");
    exit(1);
}

// Parse an argument as an unsigned int
int parse_arg(char* argv) {
    int i = 0;
    int nr = 0;

    if(!isdigit(argv[i]))
        print_usage();

    while(isdigit(argv[i])) {
        nr = nr * 10 + argv[i] - '0';
        i++;
    }

    if(argv[i] != '\0')
        print_usage();

    return nr;
}

// BIT code
int aib[1+MAX_N];
static inline int lsb(int x) {
    return x & (-x);
}

void update_aib(int pos, int val) {
    while(pos <= MAX_N) {
        aib[pos] += val;
        pos += lsb(pos);
    }
}

int query_aib(int pos) {
    int res = 0;
    while(pos > 0) {
        res = res + aib[pos];
        pos -= lsb(pos);
    }
    return res;
}

void init_aib() {
    for(int i = 1; i <= MAX_N; ++i)
        aib[i] = 0;
}

// nr_inv[i] = the number of inversions if we rotate the array
//             by i positions
long long nr_inv[MAX_N];

// best[i] = the best number of rotations divisible by i
int best[1+MAX_N];

// best_rotations[div][rem] = what is the best answer for the query with gcd=div and remainder rem
std::map<int, std::map<int, long long> > best_rotations;

int check_perm(int n, int *a) {
    init_aib();

    // Calculate the number of inversions in the original array
    for(int i = 0; i < n; ++i) {
        // We want to see how many elements greater than a[i] are there in
        // the prefix of size i - 1
        
        // To do that, we use a BIT. To do that, we mark element a[i] and see how many
        // elements from a[i] + 1...n - 1 are already marked
        
        // Since BIT doesn't work with suffix sums (it does, but it's inefficient)
        // we will transform the element a[i] into n - a[i], so that we will have to
        // do a prefix sum (in a way, reverse the elements

        // Because of this transformation, the elements will be in range 1..n,
        // so the BIT will work (BIT goes into an infinit loop if you update the position 0)

        nr_inv[0] = nr_inv[0] + query_aib(n - a[i]);
        update_aib(n - a[i], 1);
    }

    // We move the first element to the end and see how the number
    // of inversions changes
    // When we erase the element x from the beginning we lose the inversions with:
    // 0, 1, 2, 3, 4, ..., x - 1 => x elements
    // When we append the element x to the end, we will get the inversions with:
    // x + 1, x + 2, ..., n - 1 => n - x - 1 elements
    for(int i = 0; i < n - 1; ++i)
        nr_inv[i + 1] = nr_inv[i] + (n - a[i] - 1) - a[i];

    // Contains the divisors of n
    std::vector<int> divisors;

    // To calculate best, we simply do a brute-force
    // It will have a complexity of O(NlogN)
    for(int d = 1; d < n; ++d)
        if(n % d == 0) {
            best_rotations[d].clear();
            for(int i = 0; i < n; ++i) {
                if(best_rotations[d].find(i % d) != best_rotations[d].end()) {
                    best_rotations[d][i % d] = std::min(best_rotations[d][i % d], nr_inv[i]);
                } else
                    best_rotations[d][i % d] = nr_inv[i];
            }
            divisors.push_back(d);
        }

    // See which rotations yields the most answers
    int best_rot = 0, distinct_answers = 0;
    for(int i = 0; i < n; ++i) {
        std::vector<long long>answers;
        for(auto it: divisors) {
            answers.push_back(best_rotations[it][i % it]);
        }
        std::sort(answers.begin(), answers.end());
        int nr_distinct = 1;
        for(int i = 0; i + 1 < answers.size(); ++i)
            if(answers[i] != answers[i + 1])
                ++nr_distinct;
        
        if(nr_distinct > distinct_answers) {
            distinct_answers = nr_distinct;
            best_rot = i;
        }
    }
    
    std::reverse(a, a + best_rot);
    std::reverse(a + best_rot, a + n);
    std::reverse(a, a + n);

    if(show_distinct)
        fprintf(stderr, "Rotation %d yields %d distinct answers\n", best_rot, distinct_answers);

    return best_rot;
}

int gcd(int a,int b){
    if(!b)return a;
    return gcd(b,a % b);
}

std::vector<int> get_query(int n,int g,std::mt19937 &rng,int forced_m){
    int _n = n;
    assert(n % g == 0);

    n /= g;

    assert(n > 1);
    
    std::vector<int> primes;

    bool hasExpGr2 = false;

    for(int i = 2;1LL * i * i <= n;i++){
        if(n % i == 0){
            int exp = 0;
            primes.push_back(i);
            while(n % i == 0){
                n /= i;
                exp++;
            }
            hasExpGr2 |= (exp > 1);
        }
    }

    if(n != 1){
        primes.push_back(n);
        n /= n;
    }
    
    int MASK_ALL = (1 << ((int)primes.size())) - 1;

    std::vector<int> confs;

    int max_pop_count = ((int)primes.size()) - 1;

    int minimum_primes = (rng() % (max_pop_count + 1));

    for(int i = 0;i < (int)MASK_ALL + int(hasExpGr2);i++){
        if(__builtin_popcount(i) >= minimum_primes){
            confs.push_back(i);
        }
    }

    std::shuffle(confs.begin(),confs.end(),rng);

    int low = confs.size() / 2;
    int high = (int)confs.size() - 1;

    if(forced_m != -1){
        if(forced_m >= (int)confs.size()){
            return {};
        }
        low = high = forced_m - 1;
    }

    confs.resize((rng() % (high - low + 1)) + low);

    std::vector<int> answer;

    int mask = MASK_ALL;
    for(auto it:confs){
        mask &= it;
        int p = 1;
        for(int i = 0;i < (int)primes.size();i++){
            if((it >> i) & 1){
                p *= primes[i];
            }
        }
        answer.push_back(p);
    }

    if(mask != 0){
        int conf = (MASK_ALL ^ mask);
        int p = 1;
        for(int i = 0;i < (int)primes.size();i++){
            if((conf >> i) & 1){
                p *= primes[i];
            }
        }
        answer.push_back(p);
    }
    
    while(((int)answer.size()) < forced_m){
       answer.push_back(answer.back());
    }

    if(forced_m != -1){
        assert((int)answer.size() == forced_m);
    }

    std::sort(answer.begin(),answer.end());

    for(auto &it:answer){
        it *= g;
    }
    
    int actual_gcd = 0;

    for(auto it:answer){
        actual_gcd = gcd(actual_gcd,it);
        assert(_n % it == 0 && 1 <= it && it < _n);
    }

    assert(actual_gcd == g);

    return answer;
}

int a[MAX_N];

int main(int argc, char** argv) {
    for(int i = 1; i < argc - 3; ++i) {
        if(std::string("--show-best") == argv[i])
            show_best = true;
        else if(std::string("--show-distinct") == argv[i])
            show_distinct = true;
        else
            print_usage();
    }

    int N = parse_arg(argv[argc - 3]);

    fprintf(stderr, "Parsed argument: %d\n", N);
    
    int Q = parse_arg(argv[argc - 2]);
    fprintf(stderr, "Parsed argument: %d\n", Q);
    
    int forced_m = parse_arg(argv[argc - 1]);
    forced_m = (forced_m == 69 ? -1:forced_m);
    
    fprintf(stderr, "Parsed argument: %d\n", forced_m);

    
    for(int i = 0; i < N; ++i)
        a[i] = i;

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(a, a + N,rng);
    check_perm(N, a);
    //assert(check_perm(N, a) == 0);

    if(show_best) {
        fprintf(stderr, "Number of inversions: ");
        for(int i = 0; i < N; ++i)
            fprintf(stderr, "%lld ", nr_inv[i]);
        fprintf(stderr, "\nBest answer         : ");
        for(int i = 1; i < N; ++i)
            fprintf(stderr, "%d ", best[i]);
        fprintf(stderr, "\n");
    }
    std::vector<int> ds;

    for(int i = 1;i < N;i++){
        if(N % i == 0){
            ds.push_back(i);
        }
    }

    std::vector<std::vector<int> > queries;

    int total_size = 0;

    for(int i = 0;(int)queries.size() < Q;i++){
        if(i % ((int)ds.size()) == 0){
            shuffle(ds.begin(),ds.end(),rng);
        }
        std::vector<int> query = get_query(N,ds[i % ((int)ds.size())],rng,forced_m);

        if(query.empty()){
            continue;
        }
        total_size += (int)query.size();
        if(total_size > 200000){
            Q = (int)queries.size();
            break;
        }
        queries.push_back(query);
    }
    
    printf("%d %d\n", N,Q);
    for(int i = 0; i < N; ++i)
        printf("%d ", a[i]);
    printf("\n");
    
    for(auto query:queries){
        printf("%d ",(int)query.size());

        for(auto it:query)printf("%d ",it);
        printf("\n");
    }

    return 0;
}


