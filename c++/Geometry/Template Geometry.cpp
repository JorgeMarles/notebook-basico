#include <bits/stdc++.h>
using namespace std;
#define fastIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define F first
#define S second
#define pb push_back
#define sz(x) int((x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define forsn(i, s, n) for(int i = s; i < n; ++i)
#define dforn(i, n) for(int i = n-1; i >= 0; --i)
#define dforsn(i, s, n) for(int i = n-1; i >= s; --i)
#define DBG(x) cout << #x << " = " << x << endl;
typedef long long ll;
typedef pair<int, int> pii;
typedef double T;
const double PI = acos(-1.0);
const double EPS = 1e-9;
//test for equality: DON'T use "a==b" 
//abs(a-b) < EPS;    // or 
//abs(a/b - 1) < EPS;   // make sure b != 0, or even anywhere near it 
 
//test for >=: Don't use "a >= b" 
//a > b-EPS; 
 
//test for >: Don't use "a > b" 
//a >= b+EPS; 

struct pt{
	T x, y;
	
	pt operator + (pt p){return {x + p.x, y + p.y};}
	pt operator - (pt p){return {x - p.x, y - p.y};}
	pt operator * (T d){return {x*d, y*d};}
	pt operator * (pt p){return {x*p.x - y*p.y, x*p.y + y*p.x};}
	pt operator / (T d){return {x/d, y/d};}
	bool operator == (pt b) {return x == b.x && y == b.y;}
	bool operator != (pt b) {return x != b.x || y != b.y;}	
};

bool comp(pt a, pt b) {
	if(b.x == a.x) return a.y < b.y;
	return a.x < b.x;
}

T sq(pt p){return p.x*p.x + p.y*p.y;}
double abs(pt p) {return sqrt(sq(p));}

pt translate(pt p, pt v) {return p+v;} //Traslada p con base en el vector v
pt scale(pt c, double factor, pt p) { //Escala un vector p con base a el punto c un factor
	return c + (p-c)*factor;
}
pt rotate(pt p, double a){ //Rota a radianes un punto
	return {p.x*cos(a) - p.y*sin(a), p.x*sin(a) + p.y*cos(a)};
}

pt perp(pt p){ //Rota 90 grados en sentido antihorario
	return {-p.y, p.x};
}

//pt linearTransform(pt p, pt q, pt r, pt fp, pt fq){ // ??
	//return fp + (r-p)*(fq-fp)/(q-p);
//}

//Si es igual a 0 son perpendiculares dado que dot(p,q) = |p|*|q|*cos(a)
T dot(pt v, pt w){return v.x*w.x+v.y*w.y;} 
bool isPerp(pt v, pt w) {return dot(v,w) == 0;}

double angle(pt v, pt w){ //Retorna el angulo
	double coseno = dot(v, w)/abs(v) / abs(w);
	return acos(max(-1.0, min(1.0, coseno)));
	//return acos(clamp(coseno, -1, 1)); //Clamp permite mantener el valor de coseno en un rango
		//Se usa el rango [-1, 1] porque acos podria tener fallos de precision con numeros mayores
}

//Indica que tan perpendiculares son los vectores
//cross(v, w) == -cross(w, v)
//si es igual 0, son paralelos los vectores
//Si es mayor a 0, el angulo entre los vectores abre en sentido antihorario
//Si es menor a 0, el angulo entre los vectores abre en sentido horario
T cross(pt v, pt w){return v.x*w.y - v.y*w.x;} 

T orient(pt a, pt b, pt c){
	return cross(b-a, c-a); // ans = 0, si son colineares
									// ans > 0, los puntos estan en sentido antihorario
									// ans < 0, los puntos estan en sentido horario

}

//Puede ser util si queremos saber si un punto esta entre el angulo
//que forman dos vectores

