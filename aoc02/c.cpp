#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void step(vector<int>& vect, int& pos){
	if (vect[pos] == 1){
		vect[vect[pos+3]] = vect[vect[pos+2]] + vect[vect[pos+1]];
		pos += 4;
		return;
	}
	if (vect[pos] == 2){
		vect[vect[pos+3]] = vect[vect[pos+2]] * vect[vect[pos+1]];
		pos += 4;
		return;
	}
	if (vect[pos] == 99){
		pos = -1;
		return;
	}
	pos++;
}

void inputs(vector<int>& vect, int a, int b){
	vect[1] = a;
	vect[2] = b;
}

int output(vector<int> vect){
	int pos = 0;
	while(pos != -1){
		step(vect, pos);
	}
	return vect[0];
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

	for(int j = 0; j < 100; j++){
		for (int k=0; k < 100; k++){
			inputs(vect,j,k);
			if(output(vect) == 19690720){
				cout << (100 * j) + k << endl;
				j = 100;
				break;
			}
		}
	}
}
