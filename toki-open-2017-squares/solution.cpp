#include "squares.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#define GERAK false
#define DIAM true
using namespace std;


/*
 __ __
| 1| 2|
|__|__|
| 3| 4|
|__|__|
*/
vector<int> next1;
vector<int> next2;
vector<int> next3;
vector<int> next4;
vector<int> x;
vector<int> y;
vector<int> total_points;
vector<int> point_id;
vector<bool> diem;
vector<bool> is_leaf;

bool dead[111111];

priority_queue<pair<int, pair<int,int> > > closest_dists;
int ada_brp;

int init_seqtree(){
	next1.push_back(-1);
	next2.push_back(-1);
	next3.push_back(-1);
	next4.push_back(-1);
	x.push_back(-1);
	y.push_back(-1);
	total_points.push_back(0);
	is_leaf.push_back(true);
	point_id.push_back(-1);
	diem.push_back(GERAK);
	return x.size() - 1;
}

void remove_point(int id, int wow_x ,int wow_y, int minX, int minY, int maxX, int maxY){
	if (wow_x < 0 || wow_y < 0 || wow_x > 400000 || wow_y > 400000)
		return;
	//cout<<"removing "<<id<<endl;
	total_points[id]--;
	if (x[id] != -1){
		x[id] = -1;
		y[id] = -1;
		point_id[id] = -1;
		return;
	}
	//cek quadran
	int halfX = (minX + maxX) / 2;
	int halfY = (minY + maxY) / 2;
	
	if (wow_x >= minX && wow_x <= halfX && wow_y >= minY && wow_y <= halfY)
		remove_point(next1[id], wow_x, wow_y, minX, minY, halfX, halfY);

	if (wow_x >= halfX + 1 && wow_x <= maxX && wow_y >= minY && wow_y <= halfY)
		remove_point(next2[id], wow_x, wow_y, halfX + 1,  minY, maxX, halfY);

	if (wow_x >= minX && wow_x <= halfX && wow_y >= halfY + 1 && wow_y <= maxY)
		remove_point(next3[id], wow_x, wow_y, minX, halfY + 1, halfX,  maxY);

	if (wow_x >= halfX + 1 && wow_x <= maxX && wow_y >= halfY + 1 && wow_y <= maxY)
		remove_point(next4[id], wow_x, wow_y, halfX + 1, halfY + 1, maxX, maxY);

}
int ID_CUY;
void add_point(int id, int wow_x ,int wow_y, int minX, int minY, int maxX, int maxY, int is_gerak, int p_id){
	if (wow_x < 0 || wow_y < 0 || wow_x > 400000 || wow_y > 400000)
		return;
	//printf("-- %d (%d, %d) - (%d, %d)\n", id, minX, minY, maxX, maxY);
	total_points[id]++;
	//is leaf. Put it here
	if (is_leaf[id]){
		//printf("BREAK\n");
		x[id] = wow_x;
		y[id] = wow_y;
		//cout<<"taro "<<x[id]<<" "<<y[id]<<" di "<<id<<" ("<< minX<<" "<<maxX<<" : "<<minY<<" "<<maxY<<endl;
		diem[id] = is_gerak;
		point_id[id] = p_id;
		is_leaf[id] = false;
		int aaa = init_seqtree();
		int bbb = init_seqtree();
		int ccc = init_seqtree();
		int ddd = init_seqtree();
		next1[id] = aaa;
		next2[id] = bbb;
		next3[id] = ccc;
		next4[id] = ddd;

		return;
	}

	//if not empty. Make it empty, then update
	if (x[id] != -1){
		if (x[id] == wow_x && y[id] == wow_y)
			return;
		int tmp_x = x[id];
		int tmp_y = y[id];
		x[id] = -1;
		y[id] = -1;
		//total_points[id]--;
		add_point(id, tmp_x, tmp_y, minX, minY, maxX, maxY, diem[id], point_id[id]);
		point_id[id] = -1;
	}
	//cek quadran
	int halfX = (minX + maxX) / 2;
	int halfY = (minY + maxY) / 2;
	
	if (wow_x >= minX && wow_x <= halfX && wow_y >= minY && wow_y <= halfY)
		add_point(next1[id], wow_x, wow_y, minX, minY, halfX, halfY, is_gerak, p_id);

	if (wow_x >= halfX + 1 && wow_x <= maxX && wow_y >= minY && wow_y <= halfY)
		add_point(next2[id], wow_x, wow_y, halfX + 1,  minY, maxX, halfY, is_gerak, p_id);

	if (wow_x >= minX && wow_x <= halfX && wow_y >= halfY + 1 && wow_y <= maxY)
		add_point(next3[id], wow_x, wow_y, minX, halfY + 1, halfX,  maxY, is_gerak, p_id);

	if (wow_x >= halfX + 1 && wow_x <= maxX && wow_y >= halfY + 1 && wow_y <= maxY)
		add_point(next4[id], wow_x, wow_y, halfX + 1, halfY + 1, maxX, maxY, is_gerak, p_id);

}

