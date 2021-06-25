#include <iostream>
#include <math.h>

using namespace std;

bool same (int a){
	for(int x = 0; x < 5; x++){
	       	if (((int)(a / pow(10,x))) % 10 == (int)(a / pow(10,x+1))%10){
			if (((int)(a / pow(10,x))) % 10 == (int)(a / pow(10,x+2))%10){
				int m = ((int)(a / pow(10,x))) % 10;
				while(m == ((int)(a / pow(10,x+1))) % 10) x++;
				continue;
			}
			return true;
		}
	}
	return false;
}

bool mono (int a){
	for(int x = 5; x > 0; x--) if ((int)(a / pow(10,x)) % 10 > (int)(a/ pow(10,x-1))%10) return false;
	return true;
}

int main(){
	int a = 147981;
	int b = 691423;
	int total = 0;
	for(int x = a; x < b; x++) if (same(x) && mono(x)) total++;
	cout << total << endl;
	return 0;
}
