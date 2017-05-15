#include "jump.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int petaa[153][153][153];
  
std::vector<int> getMinimumPoints(int N, int Q, std::string S,
    std::vector<int> L, std::vector<int> R, std::vector<int> K) {
  std::vector<int> ans;
  for (int i=0;i<=152;i++)
  	for (int j=0;j<=152;j++)
  		for (int k=0;k<=152;k++)
  			petaa[i][j][k] = 99999999;

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

  for (int kk=1;kk<=N;kk++){
  	for (int i=0;i<N;i++){
      petaa[kk][i][i] = 0;
      //if (kk == 3) cout<<"dari "<<i<<" bisa ke: ";
      for (int j=i+1;j<N;j++){
        if (min_loc[j] - max_loc[i] <= kk){
      	 petaa[kk][i][j] = (S[ ori[j]] - '0');
         //if (kk == 3)  cout<<" "<<j<<endl;
        }
      }
    }
  
  	for (int k=0;k<N;k++)
  		for (int i=0;i<N;i++)
  			for (int j=0;j<N;j++)
  				petaa[kk][i][j] = min(petaa[kk][i][j] , petaa[kk][i][k] + petaa[kk][k][j]);

  }

  for (int i=0;i<Q;i++){
  	int l = compressed[L[i] - 1];
  	int r = compressed[R[i] - 1];
    //cout<<l<<" "<<r<<endl;
  	int k = K[i];
    if (k > N)
      k = N;
    ans.push_back(petaa[k][l][r] + S[L[i] - 1] - '0');
  }

  return ans;
}