int rx, ry;
bool ada;
bool cari_diam;
int pasangan;
int cari_range;
int wow;
void cek(int id, int cari_x1, int cari_y1, int cari_x2, int cari_y2, int minX, int minY, int maxX, int maxY){
	if (ada)
		return;
	
	if (total_points[id] == 0){
		//printf("       mentok cari di %d range (%d,%d) - (%d,%d)\n", id, cari_x1, cari_y1, cari_x2, cari_y2);
		return;
	}
	
	cari_x1 = max(cari_x1, minX);
	cari_x2 = min(cari_x2, maxX);
	cari_y1 = max(cari_y1, minY);
	cari_y2 = min(cari_y2, maxY);

	//printf("   cari di %d range (%d,%d) - (%d,%d)\n", id, cari_x1, cari_y1, cari_x2, cari_y2);
	/*if ((cari_diam == diem[id] || cari_diam == DIAM) && cari_x1 == minX && cari_x2 == maxX && cari_y1 == minY && cari_y2 == maxY && total_points[id]){
		pasangan = point_id[id];
		ada = true;
		return;
	}*/

	if (cari_x1 > cari_x2 || cari_y1 > cari_y2)
		return;	
	
	if ((cari_diam == diem[id] || cari_diam == DIAM) && x[id] != -1)
		if ((point_id[id] != -1 && !dead[point_id[id]]) || (point_id[id] == -1)){
		
		//cout<<"LHOooooooOOOOoOOOO"<<endl;
		//cout<<"kagi "<<x[id]<<" "<<y[id]<<" "<<rx<<" "<<ry<<endl;
		if ( max(abs(x[id] - rx) , abs(y[id] - ry)) <= cari_range ){
			pasangan = point_id[id];
			wow = max(abs(x[id] - rx) , abs(y[id] - ry));
			//cout<<pasangan<<endl;
			ada = true;
		}
		return;
	}

	if (is_leaf[id]){
		return;
	}	

	//cek quadran
	int halfX = (minX + maxX) / 2;
	int halfY = (minY + maxY) / 2;
	if (rand() % 2 == 0){
		cek(next4[id], cari_x1, cari_y1, cari_x2, cari_y2, halfX + 1, halfY + 1, maxX , maxY);
		cek(next3[id], cari_x1, cari_y1, cari_x2, cari_y2, minX     , halfY + 1, halfX, maxY);
		cek(next2[id], cari_x1, cari_y1, cari_x2, cari_y2, halfX + 1, minY     , maxX , halfY);
		cek(next1[id], cari_x1, cari_y1, cari_x2, cari_y2, minX     , minY     , halfX, halfY);
	} else {
		cek(next1[id], cari_x1, cari_y1, cari_x2, cari_y2, minX     , minY     , halfX, halfY);
		cek(next2[id], cari_x1, cari_y1, cari_x2, cari_y2, halfX + 1, minY     , maxX , halfY);
		cek(next3[id], cari_x1, cari_y1, cari_x2, cari_y2, minX     , halfY + 1, halfX, maxY);
		cek(next4[id], cari_x1, cari_y1, cari_x2, cari_y2, halfX + 1, halfY + 1, maxX , maxY);
	}
}

