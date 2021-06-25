#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

const int INPUT = 5;

struct op{
	int o;
	int a;
	int b;
	int c;
};

op conv(int a){
	op o;
	o.o = a % 100; 
	o.c = ((int)(a / pow(10,2))) % 10;
	o.b = ((int)(a / pow(10,3))) % 10;
	o.a = ((int)(a / pow(10,4))) % 10;
	return o;
}

int val(vector<int>& vect, int mode, int pos){
	if (mode == 1) return vect[pos];
	return vect[vect[pos]];
}

void step(vector<int>& vect, int& pos){
	op o = conv(vect[pos]);
	if (o.o == 1){
		vect[vect[pos+3]] = val(vect, o.b, pos+2) + val (vect, o.c, pos+1);
		pos += 4;
		return;
	}
	if (o.o == 2){
		vect[vect[pos+3]] = val(vect, o.b, pos+2) * val (vect, o.c, pos+1);
		pos += 4;
		return;
	}
	if (o.o == 3){
		vect[vect[pos+1]] = INPUT;
		pos += 2;
		return;
	}
	if (o.o == 4){
		cout << val(vect, o.c, pos+1) << endl;
		pos += 2;
		return;
	}
	if (o.o == 5){
		if( val(vect, o.c, pos+1) != 0) {
			pos = val(vect, o.b, pos+2);
			return;
		}
		pos +=3;
		return;
	}
	if (o.o == 6){
		if( val(vect, o.c, pos+1) == 0) {
			pos = val(vect, o.b, pos+2);
			return;
		}
		pos +=3;
		return;
	}
	if (o.o == 7){
		if(val(vect, o.c, pos+1) < val(vect, o.b, pos+2)){
			vect[vect[pos+3]] = 1;
		}else{
			vect[vect[pos+3]] = 0;
		}
		pos += 4;
		return;
	}
	if (o.o == 8){
		if(val(vect, o.c, pos+1) == val(vect, o.b, pos+2)){
			vect[vect[pos+3]] = 1;
		}else{
			vect[vect[pos+3]] = 0;
		}
		pos += 4;
		return;
	}
		
	if (o.o == 99){
		pos = -1;
		return;
	}
	pos++;
}

void run(vector<int> vect){
	int pos = 0;
	while(pos != -1){
		step(vect, pos);
	}
}

int main() {
	string line;
	vector<int> vect;
	ifstream myfile ("input");
	getline(myfile,line);
	stringstream ssin(line);

	for (int i; ssin >> i;) {
		vect.push_back(i);
		if (ssin.peek() == ',') ssin.ignore();
	}
	
	run(vect);
}
