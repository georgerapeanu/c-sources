#include <cstdio>
#include <cstring>
#include <algorithm>
#include <complex>
///bagami-as pula stiam ca nu trebuia sa dam fft
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
const int NMAX = 1 << 16;
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
int N,M,T;
 
int main(){
	
	for(int i = 0;i < NMAX;i++){
		for(int j = 0;j < 16;j++){
			ord[i] |= (((i >> j) & 1) << (15 - j));
		}
	}
	
    fscanf(f,"%d",&T);
 
    while(T--){
 
        memset(A,0,sizeof(A));
		memset(B,0,sizeof(B));
 
        fscanf(f,"%d",&N);
 
        for(int i = 0;i < N;i++){
            int x;
            fscanf(f,"%d",&x);
            A[x].a += 1;
        }
 
        fscanf(f,"%d",&M);
 
        for(int i = 0;i < M;i++){
            int x;
            fscanf(f,"%d",&x);
            B[x].a += 1;
        }
 
        mult(A,B,R);
 
        for(int i = 0;i < NMAX;i++){
            int aux = round(R[i].real());
            if(aux > 0){
                fprintf(g,"%d %d\n",i,aux);
            }
        }
 
        fprintf(g,"\n");
    }
 
    fclose(f);
    fclose(g);
 
    return 0;
}