int closest_from(int refx, int refy, bool is_gerak, bool cari_field){
	cari_diam = cari_field;
	//binser
	//if (cari_field == GERAK)
	//	remove_point(0, refx, refy, 0, 0, 200000, 200000);
	rx = refx;
	ry = refy;

	int hi = 400000;
	int lo = 0;
	int mid;
	wow = -1;
	while (lo < hi){
		mid = (lo + hi) / 2;
	 	ada = false;
	 	
	 	cari_range = mid;
		cek(0, refx - mid, refy - mid, refx + mid, refy + mid, 0, 0, 400000, 400000);
		if (!ada){
			lo = mid + 1;
		} else
			hi = wow;

	}
	//if (cari_field == GERAK)
	//	add_point(0, refx, refy, 0, 0, 200000, 200000, is_gerak, ID_CUY);
	if (cari_field == DIAM)
		pasangan = -1;
	return lo;
}



long long getTotalArea(int N, std::vector<int> X, std::vector<int> Y) {
	long long res = 0;
	//kali dua semua
	for (int i=0;i<N;i++){
		X[i] *=2;
		Y[i] *=2;
		X[i] += 100000;
		Y[i] += 100000;
	}
	//init segtree
	init_seqtree();
	for (int i=0;i<N;i++){
		//printf("taro %d %d\n", X[i], Y[i]);
		add_point(0, X[i], Y[i], 0, 0, 400000, 400000, GERAK, i);
	}

	for (int i=0;i<N;i++){
		ID_CUY = i;
		int dist = 9999999;
		dead[i] = 1; dist = min(dist, closest_from(X[i], Y[i], GERAK, GERAK) / 2); dead[i] = 0;
		//printf("terdekat dari %d %d = %d (point id %d)\n", X[i], Y[i], dist, pasangan );
		closest_dists.push(make_pair(-dist, make_pair(i, pasangan)));
	}

	//hajar
	while (closest_dists.size() > 0){
		int from = closest_dists.top().second.first;
		int to = closest_dists.top().second.second;
		long long l = -closest_dists.top().first;

		closest_dists.pop();
		
		if (dead[from]) continue;

		if (to != -1 && dead[to]) {
			//cout<<"mati "<<endl;
			dead[from] = 1; int dist = closest_from(X[from], Y[from], GERAK, DIAM); dead[from] = 0;
			dead[from] = 1; int dist2 = closest_from(X[from], Y[from], GERAK, GERAK) / 2; dead[from] = 0;
			//int expdist2 = max(abs(X[from] - X[pasangan]),abs(Y[from] - Y[pasangan] )) / 2;
			//cout<<dist<<" vs "<<dist2<<" "<<expdist2<<" :"<<pasangan<<endl; 
			if (pasangan == -1)
				dist2 = 9999999;
			//int dist2 = 9999999;
			if (dist < dist2){
				pasangan = -1;
			} else dist = dist2;

			closest_dists.push(make_pair(-dist, make_pair(from, pasangan)));

			continue;
		}

		//cerr<<from<<" to "<<to<<" : "<<" dist "<<l<<endl;
		res += (l*l);
		//cout<<res<<endl;
		dead[from] = true;
		remove_point(0, X[from], Y[from], 0, 0, 400000, 400000);
		if (to != -1){
			res += (l*l);
			dead[to] = true;
			remove_point(0, X[to], Y[to], 0, 0, 400000, 400000);
			add_point(0, X[to] + l, Y[to] + l, 0, 0, 400000, 400000, DIAM, -1);
			add_point(0, X[to] - l, Y[to] + l, 0, 0, 400000, 400000, DIAM, -1);
			add_point(0, X[to] + l, Y[to] - l, 0, 0, 400000, 400000, DIAM, -1);
			add_point(0, X[to] - l, Y[to] - l, 0, 0, 400000, 400000, DIAM, -1);

		}

		add_point(0, X[from] + l, Y[from] + l, 0, 0, 400000, 400000, DIAM, -1);
		add_point(0, X[from] - l, Y[from] + l, 0, 0, 400000, 400000, DIAM, -1);
		add_point(0, X[from] + l, Y[from] - l, 0, 0, 400000, 400000, DIAM, -1);
		add_point(0, X[from] - l, Y[from] - l, 0, 0, 400000, 400000, DIAM, -1);
		//cout<<"dah"<<endl;
	}
  return res;
}