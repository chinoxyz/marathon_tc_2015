#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>

using namespace std;

#define ri(X) scanf("%d", &(X))
#define pi(X) printf("%d", (X))
#define mp(X,Y) make_pair(X,Y)
#define pb(X) push_back(X)
#define lint long long
#define pii pair<int,int>
#define inf 1e9
#define linf 1e18
#define X first
#define Y second
#define all(X) (X).begin(),(X).end()
#define uni(X) X.erase(unique(X.begin(), X.end()), X.end());
double INF = 1e100;
double EPS = 1e-12;






string itos(int x){
  stringstream ss;
  ss << x;
  return ss.str();
}


const double pi = acos(-1);
class PT{
  public:
  double x, y;
  int i;
  PT(int xx = 0, int yy = 0, int ii = 0){
    x = xx;
    y = yy;
    i = ii;
  }
  bool operator <(const PT &p)  const { return x < p.x || (x == p.x && y < p.y); }
  bool operator ==(const PT &p)  const { return x == p.x && y == p.y; }
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (double c)     const { return PT(x*c,   y*c  ); }
  PT operator / (double c)     const { return PT(x/c,   y/c  ); }
};
double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double dist(PT p, PT q)   { return sqrt(dist2(p,q)); }
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }

double angle0(PT p){
  return atan2(p.x,p.y);
}

ostream &operator<<(ostream &os, const PT &p) {
  os << "(" << p.x << "," << p.y << ")"; 
}

// O(ni)
double ComputeArea(const vector<PT> &p) {
  double area = 0;
  for(int i = 0; i < p.size(); i++) {
    int j = (i+1) % p.size();
    area += p[i].x*p[j].y - p[j].x*p[i].y;
  }
  return fabs(area / 2.0);
}
// O(1)
bool LinesParallel(PT a, PT b, PT c, PT d) { 
  return fabs(cross(b-a, c-d)) < EPS; 
}

// O(1)
bool LinesCollinear(PT a, PT b, PT c, PT d) { 
  return LinesParallel(a, b, c, d)
      && fabs(cross(a-b, a-c)) < EPS
      && fabs(cross(c-d, c-a)) < EPS; 
}

// O(1)
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
  if (LinesCollinear(a, b, c, d)) {
    if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
      dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
    if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
      return false;
    return true;
  }
  if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
  if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
  return true;
}

// O(ni)
bool hasArea(const vector<PT> &p){
  bool allcol = 1;
  for(int i = 0; i < p.size()-1 && allcol; i++){
    if(!LinesParallel(p[i], p[i+1], p[i+1], p[(i+2)%p.size()])){
      allcol = 0;
    }
  }
  if(allcol) return 0;
  return 1;
}
// O(ni*ni)
bool IsSimple(const vector<PT> &p) {
  return true;
  
  for (int i = 0; i < p.size(); i++) {
    for (int k = i+1; k < p.size(); k++) {
      int j = (i+1) % p.size();
      int l = (k+1) % p.size();
      if (i == l || j == k) continue;
      if (SegmentsIntersect(p[i], p[j], p[k], p[l])){
        cerr << p[i] << p[j] << p[k] << p[l] << endl;
        return false;
      }
    }
  }
  return true;
}
vector<PT> ve;
vector<string> res;
int np;
int n;


class poly{
public:
  vector<int> vi;
  double cost;
  poly(vector<int> vv){
    cost = -1;
    vi = vv;
  }
  
  // O(C(Ri))
  double getCost(){
    if(cost >= 0){
      return cost;
    }
    vector<PT> vq;
    for(int i = 0; i < vi.size(); i++){
      vq.pb(ve[vi[i]]);
    }
    if(!hasArea(vq) || !IsSimple(vq)){
      //cerr << "SHiT" << endl;
      cost = inf;
      return cost;
    }
    cost = ComputeArea(vq);
    return cost;
  }
  // O(npi)
  string tostring(){
    string rp;
    for(int i = 0; i < vi.size(); i++){
      rp+=itos(vi[i])+ " ";
    }
    return rp;
  }
  
};
poly getpol1(vector<int>, int, int);
poly getpol(vector<int> vi);
poly getpolb(vector<int> vi);

