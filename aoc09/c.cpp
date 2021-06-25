#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

const int INPUT = 2;

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

long long val(vector<long long>& vect, int mode, int pos, int rb){
	if (mode == 1) return vect[pos];
	if (mode == 2) return vect[vect[pos] + rb];
	return vect[vect[pos]];
}

void step(vector<long long>& vect, int& pos, int& rb){
	op o = conv(vect[pos]);
	if (o.o == 1){
		if(o.a == 0){
			vect[vect[pos+3]] = val(vect, o.b, pos+2, rb) + val (vect, o.c, pos+1, rb);
		}else {
			vect[vect[pos+3] + rb] = val(vect, o.b, pos+2, rb) + val (vect, o.c, pos+1, rb);
		}
		pos += 4;
		return;
	}
	if (o.o == 2){
		if(o.a == 0){
			vect[vect[pos+3]] = val(vect, o.b, pos+2, rb) * val (vect, o.c, pos+1, rb);
		}else {
			vect[vect[pos+3] + rb] = val(vect, o.b, pos+2, rb) * val (vect, o.c, pos+1, rb);
		}
		pos += 4;
		return;
	}
	if (o.o == 3){
		if(o.c == 0){
			vect[vect[pos+1]] = INPUT;
		}else if(o.c == 2){
			vect[vect[pos+1] + rb] = INPUT;
		}
		pos += 2;
		return;
	}
	if (o.o == 4){
		cout << val(vect, o.c, pos+1, rb) << endl;
		pos += 2;
		return;
	}
	if (o.o == 5){
		if( val(vect, o.c, pos+1, rb) != 0) {
			pos = val(vect, o.b, pos+2, rb);
			return;
		}
		pos +=3;
		return;
	}
	if (o.o == 6){
		if( val(vect, o.c, pos+1, rb) == 0) {
			pos = val(vect, o.b, pos+2, rb);
			return;
		}
		pos +=3;
		return;
	}
	if (o.o == 7){
		if(o.a == 0){
			if(val(vect, o.c, pos+1, rb) < val(vect, o.b, pos+2, rb)){
				vect[vect[pos+3]] = 1;
			}else{
				vect[vect[pos+3]] = 0;
			}
		}else{
			if(val(vect, o.c, pos+1, rb) < val(vect, o.b, pos+2, rb)){
				vect[vect[pos+3]+rb] = 1;
			}else{
				vect[vect[pos+3]+rb] = 0;
			}
		}
		pos += 4;
		return;
	}
	if (o.o == 8){
		if(o.a == 0){
			if(val(vect, o.c, pos+1, rb) == val(vect, o.b, pos+2, rb)){
				vect[vect[pos+3]] = 1;
			}else{
				vect[vect[pos+3]] = 0;
			}
		}else{
			if(val(vect, o.c, pos+1, rb) == val(vect, o.b, pos+2, rb)){
				vect[vect[pos+3]+rb] = 1;
			}else{
				vect[vect[pos+3]+rb] = 0;
			}
		}
		pos += 4;
		return;
	}
	if (o.o == 9){
		rb += val(vect, o.c, pos+1, rb);
		pos += 2;
		return;
	}		
	if (o.o == 99){
		pos = -1;
		return;
	}
	pos++;
}

void run(vector<long long> vect){
	int pos = 0;
	int rb = 0;
	while(pos != -1){
		step(vect, pos, rb);
	}
}

int main() {
	string line;
	vector<long long> vect;
	ifstream myfile ("input");
	getline(myfile,line);
	stringstream ssin(line);

	for (long long i; ssin >> i;) {
		vect.push_back(i);
		if (ssin.peek() == ',') ssin.ignore();
	}
	for (int i = 0; i < 1000; i++) vect.push_back(0);
	
	run(vect);
}
