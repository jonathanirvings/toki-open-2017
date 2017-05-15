#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, K, Q;
    vector< vector<int> > A;
    vector< vector<int> > res;

    void InputFormat() {
        LINE(N, K, Q);
        GRID(A) % SIZE(Q, K);
    }

    void OutputFormat() {
        GRID(res) % SIZE(Q, K);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= K && K < N && N <= 12);
        CONS(1 <= Q && Q <= 500000);
        CONS(2 * K < N);
        CONS(eachElementBetween(A, 1, N));
        CONS(eachRowStrictlyIncreasing(A));
    }

    void Subtask1() {
        CONS(eachElementBetween(A, 1, N-1));
    }

    void Subtask2() {
        CONS(K == 1);
    }

    void Subtask3() {
        CONS(N <= 6);
    }

    void Subtask4() {
        CONS(K <= 2);
    }

    void Subtask5() {
        CONS(Q <= 3);
    }

    void Subtask6() {}

private:
    bool eachElementBetween(const vector< vector<int> >& v, int lo, int hi) {
        for (vector<int> row : v) {
            for (int x : row) {
                if (x < lo || x > hi) {
                    return false;
                }
            }
        }
        return true;
    }

    bool eachRowStrictlyIncreasing(const vector< vector<int> >& v) {
        for (vector<int> row : v) {
            int last = -1;
            for (int x : row) {
                if (x > last) {
                    last = x;
                } else {
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
        Subtasks({1, 3, 4, 5, 6});
        Input({
            "5 2 2",
            "1 2",
            "1 3"
        });
        Output({
            "1 2",
            "1 3"
        });
    }

    void SampleTestCase2() {
        Subtasks({1, 3, 4, 5, 6});
        Input({
            "5 2 2",
            "1 2",
            "1 3"
        });
        Output({
            "1 2",
            "1 3"
        });
    }

    void BeforeTestCase() {
        A.clear();
    }

    void TestGroup1() {
        // {N <= 6, K = 1, Q = 3}, Kartu N nggak pernah muncul
        Subtasks({1, 2, 3, 4, 5, 6});
        CASE(N = 3, K = 1, Q = 3, generate(2, 1, 3));
        CASE(N = 4, K = 1, Q = 3, generate(3, 1, 3));
        CASE(N = 5, K = 1, Q = 3, generate(4, 1, 3));
        CASE(N = 6, K = 1, Q = 3, generate(5, 1, 3));
    }

    void TestGroup2() {
        // {N <= 6, K = 2, Q = 3}, Kartu N nggak pernah muncul
        Subtasks({1, 3, 4, 5, 6});
        CASE(N = 5, K = 2, Q = 3, generate(4, 2, 3));
        CASE(N = 6, K = 2, Q = 3, generate(5, 2, 3));
    }
    
    void TestGroup3() {
        // {N <= 6, K = 1, Q = 500000}, Kartu N nggak pernah muncul
        Subtasks({1, 2, 3, 4, 6});
        CASE(N = 3, K = 1, Q = 5000, generate(2, 1, 5000));
        CASE(N = 4, K = 1, Q = 5000, generate(3, 1, 5000));
        CASE(N = 5, K = 1, Q = 5000, generate(4, 1, 5000));
        CASE(N = 6, K = 1, Q = 5000, generate(5, 1, 5000));
    }
    
    void TestGroup4() {
        // {N <= 6, K = 2, Q = 500000}, Kartu N nggak pernah muncul
        Subtasks({1, 3, 4, 6});
        CASE(N = 5, K = 2, Q = 5000, generate(4, 2, 5000));
        CASE(N = 6, K = 2, Q = 5000, generate(5, 2, 5000));
    }

    void TestGroup5() {
        // {7 <= N <= 12, K = 1, Q = 3}, Kartu N nggak pernah muncul
        Subtasks({1, 2, 4, 5, 6});
        CASE(N = 7, K = 1, Q = 3, generate(6, 1, 3));
        CASE(N = 8, K = 1, Q = 3, generate(7, 1, 3));
        CASE(N = 9, K = 1, Q = 3, generate(8, 1, 3));
        CASE(N = 10, K = 1, Q = 3, generate(9, 1, 3));
        CASE(N = 11, K = 1, Q = 3, generate(10, 1, 3));
        CASE(N = 12, K = 1, Q = 3, generate(11, 1, 3));
    }

    void TestGroup6() {
        // {7 <= N <= 12, K = 2, Q = 3}, Kartu N nggak pernah muncul
        Subtasks({1, 4, 5, 6});
        CASE(N = 7, K = 2, Q = 3, generate(6, 2, 3));
        CASE(N = 8, K = 2, Q = 3, generate(7, 2, 3));
        CASE(N = 9, K = 2, Q = 3, generate(8, 2, 3));
        CASE(N = 10, K = 2, Q = 3, generate(9, 2, 3));
        CASE(N = 11, K = 2, Q = 3, generate(10, 2, 3));
        CASE(N = 12, K = 2, Q = 3, generate(11, 2, 3));
    }

    void TestGroup7() {
        // {7 <= N <= 12, 3 <= K < N/2, Q = 3}, Kartu N nggak pernah muncul
        Subtasks({1, 5, 6});
        CASE(N = 7, K = 3, Q = 3, generate(6, 3, 3));
        CASE(N = 8, K = 3, Q = 3, generate(7, 3, 3));
        CASE(N = 9, K = 3, Q = 3, generate(8, 3, 3));
        CASE(N = 9, K = 4, Q = 3, generate(8, 4, 3));
        CASE(N = 10, K = 3, Q = 3, generate(9, 3, 3));
        CASE(N = 10, K = 4, Q = 3, generate(9, 4, 3));
        CASE(N = 11, K = 3, Q = 3, generate(10, 3, 3));
        CASE(N = 11, K = 4, Q = 3, generate(10, 4, 3));
        CASE(N = 11, K = 5, Q = 3, generate(10, 5, 3));
        CASE(N = 12, K = 3, Q = 3, generate(11, 3, 3));
        CASE(N = 12, K = 4, Q = 3, generate(11, 4, 3));
        CASE(N = 12, K = 5, Q = 3, generate(11, 5, 3));
    }

    void TestGroup8() {
        // {7 <= N <= 12, K = 1, Q = 500000}, Kartu N nggak pernah muncul
        Subtasks({1, 2, 4, 6});
        CASE(N = 7, K = 1, Q = 5000, generate(6, 1, 5000));
        CASE(N = 8, K = 1, Q = 5000, generate(7, 1, 5000));
        CASE(N = 9, K = 1, Q = 5000, generate(8, 1, 5000));
        CASE(N = 10, K = 1, Q = 5000, generate(9, 1, 5000));
        CASE(N = 11, K = 1, Q = 5000, generate(10, 1, 5000));
        CASE(N = 12, K = 1, Q = 5000, generate(11, 1, 5000));
    }

    void TestGroup9() {
        // {7 <= N <= 12, K = 2, Q = 500000}, Kartu N nggak pernah muncul
        Subtasks({1, 4, 6});
        CASE(N = 7, K = 2, Q = 5000, generate(6, 2, 5000));
        CASE(N = 8, K = 2, Q = 5000, generate(7, 2, 5000));
        CASE(N = 9, K = 2, Q = 5000, generate(8, 2, 5000));
        CASE(N = 10, K = 2, Q = 5000, generate(9, 2, 5000));
        CASE(N = 11, K = 2, Q = 5000, generate(10, 2, 5000));
        CASE(N = 12, K = 2, Q = 5000, generate(11, 2, 5000));
    }

    void TestGroup10() {
        // {7 <= N <= 12, 3 <= K < N/2, Q = 500000}, Kartu N nggak pernah muncul
        Subtasks({1, 6});
        CASE(N = 7, K = 3, Q = 5000, generate(6, 3, 5000));
        CASE(N = 8, K = 3, Q = 5000, generate(7, 3, 5000));
        CASE(N = 9, K = 3, Q = 5000, generate(8, 3, 5000));
        CASE(N = 9, K = 4, Q = 5000, generate(8, 4, 5000));
        CASE(N = 10, K = 3, Q = 5000, generate(9, 3, 5000));
        CASE(N = 10, K = 4, Q = 5000, generate(9, 4, 5000));
        CASE(N = 11, K = 3, Q = 5000, generate(10, 3, 5000));
        CASE(N = 11, K = 4, Q = 5000, generate(10, 4, 5000));
        CASE(N = 11, K = 5, Q = 5000, generate(10, 5, 5000));
        CASE(N = 12, K = 3, Q = 5000, generate(11, 3, 5000));
        CASE(N = 12, K = 4, Q = 5000, generate(11, 4, 5000));
        CASE(N = 12, K = 5, Q = 5000, generate(11, 5, 5000));
    }

    void TestGroup11() {
        // {N <= 6, K = 1, Q = 3}, Kartu N pernah muncul
        Subtasks({2, 3, 4, 5, 6});
        CASE(N = 3, K = 1, Q = 3, generate(3, 1, 3));
        CASE(N = 4, K = 1, Q = 3, generate(4, 1, 3));
        CASE(N = 5, K = 1, Q = 3, generate(5, 1, 3));
        CASE(N = 6, K = 1, Q = 3, generate(6, 1, 3));
    }

    void TestGroup12() {
        // {N <= 6, K = 2, Q = 3}, Kartu N pernah muncul
        Subtasks({3, 4, 5, 6});
        CASE(N = 5, K = 2, Q = 3, generate(5, 2, 3));
        CASE(N = 6, K = 2, Q = 3, generate(6, 2, 3));
    }
    
    void TestGroup13() {
        // {N <= 6, K = 1, Q = 500000}, Kartu N pernah muncul
        Subtasks({2, 3, 4, 6});
        CASE(N = 3, K = 1, Q = 5000, generate(3, 1, 5000));
        CASE(N = 4, K = 1, Q = 5000, generate(4, 1, 5000));
        CASE(N = 5, K = 1, Q = 5000, generate(5, 1, 5000));
        CASE(N = 6, K = 1, Q = 5000, generate(6, 1, 5000));

        CASE(N = 3, K = 1, Q = 500000, generateSingle(N, K, Q, true));
        CASE(N = 4, K = 1, Q = 500000, generateSingle(N, K, Q, true));
    }
    
    void TestGroup14() {
        // {N <= 6, K = 2, Q = 500000}, Kartu N pernah muncul
        Subtasks({3, 4, 6});
        CASE(N = 5, K = 2, Q = 5000, generate(5, 2, 5000));
        CASE(N = 6, K = 2, Q = 5000, generate(6, 2, 5000));

        CASE(N = 5, K = 2, Q = 500000, generateSingle(N, K, Q, true));
        CASE(N = 6, K = 2, Q = 500000, generateSingle(N, K, Q, true));
    }

    void TestGroup15() {
        // {7 <= N <= 12, K = 1, Q = 3}, Kartu N pernah muncul
        Subtasks({2, 4, 5, 6});
        CASE(N = 7, K = 1, Q = 3, generate(7, 1, 3));
        CASE(N = 8, K = 1, Q = 3, generate(8, 1, 3));
        CASE(N = 9, K = 1, Q = 3, generate(9, 1, 3));
        CASE(N = 10, K = 1, Q = 3, generate(10, 1, 3));
        CASE(N = 11, K = 1, Q = 3, generate(11, 1, 3));
        CASE(N = 12, K = 1, Q = 3, generate(12, 1, 3));
    }

    void TestGroup16() {
        // {7 <= N <= 12, K = 2, Q = 3}, Kartu N pernah muncul
        Subtasks({4, 5, 6});
        CASE(N = 7, K = 2, Q = 3, generate(7, 2, 3));
        CASE(N = 8, K = 2, Q = 3, generate(8, 2, 3));
        CASE(N = 9, K = 2, Q = 3, generate(9, 2, 3));
        CASE(N = 10, K = 2, Q = 3, generate(10, 2, 3));
        CASE(N = 11, K = 2, Q = 3, generate(11, 2, 3));
        CASE(N = 12, K = 2, Q = 3, generate(12, 2, 3));
    }

    void TestGroup17() {
        // {7 <= N <= 12, 3 <= K < N/2, Q = 3}, Kartu N pernah muncul
        Subtasks({5, 6});
        CASE(N = 7, K = 3, Q = 3, generate(7, 3, 3));
        CASE(N = 8, K = 3, Q = 3, generate(8, 3, 3));
        CASE(N = 9, K = 3, Q = 3, generate(9, 3, 3));
        CASE(N = 9, K = 4, Q = 3, generate(9, 4, 3));
        CASE(N = 10, K = 3, Q = 3, generate(10, 3, 3));
        CASE(N = 10, K = 4, Q = 3, generate(10, 4, 3));
        CASE(N = 11, K = 3, Q = 3, generate(11, 3, 3));
        CASE(N = 11, K = 4, Q = 3, generate(11, 4, 3));
        CASE(N = 11, K = 5, Q = 3, generate(11, 5, 3));
        CASE(N = 12, K = 3, Q = 3, generate(12, 3, 3));
        CASE(N = 12, K = 4, Q = 3, generate(12, 4, 3));
        CASE(N = 12, K = 5, Q = 3, generate(12, 5, 3));
    }

    void TestGroup18() {
        // {7 <= N <= 12, K = 1, Q = 500000}, Kartu N pernah muncul
        Subtasks({2, 4, 6});
        CASE(N = 7, K = 1, Q = 5000, generate(7, 1, 5000));
        CASE(N = 8, K = 1, Q = 5000, generate(8, 1, 5000));
        CASE(N = 9, K = 1, Q = 5000, generate(9, 1, 5000));
        CASE(N = 10, K = 1, Q = 5000, generate(10, 1, 5000));
        CASE(N = 11, K = 1, Q = 5000, generate(11, 1, 5000));
        CASE(N = 12, K = 1, Q = 5000, generate(12, 1, 5000));

        CASE(N = 7, K = 1, Q = 500000, generateSingle(N, K, Q, true));
        CASE(N = 8, K = 1, Q = 500000, generateSingle(N, K, Q, true));
    }

    void TestGroup19() {
        // {7 <= N <= 12, K = 2, Q = 500000}, Kartu N pernah muncul
        Subtasks({4, 6});
        CASE(N = 7, K = 2, Q = 5000, generate(7, 2, 5000));
        CASE(N = 8, K = 2, Q = 5000, generate(8, 2, 5000));
        CASE(N = 9, K = 2, Q = 5000, generate(9, 2, 5000));
        CASE(N = 10, K = 2, Q = 5000, generate(10, 2, 5000));
        CASE(N = 11, K = 2, Q = 5000, generate(11, 2, 5000));
        CASE(N = 12, K = 2, Q = 5000, generate(12, 2, 5000));

        CASE(N = 9, K = 2, Q = 500000, generateSingle(N, K, Q, true));
        CASE(N = 10, K = 2, Q = 500000, generateSingle(N, K, Q, true));
        CASE(N = 11, K = 2, Q = 500000, generateSingle(N, K, Q, true));
        CASE(N = 12, K = 2, Q = 500000, generateSingle(N, K, Q, true));
    }

    void TestGroup20() {
        // {7 <= N <= 12, 3 <= K < N/2, Q = 500000}, Kartu N pernah muncul
        Subtasks({6});
        CASE(N = 7, K = 3, Q = 50000, generate(7, 3, 50000));
        CASE(N = 8, K = 3, Q = 50000, generate(8, 3, 50000));
        CASE(N = 9, K = 3, Q = 50000, generate(9, 3, 50000));
        CASE(N = 9, K = 4, Q = 50000, generate(9, 4, 50000));
        CASE(N = 10, K = 3, Q = 50000, generate(10, 3, 50000));
        CASE(N = 10, K = 4, Q = 50000, generate(10, 4, 50000));
        CASE(N = 11, K = 3, Q = 500000, generate(11, 3, 500000));
        CASE(N = 11, K = 4, Q = 500000, generate(11, 4, 500000));
        CASE(N = 11, K = 5, Q = 500000, generate(11, 5, 500000));
        CASE(N = 12, K = 3, Q = 500000, generate(12, 3, 500000));
        CASE(N = 12, K = 4, Q = 500000, generate(12, 4, 500000));
        CASE(N = 12, K = 5, Q = 500000, generate(12, 5, 500000));

        CASE(N = 7, K = 3, Q = 50000, generateSingle(7, 3, 50000, true));
        CASE(N = 8, K = 3, Q = 50000, generateSingle(8, 3, 50000, true));
        CASE(N = 9, K = 3, Q = 50000, generateSingle(9, 3, 50000, true));
        CASE(N = 9, K = 4, Q = 50000, generateSingle(9, 4, 50000, true));
        CASE(N = 10, K = 3, Q = 50000, generateSingle(10, 3, 50000, true));
        CASE(N = 10, K = 4, Q = 50000, generateSingle(10, 4, 50000, true));
        CASE(N = 11, K = 3, Q = 500000, generateSingle(11, 3, 500000, true));
        CASE(N = 11, K = 4, Q = 500000, generateSingle(11, 4, 500000, true));
        CASE(N = 11, K = 5, Q = 500000, generateSingle(11, 5, 500000, true));
        CASE(N = 12, K = 3, Q = 500000, generateSingle(12, 3, 500000, true));
        CASE(N = 12, K = 4, Q = 500000, generateSingle(12, 4, 500000, true));
        CASE(N = 12, K = 5, Q = 500000, generateSingle(12, 5, 500000, true));
    }

private:
    void generate(int n, int k, int q) {
        int _q = q;
        vector< vector<int> > possible;
        for (int i = 0; i < (1 << n); i++) {
            if (__builtin_popcount(i) == k) {
                vector<int> query;
                for (int j = 0; j < n; j++) {
                    if (i & (1 << j)) {
                        query.push_back(j + 1);
                    }
                }
                possible.push_back(query);
            }
        }

        rnd.shuffle(possible.begin(), possible.end());
        rnd.shuffle(possible.begin(), possible.end());
        rnd.shuffle(possible.begin(), possible.end());
        
        // Jika Q = 3 dan n = N, maka kartu N harus muncul
        if (q == 3 && n == N) {
            int i = 0;
            while (possible[i][k-1] != n) i++;
            A.push_back(possible[i]);
            --q;
        }

        for (int i = 0; i < min(q, (int) possible.size()); i++) {
            A.push_back(possible[i]);
        }
        while (A.size() != _q) {
            A.push_back(possible[rnd.nextInt(possible.size())]);
        }
    }

    void generateSingle(int n, int k, int q, bool requiredN) {
        vector< vector<int> > possible;
        for (int i = 0; i < (1 << n); i++) {
            if (__builtin_popcount(i) == k) {
                vector<int> query;
                for (int j = 0; j < n; j++) {
                    if (i & (1 << j)) {
                        query.push_back(j + 1);
                    }
                }
                possible.push_back(query);
            }
        }

        rnd.shuffle(possible.begin(), possible.end());
        rnd.shuffle(possible.begin(), possible.end());
        rnd.shuffle(possible.begin(), possible.end());
        
        if (requiredN) {
            int i = 0;
            while (possible[i][k-1] != n) i++;
            A.push_back(possible[i]);
        } else {
            int i = 0;
            while (possible[i][k-1] == n) i++;
            A.push_back(possible[0]);
        }

        while (A.size() != q) {
            A.push_back(A[0]);
        }
    }
};