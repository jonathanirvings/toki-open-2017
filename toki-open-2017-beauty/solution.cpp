#include "beauty.h"

#include <vector>
#include <cstdio>
#include <iostream>
#include <assert.h>
#include <map>
#include <stack>
#include <queue>
#define cout if(false) cout
using namespace std;

stack<int> comp_member;
vector<int> tree_path[200002];
int tree_beauty[200002];
vector<int> beauty;
map<int,int> low_to_tree_id;
int tree_size;
int level[200002];


int treepar[200002];

void find_articulation_point(int pos, int par, vector<vector<int>> &path, vector<bool> &visited, int &v_time, vector<int> &vis_time, vector<int> &low, vector<bool> &ap){
	if (visited[pos])
		return;
	visited[pos] = true;
 	v_time++;
	vis_time[pos] = v_time;
	low[pos] = v_time;

	int M = path[pos].size();
	int child = 0;


	cout<<"   put "<<pos<<" to stack"<<endl;
	comp_member.push(pos);

	for (int i=0;i<M;i++){
		int u = path[pos][i];
		if (!visited[u]) {
			child++;
			find_articulation_point(u, pos, path, visited, v_time, vis_time, low, ap);

			low[pos] = min(low[pos], low[u]);
			if (low[u] >= vis_time[pos]){
				
				int ap_tree_id = -1;
				if (ap[pos] == false){
					cout<<pos<<" is articulation point. Create component #"<<tree_size<<endl;
					low_to_tree_id[ -(pos + 1) ] = tree_size;
					tree_beauty[tree_size] = beauty[pos];
					tree_size++;
				}
				ap[pos] = true;
				int max_beauty = 0;
				cout<<"Found component #"<<tree_size<<endl;
				cout<<"member :";
				while (comp_member.size()){
					int t = comp_member.top();
					comp_member.pop();
					cout<<" "<<t<<" beauty :"<<beauty[t]<<endl;
					low_to_tree_id[t] = tree_size;
					max_beauty = max(max_beauty, beauty[t]);
					
					if (ap[t]){
						ap_tree_id = low_to_tree_id[-(t + 1)];
						cout<<"connect "<<tree_size<<" "<<ap_tree_id<<endl;
						tree_path[ap_tree_id].push_back(tree_size);
						tree_path[tree_size].push_back(ap_tree_id);	
					}

					if (t == u)
						break;
				}
				
				ap_tree_id = low_to_tree_id[-(pos + 1)];

				tree_path[ap_tree_id].push_back(tree_size);
				tree_path[tree_size].push_back(ap_tree_id);
				cout<<endl;
				low_to_tree_id[u] = tree_size;
				tree_beauty[tree_size] = max(max_beauty, beauty[pos]);

				tree_size++;
			}
		}
		else if (u != par){
			low[pos] = min(low[pos], vis_time[u]);
		}
	}
}

void make_lca(int N, vector<vector<int>>& LCApar, vector<vector<int>>& LCAscore)
{
    for (int i=0; i<N;i++)
        for (int j=0;1<<j<N;j++){
            LCApar[i][j] = -1;
        }
    for (int i=0;i<N;i++){
    	LCApar[i][0] = treepar[i];
    	LCAscore[i][0] = tree_beauty[i];
    }


	for (int j=1;1<<j<N;j++)
    	for (int i=0;i<N;i++)
        	if (LCApar[i][j-1]!= -1){
            	LCApar[i][j] = LCApar[ LCApar[i][j-1] ][j - 1];
				LCAscore[i][j] = max( LCAscore[LCApar[i][j-1]][j - 1] , LCAscore[i][j-1]);
            }

}

int solve(int st, int ed, vector<vector<int>>& LCApar, vector<vector<int>>& LCAscore){
	int lg_v;
	int best = 0;
		if (level[st] < level[ed])
		swap(st,ed);

	for (lg_v=1;(1<<lg_v)<=level[st];lg_v++){}
    lg_v--;
		    for (int i=lg_v;i>=0;i--){
                if (level[st] - (1<<i) >= level[ed]){
          	            best =max(best, LCAscore[st][i]);
            st = LCApar[st][i];
        }
    }
    best = max(best, LCAscore[st][0]);
    best = max(best, LCAscore[ed][0]);
            if (st == ed)
    	return best;
    for (int i=lg_v;i>=0;i--)
          if (LCApar[st][i]!=-1 && LCApar[st][i]!=LCApar[ed][i]){
          	best = max(best, LCAscore[st][i]);
            best = max(best, LCAscore[ed][i]);

            st = LCApar[st][i];
            ed = LCApar[ed][i];
          }
    //naik

    best = max(best, LCAscore[ed][0]);
    best = max(best, LCAscore[st][0]);

    ed = treepar[ed];
    best = max(best, LCAscore[ed][0]);

    return best;
}


int cuy;
void make_tree(int par, int pos, int lev, vector<bool> & visited){

	cout<<par<<" "<<pos<<endl;

	if (visited[pos])
		return;
	visited[pos] = 1;
	treepar[pos] = par;
	level[pos] = lev;
	cuy++;
	int M = tree_path[pos].size();
	cout<<M<<endl;
	for (int i=0;i<M;i++){
		if (tree_path[pos][i] != par){
			cout<<"uy"<<endl;
			make_tree(pos, tree_path[pos][i], lev + 1,visited); 
		}
	}
}

vector<int> getMaximumBeauty(int N, int M, int Q, vector<int> _beauty,
	vector<int> U, vector<int> V,
	vector<int> A, vector<int> B) {
	cout<<"jalan"<<endl;
	vector<int> ans;
	beauty = _beauty;
	vector<vector<int>> path(N);
	for (int i=0;i<M;i++){
		path[ U[i] - 1 ].push_back(V[i] - 1);
		path[ V[i] - 1 ].push_back(U[i] - 1);
	}

	vector<bool> visited(N);
	vector<int> vis_time(N);
	vector<int> low(N);
	vector<bool> ap(N);

	int v_time = 0;
	cout<<"KAGI "<<endl;
	find_articulation_point(0, -1, path, visited, v_time, vis_time, low, ap );
	for (int i=0;i<N;i++){
		if (low_to_tree_id.count(i) == 0){
			cout<<i<<" GA PUNYA PASANGAN :("<<endl;
		}
		cout<<i<<" -> "<<low_to_tree_id[i]<<endl;
	}

	cout<<"Tree size : "<<tree_size<<endl;
	visited = vector<bool>(tree_size);
	make_tree(-1,0, 0, visited);
	cout<<"Cuy size :"<<cuy<<endl;

	vector<vector<int>> LCApar(tree_size, vector<int>(18) );
	vector<vector<int>> LCAscore(tree_size, vector<int>(18) );
	make_lca(tree_size, LCApar, LCAscore);
	for (int i=0;i<Q;i++){
		int a = low_to_tree_id[ --A[i] ];
		int b = low_to_tree_id[ --B[i] ];

		cout<<"before QUERY tree ID : "<<a<<" "<<b<<endl;
		if (ap[A[i]])
			a = low_to_tree_id[-(A[i] + 1) ];
		if (ap[B[i]])
			b = low_to_tree_id[-(B[i] + 1) ];
		cout<<"QUERY tree ID : "<<a<<" "<<b<<endl;
		ans.push_back(solve(a,b, LCApar, LCAscore));
	}
	
	return ans;
}
