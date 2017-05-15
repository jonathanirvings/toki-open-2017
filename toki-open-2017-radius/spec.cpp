#include <tcframe/spec.hpp>
#include <tcrand/tree.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace tcrand;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, Q;
    vector<int> U, V, A;

    void InputFormat() {
        LINE(N ,Q);
        LINES(U, V) % SIZE(N-1);
        LINES(A) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(2 <= N && N <= 100000);
        CONS(1 <= Q && Q <= 100000);
        CONS(eachElementBetween(U, 1, N));
        CONS(eachElementBetween(V, 1, N));
        CONS(eachElementBetween(A, 2, N));
        CONS(connected());
    }

    void Subtask1() {
        CONS(2 <= N && N <= 2000);
        CONS(1 <= Q && Q <= 2000);
    }

    void Subtask2() {
        CONS(line());
    }

    void Subtask3() {
        CONS(full());
    }

    void Subtask4() {
        CONS(maxDepth(50));
    }

    void Subtask5() {}
    
private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        for (int x : v) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }

    bool connected() {
        vector<int> edge[N + 5];
        for (int i = 0; i < N-1; i++) {
            edge[U[i]].push_back(V[i]);
            edge[V[i]].push_back(U[i]);
        }

        vector< vector<int> > edges;
        edges.push_back(edge[1]); // dummy
        for (int i = 1; i <= N; i++) {
            edges.push_back(edge[i]);
        }

        pair<int, int> graphStat = DFS(1, -1, edges);
        int size = graphStat.first;
        int depth = graphStat.second;

        return (size == N);
    }

    bool line() {
        for (int i = 1; i < N; i++) {
            int ii = i - 1;
            if (U[ii] != i || V[ii] != i + 1) return false;
        }
        return true;
    }

    bool full() {
        for (int i = 1; i < N; i++) {
            int ii = i - 1;
            if (U[ii] != (i + 1) / 2 || V[ii] != i + 1) return false;
        }
        return true;
    }

    bool maxDepth(int maximum) {
        vector<int> edge[N + 5];
        for (int i = 0; i < N-1; i++) {
            edge[U[i]].push_back(V[i]);
            edge[V[i]].push_back(U[i]);
        }

        vector< vector<int> > edges;
        edges.push_back(edge[1]); // dummy
        for (int i = 1; i <= N; i++) {
            edges.push_back(edge[i]);
        }

        pair<int, int> graphStat = DFS(1, -1, edges);
        int size = graphStat.first;
        int depth = graphStat.second;

        return (depth <= maximum);
    }

    pair<int, int> DFS(int pos, int par, vector< vector<int> >& edges) {
        pair<int, int> ret = pair<int, int> (1, 0);
        for (int i = 0; i < edges[pos].size(); i++) {
            int child = edges[pos][i];
            if (child != par) {
                pair<int, int> childStat = DFS(child, pos, edges);
                ret.first += childStat.first;
                ret.second = max(ret.second, 1 + childStat.second);
            }
        }
        return ret;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
private:
    Tree tree;
    bool manual;

    void makeQueries() {
        vector<int> arr;
        
        for (int i = 2; i <= N; i++) arr.push_back(i);
        rnd.shuffle(arr.begin(), arr.end());
        
        for (int i = 0; i < min(Q, (int) arr.size()); i++) A.push_back(arr[i]);
        while (A.size() != Q) A.push_back(rnd.nextInt(2, N));
    }

    void makeLine(int n) {
        N = n;
        for (int i = 1; i < N; i++) {
            U.push_back(i);
            V.push_back(i+1);
        }
    }

    void makeFull(int n) {
        N = n;
        for (int i = 1; i < N; i++) {
            U.push_back((i+1) / 2);
            V.push_back(i+1);
        }
    }

protected:
    void SampleTestCase1() {
        Subtasks({1, 4, 5});
        Input({
            "11 2",
            "1 2",
            "3 9",
            "1 10",
            "10 9",
            "5 2",
            "4 2",
            "7 6",
            "6 3",
            "8 6",
            "3 11",
            "6",
            "2"
        });
        Output({
            "3",
            "5"
        });
    }

    void BeforeTestCase() {
        manual = false;
        
        U.clear();
        V.clear();
        A.clear();
    }

    void AfterTestCase() {
        if (manual) return;

        N = tree.node_count();
        U = tree.edges().first;
        V = tree.edges().second;
        makeQueries();
    }

    void TestGroup1() {
        Subtasks({1, 2, 3, 4, 5});
        
        CASE(manual = true, N = 2, Q = 7, U = {1}, V = {2}, makeQueries());
    }

    void TestGroup2() {
        // N, Q <= 2000
        // LINE
        // DEPTH <= 50
        Subtasks({1, 2, 4, 5});

        CASE(manual = true, makeLine(3), Q = 10, makeQueries());
        CASE(manual = true, makeLine(4), Q = 10, makeQueries());
        CASE(manual = true, makeLine(6), Q = 666, makeQueries());
        CASE(manual = true, makeLine(50), Q = 1000, makeQueries());
        CASE(manual = true, makeLine(51), Q = 1000, makeQueries());
    }

    void TestGroup3() {
        // N, Q <= 2000
        // LINE
        // DEPTH > 50
        Subtasks({1, 2, 5});

        CASE(manual = true, makeLine(777), Q = 2000, makeQueries());
        CASE(manual = true, makeLine(1412), Q = 2000, makeQueries());
        CASE(manual = true, makeLine(1999), Q = 2000, makeQueries());
        CASE(manual = true, makeLine(2000), Q = 2000, makeQueries());
    }

    void TestGroup4() {
        // N, Q <= 2000
        // FULL
        Subtasks({1, 3, 4, 5});

        CASE(manual = true, makeFull(13), Q = 2000, makeQueries());
        CASE(manual = true, makeFull(666), Q = 2000, makeQueries());
        CASE(manual = true, makeFull(1999), Q = 2000, makeQueries());
        CASE(manual = true, makeFull(2000), Q = 2000, makeQueries());

        CASE(manual = true, makeFull(3), Q = 20, makeQueries());
        CASE(manual = true, makeFull(4), Q = 20, makeQueries());
        CASE(manual = true, makeFull(5), Q = 20, makeQueries());
        CASE(manual = true, makeFull(6), Q = 20, makeQueries());
        CASE(manual = true, makeFull(7), Q = 20, makeQueries());
        CASE(manual = true, makeFull(8), Q = 20, makeQueries());
        CASE(manual = true, makeFull(9), Q = 20, makeQueries());
        CASE(manual = true, makeFull(10), Q = 20, makeQueries());
        CASE(manual = true, makeFull(11), Q = 20, makeQueries());
        CASE(manual = true, makeFull(12), Q = 20, makeQueries());
        CASE(manual = true, makeFull(13), Q = 20, makeQueries());
        CASE(manual = true, makeFull(1021), Q = 2000, makeQueries());
        CASE(manual = true, makeFull(1022), Q = 2000, makeQueries());
        CASE(manual = true, makeFull(1023), Q = 2000, makeQueries());
        CASE(manual = true, makeFull(1024), Q = 2000, makeQueries());
        CASE(manual = true, makeFull(1025), Q = 2000, makeQueries());
        CASE(manual = true, makeFull(1026), Q = 2000, makeQueries());
        CASE(manual = true, makeFull(1027), Q = 2000, makeQueries());
    }

    void TestGroup5() {
        // N, Q <= 2000
        // FREE
        // DEPTH <= 50
        Subtasks({1, 4, 5});

        CASE(tree = TreeRandomizer().index_base(1).node_count(42).depth(10).leaf_count(10).next(), Q = 2000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(666).depth(50).leaf_count(333).next(), Q = 2000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(1999).depth(50).leaf_count(123).next(), Q = 2000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(2000).depth(50).leaf_count(1337).next(), Q = 2000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(2000).depth(10).child_count(80,100).next(), Q = 2000);

        CASE(tree = StarTreeRandomizer().index_base(1).node_count(1997).next(), Q = 2000);
        CASE(tree = StarTreeRandomizer().index_base(1).node_count(1998).next(), Q = 2000);
        CASE(tree = CaterpillarTreeRandomizer().index_base(1).node_count(1258).depth(50).next(), Q = 2000);
        CASE(tree = CaterpillarTreeRandomizer().index_base(1).node_count(1879).depth(50).next(), Q = 2000);
    }

    void TestGroup6() {
        // N, Q <= 2000
        // FREE
        // DEPTH > 50
        Subtasks({1, 5});

        CASE(tree = TreeRandomizer().index_base(1).node_count(1999).depth(100).leaf_count(100).next(), Q = 2000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(1999).depth(1234).leaf_count(123).next(), Q = 2000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(2000).depth(400).leaf_count(1500).next(), Q = 2000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(2000).depth(1500).leaf_count(500).next(), Q = 2000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(2000).depth(100).child_count(10,100).next(), Q = 2000);

        CASE(tree = CaterpillarTreeRandomizer().index_base(1).node_count(2000).depth(1024).next(), Q = 2000);
        CASE(tree = CaterpillarTreeRandomizer().index_base(1).node_count(2000).depth(1945).next(), Q = 2000);
    }

    void TestGroup7() {
        // N, Q > 2000
        // LINE
        Subtasks({2, 5});

        CASE(manual = true, makeLine(45678), Q = 45677, makeQueries());
        CASE(manual = true, makeLine(98765), Q = 98764, makeQueries());
        CASE(manual = true, makeLine(99999), Q = 100000, makeQueries());
        CASE(manual = true, makeLine(100000), Q = 100000, makeQueries());
    }

    void TestGroup8() {
        // N, Q > 2000
        // FULL
        Subtasks({3, 4, 5});

        CASE(manual = true, makeFull(23456), Q = 23455, makeQueries());
        CASE(manual = true, makeFull(76543), Q = 76542, makeQueries());
        CASE(manual = true, makeFull(99999), Q = 99999, makeQueries());
        CASE(manual = true, makeFull(100000), Q = 100000, makeQueries());

	CASE(manual = true, makeFull(65533), Q = 70000, makeQueries());
        CASE(manual = true, makeFull(65534), Q = 70000, makeQueries());
        CASE(manual = true, makeFull(65535), Q = 70000, makeQueries());
        CASE(manual = true, makeFull(65536), Q = 70000, makeQueries());
        CASE(manual = true, makeFull(65537), Q = 70000, makeQueries());
        CASE(manual = true, makeFull(65538), Q = 70000, makeQueries());
        CASE(manual = true, makeFull(65539), Q = 70000, makeQueries());
    }

    void TestGroup9() {
        // N, Q > 2000
        // FREE
        // DEPTH <= 50
        Subtasks({4, 5});

        CASE(tree = TreeRandomizer().index_base(1).node_count(88888).depth(50).leaf_count(54321).next(), Q = 100000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(98765).depth(50).leaf_count(5432).next(), Q = 100000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(99999).depth(50).leaf_count(88888).next(), Q = 100000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(100000).depth(50).leaf_count(55555).next(), Q = 100000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(100000).depth(50).child_count(200,1000).next(), Q = 100000);

        CASE(tree = StarTreeRandomizer().index_base(1).node_count(98765).next(), Q = 100000);
        CASE(tree = StarTreeRandomizer().index_base(1).node_count(86468).next(), Q = 100000);
        CASE(tree = CaterpillarTreeRandomizer().index_base(1).node_count(77777).depth(49).next(), Q = 100000);
        CASE(tree = CaterpillarTreeRandomizer().index_base(1).node_count(100000).depth(50).next(), Q = 100000);
    }

    void TestGroup10() {
        // N, Q > 2000
        // FREE
        // DEPTH > 50
        Subtasks({5});

        CASE(tree = TreeRandomizer().index_base(1).node_count(99999).depth(1234).leaf_count(54321).next(), Q = 100000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(99999).depth(54321).leaf_count(1234).next(), Q = 100000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(100000).depth(666).leaf_count(666).next(), Q = 100000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(100000).depth(33333).leaf_count(66666).next(), Q = 100000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(100000).depth(88888).leaf_count(11111).next(), Q = 100000);
        CASE(tree = TreeRandomizer().index_base(1).node_count(100000).depth(1000).child_count(20,100).next(), Q = 100000);

        CASE(tree = CaterpillarTreeRandomizer().index_base(1).node_count(77777).depth(17845).next(), Q = 100000);
        CASE(tree = CaterpillarTreeRandomizer().index_base(1).node_count(100000).depth(89898).next(), Q = 100000);
    }
};
