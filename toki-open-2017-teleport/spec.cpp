#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

#define SZ(a) ((int)(a).size())

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int ONE_MILLION = 1000 * 1000;
const int ONE_BILLION = 1000 * 1000 * 1000;

class ProblemSpec : public BaseProblemSpec {
protected:
  int R, C, K;
  vector<vi> T, P;
  ll answer;

  void InputFormat() {
    LINE(R, C, K);
    GRID(T) % SIZE(R, C);
    GRID(P) % SIZE(R, C);
  }

  void OutputFormat() {
    LINE(answer);
  }

  void Constraints() {
    CONS(1 <= R && R <= 1500);
    CONS(1 <= C && C <= 1500);
    CONS(0 <= K && K <= ONE_BILLION);
    CONS(validPoints());
    CONS(validTeleportMatrixEntries());
  }

  void Subtask1() {
    CONS(R <= 30);
    CONS(C <= 30);
    CONS(K <= 30);
  }

  void Subtask2() {
    CONS(R <= 250);
    CONS(C <= 250);
    CONS(K <= 250);
  }

  void Subtask3() {
    CONS(R <= 30);
    CONS(C <= 30);
  }

  void Subtask4() {
    CONS(K == 0);
  }

  void Subtask5() {
  }

private:
  bool validPoints() {
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (P[i][j] < -1000000 || P[i][j] > 1000000) {
          return false;
        }
      }
    }
    return true;
  }
  bool validTeleportMatrixEntries() {
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (T[i][j] != 0 && T[i][j] != 1) {
          return false;
        }
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

  void SampleTestCase1() {
    Subtasks({1, 2, 3, 5});
    Input({
    "3 3 1",
    "0 1 0",
    "0 0 0",
    "0 1 0",
    "1 2 3",
    "4 5 6",
    "7 8 9"
    });
    Output({"34"});
  }

  void BeforeTestCase() {
    T.clear();
    P.clear();
    R = C = K = -1;
  }

  void TestGroup1() {
    // K = 0
    // 1 <= R, C <= 30
    
    Subtasks({1, 2, 3, 4, 5});

    CASE(R = C = 30; K = 0; P = vvi(R, vi(C, 0)); T = randomTeleports();
         for (int i = 0; i < C; i++) {
           P[R - 1][i] = -1;
         });

    CASE(R = C = 1; K = 0; P = minPoints(); T = randomTeleports());
    CASE(R = C = 1; K = 0; P = maxPoints(); T = randomTeleports());
    CASE(R = 1; C = rnd.nextInt(2, 29); K = 0; P = minPoints(); T = randomTeleports());
    CASE(R = rnd.nextInt(2, 29); C = 1; K = 0; P = minPoints(); T = randomTeleports());
    CASE(R = 1; C = rnd.nextInt(2, 29); K = 0; P = maxPoints(); T = randomTeleports());
    CASE(R = rnd.nextInt(2, 29); C = 1; K = 0; P = maxPoints(); T = randomTeleports());
    CASE(R = C = 30; K = 0; P = minPoints(); T = randomTeleports());
    CASE(R = C = 30; K = 0; P = maxPoints(); T = randomTeleports());
    CASE(R = 3; C = 6; K = 0;
         T = {{0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 1, 0},
              {0, 0, 0, 0, 0, 0}},
         P = {{1, 2, 3, -ONE_MILLION, -ONE_MILLION, -ONE_MILLION},
              {4, 5, 6, -ONE_MILLION, 1000, -ONE_MILLION},
              {10, -1, 9, -ONE_MILLION, -ONE_MILLION, -ONE_MILLION}});
    CASE(R = rnd.nextInt(1, 30); C = rnd.nextInt(1, 30); K = 0; P = randomPoints(50); T = randomTeleports());
    CASE(R = rnd.nextInt(1, 30); C = rnd.nextInt(1, 30); K = 0; P = randomPoints(20); T = randomTeleports());
    CASE(R = rnd.nextInt(1, 30); C = rnd.nextInt(1, 30); K = 0; P = randomPoints(80); T = randomTeleports());
  }

  void TestGroup2() {
    // K = 0
    // 31 <= R, C <= 250

    Subtasks({2, 4, 5});

    CASE(R = C = 31; K = 0; P = minPoints(); T = randomTeleports());
    CASE(R = C = 31; K = 0; P = maxPoints(); T = randomTeleports());
    CASE(R = 31; C = rnd.nextInt(32, 250); K = 0; P = minPoints(); T = randomTeleports());
    CASE(R = rnd.nextInt(32, 250); C = 31; K = 0; P = minPoints(); T = randomTeleports());
    CASE(R = 31; C = rnd.nextInt(32, 250); K = 0; P = maxPoints(); T = randomTeleports());
    CASE(R = rnd.nextInt(32, 250); C = 31; K = 0; P = maxPoints(); T = randomTeleports());
    CASE(R = C = 250; K = 0; P = minPoints(); T = randomTeleports());
    CASE(R = C = 250; K = 0; P = maxPoints(); T = randomTeleports());
    CASE(R = rnd.nextInt(31, 250); C = rnd.nextInt(31, 250); K = 0; P = randomPoints(50); T = randomTeleports());
    CASE(R = rnd.nextInt(31, 250); C = rnd.nextInt(31, 250); K = 0; P = randomPoints(20); T = randomTeleports());
    CASE(R = rnd.nextInt(31, 250); C = rnd.nextInt(31, 250); K = 0; P = randomPoints(80); T = randomTeleports());
  }

  void TestGroup3() {
    // K = 0
    // 251 <= R, C <= 1500

    Subtasks({4, 5});

    CASE(R = 251; C = rnd.nextInt(251, 1500); K = 0; P = minPoints(); T = randomTeleports());
    CASE(R = rnd.nextInt(251, 1500); C = 251; K = 0; P = minPoints(); T = randomTeleports());
    CASE(R = 251; C = rnd.nextInt(251, 1500); K = 0; P = maxPoints(); T = randomTeleports());
    CASE(R = rnd.nextInt(251, 1500); C = 251; K = 0; P = maxPoints(); T = randomTeleports());
    CASE(R = rnd.nextInt(251, 1500); C = rnd.nextInt(251, 1500); K = 0; P = randomPoints(20); T = randomTeleports());
    CASE(R = rnd.nextInt(251, 1500); C = rnd.nextInt(251, 1500); K = 0; P = randomPoints(80); T = randomTeleports());
  }

  void TestGroup4() {
    // 1 <= K <= 30
    // 1 <= R, C <= 30

    Subtasks({1, 2, 3, 5});
    
    CASE(R = C = 1; K = 1; T = {{1}}; P = {{ONE_MILLION}});
    CASE(R = C = 1; K = 1; T = {{1}}; P = {{-ONE_MILLION}});
    CASE(R = C = 1; K = 30; T = {{1}}; P = {{-ONE_MILLION}});
    CASE(R = 30; C = 30; K = 30; T = vvi(R, vi(C, 0)); P = maxPoints());
    CASE(R = 30; C = 30; K = 30; T = vvi(R, vi(C, 0)); P = minPoints());
    CASE(R = C = 30; K = 5; T = vvi(R, vi(C, 0)); P = vvi(R, vi(C, -ONE_MILLION)); T[0][10] = 1; P[0][10] = ONE_MILLION);
    CASE(R = 30; C = 30; K = 1; T = vvi(R, vi(C, 1)); P = maxPoints());
    CASE(R = 30; C = 30; K = 1; T = vvi(R, vi(C, 1)); P = minPoints());
    CASE(R = 30; C = 30; K = 30; T = vvi(R, vi(C, 1)); P = maxPoints());
    CASE(R = 30; C = 30; K = 30; T = vvi(R, vi(C, 1)); P = minPoints());
    CASE(R = C = 30; K = 1; T = vvi(R, vi(C, 1)); P = vvi(R, vi(C, -ONE_MILLION)); T[15][15] = 1; P[15][15] = ONE_MILLION);
    CASE(R = C = 30; K = 2; T = vvi(R, vi(C, 1)); P = vvi(R, vi(C, -ONE_MILLION)); T[15][15] = 1; P[15][15] = ONE_MILLION);
    CASE(R = C = 30; K = 30; T = vvi(R, vi(C, 1)); P = vvi(R, vi(C, -ONE_MILLION)); T[15][15] = 1; P[15][15] = ONE_MILLION);
    CASE(R = 1; C = 5; K = 1; T = {{0, 1, 0, 1, 0}}; P = {{1, -2, 4, 3, 0}});
    CASE(R = 1; C = 5; K = 2; T = {{0, 1, 0, 1, 0}}; P = {{1, -2, 4, 3, 0}});
    CASE(R = 1; C = 5; K = 30; T = {{0, 1, 0, 1, 0}}; P = {{1, -2, 4, 3, 0}});
    CASE(R = 2; C = 3; K = 1; T = {{0, 0, 0}, {1, 0, 1}}; P = {{0, -ONE_MILLION, -ONE_MILLION}, {-1, 2, 1}});
    CASE(R = 2; C = 3; K = 2; T = {{0, 0, 0}, {1, 0, 1}}; P = {{0, -ONE_MILLION, -ONE_MILLION}, {-1, 2, 1}});
    CASE(R = 2; C = 3; K = 30; T = {{0, 0, 0}, {1, 0, 1}}; P = {{0, -ONE_MILLION, -ONE_MILLION}, {-1, 2, 1}});
    CASE(R = 3; C = 6; K = 1;
         T = {{0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 1, 0},
              {0, 0, 0, 0, 0, 0}},
         P = {{1, 2, 3, -ONE_MILLION, -ONE_MILLION, -ONE_MILLION},
              {4, 5, 6, -ONE_MILLION, 1000, -ONE_MILLION},
              {10, -1, 9, -ONE_MILLION, -ONE_MILLION, -ONE_MILLION}});
    CASE(R = 3; C = 6; K = 2;
         T = {{0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 1, 0},
              {0, 0, 0, 0, 0, 0}},
         P = {{1, 2, 3, -ONE_MILLION, -ONE_MILLION, -ONE_MILLION},
              {4, 5, 6, -ONE_MILLION, 1000, -ONE_MILLION},
              {10, -1, 9, -ONE_MILLION, -ONE_MILLION, -ONE_MILLION}});
    CASE(R = 3; C = 3; K = 1;
         T = {{1, 0, 0},
              {0, 0, 0},
              {0, 0, 1}},
         P = {{-3, -2, -1},
              {-ONE_MILLION, -ONE_MILLION, -ONE_MILLION},
              {-4, -5, -6}});
    CASE(R = 3; C = 3; K = 30;
         T = {{1, 0, 0},
              {0, 0, 0},
              {0, 0, 1}},
         P = {{-3, -2, -1},
              {-ONE_MILLION, -ONE_MILLION, -ONE_MILLION},
              {-4, -5, -6}});
    CASE(R = 3; C = 3; K = 30;
         T = {{1, 0, 0},
              {0, 0, 1},
              {0, 0, 0}},
         P = maxPoints());
    CASE(R = rnd.nextInt(1, 30); C = rnd.nextInt(1, 30); K = rnd.nextInt(1, 30); P = randomPoints(30); T = randomTeleports());
    CASE(R = rnd.nextInt(1, 30); C = rnd.nextInt(1, 30); K = rnd.nextInt(1, 30); P = randomPoints(50); T = randomTeleports());
    CASE(R = rnd.nextInt(1, 30); C = rnd.nextInt(1, 30); K = rnd.nextInt(1, 30); P = randomPoints(70); T = randomTeleports());
  }

  void TestGroup5() {
    // 31 <= K <= 1e9
    // 1 <= R, C <= 30
    
    Subtasks({3, 5});

    CASE(R = C = 1; K = ONE_BILLION; T = {{1}}; P = {{ONE_MILLION}});
    CASE(R = C = 1; K = ONE_BILLION; T = {{1}}; P = {{-ONE_MILLION}});
    CASE(R = C = 1; K = ONE_BILLION; T = {{1}}; P = {{-ONE_MILLION}});
    CASE(R = 30; C = 30; K = 1e9; T = vvi(R, vi(C, 0)); P = maxPoints());
    CASE(R = 30; C = 30; K = 1e9; T = vvi(R, vi(C, 0)); P = minPoints());
    CASE(R = C = 30; K = ONE_BILLION; T = vvi(R, vi(C, 0)); P = vvi(R, vi(C, -ONE_MILLION)); T[0][10] = 1; P[0][10] = ONE_MILLION);
    CASE(R = 30; C = 30; K = ONE_BILLION; T = vvi(R, vi(C, 1)); P = maxPoints());
    CASE(R = 30; C = 30; K = ONE_BILLION; T = vvi(R, vi(C, 1)); P = minPoints());
    CASE(R = C = 30; K = ONE_BILLION; T = vvi(R, vi(C, 1)); P = vvi(R, vi(C, -ONE_MILLION)); T[15][15] = 1; P[15][15] = ONE_MILLION);
    CASE(R = 1; C = 5; K = ONE_BILLION; T = {{0, 1, 0, 1, 0}}; P = {{1, -2, 4, 3, 0}});
    CASE(R = 2; C = 3; K = ONE_BILLION; T = {{0, 0, 0}, {1, 0, 1}}; P = {{0, -ONE_MILLION, -ONE_MILLION}, {-1, 2, 1}});
    CASE(R = 3; C = 6; K = ONE_BILLION;
         T = {{0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 1, 0},
              {0, 0, 0, 0, 0, 0}},
         P = {{1, 2, 3, -ONE_MILLION, -ONE_MILLION, -ONE_MILLION},
              {4, 5, 6, -ONE_MILLION, 1000, -ONE_MILLION},
              {10, -1, 9, -ONE_MILLION, -ONE_MILLION, -ONE_MILLION}});
    CASE(R = rnd.nextInt(1, 30); C = rnd.nextInt(1, 30); K = rnd.nextInt(31, ONE_BILLION); P = randomPoints(30); T = randomTeleports());
    CASE(R = rnd.nextInt(1, 30); C = rnd.nextInt(1, 30); K = rnd.nextInt(31, ONE_BILLION); P = randomPoints(50); T = randomTeleports());
    CASE(R = rnd.nextInt(1, 30); C = rnd.nextInt(1, 30); K = rnd.nextInt(31, ONE_BILLION); P = randomPoints(70); T = randomTeleports());
  }

  void TestGroup6() {
    // 1 <= K <= 250
    // 31 <= R, C <= 250
    
    Subtasks({2, 5});

    CASE(R = 250; C = 250; K = 250; T = vvi(R, vi(C, 1)); P = maxPoints());
    CASE(R = 250; C = 250; K = 250; T = vvi(R, vi(C, 1)); P = minPoints());
    CASE(R = 250; C = 250; K = 250; T = vvi(R, vi(C, 0)); P = maxPoints());
    CASE(R = 250; C = 250; K = 250; T = vvi(R, vi(C, 0)); P = minPoints());
    CASE(R = C = 250; K = 1; T = vvi(R, vi(C, 1)); P = vvi(R, vi(C, -ONE_MILLION)); T[200][30] = 1; P[200][30] = ONE_MILLION);
    CASE(R = C = 250; K = 250; T = vvi(R, vi(C, 1)); P = vvi(R, vi(C, -ONE_MILLION)); T[200][30] = 1; P[200][30] = ONE_MILLION);
    CASE(R = C = 250; K = 1; isolated(rnd.nextInt(R), C / 2 + 5));
    CASE(R = C = 250; K = 2; isolated(rnd.nextInt(R), C / 2 + 5));
    CASE(R = C = 250; K = 250; isolated(rnd.nextInt(R), C / 2 + 5));
    CASE(R = C = 250; K = 1; isolated(R - 1, C / 2 + 5));
    CASE(R = C = 250; K = 2; isolated(R - 1, C / 2 + 5));
    CASE(R = C = 250; K = 250; isolated(R - 1, C / 2 + 5));
    CASE(R = rnd.nextInt(31, 250); C = rnd.nextInt(31, 250); K = rnd.nextInt(1, 250); P = randomPoints(30); T = randomTeleports());
    CASE(R = rnd.nextInt(31, 250); C = rnd.nextInt(31, 250); K = rnd.nextInt(1, 250); P = randomPoints(50); T = randomTeleports());
    CASE(R = rnd.nextInt(31, 250); C = rnd.nextInt(31, 250); K = rnd.nextInt(1, 250); P = randomPoints(70); T = randomTeleports());
  }

  void TestGroup7() {
    // 1 <= K <= 1e9
    // 251 <= R, C <= 1500
    
    Subtasks({5});

    CASE(R = 1500; C = 1500; K = ONE_BILLION; T = vvi(R, vi(C, 1)); P = maxPoints());
    CASE(R = 1500; C = 1500; K = ONE_BILLION; T = vvi(R, vi(C, 0)); P = minPoints());
    CASE(R = C = 1500; K = 1; T = vvi(R, vi(C, 0)); P = vvi(R, vi(C, -ONE_MILLION)); T[300][30] = 1; P[300][30] = ONE_MILLION);
    CASE(R = C = 1500; K = 250; T = vvi(R, vi(C, 0)); P = vvi(R, vi(C, -ONE_MILLION)); T[300][30] = 1; P[300][30] = ONE_MILLION);
    CASE(R = C = 1500; K = 1e9; isolated(rnd.nextInt(R), C / 2 + 5));
    CASE(R = C = 1500; K = 1e9; isolated(R - 1, C / 2 + 5));
    CASE(R = rnd.nextInt(251, 1500); C = rnd.nextInt(251, 1500); K = rnd.nextInt(1e8, ONE_BILLION); P = randomPoints(30); T = randomTeleports());
    CASE(R = rnd.nextInt(251, 1500); C = rnd.nextInt(251, 1500); K = rnd.nextInt(1e8, ONE_BILLION); P = randomPoints(70); T = randomTeleports());
  }

private:
  vector<vi> minPoints() {
    assert(R > 0 && C > 0);
    return vector<vi>(R, vi(C, -ONE_MILLION));
  }

  vector<vi> maxPoints() {
    assert(R > 0 && C > 0);
    return vector<vi>(R, vi(C, ONE_MILLION));
  }

  vector<vi> randomPoints(int negProb) {
    assert(R > 0 && C > 0);
    vector<vi> ret(R, vi(C));
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        ret[i][j] = rnd.nextInt(0, ONE_MILLION);
        int cur = rnd.nextInt(0, 100);
        if (cur <= negProb) {
          ret[i][j] = -ret[i][j];
        }
      }
    }
    return ret;
  }

  vector<vi> randomTeleports() {
    assert(R > 0 && C > 0);
    vector<vi> ret(R, vi(C));
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        ret[i][j] = rnd.nextInt(2);
      }
    }
    return ret;
  }

  void isolated(int pr, int pc) {
    assert(R > 0 && C > 0);
    assert(pc >= C / 2 && pc < C);
    T = vvi(R, vi(C, 0));
    P = vvi(R, vi(C, -ONE_MILLION));
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C / 2; j++) {
        T[i][j] = 0;
        P[i][j] = rnd.nextInt(0, 10000);
      }
    }
    T[pr][pc] = 1;
    P[pr][pc] = ONE_MILLION;
    T[rnd.nextInt(R)][rnd.nextInt(C / 2)] = 1;
  }

  void randomArray(vector<int> &A, int size, int L = 1, int R = 100000) {
    A.clear();
    for (int i = 0; i < size; i++) {
      A.push_back(rnd.nextInt(L, R));
    }
  }

  void uniformArray(vector<int> &A, int size, int value) {
    A.assign(size, value);
  }

  void randomArray(vector<int> &A) {
    A.clear();
    for (int i = 0; i < SZ(A); i++) {
      A.push_back(rnd.nextInt(-100000, 100000));
    }
  }
};

