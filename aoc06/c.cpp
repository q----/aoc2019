#include<iostream>
#include<fstream>
#include<string.h>
#include<vector>
#include<set>


using namespace std;

struct p{
	string n;
	int o = 0;
};
struct o{
	string c;
	string s;
};
o conv(string i){
	o o;
	string str = "";
	for (int m = 0; m < i.size(); m++){
		if(i[m] == ')'){
			o.c = str;
			str="";
			continue;
		}
		str += i[m];
	}
	o.s = str;
	return o;
}

string center(vector<o>& in){
	set<string> cand;
	set<string> nocand;
	for(size_t x = 0; x < in.size(); x++){
		cand.insert(in[x].c);
		nocand.insert(in[x].s);
	}
	cout << cand.size() << endl << nocand.size() << endl;
	set<string>::iterator it = nocand.begin();
	while (it != nocand.end()){
		cand.erase(*it);
		it++;
	}
	it = cand.begin();
	return *it;
}

bool bin (vector<p>& plan, o a){
	vector<p>::iterator it = plan.begin();
	while(it != plan.end()){
 		if(it->n == a.c){
			p b;
			b.n = a.s;
			b.o = it->o + 1;
			plan.push_back(b);
			return true;
		}
		it++;
	}
	return false;
}


int main() {
	string line;
	ifstream myfile ("input");
	vector<o> in;
	while(getline(myfile,line)){
		in.push_back(conv(line));

	}
	vector<p> plan;
	p c;
	c.n = center(in);
	plan.push_back(c);
	
	while(in.size() > 0){
		vector<o>::iterator it = in.begin();
		while(it != in.end()){
			if(bin(plan, *it)) {
				in.erase(it);
				cout << in.size() << endl;
				break;
			}
			it++;
		}
	}
	cout << plan.size() << endl;
	int total = 0;
	set<string> fuck;
	for(size_t i = 0; i < plan.size(); i++){
		total += plan[i].o;
		fuck.insert(plan[i].n);
	}
	cout << fuck.size() << endl;
	cout << total << endl;

	return 0;
}
