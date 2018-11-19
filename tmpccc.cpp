#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
#include <vector>

using namespace std;

FILE * f = fopen("ccc.in","r");
FILE * g = fopen("ccc.out","w");

const double eps = 1-6;

int aprox(double d){
	if(((int)d + 1) - d < eps){
		return (int)d + 1;
	}
	return d;
}

int main(){


	int n;
	fscanf(f,"%d",&n);
	
	for(int i = 1;i <= n;i++){
		double r1,c1,r2,c2;
		fscanf(f,"%lf %lf %lf %lf\n",&r1,&c1,&r2,&c2);
		
		if(r1 == r2){
			for(int i = min(c1,c2);i <= max(c1,c2);i++){
				fprintf(g,"%d %d ",(int)r1,i);
			}
			fprintf(g,"\n");
			continue;
		}
		
		if(c1 == c2){
			for(int i = min(r1,r2);i <= max(r1,r2);i++){
				fprintf(g,"%d %d ",i,(int)c1);
			}
			fprintf(g,"\n");
			continue;
		}
		
		for(int i = min(r1,r2);i <= max(r1,r2);i++){
			for(int j = min(c1,c2);j <= max(c1,c2);j++){
				double a = (c2 - c1) / (r2 - r1);
				double b = c1 + 0.5 - a * (r1 + 0.5);
				double x1 = i;
				double x2 = i + 1;
				double x3 = (j - b) / a;
				double x4 = (j + 1 - b) / a;
				
				// if(i == 11 && j == 10)printf("%lf %lf %lf %lf\n",x1,x2,x3,x4);
				
				if(x1 > x2)swap(x1,x2);
				if(x3 > x4)swap(x3,x4);
				
				if(x2 < x3 || x4 < x1){
					;
				}
				else{
					fprintf(g,"%d %d ",(int)i,(int)j);
				}
			}
		}
			fprintf(g,"\n");
		
	}

	fclose(f);
	fclose(g);
	
	return 0;
}