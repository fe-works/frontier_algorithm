#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using Graph = vector < vector < int > >;

#define NOT_FOUND -1

// 単方向のinput用グラフ．
// 接点検討用のグラフ．
// 分ける必要がある？？
int already_searched(vector<int> G, int node){
    //ノードに対する接続点の集合と，基準となる点
    for(int i=0; i<G.size(); i++){
        // printf("%d \n", G[i]);
        if(G[i] > node) return 0;
    }
    return 1;
}

int vec_find(vector<int> vec, int wanted){
    vector<int>::iterator itr;
    itr = find(vec.begin(), vec.end(), wanted);
    if (!(itr == vec.end())) return distance(vec.begin(), itr);
    else return NOT_FOUND;
}

void frontierStructure(Graph& G, Graph& DiaGraph, Graph& frontier, int N){
    int cnt = 0, itr;
    bool isFinished;

    for(int i=0; i<N; i++){
        for(int j=0; j<G[i].size(); j++){
            int next_node = G[i][j];
            printf("START: %d, END: %d \n", i, next_node);
            if(cnt != 0) copy(frontier[cnt-1].begin(), frontier[cnt-1].end(), back_inserter(frontier[cnt]));

            itr = vec_find(frontier[cnt], next_node);
            isFinished = already_searched(DiaGraph[next_node], i);
            if(!isFinished){
                if(itr == NOT_FOUND){
                    frontier[cnt].push_back(next_node);
                    printf("ADD: %d \n", next_node);
                }
            } else {
                if(itr != NOT_FOUND){
                    frontier[cnt].erase(frontier[cnt].begin() + itr);
                    printf("DELETE: %d \n", next_node);
                }
            }

            itr = vec_find(frontier[cnt], i);
            isFinished = already_searched(DiaGraph[i], next_node);

            //Already_searchedの条件式がおかしい．
            if(!isFinished){ //ノードに接続する辺で未探索がある
                if(itr == NOT_FOUND){ //Frontierにない場合
                    frontier[cnt].push_back(i);
                    printf("ADD: %d \n", i);
                }
            } else { //すべてノードに接続している辺が探索済み
                if(itr != NOT_FOUND){
                    frontier[cnt].erase(frontier[cnt].begin() + itr);
                    printf("DELETE: %d \n", i);
                }
            }
            printf("=======\n");
            cnt += 1;
        }
    }
}

int main(void){
    int N, M;
    cin >> N >> M;

    Graph graph(N); //無向
    Graph diagraph(N); //有向

    Graph frontier(M);

    int start,end;

    for (int i=0; i<M; i++){
        cin >> start >> end;
        graph[start].push_back(end);
        diagraph[start].push_back(end);
        diagraph[end].push_back(start);
    }

    frontierStructure(graph, diagraph, frontier, N);

    //3: 完成したフロンティアの表示
    for(int i=0; i<M; i++){
        for(int j=0; j<frontier[i].size(); j++){
            cout << frontier[i][j] + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
