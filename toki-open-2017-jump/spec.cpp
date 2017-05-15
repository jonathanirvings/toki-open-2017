#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MAXN = 300000;
const int MAXQ = 300000;
const int MAX_NONZERO = 2000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, Q;
  string S;
  vector<int> L, R, K;
  vector<int> result;

  void InputFormat() {
    LINE(N, Q);
    LINE(S);
    LINES(L, R, K) % SIZE(Q);
  }

  void OutputFormat() {
    LINES(result) % SIZE(Q);
  }

  void GradingConfig() {
    TimeLimit(4);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= Q && Q <= MAXQ);
    CONS(S.size() == N);
    CONS(isDigitString(S));
    CONS(eachElementBetween(L, 1, N));
    CONS(eachElementBetween(R, 1, N));
    CONS(eachLessThan(L, R));
    CONS(eachElementBetween(K, 1, N - 1));
    CONS(nonZeroDigits(S) <= MAX_NONZERO);
  }

  void Subtask1() {
    CONS(N <= 75);
  }

  void Subtask2() {
    CONS(N <= 200);
  }

  void Subtask3() {
    CONS(N <= MAX_NONZERO); 
  }

  void Subtask4() {
    CONS(nonZeroDigits(S) <= 75);
  }

  void Subtask5() {
    CONS(nonZeroDigits(S) <= 200);
  }

  void Subtask6() {
  }

