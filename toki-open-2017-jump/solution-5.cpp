#include "jump.h"

#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int petaa[405][405];

int jump[405][405][11];
int dp(int k,int st, int ed){
  if (st >= ed)
    return 0;

  if (petaa[st][ed] != -1)
    return petaa[st][ed];
  petaa[st][ed] = 999999;
  for (int i=0;i<=9;i++){
    if (jump[k][st][i] != -1){
      petaa[st][ed] = min(petaa[st][ed] , dp(k, jump[k][st][i], ed) + i);
    }
  }
  return petaa[st][ed];
}

std::vector<int> getMinimumPoints(int N, int Q, std::string S,
    std::vector<int> L, std::vector<int> R, std::vector<int> K) {
  std::vector<int> ans(Q);


  vector<int> pos;
  vector<int> compressed(N);
  vector<int> min_loc;
  vector<int> max_loc;
  vector<int> ori;
  for (int i=0;i<N;i++){
    if (i > 0 && S[i] != '0' && S[i-1] == '0') max_loc.push_back(i-1);
    if (S[i] > '0') pos.push_back(S[i] - '0'), ori.push_back(i), min_loc.push_back(i), max_loc.push_back(i);
    else if (S[i] == '0' && (i == 0 || S[i-1] != '0')) ori.push_back(i),pos.push_back(0), min_loc.push_back(i);
    compressed[i] = pos.size() - 1;
  }
  max_loc.push_back(999999);

  //cout<<"KAGI"<<endl;

  N = pos.size();
  memset(jump, -1, sizeof jump);

  vector<pair<int,int>> sorted_Q;
  for (int i=0;i<Q;i++){
    sorted_Q.push_back(make_pair(min(N,K[i]), i));
  }
  sort(sorted_Q.begin(), sorted_Q.end());

  int q_id = 0;

  for (int kk=1;kk<=N;kk++){
    memset(petaa, -1, sizeof petaa);

    for (int i=0;i<N;i++){
      //petaa[i][i] = 0;
      //if (kk == 3) cout<<"dari "<<i<<" bisa ke: ";
      for (int j=i+1;j<N;j++){
        if (min_loc[j] - max_loc[i] <= kk){
         petaa[i][j] = (S[ ori[j]] - '0');
         jump[kk][i][(S[ ori[j]] - '0')] = j;
         //if (kk == 3)  cout<<" "<<j<<endl;
        }
      }
    }
      
    while (q_id < Q && sorted_Q[q_id].first == kk){
      int i = sorted_Q[q_id].second;

      int l = compressed[L[i] - 1];
      int r = compressed[R[i] - 1];
      //cout<<l<<" "<<r<<endl;
      int k = K[i];
      if (k > N)
        k = N;
      ans[i] = dp(k,l,r) + S[L[i] - 1] - '0';
      q_id++;
    }
  }

  return ans;
}