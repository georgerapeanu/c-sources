/// ultime doua cifre nenule
/*#include <iostream>

using namespace std;

int main(){
    int n,cifra=0,p,r;

    cin>>n;
    p=n%10;
    r=(n/10)%10;
    if(p!=0&&r!=0)cout<<"da";

    else{ cout<<"nu";

    }
    return 0;
}
*/
/*
///aria triugnhiului cu laturi a,b,c;
#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int a,b,c;
    float p,aria;
    cin>>a;
    cin>>b;
    cin>>c;
    p=(a+b+c)/2;
    aria=sqrt(p*(p-a)*(p-b)*(p-c));
    cout << aria;
    return 0;
}
*/
/*
///verificare prima cifra
#include <iostream>
using namespace std;

int main()
{
    int n,c;
    cin >> n >> c;
    int cf = 0;
    /*  int cn = n;

      while(cn > 0){
          cf++; /// numarul cifrelor creste
          cn /= 10; /// o dam afara pe ultima
      }

      int p10 = 1;
      int i;

      for(i = 1;i <= cf - 1;i++){
          p10 = p10 * 10;
      }

      int prima_cifra = n / p10;

      if(c == prima_cifra){
          cout <<"da ";
      }
      else{
          cout << "nu";
      }

    int uc = 0;

    while(n > 0)
    {
        uc = n % 10;
        n /= 10;
    }

    if(uc == c)
    {
        cout << "da";
    }
    else
    {
        cout << "nu";
    }

    return 0;
}
*/

/* algoritmu lui euclid
    int cmmdc(int a,int b){

        while(b != 0){
            int rest = a % b;
            a = b;
            b = rest;
        }

        return a;
    }
    ///cmmmc * cmmdc = a * b
*/

///verificare numar prim
#include <fstream>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

///int functie(parametrii){...;return 0;}

int e_prim(int n){
    for(int numar = 2;numar <= n / 2;numar++){
        if(n % numar){
            return 0;
        }
    }
    return 1;
}

int main(){

    int n;

    cin >> n;

    if(e_prim(n)){
        cout << "e prim";
    }
    else{
        cout << "nu e prim";
    }

    return 0;
}
*/
