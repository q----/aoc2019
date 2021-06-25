#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <string.h>

using namespace std;

struct ele{
	int q;
	string n;
};

struct eq{
	vector<ele> in;
	ele out;
};

ele cconv(string in){
	ele out;
	size_t pos = in.find(' ');
	stringstream ssin(in.substr(0,pos));
	ssin >> out.q;
	out.n = in.substr(pos+1);
	return out;
}

eq conv(string in){
	stack <string> a;
	string temp;
	eq out;
	for(int i = 0; i < in.length(); i++){
		if(in[i] == ','){
			a.push(temp);
			temp = "";
			i++;
			continue;
		}else if(in[i] == '='){
			temp.pop_back();
			a.push(temp);
			temp = "";
			i += 2;
			continue;
		}
		temp += in[i];
	}
	
	out.out = cconv(temp);
	while(!a.empty()){
		out.in.push_back(cconv(a.top()));
		a.pop();
	}
	return out;
}

void addd(ele e, vector<ele>& have){
	if(e.q == 0) return;
	for(int i = 0; i < have.size(); i++){
	       	if(e.n == have[i].n){
		       have[i].q += e.q;
		       return;
		}
	}
	have.push_back(e);
}

void get(ele w, queue<ele>& want, vector<eq> equations, vector<ele>& have){
	int mult = 1;
	int pos;
	ele extra;
	for(int i = 0; i < equations.size(); i++){
		if(equations[i].out.n == w.n){
			extra = equations[i].out;
			pos = i;
		}
	}

	while(w.q > extra.q * mult) mult++;
	
	extra.q = extra.q * mult - w.q;
	
	addd(extra, have);

	for(int i = 0; i < equations[pos].in.size(); i++){
		equations[pos].in[i].q *= mult;
		want.push(equations[pos].in[i]);
	}
}

bool bank(ele& w, vector<ele>& have){
	for(size_t i = 0; i < have.size(); i++){
		if(w.n == have[i].n){
			int disc = w.


int main(){
	string line;
	vector<eq> equations;
	ifstream myfile ("input");
	while(getline(myfile,line)) equations.push_back(conv(line));

	queue<ele> want;
	
	ele fuel;
	fuel.n = "FUEL";
	fuel.q = 1;
	want.push(fuel);

	vector<ele> have;
	int orewant = 0;

	do{
		ele w = want.front();
		want.pop();
		if(w.n == "ORE"){
			orewant += w.q;
			continue;
		}
		bank(w, have);
		get(w, want, equations, have);
	} while(want.size() > 1);

	cout << orewant << endl;	
	return 0;
}
