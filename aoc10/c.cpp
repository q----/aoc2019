#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <set>
#include <algorithm>

using namespace std;

struct a{
  int x = -1;
  int y = 0;
};

double slope(a x, a y){
  if((x.x - y.x) == 0) return 100000;
  return (((double)(y.y - x.y)) / (x.x - y.x));
}

bool abo(a x, a y){
  return ((x.y * 100 + x.x) < (y.y * 100 + y.x));
}

pair<set<double>,set<double>> numsee(a ast, vector<a> asts){
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
  return pair<set<double>,set<double>>(ayy, bee);
}  

int dist(a c, a d){
  return abs(c.x - d.x) + abs(c.y - d.y);
}

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
  pair<set<double>,set<double>> slopes;
  for(int i = 0; i < asteroids.size(); i++){
    pair<set<double>,set<double>> lopes = numsee(asteroids[i], asteroids);
    int num = lopes.first.size() + lopes.second.size();
    if(largest < num){
      largest = num;
      station = asteroids[i];
      slopes = lopes;
    }
  }
  cout << largest << endl;

  vector<double> g;
  vector<double> l;
  vector<double> gb;
  vector<double> lb;

  for(auto d : slopes.second){
    if(d > 0) g.push_back(d);
    if(d <= 0) l.push_back(d);
  }
  for(auto d : slopes.first){
    if(d > 0) gb.push_back(d);
    if(d <= 0) lb.push_back(d);
  }

  sort(g.begin(),g.end(), greater<double>());
  sort(lb.begin(),lb.end(), greater<double>());
  sort(gb.begin(),gb.end(), greater<double>());
  sort(l.begin(),l.end(), greater<double>());

  g.insert(g.end(),lb.begin(),lb.end());
  g.insert(g.end(),gb.begin(),gb.end());
  g.insert(g.end(),l.begin(),l.end());
  


  vector<a> cand;
  for(a d : asteroids){
    if(slope(station,d) == g[199]){
      cand.push_back(d);
    }
  }

  a dest = cand[0];
  cout << cand.size() << endl;
  for(auto ql : cand){
    cout << ql.x << " " << ql.y << endl;
  }
  
  //this is wrong.
  for(int i = 1; i < cand.size(); i++){
    if(dist(station,dest) > dist(station,cand[i])){
      dest = cand[i];
    }
  }
  
  cout << dest.x * 100 + dest.y << endl;

  return 0;
}
