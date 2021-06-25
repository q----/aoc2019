#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int zc(string a, char b){
	int c = 0;
	for(int i = 0; i < a.size(); i++)if(a[i] == b)c++;
	return c;
}

char color(string input){
	for(int x = 0; x < input.size(); x++) if(input[x] == '0' || input[x] == '1') return input[x];
	return '2';
}

char paint(int x, int y, string input){
	string f = "";
	for(int m = 25 * y + x; m < input.size(); m+=150) f += input[m];
	return color(f);
}


int main() {
	string line;
	ifstream myfile ("input");
	getline (myfile,line);
	
	int m = 0;
	int layer = 1;
	int zeros = 10000;
	for(int i = 0; i < line.size()/150; i++){
		int x = zc(line.substr(150*i, 150),'0');
		if(x < zeros){
			zeros = x;
			layer = i + 1;
			m = zc(line.substr(150*i, 150),'1')* zc(line.substr(150*i, 150),'2');
		}
	}

	cout << m << endl;
	
	for(int y = 0; y < 6; y++){
		for(int x = 0; x < 25; x++){
			cout << paint(x,y,line);
		}
		cout << endl;
	}
	return 0;
}
