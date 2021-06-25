#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <set>
#include <queue>

using namespace std;

struct op{
	int o;
	int a;
	int b;
	int c;
};

struct p{
	int x = -1;
	int y = -1;
	
	bool operator < (const p& rhs) const{
		return x*10000 + y < rhs.x * 10000 + rhs.y;
	};
};

struct game{
	vector<vector<int>> board;
};

char tra(int in){
	vector<char> out{' ', '@', 'X', '-', 'O'};
	return out[in];
}

int input(){
	char a;
	ofstream myfile;
	myfile.open("inputs", ios_base::app);
	while(a != 'j' && a != 'k' && a != 'l') cin >> a;
	
	if(a == 'j'){
		myfile << -1 << endl;
		myfile.close();
	       	return -1;
	}
	if(a == 'l'){
		myfile << 1 << endl;
		myfile.close();
	       	return 1;
	}
	myfile << 0 << endl;
	myfile.close();
	return 0;
}

int innput(queue<int>& files){
	if(files.size() != 0){
		cout << endl << endl << files.size() << endl << endl;
		int out = files.front();
		files.pop();
		return out;
	}
	return input();
}

void disp(game& b, int score){
	cout << score << endl;
	for(int i = 0; i < 21; i++){
		for(int j = 0; j < 50; j++){
			cout << tra(b.board[i][j]);
		}
		cout << endl;
	}
	cout << "What's your move? ";
}

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

void step(vector<long long>& vect, int& pos, int& rb, int& out, game& b, int score, queue<int>& inputs){
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
		disp(b, score);
		if(o.c == 0){
			vect[vect[pos+1]] = innput(inputs);
		}else if(o.c == 2){
			vect[vect[pos+1] + rb] = innput(inputs);
		}
		pos += 2;
		return;
	}
	if (o.o == 4){
		out = val(vect, o.c, pos+1, rb);
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

void run(vector<long long> vect, queue<int> inputs){
	int pos = 0;
	int rb = 0;
	int out = -2;
	int count = 0;
	int score = 0;
	vector<vector<int>> boa (50, vector<int>(50));
	p po;
	game b;
	b.board = boa;
	while(pos != -1){
		step(vect, pos, rb, out, b, score, inputs);
		if(out != -2){
			count++;
			if(count % 3 == 1){
				po.x = out;
			}else if(count % 3 == 2){
				po.y = out;
			}else{
				if(po.x == -1 && po.y == 0){
					score = out;
				}else{
					b.board[po.y][po.x] = out;
				}
			}
			out = -2;
		}
	}
	cout << score << endl;
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
	
	string l;
	ifstream file ("inputs_p");
	queue<int> inpu;
	while(getline(file,l)){
		int i;
		stringstream ss(l);
	       	ss >> i;
		inpu.push(i);
	}
	
	run(vect,inpu);
}
