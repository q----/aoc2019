#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

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

string step(vector<o>& in, string p){
	for(size_t x = 0; x < in.size(); x++) if(in[x].s == p) return in[x].c;
	return "";
}

void path(vector<string>& you, vector<o> & in, string str){
	do{
		you.push_back(str);
		str = step(in, str);		
	}while(str != "");
}

int main() {
	string line;
	ifstream myfile ("input");
	vector<o> in;
	while(getline(myfile,line)){
		in.push_back(conv(line));

	}
	vector<string> you;
	vector<string> san;
	path(you, in, "YOU");
	path(san, in, "SAN");
	
	int i = 0;
	while(you[you.size()-i-1] == san[san.size()-i-1]) i++;
	cout << you.size() + san.size() - (2 * i) -2 << endl;

	return 0;
}
