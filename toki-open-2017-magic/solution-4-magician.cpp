#include "magician.h"

#include <algorithm>
#include <vector>

namespace magician {
  int N, K;

  int next(int x) {
    return x % N + 1;
  }

  std::vector<int> findOriginalCards(std::vector<int> cards) {
    if (K == 1) {
      if (cards[1] - cards[0] == 1) {
        return {cards[0]};
      } else {
        return {cards[1]};
      }
    } else {
      std::vector<int> order = {0, 1, 2};
      std::vector<int> ans;
      do {
        if (next(cards[order[0]]) == cards[order[1]] && next(cards[order[1]]) == cards[order[2]]) {
          ans = {cards[order[0]], cards[order[1]]};
        }
        if (next(cards[order[0]]) == cards[order[1]] && next(cards[order[1]]) != cards[order[2]]) {
          ans = {cards[order[0]], cards[order[2]]};
        }
      } while (next_permutation(order.begin(), order.end()));
      sort(ans.begin(), ans.end());
      return ans;
    }
  }
}

void initMagician(int N, int K) {
  magician::N = N;
  magician::K = K;
}

std::vector<int> findOriginalCards(std::vector<int> cards) {
  return magician::findOriginalCards(cards);
}
