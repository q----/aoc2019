#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <set>

using namespace std;

struct op{
	int o;
	int a;
	int b;
	int c;
};

struct p{
	int x = 0;
	int y = 0;
	bool operator < (const p& rhs) const{
		return x * 10000 + y < rhs.x * 10000 + rhs.y;
	};
};

struct r{
	p pos;
	char dir = 'U';
};

op conv(int a){
	op o;
	o.o = a % 100; 
	o.c = ((int)(a / pow(10,2))) % 10;
	o.b = ((int)(a / pow(10,3))) % 10;
	o.a = ((int)(a / pow(10,4))) % 10;
	return o;
}

void move(r& bot){
	if(bot.dir == 'U'){
		bot.pos.y++;
	}else if(bot.dir == 'D'){
		bot.pos.y--;
	}else if(bot.dir == 'L'){
		bot.pos.x--;
	}else{
		bot.pos.x++;
	}
}

void turn(r& bot, int input){
	if(input == 1){
		if(bot.dir == 'U'){
			bot.dir = 'L';
		}else if(bot.dir == 'L'){
			bot.dir = 'D';
		}else if(bot.dir == 'D'){
			bot.dir = 'R';
		}else{
			bot.dir = 'U';
		}
	}else{
		if(bot.dir == 'U'){
			bot.dir = 'R';
		}else if(bot.dir == 'R'){
			bot.dir = 'D';
		}else if(bot.dir == 'D'){
			bot.dir = 'L';
		}else{
			bot.dir = 'U';
		}
	}
}
		

long long val(vector<long long>& vect, int mode, int pos, int rb){
	if (mode == 1) return vect[pos];
	if (mode == 2) return vect[vect[pos] + rb];
	return vect[vect[pos]];
}

void step(vector<long long>& vect, int& pos, int& rb, int input, int & out){
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
			vect[vect[pos+1]] = input;
		}else if(o.c == 2){
			vect[vect[pos+1] + rb] = input;
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

void paint(p pos, int out, set<p>& white){
	if(out == 1){
		white.insert(pos);
	}else{
		white.erase(pos);
	}
}

bool isWhite(p pos, set<p>& white){
	return white.find(pos) != white.end();
}

void output(r& bot, int& out, set<p>& white, set<p>& painted, int& count){
	if(count % 2 == 1){
		painted.insert(bot.pos);
		paint(bot.pos, out, white);
	}else{
		turn(bot, out);
		move(bot);
	}
	out = -1;
}

void grid(set<p>& painted){
	set<p>::iterator it = painted.begin();
	p tr;
	p bl;
	while(it != painted.end()){
		tr.x = max(tr.x, (*it).x);	
		bl.x = min(bl.x, (*it).x);	
		tr.y = max(tr.y, (*it).y);	
		bl.y = min(bl.y, (*it).y);	
		it++;	
	}

	cout << tr.y << ": " << bl.y << endl;
	cout << tr.x << ": " << bl.x << endl;

	for(int i = tr.y; i >= bl.y; i--){
		for(int j = tr.x; j >= bl.x; j--){
			p chk;
			chk.x = j;
			chk.y = i;
			if(isWhite(chk, painted)){
				cout << '#';
			}else{
				cout << '.';
			}
		}
		cout << endl;
	}
}

void run(vector<long long> vect){
	int pos = 0;
	int rb = 0;
	int out = -1;
	set<p> white;
	set<p> painted;
	int count = 0;
	r bot;
	paint(bot.pos, 1, white);
	while(pos != -1){
		step(vect, pos, rb, isWhite(bot.pos, white), out);
		if(out != -1) output(bot, out, white, painted, ++count);
	}
	grid(white);
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
