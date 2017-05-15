#include <tcframe/spec.hpp>
#include <tcrand/graph.hpp>
#include <tcrand/tree.hpp>
#include <tcrand/vector.hpp>
#include <tuple>
using namespace tcframe;
using namespace tcrand;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M, Q;
    
    vector<int> Beauty, U, V, A, B, res;
    void InputFormat() {
        LINE(N, M, Q);
        LINE(Beauty % SIZE(N));
        LINES(U,V) % SIZE(M);
        LINES(A,B) % SIZE(Q);

    }

    void OutputFormat() {
        LINES(res) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(forEachInRange(Beauty, 1, 1000000000));
        CONS(forEachInRange(U, 1, N));
        CONS(forEachInRange(V, 1, N));
        CONS(forEachInRange(A, 1, N));
        CONS(forEachInRange(B, 1, N));

        CONS(forEachDifferent(A,B));
        CONS(simpleGraph(N,U,V));

    }

    void Subtask1() {
        CONS(2 <= N && N <= 15);
        CONS(1 <= M && M <= 30);
        CONS(1 <= Q && Q <= 15);
    }

    void Subtask2() {
        CONS(2 <= N && N <= 100);
        CONS(1 <= M && M <= 200);
        CONS(1 <= Q && Q <= 15);
    }

    void Subtask3() {
        CONS(2 <= N && N <= 100000);
        CONS(1 <= M && M <= 200000);
        CONS(1 <= Q && Q <= 15);
    }
    
    void Subtask4() {
        CONS(2 <= N && N <= 1500);
        CONS(1 <= M && M <= 3000);
        CONS(1 <= Q && Q <= 100000);
    }

    void Subtask5() {
        CONS(2 <= N && N <= 100000);
        CONS(1 <= M && M <= 200000);
        CONS(1 <= Q && Q <= 100000);
    }
private:
    bool forEachInRange(vector<int> &vec, int lo, int hi){
        for (int v:vec) if (v < lo || v > hi) return false;
        return true;
    }

    bool forEachDifferent(vector<int> &a, vector<int> &b){
        int x = a.size();
        for (int i=0;i<x;i++)
            if (a[i] == b[i]) 
                return false;

        return true;
    }

    void dfs(int pos, vector<vector<int>>& path, vector<bool> &visit){
        if (visit[pos]) return;
        visit[pos] = 1;
        int _m = path[pos].size();
        for (int i=0;i<_m;i++){
            dfs(path[pos][i], path, visit);
        }
    }

    bool simpleGraph(int N, vector<int>& u, vector<int>& v){
        vector<vector<int>> path(N);
        set<pair<int,int>> pathset;
        int _m = u.size();
        for (int i=0;i<_m;i++){
            path[u[i]-1].push_back(v[i]-1);
            path[v[i]-1].push_back(u[i]-1); 

            if (pathset.count(make_pair(u[i], v[i])) || pathset.count(make_pair(v[i], u[i])) )
                return false;
            pathset.insert(make_pair(u[i], v[i]));
        }

        vector<bool> visit(N);
        dfs(0, path, visit);
        for (int i=0;i<N;i++)
            if (!visit[i]){
                return false;
            }

        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    Graph g;
    int min_beauty;
    int max_beauty;
    int is_sort;
    const int UP = 1;
    const int DOWN = 2;

    void BeforeTestCase(){
        min_beauty = 1;
        max_beauty = 1000000000;
        is_sort = 0;
    }
    
    void AfterTestCase(){
        U = g.edges().first;
        V = g.edges().second;
        M = V.size();
        N = g.node_count();
        VectorRandomizer<int> b_rand;
        VectorRandomizer<int> q_rand;

        b_rand.length(N).unique(1).engine([&] {return rand_int(min_beauty,max_beauty); } );
        q_rand.length(Q).engine([&] {return rand_int(1,N);});
        A = q_rand.next();
        B = q_rand.next();
        for (int i=0;i<Q;i++)
            while (A[i] == B[i]) B[i] = rand_int(1,N);
        Beauty = b_rand.next();

        if (is_sort)
            sort(Beauty.begin(), Beauty.end());
        if (is_sort == DOWN)
            reverse(Beauty.begin(), Beauty.end());
    }

    void SampleTestCase1() {

        Subtasks({1,2,3,4,5});
        Input({
            "5 5 3",
            "9 7 10 5 4",
            "2 1",
            "4 3",
            "5 4",
            "1 5",
            "5 2",
            "3 1",
            "2 5",
            "4 5"
        });
    }

    void SampleTestCase2() {

        Subtasks({1,2,3,4,5});
        Input({
            "7 8 5",
            "100 80 70 1 2 200 300",
            "1 2",
            "1 3",
            "2 3",
            "1 7",
            "1 6",
            "6 7",
            "2 4",
            "3 5",
            "1 4",
            "2 3",
            "3 5",
            "6 1",
            "6 3"
        });
    }

    void PrepareRandom(int n, int q){
        //rand graphs
        CASE(Q = q, g = GraphRandomizer().index_base(1).node_count(n).edge_count(n * 1.05).next());
        CASE(Q = q, g = GraphRandomizer().index_base(1).node_count(n * rand_double(0.95,0.99)).edge_count(n * 1.1).next());
        //rand trees
        CASE(Q = q, g = TreeRandomizer().index_base(1).node_count(n).next());
        CASE(Q = q, g = TreeRandomizer().index_base(1).node_count(n * 0.9).next());


    }

    void PrepareBridged(int n,int q){
        CASE(Q = q, g = GraphRandomizer().index_base(1).node_count(n).edge_count(n*2).bridge_count(n * 0.1).next());
        CASE(Q = q, g = GraphRandomizer().index_base(1).node_count(n).edge_count(n*1.5).bridge_count(n * 0.2).next());
        CASE(Q = q, g = GraphRandomizer().index_base(1).node_count(n).edge_count(n*1.2).bridge_count(n * 0.4).next());
    }

    void PrepareTree(int n, int q){
        CASE(Q = q; g = StarTreeRandomizer().index_base(1).node_count(n).next() ); //star tree
        CASE(Q = q; g = ChainTreeRandomizer().index_base(1).node_count(n).next() ); //chain
        CASE(Q = q; g = CaterpillarTreeRandomizer().index_base(1).node_count(n).child_count(2,10).next() ); //caterpillar
        
        CASE(Q = q; g = TreeRandomizer().index_base(1).node_count(n - (n%2==0)).child_count(2,2).depth(log2(n)).next(); is_sort = UP);
        CASE(Q = q; g = TreeRandomizer().index_base(1).node_count(n - (n%2==0)).child_count(2,2).depth(log2(n)).next(); is_sort = DOWN);
        
    }
    void Prepare(int n, int q){
        PrepareRandom(n, q);
        PrepareBridged(n, q);
        PrepareTree(n, q);
    }

    void TestGroup1() {
        Subtasks({1,2,3,4,5});
        CASE(Q = 15, g = PetersenGraphRandomizer().index_base(1).next());
        Prepare(15,15);
    }

    void TestGroup2() {
        Subtasks({2,3,4,5});
        Prepare(100,15);
    }

    void TestGroup3() {
        Subtasks({3,5});
        Prepare(100000,15);
    }

    void TestGroup4() {
        Subtasks({4,5});
        Prepare(1000,100000);
    }

    void TestGroup5() {
        Subtasks({5});
        Prepare(100000,100000);
    }

    void TestGroup6() {
        Subtasks({3,4,5});
        Prepare(1000,15);
    }
};

