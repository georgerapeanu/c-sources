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
  
  complex_t operator * (const complex_t &other)const{
    return complex_t(this->a * other.a - this->b * other.b, this->b * other.a + this->a * other.b);
  }

  void afis(){
    printf("%.4f %.4f\n",(double)a,(double)b);
  }
};

const int LGMAX = 17;

complex_t tmp[1 << LGMAX];
complex_t pw[LGMAX + 1];
complex_t invpw[LGMAX + 1];
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
    for(int offset = 0;offset < (1 << k);offset += (1 << h)){
      int hlf = (1 << (h - 1));
      complex_t root = complex_t(1,0);
      complex_t modifier = my_pw[k - h + 1];
      for(int i = 0;i < (1 << h);i++){
        if(i < hlf){
          tmp[i] = a[offset + i] + root * a[offset + i + hlf];
        }else{
          tmp[i] = a[offset + i - hlf] + root * a[offset + i];
        }
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
  
  freopen("bacterii2.in","r",stdin);
  freopen("bacterii2.out","w",stdout);

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
      for(int i = 0;i < k;i++){
        int tmp;
        scanf("%d",&tmp);
        a[tmp].a++;
      }
      scanf("%d",&k);
      for(int i = 0;i < k;i++){
        int tmp;
        scanf("%d",&tmp);
        b[tmp].a++;
      }
      fft(LGMAX,a,false);
      fft(LGMAX,b,false);
      for(int i = 0;i < (1 << LGMAX);i++){
        a[i] = a[i] * b[i];
      }
      fft(LGMAX,a,true);
      for(int i = 0;i < (1 << LGMAX);i++){
        a[i].a /= (1 << LGMAX);
        int ans = round(a[i].a);

        if(ans > 0){
          printf("%d %d\n",i,ans);
        }
      }
      printf("\n");
    }

    return 0;
}
