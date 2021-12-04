#include <bits/stdc++.h>

using namespace std;

struct complex_t{
  long double a,b;

  complex_t(long double a = 0,long double b = 0){
    this->a = a;
    this->b = b;
  }

  complex_t operator + (const complex_t &other)const{
    return complex_t(this->a + other.a, this->b + other.b);
  }
  
  complex_t operator - (const complex_t &other)const{
    return complex_t(this->a - other.a, this->b - other.b);
  }

  complex_t operator * (const complex_t &other)const{
    return complex_t(this->a * other.a - this->b * other.b, this->b * other.a + this->a * other.b);
  }

  void afis(){
    printf("%.4f %.4f\n",(double)a,(double)b);
  }
};

const int LGMAX = 17;
const long double eps = 1e-7;

complex_t tmp[1 << LGMAX];
complex_t pw[LGMAX + 1];
complex_t invpw[LGMAX + 1];

///pw[i] = (1^(1/2^LGMAX)) ^ 2^(i-1)

void fft(int k,complex_t a[],bool inv){
  complex_t *my_pw;

  if(inv == false){
    my_pw = pw;
  }else{
    my_pw = invpw;
  }
  
  int lst = 0;
  for(int i = 0;i < (1 << k);i++){
    int new_i = 0;
    for(int h = 0;h < k;h++){
      new_i <<= 1;
      new_i |= ((i >> h) & 1);
    }

    tmp[lst++] = a[new_i];
  }
  for(int i = 0;i < (1 << k);i++){
   a[i] = tmp[i];
  }
  for(int h = 1;h <= k;h++){
    int hlf = (1 << (h - 1));
    for(int offset = 0;offset < (1 << k);offset += (1 << h)){
      complex_t root = complex_t(1,0);
      complex_t modifier = my_pw[k - h + 1];
      for(int i = 0;i < hlf;i++){
        tmp[i] = a[offset + i] + root * a[offset + hlf + i];
        tmp[hlf + i] = a[offset + i] - root * a[offset + hlf + i];
        root = root * modifier;
      }
      for(int i = 0;i < (1 << h);i++){
        a[offset + i] = tmp[i];
      }
    }
  }
}

complex_t a[1 << LGMAX];
complex_t b[1 << LGMAX];

int main(){
    
    const long double PI = acos(-1);
    const long double angle = 2 * PI / (1 << LGMAX);
    
    int t;
    scanf("%d",&t);

    invpw[0] = pw[0] = complex_t(1,0);
    pw[1] = complex_t(cos(angle),sin(angle));
    invpw[1] = pw[1];
    invpw[1].b *= -1;
    for(int i = 2;i <= LGMAX;i++){
      pw[i] = pw[i - 1] * pw[i - 1];
      invpw[i] = invpw[i - 1] * invpw[i - 1];
    }

    for(int test = 1;test <= t;test++){
      for(int i = 0;i < (1 << LGMAX);i++){
        a[i] = b[i] = complex_t();
      }
      int k;
      scanf("%d",&k);
      for(int i = 0;i <= k;i++){
        int tmp;
        scanf("%d",&tmp);
        a[i].a = tmp;
      }
      scanf("%d",&k);
      for(int i = 0;i <= k;i++){
        int tmp;
        scanf("%d",&tmp);
        b[i].a = tmp;
      }
      fft(LGMAX,a,false);
      fft(LGMAX,b,false);
      for(int i = 0;i < (1 << LGMAX);i++){
        a[i] = a[i] * b[i];
      }
      fft(LGMAX,a,true);

      int ans_grad = 0;

      for(int i = 0;i < (1 << LGMAX);i++){
        if(round(a[i].a)){
          ans_grad = i;
        }
      }

      printf("Case %d: %d ",test,ans_grad);
      for(int i = 0;i <= ans_grad;i++){
        a[i].a /= (1 << LGMAX);
        printf("%d ",int(round(a[i].a)));
      }
      printf("\n");
    }

    return 0;
}