class solution{
  public:
  vector<poly> vp;
  double cost;
  solution(){
    cost = inf;
  }
  solution(vector<poly> vv){
    vp = vv;
    cost = -1;
  }
  
  // O(C(R)) 
  double getCost(){
    if(cost >= 0){
      return cost;
    }
    cost = 0;
    for(int i = 0; i < vp.size(); i++){
      cost+=vp[i].getCost();
    }
    return cost;
  }
  
  // O(np)
  vector<string> tovs(){
    vector<string> vs;
    for(int i = 0; i < vp.size(); i++){
      vs.pb(vp[i].tostring());
    }
    return vs;
  }
  
  // O(ni lg ni + C(R));
  void split(int k, int w){
    if(vp.size() >= n) return;
    assert(0 <= k && k < vp.size());
    if(vp[k].vi.size() <= 6) return;
    //cerr <<"Hola:  "<< k << " " << vp.size() <<" " << endl;
    int rot = rand()%2;
    vector<int>&vi = vp[k].vi;
    vector<pair<pair<int,int>,int> > vs;
    for(int i = 0; i < vi.size(); i++){
      if(rot == 0){
        vs.pb(mp(mp(ve[vi[i]].x,ve[vi[i]].y),vi[i]));
      }else{
        vs.pb(mp(mp(ve[vi[i]].y,ve[vi[i]].x),vi[i]));
      }
    }
    sort(all(vs));
    vector<int> rp[2];
    for(int i = 0; i < vs.size(); i++){
      rp[i< w].pb(vs[i].Y);//
    }
    vp[k] = getpol(rp[0]);
    vp.pb(getpol(rp[1]));
    cost = -1;
  }
  
  // O(ni lg ni + C(R))
  void splitg(int k){
    assert(0 <= k && k < vp.size());
    split(k,vp[k].vi.size()/2);
  }
  
  // O(ni lg ni + c(R))
  void splitr(int k){
    assert(0 <= k && k < vp.size());
    int siz = vp[k].vi.size();
    if(siz <= 8) return;
    split(k, 3+(rand()%(siz-6)));
  }
  
  // O(ni lg ni + C(R))
  void star(int k){
    assert(0 <= k && k < vp.size());
    vp[k] = getpol(vp[k].vi);
    cost = -1;
  }
};
// O(ni lg ni)
poly getpol1(vector<int> vi, int s=0){
  assert(vi.size() >= 2);
  if(vi.size() == 3) return vi;
  PT ic = ve[vi[s]];
  
  vector<pair<pair<double,double>, int> > vs;
  for(int i = 0; i < vi.size(); i++){
    if(vi[i] == vi[s]){
      continue;
    }
    double ang = angle0(ve[vi[i]]-ic);
    double di = dist2(ic, ve[vi[i]]);
    vs.pb(mp(mp(ang,di),vi[i]));
  }
  sort(all(vs));
  vi[0] = vi[s];
  
  int ki = 0;
  for(int i = 0; i < vs.size()-1; i++){
    if(fabs(vs[i].X.X-vs[i+1].X.X) >= pi){
      ki = i+1;
    }
  }
  for(int i = 0; i < vs.size(); i++){
    vi[i+1] = vs[(i+ki)%vs.size()].Y;
  }
  vector<pair<double, int> > vc;
  int si = vi.size()-1;
  for(int k = vi.size()-1; k >= 0; k--){
    if(LinesParallel(ve[vi[0]], ve[vi[vi.size()-1]], ve[vi[(k+1)%vi.size()]], ve[vi[k]])){
      double di = dist2(ve[vi[0]], ve[vi[k]]);
      vc.pb(mp(-di,vi[k]));
      si = k;
    }else{
      break;
    }
  }
  
  sort(all(vc));
  for(int i = 0; i < vc.size(); i++){
    vi[si+i] = vc[i].Y;
  }
  
  return poly(vi);
}

// O(ni lg ni)
poly getpol(vector<int> vi){
  return getpol1(vi, rand()%vi.size());
}

