#include "magician.h"

#include <map>
#include <set>
#include <vector>

namespace magician {

  std::vector<int> leftNodes, rightNodes;
  std::map<int, int> leftNodesIndex, rightNodesIndex;
  std::vector<int> matchedWith;
  std::set<std::pair<int, int>> visited;
  int N, K;

  bool dfs(int now, int mask) {
    if (now == leftNodes.size()) {
      return true;
    }
    if (visited.count(std::make_pair(now, mask))) {
      return false;
    }
    visited.insert(std::make_pair(now, mask));
    int bit = leftNodes[now];
    for (int i = 0; i < N; ++i) {
      if (!(bit & (1 << i))) {
        int rightNode = bit ^ (1 << i);
        int rightNodeIndex = rightNodesIndex[rightNode];
        if (mask & (1 << rightNodeIndex)) {
          continue;
        }
        matchedWith[now] = rightNodeIndex;
        if (dfs(now + 1, mask ^ (1 << rightNodeIndex))) {
          return true;
        }
      }
    }
    return false;
  }

  void init() {
    for (int bit = 0; bit < (1 << N); ++bit) {
      if (__builtin_popcount(bit) == K) {
        leftNodesIndex[bit] = leftNodes.size();
        leftNodes.push_back(bit);
      } else {
        rightNodesIndex[bit] = rightNodes.size();
        rightNodes.push_back(bit);
      }
    }
    matchedWith.resize(leftNodes.size());
    dfs(0, 0);
  }

  std::vector<int> findOriginalCards(std::vector<int> cards) {
    int bit = 0;
    for (int i = 0; i < K + 1; ++i) {
      bit ^= (1 << (cards[i] - 1));
    }
    for (int i = 0; i < leftNodes.size(); ++i) {
      if (rightNodes[matchedWith[i]] == bit) {
        std::vector<int> ans;
        for (int j = 0; j < N; ++j) {
          if (leftNodes[i] & (1 << j)) {
            ans.push_back(j + 1);
          }
        }
        return ans;
      }
    }
    return {};
  }
}

void initMagician(int _N, int _K) {
  magician::N = _N;
  magician::K = _K;
  magician::init();
}

std::vector<int> findOriginalCards(std::vector<int> cards) {
  return magician::findOriginalCards(cards);
}