bool isAngle(pt a, pt b, pt c, pt p){
	assert(orient(a,b,c) != 0); //no tendria sentido la pregunta si son colineares
	if (orient(a,b,c) < 0) swap(b,c); //Por conveniencia si no tocaria validar mas cosas despues
	return orient(a, p, c) >= 0 && orient(a, b, p) >= 0;
	//return orient(a,b,p) >= 0 && orient(a,c,p) <= 0; esta tambien vale
	//Tecnicamente hay varias maneras de validarlo
}

//Retorna el angulo de apertura siempre en sentido antihorario
double orientedAngle(pt a, pt b, pt c){
	if(orient(a, b, c) >= 0) return angle(b-a, c-a); 
	return 2*PI - angle(b-a, c-a);
}

bool isConvex(vector<pt> p){
	bool hasPos = false;
	bool hasNeg = false;
	for(int i=0, n = p.size(); i<n; i++){
		int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]); 	//Se calcula los productos cruz de puntos consecutivos
		if(o > 0) hasPos = true;								//Todos son pos o neg si es convexo.
		if(o < 0) hasNeg = true;
	}
	return !(hasPos && hasNeg);
}

//Polar sort 

bool half(pt p){ //Para saber si esta en la mitad superior o inferior
					  //Como se ordena con base en el producto cruz si esta muy lejos el producto cruz da negativo					
	assert(p.x == 0 && p.y == 0); //(0, 0) no esta definido	
	//Arriba si esta entre (0, pi]
	//Abajo si esta entre (-pi, 0]
	//Retorna true si esta arriba
	return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSort(vector<pt> &v){
	sort(v.begin(), v.end(), [] (pt v, pt w){
		return make_tuple(half(v), 0) <	
				make_tuple(half(w), cross(v, w));
				//Primero compara si v esta abajo y w en la mitad superior
				//si estan en el mismo sector entonces determina si el producto
				//cruz es mayor a 0.
				//Retorna true si v esta antes que w en el ordenamiento
	});
}

// {half(v), 0, sq(v)} < {half(w), cross(v, w), sq(w)}, 
// si el cross es 0 el elemento menor es el que esta mas cerca


void polarSortAround(pt o, vector<pt> &v){ //Polar sort con respecto a un punto o conviene restar o 
														//a todos los puntos antes de hacer el sort
	for(auto &q: v) q = q-o;
	polarSort(v);
}

struct line {
	pt v; T c;
	// From direction vector v and offset c
	line(pt v, T c) : v(v), c(c) {} 
	// From equation ax+by=c
	line(T a, T b, T c) : v({b,-a}), c(c) {}
	// From points P and Q
	line(pt p, pt q) : v(q-p), c(cross(v,p)) {}
	// Will be defined later:
	// - these work with T = int
	T side(pt p) {return cross(v,p)-c;} //Algo parecido a orient
	double dist(pt p) {return abs(side(p)) / abs(v);} //Distancia de P a la linea
	line perpThrough(pt p) {return {p, p + perp(v)};} //Linea perpendicular a l

	bool cmpProj(pt p, pt q) { //Comparador para ordenar puntos sobre la linea
		return dot(v,p) < dot(v,q);
	}
	
	line translate(pt t) {return {v, c + cross(v,t)};} //Traslada la linea con base en un vector
	line shiftLeft(double dist) {return {v, c + dist*abs(v)};} //Mueve la linea perpendicularmente una distancia
	// - these require T = double
	pt proj(pt p) {return p - perp(v)*side(p)/sq(v);} //Retorna el punto mas cercano de la linea a p
	pt refl(pt p) {return p - perp(v)*2*side(p)/sq(v);} //Retorna el punto reflejo de p con respecto a la linea

};

bool inter(line l1, line l2, pt &out) { 
	T d = cross(l1.v, l2.v);
	if (d == 0) return false;
	out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point coordinates
	return true;
	//Retorna true si se pudo hallar un punto de cruce
	//Determina en que punto se cruzan dos lineas
}


line bisector(line l1, line l2, bool interior) {
	assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
	double sign = interior ? 1 : -1;
	return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign,
	l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
	//Retorna una linea que forma angulos iguales con las otras dos lines
	//La interna es la que esta entre el vector l1 y l2
	//La externa es la otra
}

double segPoint(pt a, pt b, pt p, pt &ans) {
	if (a != b) {
		line l(a,b);
		if (l.cmpProj(a,p) && l.cmpProj(p,b)){// if closest to projection
			ans = l.proj(p);
			return l.dist(p); // output distance to line
		} 		
	}
	if(abs(p-a) < abs(p-b)) ans = a;
	else ans = b;
	return min(abs(p-a), abs(p-b)); // otherwise distance to A or B
}

double segSeg(pt a, pt b, pt c, pt d) {
	pt ax;
	return min({segPoint(a,b,c,ax), segPoint(a,b,d,ax),
	segPoint(c,d,a,ax), segPoint(c,d,b,ax)});
}

bool inDisk(pt a, pt b, pt p) {
	return dot(a-p, b-p) <= 0;
}

bool onSegment(pt a, pt b, pt p) {
	return orient(a,b,p) == 0 && inDisk(a,b,p);
}

bool properInter(pt a, pt b, pt c, pt d, pt &out) {
	double oa = orient(c,d,a), // basado en la orientacion sabemos si se cruzan
	ob = orient(c,d,b),
	oc = orient(a,b,c),
	od = orient(a,b,d);
	// Proper intersection exists iff opposite signs
	if (oa*ob < 0 && oc*od < 0) {
		out = (a*ob - b*oa) / (ob-oa);
		return true;
	}
	return false;
}

//Circulo dado tres puntos
//Es la interseccion del segmento perpendicular
//al segmento AB y del segmento perpendicular a AC
pt circumCenter(pt a, pt b, pt c) {
	b = b-a, c = c-a; // consider coordinates relative to A
	assert(cross(b,c) != 0); // no circumcircle if A,B,C aligned
	return a + perp(b*sq(c) - c*sq(b))/cross(b,c)/2;
}	

bool above(pt a, pt p) {
	return p.y >= a.y;
}
// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) {
	return (above(a,q) - above(a,p)) * orient(a,p,q) > 0;
}

