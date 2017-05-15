#include "magician.h"

#include <assert.h>
#include <map>
#include <vector>

namespace magician {
  class BipartiteGraph
  {
  public:
    int m, n;
    std::vector<int> with;
    std::vector<std::vector<int> > adj;
    std::vector<bool> visited;

    void reset(int _m,int _n) {
      m = _m; n = _n;
      with.resize(n);
      adj.resize(m);
      visited.resize(n);
      for (int i = 0; i < m; ++i) {
        adj[i].clear();
      }
    }
    void addEdge(int a,int b) {
      adj[a].push_back(b);
    }
    bool match(int x) {
      for (int i = 0; i < adj[x].size(); ++i) {
        int j = adj[x][i];
        if (visited[j]) continue;
        visited[j] = true;
        if (with[j] == -1 || match(with[j])) {
          with[j] = x;
          return true;
        }
      }
      return false;
    }
    int countMCBM(void) {
      int ans = 0;
      for (int i = 0; i < n; ++i) {
        with[i] = -1;
      }
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          visited[j] = false;
        }
        if(match(i)) {
          ++ans;
        }
      }
      return ans;
    }
  };

  int N, K;

  std::vector<int> findOriginalCards(std::vector<int> cards) {
    BipartiteGraph BG;
    std::vector<int> leftNodes, rightNodes;
    std::map<int, int> leftNodesIndex, rightNodesIndex;

    for (int bit = 0; bit < (1 << N); ++bit) {
      if (__builtin_popcount(bit) == K) {
        leftNodesIndex[bit] = leftNodes.size();
        leftNodes.push_back(bit);
      }
      if (__builtin_popcount(bit) == K + 1) {
        rightNodesIndex[bit] = rightNodes.size();
        rightNodes.push_back(bit);
      }
    }

    BG.reset(leftNodes.size(), rightNodes.size());

    for (int bit : leftNodes) {
      for (int i = 0; i < N; ++i) {
        if (!(bit & (1 << i))) {
          int rightBit = bit ^ (1 << i);
          BG.addEdge(leftNodesIndex[bit], rightNodesIndex[rightBit]);
        }
      }
    }

    assert(BG.countMCBM() == leftNodes.size());

    int bit = 0;
    for (int i = 0; i < K + 1; ++i) {
      bit ^= (1 << (cards[i] - 1));
    }
    int leftBit = leftNodes[BG.with[rightNodesIndex[bit]]];
    std::vector<int> ans;

    for (int i = 0; i < N; ++i) {
      if (leftBit & (1 << i)) {
        ans.push_back(i + 1);
      }
    }

    return ans;
  }
}

void initMagician(int N, int K) {
  magician::N = N;
  magician::K = K;
}

std::vector<int> findOriginalCards(std::vector<int> cards) {
  return magician::findOriginalCards(cards);
}
