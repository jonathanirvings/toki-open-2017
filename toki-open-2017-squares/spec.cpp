#include <tcframe/spec.hpp>
#include <tcrand/graph.hpp>
#include <tcrand/tree.hpp>
#include <tcrand/vector.hpp>
#include <tuple>
#include <utility>
#define MP make_pair
using namespace tcframe;
using namespace tcrand;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    long long res;
    vector<int> X,Y;
    void InputFormat() {
        LINE(N);
        LINES(X,Y) % SIZE(N);
    }

    void OutputFormat() {
        LINE(res);
    }

    void GradingConfig() {
        TimeLimit(6);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(forEachInRange(X, 0, 100000));
        CONS(forEachInRange(Y, 0, 100000));
        CONS(unique(X,Y));
    }

    void Subtask1() {
        CONS(2 <= N && N <= 100);
        CONS(forEachInRange(X, 0, 100));
        CONS(forEachInRange(Y, 0, 100));
    }

    void Subtask2() {
        CONS(2 <= N && N <= 100);
    }

    void Subtask3() {
        CONS(2 <= N && N <= 4000);
    }

    void Subtask4() {
        CONS(2 <= N && N <= 10000);
    }
    
    void Subtask5() {
        CONS(2 <= N && N <= 20000);
    }

private:
    bool forEachInRange(vector<int> &vec, int lo, int hi){
        for (int v:vec) if (v < lo || v > hi) return false;
        return true;
    }

    bool unique(vector<int> &a, vector<int> &b){
        set<pair<int,int>> points;
        int x = a.size();
        for (int i=0;i<x;i++){
            if (points.count(make_pair(a[i], b[i]))) 
                return false;
            points.insert(make_pair(a[i], b[i]));
        }
        return true;
    }
};

pair<int,int> smallRandPoint(){ 
    return MP(rand_int(0,100), rand_int(0, 100));
}

pair<int,int> randpair(int a, int b){
    return MP(rand_int(a,b), rand_int(a,b));
}


class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    VectorRandomizer<pair<int, int>> vr;
    vector<pair<int,int>> XY;
    
    void BeforeTestCase(){
        vr = VectorRandomizer<pair<int, int>>().unique(1).engine([]{
            return MP(rand_int(0,100000), rand_int(0, 100000)); 
        });
    }
    
    void AfterTestCase(){
        N = XY.size();
        X.clear(); Y.clear();
        for (auto point:XY){
            X.push_back(point.first);
            Y.push_back(point.second);
        }
    }

    void SampleTestCase1(){
        Subtasks({1,2,3,4,5});
        Input({
            "3",
            "0 0",
            "0 2",
            "2 0"
        });

        Output({"12"});
    }

    void randoms(int N){
        CASE(XY = vr.length(N).next());
        CASE(XY = vr.length(N * 0.9).next());
        CASE(XY = vr.length(N).engine([]{return randpair(500, 1000); } ).next());
        CASE(XY = vr.length(N).engine([]{return MP(rand_int(0,100), rand_int(0,100000)); } ).next());
        CASE(XY = vr.length(N).engine([]{return MP(rand_int(0,100000), rand_int(0,100)); } ).next());

    }

    void lines(int N){
        CASE(XY = vr.length(N * 0.5 + 1).engine([]{int x = rand_int(0,100000); return MP(x,x); } ).next()); //diagonal
        CASE(XY = vr.length(N * 0.5 + 1).engine([]{return MP(0,rand_int(0,100000)); } ).next()); //garis
        CASE(XY = vr.length(N * 0.5 + 1).engine([]{return MP(rand_int(0,100000),0); } ).next()); //garis
    }

    void skews(int N) {
        for (int i = 2; i <= 18; i += 4) {
            CASE(skew(N, i));
        }
    }

    void skew(int N, int tries) {
        XY.clear();
        set<pair<int, int>> points;
        for (int i = 0; i < N; ++i) {
            while (true) {
                int x = 99999999;
                int y = 99999999;
                if (rnd.nextInt(10) == 0) {
                    x = min(x, rnd.nextInt(0, 100000));
                    y = min(y, rnd.nextInt(0, 100000));
                } else {
                    for (int j = 0; j < tries; ++j) {
                        x = min(x, rnd.nextInt(0, 100000));
                        y = min(y, rnd.nextInt(0, 100000));
                    }
                }
                if (points.count(make_pair(x, y))) {
                    continue;
                }
                points.insert(make_pair(x, y));
                XY.push_back(make_pair(x, y));
                break;
            }
        }
    }

    void prepare(int N){
        lines(N);
        randoms(N);
        skews(N);
    }

    void TestGroup1() {
        Subtasks({1,2,3,4,5});
        CASE(XY = {MP(0,0), MP(100,100), MP(0,100), MP(100,0)});
        CASE(XY = vr.length(2).engine(smallRandPoint).next());
        CASE(XY = vr.length(3).engine(smallRandPoint).next());
        CASE(XY = vr.length(25).engine(smallRandPoint).next());
        CASE(XY = vr.length(77).engine(smallRandPoint).next());
        CASE(XY = vr.length(100).engine(smallRandPoint).next());
        CASE(XY = vr.length(100).engine(smallRandPoint).next());
        CASE(XY = vr.length(100).engine(smallRandPoint).next());
        CASE(XY = vr.length(100).engine([]{return randpair(0, 9); } ).next());
    }

    void TestGroup2() {
        Subtasks({2,3,4,5});
        CASE(XY = {MP(0,0), MP(100000,100000), MP(0,100000), MP(100000,0)});
        CASE(XY = {MP(0,0), MP(100000,100000)});
        CASE(XY = {MP(0,100000), MP(100000,0)});
        CASE(XY = {MP(0,100), MP(1,100), MP(100000,1)} );
        CASE(XY = {MP(100,0), MP(100,1), MP(1,100000)} );
    }

    void TestGroup3() {
        Subtasks({2,3,4,5});
        prepare(100);
    }

   void TestGroup4() {
        Subtasks({3,4,5});
        prepare(4000);
    }

   void TestGroup5() {
        Subtasks({4,5});
        prepare(10000);
    }
   
   void TestGroup6() {
        Subtasks({5});
        prepare(20000);
    }

};



