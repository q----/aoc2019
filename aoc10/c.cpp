#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <set>

using namespace std;

struct a{
	int x = -1;
	int y = 0;
};

double slope(a x, a y){
	if((x.x - y.x) == 0) return 100000;
	return (((double)(x.y - y.y)) / (x.x - y.x));
}

bool abo(a x, a y){
	return ((x.x * 100 + x.y) > (y.x * 100 + y.y));
}

int numsee(a ast, vector<a> asts){
	set<double> ayy;
	set<double> bee;
	for(size_t i = 0; i < asts.size(); i++){
		if(ast.x == asts[i].x && ast.y == asts[i].y) continue;
		if(abo(ast, asts[i])){
			ayy.insert(slope(ast, asts[i]));
		} else {
			bee.insert(slope(ast, asts[i]));
		}
	}
	return ayy.size() + bee.size();
}	
int dist(a c, a d){
	return abs(c.x - d.x) + abs(c.y - d.y);
}

a destroy(vector<a>& asts, a stat, a dest){
	bool above = abo(stat,dest);
	double m = slope(stat,dest);
	double diff = 1000000;

	for(size_t i = 0; i < asts.size(); i++){
		if



int main() {
	vector<a> asteroids;
	string line;
	ifstream myfile ("input");
	vector<string> input;
	while(getline(myfile, line)) input.push_back(line);

	for(int i = 0; i < input.size(); i++){
		for(int j = 0; j < input[i].size(); j++){
			if(input[i][j] == '#'){
				a o;
				o.y = i;
				o.x = j;
				asteroids.push_back(o);
			}
		}
	}
	int largest = 0;
	a station;
	for(int i = 0; i < asteroids.size(); i++){
		int num = numsee(asteroids[i], asteroids);
		if(largest < num){
			largest = num;
			station = asteroids[i];
		}
	}
	cout << largest << endl;

	a dest;
	for(int i = 0; i < 200; i++){
		dest = destroy(asteroids, station, dest);
	}
	cout << dest.x * 100 + dest.y << endl;
	return 0;
}
