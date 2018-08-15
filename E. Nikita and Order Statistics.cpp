#include <iostream>
#include <algorithm>

using namespace std;
  
FILE *f = fopen("bacterii2.in","r");
FILE *g = fopen("bacterii2.out","w");  
 
struct Complex{
    double a,b;
 
    Complex(){
    }
     
    Complex(double c,double d){
        a = c;
        b = d;
    }
 
    Complex operator + (const Complex &other)const{
        return Complex(a + other.a,b + other.b);
    }
 
    Complex operator * (const Complex &other)const{
        return Complex(a * other.a - b * other.b,a * other.b + b * other.a);
    }
 
    Complex conj()const{
        return Complex(a,-b);
    }
 
    double arg()const{
        return sqrt(a * a + b * b);
    }
     
    double sqrArg()const{
        return a * a + b * b;
    }
     
    Complex operator / (const Complex &other)const{
        Complex a = (*this) * other.conj();
        double arg = other.sqrArg();
        a.a /= arg;
        a.b /= arg;
        return a;
    }
 
    Complex operator - (const Complex &other)const{
        return Complex(a - other.a,b - other.b);
    }
     
    double real(){
        return a;
    }
     
    double imag(){
        return b;
    }
}; 
 
const double PI = acos(-1);
const int NMAX = 1 << 20;
int ord[NMAX];
  
 void FFT(Complex *In,Complex *Out,int N,bool inverse){
    for(int i = 0;i < NMAX;i++){
        Out[i] = In[ord[i]];
    }
    for(int step = 2;step <= NMAX;step *= 2){
        double angle = 2 * PI / step;
        Complex root,modifier(cos(angle),sin(angle) * (inverse == 1 ? -1 : 1));
        for(int i = 0;i < NMAX;i += step){
            root = Complex(1,0);
            for(int j = i;j < i + step / 2;j++){
                Complex aux = root * Out[step / 2 + j];
                Out[j + step / 2] = Out[j] - aux;
                Out[j] = Out[j] + aux;
                root = root * modifier;
            }
        }
    }       
 }
  
void mult(Complex *A,Complex *B,Complex *R){
    FFT(A,R,NMAX,0);
    FFT(B,A,NMAX,0);
  
    for(int i = 0;i < NMAX;i++){
        B[i] = R[i] * A[i] / Complex(NMAX,0);
    }
    FFT(B,R,NMAX,1);
}
  
Complex A[NMAX];
Complex B[NMAX];
Complex R[NMAX];
int N,X;
int S[NMAX];
int fr[NMAX];

int main(){
     
    for(int i = 0;i < NMAX;i++){
        for(int j = 0;j < 20;j++){
            ord[i] |= (((i >> j) & 1) << (19 - j));
        }
    }
    
	cin >> N >> X;

	fr[0] = 1;
	
	for(int i = 1;i <= N;i++){
		int val;
		cin >> val;
		S[i] = S[i - 1] + (val < X);
		fr[S[i]]++;
	}
	
	for(int i = 0;i <= N;i++){
		A[S[N] + S[i]].a++;
		B[S[N] - S[i]].a++;
	}
	
	mult(A,B,R);
	
	R[2 * S[N]].a = 0;
	
	for(int i = 0;i <= S[N];i++){
		R[2 * S[N]].a += 1LL * fr[i] * (fr[i] - 1) / 2;
	}
	
	for(int i = 2 * S[N];i <= 2 * S[N] + N;i++){
		cout << (long long)round(R[i].a) << " ";
	}
    return 0;
}