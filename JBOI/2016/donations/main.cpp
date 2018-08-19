#include <iostream>
#include <string>
using namespace std;

//DON'T EDIT THIS FUNCTION, AS IT'S HERE TO SUPPORT
//THE COMMUNICATION WITH THE INTERACTIVE GRADER
int count(string expression) {
	cout << expression << endl;

	int matchingRecords;
	cin >> matchingRecords;
	return matchingRecords;
}
string tostring(int nr)
{
    if(nr==0)return "0";
    string rez;
    while(nr)
    {
        rez=char(nr%10+'0')+rez;
        nr/=10;
    }
    return rez;
}

//YOUR SOLUTION STARTS HERE
int findMoney(int N) {
    int age=99;
    while(1)
    {
        int nr=count("age<="+tostring(age)+"&&name!=bidik");
        if(nr!=0)break;
        age--;
    }
    age--;
    int tmp=count("age<="+tostring(age)+"&&name!=bidik");
    long long st=0,dr=2000000000-1;
    while(st<dr)
    {
        long long mid=(st+dr+1)/2;
        int nr=count("age<="+tostring(age)+"&&name!=bidik||name==bidik&&money>="+tostring(mid));
        if(nr!=tmp+1)dr=mid-1;
        else st=mid;
    }
    return st;
}

int main(){
	int n;
	cin >> n;

	cout << findMoney(n) << endl;
	return 0;
}
