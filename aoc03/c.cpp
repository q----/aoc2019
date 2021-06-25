#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

struct I{
	char d;
	int l;
};
struct P{
	int x = 0;
	int y = 0;
};
struct l{
	P s;
	P e;	
	char d;
	char b;
	int l;
};
I conv(string x){
	I o;
	o.d = x[0];
	stringstream s(x.substr(1,x.size()-1));
	o.l = 0;
	s >> o.l;
	return o;
}

l conv2(I i, P& p){
	l o;
	o.s = p;
	o.e = p;
	o.l = i.l;
	if(i.d == 'L'){
		o.b = 'e';
		o.d = 'h';
		o.s.x -= i.l;
		p = o.s;
	}else if(i.d == 'R'){
		o.b = 's';
		o.d = 'h';
		o.e.x += i.l;
		p = o.e;
	}else if(i.d == 'U'){
		o.b = 's';
		o.d = 'v';
		o.e.y += i.l;
		p = o.e;
	}else if(i.d == 'D'){
		o.b = 'e';
		o.d = 'v';
		o.s.y -= i.l;
		p = o.s;
	}
	return o;
}

int cd1(l l1, l l2){
	if(l1.s.x < l2.s.x && l1.e.x > l2.s.x){
		if(l2.s.y < l1.s.y && l2.e.y > l1.s.y){
			return abs(l1.s.y) + abs(l2.s.x);
		}
	}
	return -1;
}

int cd(l l1, l l2){
	if(l1.d == l2.d) return -1;
	if(l1.d == 'h'){
		return cd1(l1, l2);
	}else{
		return cd1(l2, l1);
	}
}

int cs1(l l1, l l2){
	int len = 0;
	if(l1.b == 's'){
		len += l2.s.x - l1.s.x;
	}else{
		len += l1.e.x - l2.s.x;
	}
	if(l2.b == 's'){
		len += l1.s.y - l2.s.y;
	}else{
		len += l2.e.y - l1.s.y;
	}
	return len;
}

int cs(l l1, l l2){
	if (cd(l1, l2) == -1) return -1; 
	if(l1.d == 'h'){
		return cs1(l1, l2);
	}else{
		return cs1(l2, l1);
	}
}

int main(){
	string line;
	ifstream myfile ("input");
	getline(myfile, line);
	vector<l> wi1;
	vector<string> results;
	string str = "";
	for(int i = 0; i < line.size(); i++){
		if (line[i] == ','){
			results.push_back(str);
			str="";
			continue;
		}
		str += line[i];
	}
	results.push_back(str);
	P p;
	for(size_t i = 0; i < results.size(); i++){
		wi1.push_back(conv2(conv(results[i]),p));
	}

	getline(myfile, line);
	vector<l> wi2;
	vector<string> results2;
	str = "";
	for(int i = 0; i < line.size(); i++){
		if (line[i] == ','){
			results2.push_back(str);
			str="";
			continue;
		}
		str += line[i];
	}
	results2.push_back(str);
	P q;
	for(size_t i = 0; i < results2.size(); i++){
		wi2.push_back(conv2(conv(results2[i]),q));
	}
	int l1 = 0;
	int dis = -1;
	int dos = -1;
	for(size_t i = 0; i < wi1.size(); i++){
		int l2 = 0;
		for(size_t j = 0; j < wi2.size(); j++){
			int k = cs(wi1[i],wi2[j]);
			int w = cd(wi1[i],wi2[j]);
			if ( k != -1){
				if(dis == -1){
					dis = k + l1 + l2;
					dos = w;
					continue;
				}
				dis = min(dis, k + l1 + l2);
				dos = min(dos, w);
			}

			l2 += wi2[j].l;
		}
		l1 += wi1[i].l;
	}
	cout << dos << endl;
	cout << dis << endl;
	return 0;

}
