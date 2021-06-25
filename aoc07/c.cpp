#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <set>

using namespace std;

const int INPUT = 5;

struct op{
	int o;
	int a;
	int b;
	int c;
};

struct amp{
	vector<int> vect;
	int pos = 0;
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

void step(vector<int>& vect, int& pos, int& input, bool& ai, int& machine){
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
		if(!ai){
			machine--;
			return;
		}
		vect[vect[pos+1]] = input;
		ai = false;
		pos += 2;
		return;
	}
	if (o.o == 4){
		input = val(vect, o.c, pos+1);
		ai = true;
		machine++;
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

bool nohalt(vector<amp> m){
	for(int i = 0; i < 5; i++)if(m[i].pos == -1) return false;
	return true;
}

int run(vector<amp> m){
	int input = 0;
	int machine = 0;
	bool ai = true;
	while(nohalt(m)){
		step(m[machine % 5].vect, m[machine % 5].pos, input, ai, machine);
	}
	return input;
}

bool isgood(vector<int> in){
	set<int> x;
	for(size_t i = 0; i < in.size(); i++) if (in[i] >= 5) x.insert(in[i]);
	return (x.size() == 5);
}

void increment(vector<int>& in){
	int x = 0;
	for(size_t i = 0; i < in.size(); i++) x = 10*x + in[i];
	x++;
	vector<int> a;
	for(int i = 4; i >= 0; i--)a.push_back(((int)(x/pow(10,i))) %10);
	in = a;
}

void combo(vector<int> & in){
	if(in.empty()){
		for(int i = 0; i < 5; i++) in.push_back(i+5);
		return;
	}
	do{
		increment(in);
	}while(!isgood(in));
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
	
	vector<int> in;
	int m = 0;

	for(int x = 0; x < 130; x++){
		combo(in);
		vector<amp> amps;
		for(int i = 0; i < in.size(); i++){
			amp a;
			a.vect = vect;
			bool th = true;
			int f = 0;
			step(a.vect, a.pos, in[i], th, f);
			amps.push_back(a);
		}
		m = max(m,run(amps));	
	}

	cout << m << endl;
}
