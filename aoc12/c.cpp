#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

struct dir{
	int pos;
	int vel = 0;
};

struct moon{
	dir x;
	dir y;
	dir z;
};

moon conv(string in){
	moon io;
	int found;
	string temp;
	vector<int> out;
	for(int i = 0; i < in.length(); i++){
		if(in[i] == ','){
			stringstream(temp) >> found;
			out.push_back(found);
			temp = "";
			continue;
		}
		temp += in[i];
	}
	io.x.pos = out[0];
	io.y.pos = out[1];
	io.z.pos = out[2];
	return io;
}

void gravity(moon& a, moon& b){
	if(a.x.pos < b.x.pos){
		a.x.vel++;
		b.x.vel--;
	}else if(a.x.pos > b.x.pos){
		a.x.vel--;
		b.x.vel++;
	}
	if(a.y.pos < b.y.pos){
		a.y.vel++;
		b.y.vel--;
	}else if(a.y.pos > b.y.pos){
		a.y.vel--;
		b.y.vel++;
	}
	if(a.z.pos < b.z.pos){
		a.z.vel++;
		b.z.vel--;
	}else if(a.z.pos > b.z.pos){
		a.z.vel--;
		b.z.vel++;
	}
}

void move(vector<moon>& m){
	for(int i = 0; i < m.size(); i++){
		m[i].x.pos += m[i].x.vel;
		m[i].y.pos += m[i].y.vel;
		m[i].z.pos += m[i].z.vel;
	}
}

int energy(vector<moon> moons){
	int total = 0;
	for(int i = 0; i < moons.size(); i++){
		int pot = abs(moons[i].x.pos) + abs(moons[i].y.pos) + abs(moons[i].z.pos);
		int kin = abs(moons[i].x.vel) + abs(moons[i].y.vel) + abs(moons[i].z.vel);
		total += pot * kin;
	}
	return total;
}

int main(){
	vector<moon> moons;
	string line;
	ifstream myfile ("input");
	while(getline(myfile,line)){
		moons.push_back(conv(line));
	}

	for(int t = 0; t < 1000; t++){
		for(int i = 0; i < moons.size() - 1; i++){
			for(int j = i+1; j < moons.size(); j++){
				gravity(moons[i], moons[j]);
			}
		}
		move(moons);
	}

	cout << energy(moons) << endl;

	return 0;
}
