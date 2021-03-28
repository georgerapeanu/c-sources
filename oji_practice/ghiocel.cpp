#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> get_digits(long long n){
    vector<int> digits;

    while(n){
        digits.push_back(n % 10);
        n /= 10;
    }

    reverse(digits.begin(),digits.end());
    return digits;
}

bool is_urcas(long long n){
    vector<int> digits = get_digits(n);
    int ind = 0;

    while(ind < (int)digits.size() - 1 && digits[ind] < digits[ind + 1]){
        ind++;
    }

    return ind == (int)digits.size() - 1;
}

bool is_coboras(long long n){
    vector<int> digits = get_digits(n);
    int ind = 0;

    while(ind < (int)digits.size() - 1 && digits[ind] > digits[ind + 1]){
        ind++;
    }

    return ind == (int)digits.size() - 1;
}

bool is_deal(long long n){
    vector<int> digits = get_digits(n);
    int ind = 0;

    while(ind < (int)digits.size() - 1 && digits[ind] < digits[ind + 1]){
        ind++;
    }

    if(ind == 0 || ind == (int)digits.size() - 1){
        return false;
    }
    
    while(ind < (int)digits.size() - 1 && digits[ind] > digits[ind + 1]){
        ind++;
    }

    return ind == (int)digits.size() - 1;
}

bool is_vale(long long n){
    vector<int> digits = get_digits(n);
    int ind = 0;

    while(ind < (int)digits.size() - 1 && digits[ind] > digits[ind + 1]){
        ind++;
    }

    if(ind == 0 || ind == (int)digits.size() - 1){
        return false;
    }
    
    while(ind < (int)digits.size() - 1 && digits[ind] < digits[ind + 1]){
        ind++;
    }

    return ind == (int)digits.size() - 1;
}

int n;
long long value;
int cnt_urcas;
int cnt_coboras;
int cnt_deal;
int cnt_vale;

int main(){
   
    freopen("ghiocel.in","r",stdin);
    freopen("ghiocel.out","w",stdout);

    scanf("%d",&n);

    while(n--){
        scanf("%lld",&value);
        cnt_urcas += is_urcas(value);
        cnt_coboras += is_coboras(value);
        cnt_deal += is_deal(value);
        cnt_vale += is_vale(value);
    }

    printf("%d\n%d\n%d\n%d\n",cnt_urcas,cnt_coboras,cnt_deal,cnt_vale);

    return 0;
}
