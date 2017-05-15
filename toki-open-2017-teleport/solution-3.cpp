#include "teleport.h"
#include <cstdio>
#include <vector>

using namespace std;

#define MINUS_INFINITY -2000000000000000000LL

int R, C, K;
vector<vector<int> > T, P;
long long mem[37][37][37][37];
bool sudah[37][37][37][37];

long long DP(int x_sta, int y_sta, int x_fin, int y_fin) {
  if (sudah[x_sta][y_sta][x_fin][y_fin]) return mem[x_sta][y_sta][x_fin][y_fin];
  sudah[x_sta][y_sta][x_fin][y_fin] = true;
	
  if (x_sta == x_fin && y_sta == y_fin) return mem[x_sta][y_sta][x_fin][y_fin] = P[x_sta][y_sta];
	if (x_sta >= x_fin) return mem[x_sta][y_sta][x_fin][y_fin] = MINUS_INFINITY;

	long long ans = MINUS_INFINITY;
	if (y_sta > 0) ans = max(ans,DP(x_sta+1,y_sta-1,x_fin,y_fin));
	ans = max(ans,DP(x_sta+1,y_sta,x_fin,y_fin));
	if (y_sta < C - 1) ans = max(ans,DP(x_sta+1,y_sta+1,x_fin,y_fin));

	return mem[x_sta][y_sta][x_fin][y_fin] = P[x_sta][y_sta] + ans;
}

long long getMaximumPoints(int RR, int CC, int KK, vector<vector<int> > TT, vector<vector<int> > PP) {
	R = RR;
	C = CC;
	K = KK;
	T = TT;
	P = PP;
	
	long long ans = MINUS_INFINITY;
	long long start = MINUS_INFINITY;
	long long end = MINUS_INFINITY;
	long long middle = 0;

	for (int i = 0; i < R; i++) {
  		for (int j = 0; j < C; j++) {
	  		for (int k = 0; k < R; k++) {
	  			for (int l = 0 ; l < C; l++) {
	  				mem[i][j][k][l] = MINUS_INFINITY;
            sudah[i][j][k][l] = false;
	  			}
	  		}
	  	}
  	}

  	for (int j = 0; j < C; j++) {
  		for (int l = 0; l < C; l++) {
  			ans = max(ans,DP(0,j,R-1,l));
  		}
  	}

	for (int j = 0; j < C; j++) {
  		for (int x = 0; x < R; x++) {
  			for (int y = 0; y < C; y++) {
  				if (T[x][y] == 1) start = max(start,DP(0,j,x,y));
  			}
  		}
  	}

	for (int l = 0; l < C; l++) {
  		for (int x = 0; x < R; x++) {
  			for (int y = 0; y < C; y++) {
  				if (T[x][y] == 1) end = max(end,DP(x,y,R-1,l));
  			}
  		}
  	}

  	for (int x_sta = 0; x_sta < R; x_sta++) {
  		for (int y_sta = 0; y_sta < C; y_sta++) {
  			for (int x_fin = 0; x_fin < R; x_fin++) {
  				for (int y_fin = 0; y_fin < C; y_fin++) {
  					if (T[x_sta][y_sta] == 1 && T[x_fin][y_fin]) middle = max(middle,DP(x_sta,y_sta,x_fin,y_fin));
  				}
  			}
  		}
  	}

  	if (K > 0) ans = max(ans,start + end + (K-1) * middle);

  	return ans;
}
