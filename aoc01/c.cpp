#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int req (int in){
	return in/3 - 2;
}

int fullreq (int in){
	int x = in;
	int total = 0;
	while (x > 0){
		x = req(x);
		total += max(0,x);
	}
	return total;
}

int main(){
	int total = 0;
	string line;
	
	ifstream myfile ("input");
	while (getline (myfile,line)){
		stringstream s(line);
		int x = 0;
		s >> x;
		total += fullreq(x);
	}
	cout << total << endl;
	return 0;
}