// O(ni lg ni)
poly getpolb(vector<int> vi){
  assert(vi.size() >= 2);
  if(vi.size() == 3) return vi;
  vector<PT> vp;
  for(int i = 0;i < vi.size(); i++){
    vp.pb(ve[vi[i]]);
  }
  sort(all(vp));
  PT ic = vp[0]+PT(pi/4,pi/4);
  vector<pair<pair<double,double>, int> > vs;
  for(int i = 0; i < vi.size(); i++){
    if(ve[vi[i]] == ic){
      vs.pb(mp(mp(-10,-10),vi[i]));
      continue;
    } 
    double ang = angle0(ve[vi[i]]-ic);
    double di = dist2(ic, ve[vi[i]]);
    vs.pb(mp(mp(ang,di),vi[i]));
  }
  sort(all(vs));
  
  /*
  
  int ki = vi.size()-1;
  for(int k = vi.size()-2; k >= 0; k--){
    
    
    if(LinesCollinear(ve[vs[0].Y], ve[vs[k].Y], ve[vs[k+1].Y], ve[vs[k].Y])){
      ki = k;
    }else{
      break;
    }
  }
  
  for(int k = 0; k < vs.size(); k++){
    if(vs[k].Y == 742){
      cerr << k << endl;
      cerr << vs[(vs.size()+k-1)%vs.size()].Y<< " " << vs[k].Y << " " << vs[k+1].Y << endl;
    }
  }
  /*
  fprintf(stderr, "init:%d\n", vs[0].Y);
  if(ki != vi.size()-1){
    fprintf(stderr, "HOLA!! %d %d\n", ki, vi.size());
    reverse(vs.begin()+ki, vs.end());
  }*/
  
  for(int i = 0; i < vs.size(); i++){
    vi[i] = vs[i].Y;
  }
  
  return poly(vi);
}


// O(np lg np)
solution getsolb(){
  vector<int> vi;
  for(int i = 0; i < np; i++){
    vi.pb(i);
  }
  vector<poly> res;
  res.pb(getpolb(vi));
  return solution(res);
}
// O(np lg np)
solution getsol1(){
  vector<int> vi;
  for(int i = 0; i < np; i++){
    vi.pb(i);
  }
  vector<poly> res;
  res.pb(getpol(vi));
  return solution(res);
}



solution localsearch(){
  solution res = getsolb();
  //res.splitg(rand()%res.vp.size());
  solution rp;
  for(int i = 0; i < 50 ; i++){
    
    rp =res;
    rp.star(rand()%rp.vp.size());
    //cerr << "NEW: " << res.getCost() << " " << rp.getCost() << endl;
    if(rp.getCost() < res.getCost()){
      res = rp;
    }
    
    rp = res;
    rp.splitr(rand()%rp.vp.size());
    
    //cerr << "SPLIT: " << res.getCost() << " " << rp.getCost() << endl;
    if(rp.getCost() < res.getCost()){
      res = rp;
    }
  }  
  
  
  
  
  return res;
}






class SmallPolygons{
  
  
  public:
  vector <string> choosePolygons(vector <int> points, int N){
    np = points.size();
    n = N;
    for(int i = 0; i < np; i+=2){
      ve.pb(PT(points[i],points[i+1],i/2));
    }
    np/=2;
    
    
    int num = 10;
    
    if(np < 50){
      num = 30000;
    }else if(np < 100){
      num = 1000;
    }else if(np < 500){
      num = 300;
    }else{
      num = 100;
    }
    
    solution res = getsolb(), rp;
    for(int k = 0; k < num; k++){
      rp = localsearch();
      if(rp.getCost() < res.getCost()){
        res = rp;
      }
    }
    
    
    
    
    
    return res.tovs();
  }

};
int main(){
  int Np; 
  vector<int> points;
  int N;
  int v;
  vector<string> ret;
  cin >> Np;
  for (int i=0; i < Np; i++){
    cin >> v;
    points.pb(v);
  }
  cin >> N;
  
  ret = SmallPolygons().choosePolygons(points, N);
  
  
  printf("%d\n", ret.size());
  for (int i=0; i < ret.size(); i++){
    printf("%s\n", ret[i].c_str());
    //fprintf(stderr,"VEC: %s\n", ret[i].c_str());
  }
  fflush(stdout);

  return 0;
}