private:

  bool eachElementBetween(const vector<int> &A, int lo, int hi) {
    for (int it : A) {
      if (it < lo || it > hi) {
        return false;
      }
    }
    return true;
  }

  bool eachLessThan(const vector<int> &L, const vector<int> &R) {
    for (int i = 0; i < L.size(); ++i) {
      if (L[i] >= R[i]) {
        return false;
      }
    }
    return true;
  }

  int nonZeroDigits(const string &S) {
    int ret = 0;
    for (const char &c : S) {
      if (c != '0') {
        ++ret;
      }
    }
    return ret;
  }

  bool isDigitString(const string &S) {
    for (const char &c : S) {
      if (c < '0' || c > '9') {
        return false;
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

  void SampleTestCase1() {
    Subtasks({1, 2, 3, 4, 5, 6});
    Input({"6 4", "199420", "2 3 1", "2 3 2", "2 4 1", "2 4 2"});
    Output({"18", "18", "22", "13"});
  }

  void BeforeTestCase() {
  }

  void TestGroup1() { // last of subtask 1
    // 2 <= N <= 75
    // 0 <= nonzero <= 75
    // 1 < Q <= 300k
    Subtasks({1, 2, 3, 4, 5, 6});

    CASE(N = 5, Q = 1, S = "11911", L = {1}, R = {5}, K = {2});
    CASE(N = 5, Q = 1, S = "11991", L = {1}, R = {5}, K = {2});
    CASE(N = 42, Q = 1, S = "575706564657323142006122650060900607230994", L = {18}, R = {40}, K = {3});
    generateCommonCases(2, 75, 0, 75, 1, MAXQ);
  }

  void TestGroup2() {
    // 76 <= N <= 200
    // 0 <= nonzero <= 75
    // 1 < Q <= 300k
    Subtasks({2, 3, 4, 5, 6});

    generateLessImportantCases(76, 200, 0, 75, 1, MAXQ);
  }

  void TestGroup3() {
    // 201 <= N <= 2000
    // 0 <= nonzero <= 75
    // 1 < Q <= 300k
    Subtasks({3, 4, 5, 6});

    generateLessImportantCases(201, MAX_NONZERO, 0, 75, 1, MAXQ);
  }

  void TestGroup4() { // last of subtask 4
    // 2001 <= N <= 300k
    // 0 <= nonzero <= 75
    // 1 < Q <= 300k
    Subtasks({4, 5, 6});

    generateCommonCases(MAX_NONZERO + 1, MAXN, 0, 75, 1, MAXQ);
  }

  void TestGroup5() { // last of subtask 2
    // 76 <= N <= 200
    // 76 <= nonzero <= 200
    // 1 < Q <= 300k
    Subtasks({2, 3, 5, 6});

    generateCommonCases(76, 200, 76, 200, 1, MAXQ);
  }

  void TestGroup6() {
    // 201 <= N <= 2000
    // 76 <= nonzero <= 200
    // 1 < Q <= 300k
    Subtasks({3, 5, 6});

    generateLessImportantCases(201, MAX_NONZERO, 76, 200, 1, MAXQ);
  }

  void TestGroup7() { // last of subtask 5
    // 2001 <= N <= 300k
    // 76 <= nonzero <= 200
    // 1 < Q <= 300k
    Subtasks({5, 6});

    generateCommonCases(MAX_NONZERO + 1, MAXN, 76, 200, 1, MAXQ);
  }

  void TestGroup8() { // last of subtask 3
    // 201 <= N <= 2000
    // 201 <= nonzero <= 2000
    // 1 < Q <= 300k
    Subtasks({3, 6});

    generateCommonCases(201, MAX_NONZERO, 201, MAX_NONZERO, 1, MAXQ);
  }

  void TestGroup9() {
    // 2001 <= N <= 300k
    // 201 <= nonzero <= 2000
    // 1 < Q <= 300k
    Subtasks({6});

    generateCommonCases(MAX_NONZERO + 1, MAXN, 201, MAX_NONZERO, 1, MAXQ);
  }

private:
  void generateLessImportantCases(int minN, int maxN, int minNonZero, int maxNonZero, int minQ, int maxQ) {
    CASE(N = rnd.nextInt(minN, maxN), Q = rnd.nextInt(minQ, maxQ), assignSize(), randomCase(minNonZero, maxNonZero));
    CASE(N = rnd.nextInt(minN, maxN), Q = rnd.nextInt(minQ, maxQ), assignSize(), fewNonZeroInterval(minNonZero, maxNonZero, 0));
    CASE(N = rnd.nextInt(minN, maxN), Q = rnd.nextInt(minQ, maxQ), assignSize(), randomCase(minNonZero, maxNonZero), K.assign(Q, 1));
  }

  void generateCommonCases(int minN, int maxN, int minNonZero, int maxNonZero, int minQ, int maxQ) {
    CASE(N = minN, Q = minQ, assignSize(), randomCase(minNonZero, minNonZero));
    CASE(N = rnd.nextInt(minN, maxN), Q = rnd.nextInt(minQ, maxQ), assignSize(), randomCase(minNonZero, maxNonZero));
    CASE(N = maxN, Q = maxQ, assignSize(), randomCase(maxNonZero, maxNonZero));
    CASE(N = maxN, Q = maxQ, assignSize(), randomCase(maxNonZero, maxNonZero), queryAllEndPoints());
    CASE(N = maxN, Q = maxQ, assignSize(), fewNonZeroInterval(maxNonZero, maxNonZero, 0));
    CASE(N = maxN, Q = maxQ, assignSize(), fewNonZeroInterval(maxNonZero, maxNonZero, 2));
    CASE(N = maxN, Q = maxQ, assignSize(), randomCase(maxNonZero, maxNonZero), K.assign(Q, 1));
    CASE(N = maxN, Q = maxQ, assignSize(), randomCase(maxNonZero, maxNonZero), K.assign(Q, 2));
  }

  void assignSize() {
    S.assign(N, '0');
    L.assign(Q, 0);
    R.assign(Q, 0);
    K.assign(Q, 0);
  }

  void randomCase(int minNonZero, int maxNonZero) {
    int nonZero = rnd.nextInt(minNonZero, maxNonZero);
    nonZero = min(nonZero, N);
    vector<int> nonZeroPositions;
    for (int i = 0; i < N; ++i) {
      nonZeroPositions.push_back(i);
    }
    rnd.shuffle(nonZeroPositions.begin(), nonZeroPositions.end());
    for (int i = 0; i < nonZero; ++i) {
      S[nonZeroPositions[i]] = rnd.nextInt('1', '9');
    }
    for (int i = 0; i < Q; ++i) {
      L[i] = rnd.nextInt(1, N - 1);
      R[i] = rnd.nextInt(L[i] + 1, N);
      if (rnd.nextInt(10) == 0) {
        K[i] = rnd.nextInt(1, N - 1);
      } else {
        K[i] = rnd.nextInt(1, R[i] - L[i]);
      }
    }
  }

  void fewNonZeroInterval(int minNonZero, int maxNonZero, int holes) {
    int nonZero = rnd.nextInt(minNonZero, maxNonZero);
    int nonZeroStartPosition = rnd.nextInt(0, N - nonZero);

    for (int i = nonZeroStartPosition; i < nonZeroStartPosition + nonZero; ++i) {
      S[i] = rnd.nextInt('1', '9');
    }

    for (int i = 0; i < holes; ++i) {
      int a = rnd.nextInt(0, N - 1);
      int b = rnd.nextInt(0, N - 1);
      swap(S[a], S[b]);
    }

    for (int i = 0; i < Q; ++i) {
      int r = rnd.nextInt(10);
      if (r == 0) {
        L[i] = rnd.nextInt(1, N - 1);
        R[i] = rnd.nextInt(L[i] + 1, N);
      } else if (r == 1) {
        L[i] = rnd.nextInt(nonZeroStartPosition, nonZeroStartPosition + nonZero - 2);
        ++L[i];
        R[i] = rnd.nextInt(L[i] + 1, N);
      } else if (r == 2) {
        R[i] = rnd.nextInt(nonZeroStartPosition + 1, nonZeroStartPosition + nonZero - 1);
        ++R[i];
        L[i] = rnd.nextInt(1, R[i] - 1);
      } else {
        L[i] = rnd.nextInt(nonZeroStartPosition, nonZeroStartPosition + nonZero - 2);
        R[i] = rnd.nextInt(L[i] + 1, nonZeroStartPosition + nonZero - 1);
        ++L[i];
        ++R[i];
      }
      if (rnd.nextInt(10) == 0) {
        K[i] = rnd.nextInt(1, N - 1);
      } else {
        K[i] = rnd.nextInt(1, R[i] - L[i]);
      }
    }
  }

  void queryAllEndPoints() {
    for (int i = 0; i < Q; ++i) {
      L[i] = 1;
      R[i] = N;
      K[i] = rnd.nextInt(1, N - 1);
    }
  }
};
