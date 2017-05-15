#include "jump.h"

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

std::vector<int> getMinimumPoints(int N, int Q, std::string S,
    std::vector<int> L, std::vector<int> R, std::vector<int> K) {
  std::vector<int> ans;
  int petaa[77][77][77];
  for (int i=0;i<=N;i++)
  	for (int j=0;j<=N;j++)
  		for (int k=0;k<=N;k++)
  			petaa[i][j][k] = 99999999;
  for (int kk=1;kk<=N;kk++){
  	for (int i=0;i<N;i++)
  		for (int j=i+1;j<N && j <= i + kk;j++)
  			petaa[kk][i][j] = (S[j] - '0');

  
  	for (int k=0;k<N;k++)
  		for (int i=0;i<N;i++)
  			for (int j=0;j<N;j++)
  				petaa[kk][i][j] = min(petaa[kk][i][j] , petaa[kk][i][k] + petaa[kk][k][j]);

  }

  for (int i=0;i<Q;i++){
  	int l = L[i] - 1;
  	int r = R[i] - 1;
  	int k = K[i];
  	ans.push_back(petaa[k][l][r] + S[l] - '0');
  }

  return ans;
}