bool inPolygon(vector<pt> p, pt a, bool strict = true) {
	int numCrossings = 0;
	for (int i = 0, n = p.size(); i < n; i++) {
		if (onSegment(p[i], p[(i+1)%n], a))
			return !strict; // strict es para determinar si esta en el borde o no
								 // (si para el problema estar en el borde es estar dentro
								 // return strict, sino return !strict)
		numCrossings += crossesRay(a, p[i], p[(i+1)%n]);
	}
	return numCrossings & 1;
}

struct cmpX {
	bool operator()(const pt a, const pt b) const  {
		return make_pair(a.x, a.y) < make_pair(b.x, b.y);
	}
};

set<pt,cmpX> inters(pt a, pt b, pt c, pt d) {
	pt out;
	if (properInter(a,b,c,d,out)) return {out};
	set<pt,cmpX> s;
	if (onSegment(c,d,a)) s.insert(a);
	if (onSegment(c,d,b)) s.insert(b);
	if (onSegment(a,b,c)) s.insert(c);
	if (onSegment(a,b,d)) s.insert(d);
	return s;
}

double area(pt &a, pt &b, pt &c) {
    return abs((a.x - c.x)*(b.y - a.y) - (a.x - b.x)*(c.y - a.y));
}

//Compute the diameter of a polygon using rotating-caliper method to generate
//all antipodal pairs. Return the max distance between an antipodal pair extremes.
double diameter(vector<pt> &h) {
    int m = h.size();

    //Return trivial results for polygons with less than 3 points.
    if (m <= 1)
        return 0;
    if (m == 2)
        return abs(h[0] - h[1]);

    //Search the point k which is antipodal of point 0
    int k = 1;
    while (area(h[m - 1], h[0], h[(k + 1) % m]) > area(h[m - 1], h[0], h[k]))
        ++k;

    double res = 0;
    //Generate all antipodal pairs in i,j
    for (int i = 0, j = k; i <= k && j < m; ++i) {
        res = max(res, abs(h[i] - h[j]));
        //Advance point j while j is antipodal pair of i
        while (j < m && area(h[i], h[(i + 1) % m], h[(j + 1) % m]) > area(h[i], h[(i + 1) % m], h[j])) {
            res = max(res, abs(h[i] - h[(j + 1) % m]));
            ++j;
        }
    }
    return res;
}


