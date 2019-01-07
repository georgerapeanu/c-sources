#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n;
long long l[NMAX + 5];
char s[NMAX + 5];

int main(){
	
	fscanf(stdin,"%d\n",&n);
	for(int i = 1;i <= n;i++){
		fscanf(stdin,"%lld ",&l[i]);
	}
	
	fscanf(stdin,"\n");
	fgets(s + 1,NMAX + 5,stdin);

	long long stamina = 0;
	long long time = 0;
	long long g2 = 0;
	bool water = false;
	
	for(int i = 1;i <= n;i++){
		if(s[i] == 'L'){
			time += l[i];
			stamina -= l[i];
			if(stamina < 0){
				time += (-stamina) * (water ? 3 : 5);
				stamina = 0;
			}
		}
		else if(s[i] == 'W'){
			time += 3 * l[i];
			stamina += l[i];
			water = true;
		}
		else{
			time += 5 * l[i];
			stamina += l[i];
			g2 += l[i] * 2;
		}
		
		g2 = min(g2,stamina);
	}
	
	if(stamina > 0){
		time -= (g2) * 2;
		time -= (stamina - g2);
	}
	
	printf("%lld",time);
	
	return 0;
}