#include "jump.h"

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;  
string S;
int petaa[201][201][201];
int jump[201][201][11];
int dp(int k, int st, int ed){
  if (st >= ed)
    return 0;

  if (petaa[k][st][ed] != -1)
    return petaa[k][st][ed];
  petaa[k][st][ed] = 999999;
  for (int i=0;i<=9;i++){
    if (jump[k][st][i] != -1){
      petaa[k][st][ed] = min(petaa[k][st][ed] , dp(k, jump[k][st][i], ed) + i);
    }
  }
  return petaa[k][st][ed];
}

std::vector<int> getMinimumPoints(int N, int Q, std::string _S,
    std::vector<int> L, std::vector<int> R, std::vector<int> K) {
  std::vector<int> ans;
  memset(petaa, -1, sizeof petaa);
  memset(jump, -1, sizeof jump);
  S = _S;
  for (int kk=1;kk<=N;kk++)
  	for (int i=0;i<N;i++)
  		for (int j=i+1;j<N && j <= i + kk;j++){
        petaa[kk][i][j] = S[j] - '0';
        jump[kk][i][S[j] - '0'] = j;
      }


  for (int i=0;i<Q;i++){
  	int l = L[i] - 1;
  	int r = R[i] - 1;
  	int k = K[i];
  	ans.push_back(dp(k,l,r) + S[l] - '0');
  }

  return ans;
}