/*	
	Recibe una lista ordenada de puntos, orden lexicografico.
	Retorna el cuadrado de la distancia más corta entre dos puntos (d*d)
	
	Existe otro algoritmo pero es más complejo de entender.
*/

long long closest_pair(vector<pt> pts){
	set<pair<ll, ll>> cur;
	ll dist = 1e18;
	int j = 0;
	for(int i=0; i<(int) pts.size(); i++){
		ll d = ceil(sqrt(dist));
		while(j <= i && pts[i].x - pts[j].x >= d){
			cur.erase({pts[j].y, pts[j].x});
			j++;
		}
		auto it1 = cur.lower_bound({pts[i].y - d, pts[i].x});
		auto it2 = cur.upper_bound({pts[i].y + d, pts[i].x});
		
		for(auto it = it1; it != it2; it++){
			ll dx = pts[i].x - (*it).second;
			ll dy = pts[i].y - (*it).first;
			dist = min(dist, dx*dx + dy*dy);
		}
		cur.insert({pts[i].y, pts[i].x});
	}
	return dist;
}

T closest_pair_double_ver(vector<pt> &pts){
	set<pair<T, T>> cur;
	T dist = 1e18;
	int j = 0;
	for(int i=0; i<(int) pts.size(); i++){
		while(j <= i && (pts[i].x - pts[j].x) > dist-EPS){
			cur.erase({pts[j].y, pts[j].x});
			j++;
		}
		auto it1 = cur.lower_bound({pts[i].y - dist, pts[i].x});
		auto it2 = cur.upper_bound({pts[i].y + dist, pts[i].x});
		
		for(auto it = it1; it != it2; it++){
			T dx = pts[i].x - (*it).second;
			T dy = pts[i].y - (*it).first;
			dist = min(dist, sqrt(dx*dx + dy*dy));
		}
		cur.insert({pts[i].y, pts[i].x});
	}
	return dist;
}

void ordMinY(vector<pt> &pts){
	int pos = 0;
	for(int i=0; i<(int)pts.size(); i++){
		if(pts[i].y < pts[pos].y || (pts[i].y == pts[pos].y && pts[i].x < pts[pos].x)){
			pos = i;
		}
	}
	rotate(pts.begin(), pts.begin() + pos, pts.end());
}
 
vector<pt> minkowski(vector<pt> a, vector<pt> b){
	ordMinY(a); ordMinY(b);
	vector<pt> sum;
	a.push_back(a[0]); a.push_back(a[1]);
	b.push_back(b[0]); b.push_back(b[1]);
	int i = 0, j = 0;
	while(i < (int)a.size() - 2 || j < (int)b.size() - 2){
		sum.push_back(a[i] + b[j]);
		ll crp = cross(a[i+1] - a[i], b[j+1] - b[j]);
		if(crp >= 0 && i < (int)a.size() - 2){
			i++;
		} 
		if(crp <= 0 && j < (int)b.size() - 2){
			j++;
		} 
	}
	return sum;
}
 
bool pointInTriangle(pt a, pt b, pt c, pt p){
	ll s1 = abs(cross(b - a, c - a));
	ll s2 = abs(cross(b - a, p - a)) + abs(cross(p - a, c - a)) + abs(cross(b - p, c - p));
	return s1 == s2;
}

