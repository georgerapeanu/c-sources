#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int NMAX = 1e6;

int t;
pair<int,int> a,b,c;

int fact[NMAX + 5];
int ifact[NMAX + 5];

int add(int a,int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a,int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a,int b){
  return 1LL * a * b % MOD;
}

int lgpow(int base,int exp){
  int ans = 1;

  while(exp){
    if(exp & 1){
      ans = mult(ans,base);
    }
    base = mult(base,base);
    exp >>= 1;
  }

  return ans;
}

int comb(int n,int k){
  if(k < 0 || k > n){
    return 0;
  }
  int tmp =  mult(fact[n],mult(ifact[k],ifact[n - k]));
  return tmp;
}

long long gcd(long long p,long long q){
  if(q == 0){
    return (p < 0 ? -p:p);
  }
  return gcd(q,p % q);
}

class Fraction{
public:
  long long p;
  long long q;

public:
  Fraction(long long p,long long q){
    long long g = gcd(p,q);
    this->p = p / g;
    this->q = q / g;
    if(this->q < 0){
      this->q *= -1;
      this->p *= -1;
    }
  }

  bool operator == (const Fraction &other)const{
    return this->p == other.p && this->q == other.q;
  }

  bool operator < (const Fraction &other)const{
    if(this->p == 0){
      return other.p > 0;
    }
    if(other.p == 0){
      return this->p < 0;
    }
    if((this->p > 0 ? 1:-1) * (other.p > 0 ? 1:-1) < 0){
      return this->p < 0;
    }
    if(this->p / this->q != other.p / other.q){
      return this->p / this->q < other.p / other.q;
    }

    return 1LL * (this->p % this->q) * other.q < 1LL * (other.p % other.q) * this->q;

  }

  long long ceil(){
    if(p < 0){
      return (-((-p) / q));
    }
    return (p / q) + ((p % q) > 0);
  }
  long long floor(){
    if(p < 0){
      return (-((-p) / q)) - (((-p) % q) > 0);
    }
    return p / q;
  }
};

struct line_t{
  int a;
  int b;
  long long c;
};

int main(){
    
    fact[0] = 1;
    for(int i = 1;i <= NMAX;i++){
      fact[i] = mult(fact[i - 1],i);
    }
    ifact[NMAX] = lgpow(fact[NMAX],MOD - 2);
    for(int i = NMAX - 1;i >= 0;i--){
      ifact[i] = mult(ifact[i + 1],i + 1);
    }

    scanf("%d",&t);

    while(t--){
      int ans = 0;
      scanf("%d %d",&a.first,&a.second);
      scanf("%d %d",&b.first,&b.second);
      scanf("%d %d",&c.first,&c.second);

      a = make_pair(a.first + a.second,a.second - a.first);
      b = make_pair(b.first + b.second,b.second - b.first);
      c = make_pair(c.first + c.second,c.second - c.first);

      vector<pair<int,int> > points = {a,b,c};
      vector<line_t> lines;
      for(int i = 0,n = 1;i < 3;i++,n = (n == 2 ? 0:n + 1)){
        int a = points[n].second - points[i].second;
        int b = points[i].first - points[n].first;
        long long c = 0 - 1LL * a * points[i].first - 1LL * b * points[i].second;
        if(a < 0){
          a *= -1;
          b *= -1;
          c *= -1;
        }
        lines.push_back({a,b,c});
      }
      

      for(int y = 0;y <= 2 * NMAX;y += 2){
        vector<Fraction> inter;
        for(int i = 0,n = 1;i < 3;i++,n = (n == 2 ? 0:n + 1)){
          if(lines[i].a == 0){
            continue;
          }
          Fraction x = Fraction((- 1LL * lines[i].b * y - lines[i].c), lines[i].a);
          if((-1LL * lines[i].b * y - lines[i].c - 1LL * lines[i].a * min(points[i].first,points[n].first)) >= 0 && 
              -1LL * lines[i].b * y - lines[i].c - 1LL * lines[i].a * max(points[i].first,points[n].first) <= 0){
            inter.push_back(x);
          }
        }
        sort(inter.begin(),inter.end());
        for(int i = 0;i + 1 < (int)inter.size();i++){
          if(inter[i + 1] == inter[i]){
            for(int j = i;j + 1 < (int)inter.size();j++){
              inter[j] = inter[j + 1];
            }
            inter.pop_back();
            i--;
          }
        }
     
    /* 
        printf("@y=%d\n",y);
        for(auto it:inter){
          printf("(%lld %lld) ",it.p,it.q);
        }
        printf("\n");
    */  
        if((int)inter.size() == 0){
          continue;
        }
        if((int)inter.size() == 1){
          inter.push_back(inter[0]);
        }
        assert((int)inter.size() != 3);
        int left,right;
        left = inter[0].ceil();
        right = inter[1].floor();
        left = max(left,0);

        left += (left & 1);
        right -= (right & 1);

        if(left > right){
          continue;
        }
        ///(x,y) -> ((x + y) / 2,y / 2)
        ///comb((left + y) / 2,y / 2) + comb((left + y + 2) / 2,y / 2) + ... + comb((right + y) / 2, y / 2))
        ///comb((right + y + 2) / 2,y / 2 + 1) - comb((left + y) / 2,y / 2 + 1)
        ans = add(ans,comb(((right + y + 2) >> 1),(y >> 1) + 1));
        if(left > 0){
          ans = scad(ans,comb(((left + y + 0) >> 1),(y >> 1) + 1));
        }
      }
      printf("%d\n",ans);
    }

    return 0;
}