bool pointInConvexPolygon(vector<pt> &pts, pt p){
	//Podrias mover todos los puntos con respecto a 
	//pts[0] antes de hacer esto, eso reduce el codigo
	int n = pts.size();
	if(cross(pts[1] - pts[0], p - pts[0]) >= 0 && cross(p - pts[0], pts[n-1] - pts[0]) >= 0){
		if(cross(pts[1] - pts[0], p - pts[0]) == 0){
			return sq(p - pts[0]) <= sq(pts[1] - pts[0]);
		}
		if(cross(pts[n-1] - pts[0], p - pts[0]) == 0){
			return sq(p - pts[0]) <= sq(pts[n-1] - pts[0]);
		}	
		int l = 1, r = n-1;
		while(l <= r){
			int mid = (l+r)/2;
			if(cross(pts[mid] - pts[0], p - pts[0]) >= 0){
				l = mid + 1;
			}else{
				r = mid - 1;
			}
		}
		if(r == 0) return false;
		return pointInTriangle(pts[0], pts[r], pts[r+1], p);
	}
	return false;
}

struct CHTrick {
    // queries are (x, 1) * (point.x, point.y)
    // kx + b es igual a dot({k, b}*{x, 1})
    // this code is for max
	int n;
	vector<pt> hull;
	CHTrick(){ n = 0; }
	CHTrick(std::vector<pt> pts) {
	  sort(pts.rbegin(), pts.rend(), comp);
	  n = 0;
	
	}
    
	void add(ll k, ll b){
		//pt a = {k, b}; 
	}

	long long qry(long long x) {
		return 0;
	}
	

};

int main(){
	fastIO;
}

/*
⣿⣿⣿⣿⣿⣿⡷⣯⢿⣿⣷⣻⢯⣿⡽⣻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠸⣿⣿⣆⠹⣿⣿⢾⣟⣯⣿⣿⣿⣿⣿⣿⣽⣻⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣻⣽⡿⣿⣎⠙⣿⣞⣷⡌⢻⣟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⡄⠹⣿⣿⡆⠻⣿⣟⣯⡿⣽⡿⣿⣿⣿⣿⣽⡷⣯⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣟⣷⣿⣿⣿⡀⠹⣟⣾⣟⣆⠹⣯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢠⡘⣿⣿⡄⠉⢿⣿⣽⡷⣿⣻⣿⣿⣿⣿⡝⣷⣯⢿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣯⢿⣾⢿⣿⡄⢄⠘⢿⣞⡿⣧⡈⢷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣧⠘⣿⣷⠈⣦⠙⢿⣽⣷⣻⣽⣿⣿⣿⣿⣌⢿⣯⢿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣟⣯⣿⢿⣿⡆⢸⡷⡈⢻⡽⣷⡷⡄⠻⣽⣿⣿⡿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣏⢰⣯⢷⠈⣿⡆⢹⢷⡌⠻⡾⢋⣱⣯⣿⣿⣿⣿⡆⢻⡿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⡎⣿⢾⡿⣿⡆⢸⣽⢻⣄⠹⣷⣟⣿⣄⠹⣟⣿⣿⣟⣿⣿⣿⣿⣿⣿⣽⣿⣿⣿⡇⢸⣯⣟⣧⠘⣷⠈⡯⠛⢀⡐⢾⣟⣷⣻⣿⣿⣿⡿⡌⢿⣻⣿⣿
⣿⣿⣿⣿⣿⣿⣧⢸⡿⣟⣿⡇⢸⣯⣟⣮⢧⡈⢿⣞⡿⣦⠘⠏⣹⣿⣽⢿⣿⣿⣿⣿⣯⣿⣿⣿⡇⢸⣿⣿⣾⡆⠹⢀⣠⣾⣟⣷⡈⢿⣞⣯⢿⣿⣿⣿⢷⠘⣯⣿⣿
⣿⣿⣿⣿⣿⣿⣿⡈⣿⢿⣽⡇⠘⠛⠛⠛⠓⠓⠈⠛⠛⠟⠇⢀⢿⣻⣿⣯⢿⣿⣿⣿⣷⢿⣿⣿⠁⣾⣿⣿⣿⣧⡄⠇⣹⣿⣾⣯⣿⡄⠻⣽⣯⢿⣻⣿⣿⡇⢹⣾⣿
⣿⣿⣿⣿⣿⣿⣿⡇⢹⣿⡽⡇⢸⣿⣿⣿⣿⣿⣞⣆⠰⣶⣶⡄⢀⢻⡿⣯⣿⡽⣿⣿⣿⢯⣟⡿⢀⣿⣿⣿⣿⣿⣧⠐⣸⣿⣿⣷⣿⣿⣆⠹⣯⣿⣻⣿⣿⣿⢀⣿⢿
⣿⣿⣿⣿⣿⣿⣿⣿⠘⣯⡿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣧⡈⢿⣳⠘⡄⠻⣿⢾⣽⣟⡿⣿⢯⣿⡇⢸⣿⣿⣿⣿⣿⣿⡀⢾⣿⣿⣿⣿⣿⣿⣆⠹⣾⣷⣻⣿⡿⡇⢸⣿
⣿⣿⣿⣿⣿⣿⣿⣿⡇⢹⣿⠇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠻⡇⢹⣆⠹⣟⣾⣽⣻⣟⣿⣽⠁⣾⣿⣿⣿⣿⣿⣿⣇⣿⣿⠿⠛⠛⠉⠙⠋⢀⠁⢘⣯⣿⣿⣧⠘⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⡈⣿⡃⢼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡙⠌⣿⣆⠘⣿⣞⡿⣞⡿⡞⢠⣿⣿⣿⣿⣿⡿⠛⠉⠁⢀⣀⣠⣤⣤⣶⣶⣶⡆⢻⣽⣞⡿⣷⠈⣿
⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠘⠁⠉⠉⠉⠉⠉⠉⠉⠉⠉⠙⠛⠛⢿⣄⢻⣿⣧⠘⢯⣟⡿⣽⠁⣾⣿⣿⣿⣿⣿⡃⢀⢀⠘⠛⠿⢿⣻⣟⣯⣽⣻⣵⡀⢿⣯⣟⣿⢀⣿
⣿⣿⣿⣟⣿⣿⣿⣿⣶⣶⡆⢀⣿⣾⣿⣾⣷⣿⣶⠿⠚⠉⢀⢀⣤⣿⣷⣿⣿⣷⡈⢿⣻⢃⣼⣿⣿⣿⣿⣻⣿⣿⣿⡶⣦⣤⣄⣀⡀⠉⠛⠛⠷⣯⣳⠈⣾⡽⣾⢀⣿
⣿⢿⣿⣿⣻⣿⣿⣿⣿⣿⡿⠐⣿⣿⣿⣿⠿⠋⠁⢀⢀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣌⣥⣾⡿⣿⣿⣷⣿⣿⢿⣷⣿⣿⣟⣾⣽⣳⢯⣟⣶⣦⣤⡾⣟⣦⠘⣿⢾⡁⢺
⣿⣻⣿⣿⡷⣿⣿⣿⣿⣿⡗⣦⠸⡿⠋⠁⢀⢀⣠⣴⢿⣿⣽⣻⢽⣾⣟⣷⣿⣟⣿⣿⣿⣳⠿⣵⣧⣼⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣽⣳⣯⣿⣿⣿⣽⢀⢷⣻⠄⠘
⣿⢷⣻⣿⣿⣷⣻⣿⣿⣿⡷⠛⣁⢀⣀⣤⣶⣿⣛⡿⣿⣮⣽⡻⣿⣮⣽⣻⢯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⢀⢸⣿⢀⡆
⠸⣟⣯⣿⣿⣷⢿⣽⣿⣿⣷⣿⣷⣆⠹⣿⣶⣯⠿⣿⣶⣟⣻⢿⣷⣽⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢀⣯⣟⢀⡇
⣇⠹⣟⣾⣻⣿⣿⢾⡽⣿⣿⣿⣿⣿⣆⢹⣶⣿⣻⣷⣯⣟⣿⣿⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢀⡿⡇⢸⡇
⣿⣆⠹⣷⡻⣽⣿⣯⢿⣽⣻⣿⣿⣿⣿⣆⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⢸⣿⠇⣼⡇
⡙⠾⣆⠹⣿⣦⠛⣿⢯⣷⢿⡽⣿⣿⣿⣿⣆⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠎⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⢀⣿⣾⣣⡿⡇
⣿⣷⡌⢦⠙⣿⣿⣌⠻⣽⢯⣿⣽⣻⣿⣿⣿⣧⠩⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⢰⢣⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⢀⢀⢿⣞⣷⢿⡇
⣿⣽⣆⠹⣧⠘⣿⣿⡷⣌⠙⢷⣯⡷⣟⣿⣿⣿⣷⡀⡹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣈⠃⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢀⣴⡧⢀⠸⣿⡽⣿⢀
⢻⣽⣿⡄⢻⣷⡈⢿⣿⣿⢧⢀⠙⢿⣻⡾⣽⣻⣿⣿⣄⠌⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⢁⣰⣾⣟⡿⢀⡄⢿⣟⣿⢀
⡄⢿⣿⣷⢀⠹⣟⣆⠻⣿⣿⣆⢀⣀⠉⠻⣿⡽⣯⣿⣿⣷⣈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⢀⣠⠘⣯⣷⣿⡟⢀⢆⠸⣿⡟⢸
⣷⡈⢿⣿⣇⢱⡘⢿⣷⣬⣙⠿⣧⠘⣆⢀⠈⠻⣷⣟⣾⢿⣿⣆⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⣠⡞⢡⣿⢀⣿⣿⣿⠇⡄⢸⡄⢻⡇⣼
⣿⣷⡈⢿⣿⡆⢣⡀⠙⢾⣟⣿⣿⣷⡈⠂⠘⣦⡈⠿⣯⣿⢾⣿⣆⠙⠻⠿⠿⠿⠿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⢋⣠⣾⡟⢠⣿⣿⢀⣿⣿⡟⢠⣿⢈⣧⠘⢠⣿
⣿⣿⣿⣄⠻⣿⡄⢳⡄⢆⡙⠾⣽⣿⣿⣆⡀⢹⡷⣄⠙⢿⣿⡾⣿⣆⢀⡀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⣀⣠⣴⡿⣯⠏⣠⣿⣿⡏⢸⣿⡿⢁⣿⣿⢀⣿⠆⢸⣿
⣿⣿⣿⣿⣦⡙⣿⣆⢻⡌⢿⣶⢤⣉⣙⣿⣷⡀⠙⠽⠷⠄⠹⣿⣟⣿⣆⢙⣋⣤⣤⣤⣄⣀⢀⢀⢀⢀⣾⣿⣟⡷⣯⡿⢃⣼⣿⣿⣿⠇⣼⡟⣡⣿⣿⣿⢀⡿⢠⠈⣿
⣿⣿⣿⣿⣿⣷⣮⣿⣿⣿⡌⠁⢤⣤⣤⣤⣬⣭⣴⣶⣶⣶⣆⠈⢻⣿⣿⣆⢻⣿⣿⣿⣿⣿⣿⣷⣶⣤⣌⣉⡘⠛⠻⠶⣿⣿⣿⣿⡟⣰⣫⣴⣿⣿⣿⣿⠄⣷⣿⣿⣿
*/
