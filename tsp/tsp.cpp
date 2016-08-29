#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
using namespace std;


void dfs(vector<map<int, int>>& mst, int numNodes){
    vector<bool> visited(numNodes, false);
    // arbitrary start node
    stack<int> cityStack;
    visited[0] = true;
    cityStack.push(0);
    int currNode;
    while(!cityStack.empty()){
        currNode = cityStack.top();
        cityStack.pop();
        // Iterate over each node in the current map
        for(auto& m : mst[currNode]){
            if(!visited[m.first]){
                visited[m.first] = true;
                cout << m.first << " is the node being visited " << endl;
                cityStack.push(m.first);
            }
        }
    }
}

void prims(int numNodes, vector<map<int, int>>& grid, vector<map<int, int>>& minPath){
    vector<bool> visited(numNodes, false);
    vector<int> cost(numNodes, -1);
    vector<int> parent(numNodes, -1);
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> pQueue;
    // Arbitrary end at 0, minPath 0 as shouldn't cost anthing to go to self
    pQueue.push(make_pair(0,0));
    cost[0] = 0;

    int vertex;
    while(!pQueue.empty()){
        // Vertices are second
        vertex = pQueue.top().second;
        pQueue.pop();
        if(visited[vertex]) continue;
        visited[vertex] = true;
        for(auto& adjacent : grid[vertex]){
            int city = adjacent.first;
            int cityDistance = adjacent.second;
            if(!visited[city]){
                if(cost[city] < 0 || cost[city] > cityDistance){
                    cost[city] = cityDistance;
                    parent[city] = vertex;
                    //cout << "minPath stored at " << vertex << " and " << city << " is " << minPath[vertex][city] << endl;
                    //minPath[city] = cityDistance;
                    pQueue.push(make_pair(cost[city], city));
                }
            }
        }
    }
    // Populate graph
    for(int i = 0; i < numNodes; ++i){
        if(parent[i] > -1){
            minPath[parent[i]][i] = cost[i];
        }
    }
}


// Find min spanning tree of graph provided
// Perform DFS on the MST, visit in order of discovery time
void tsp(int numNodes, vector<map<int, int>>& grid){
    vector<map<int, int>> minPath(numNodes, map<int, int>());
    // for(int i = 0; i < numNodes; ++i){
    //     for(auto& s : grid[i]){
    //         cout << "Node u = " << i << " Node v = " << s.first << " Weight = " << s.second << endl;
    //     }
    // }
    cout << endl;
    prims(numNodes, grid, minPath);
    for(int i = 0; i < numNodes; ++i){
        for(auto& s : minPath[i]){
            cout << "Node u = " << i << " Node v = " << s.first << " edge weight = " << s.second << endl;
        }
    }

    dfs(minPath, numNodes);
}

int main(){
    int numNodes, numEdges;
    cin >> numNodes >> numEdges;
    // construct graph

    vector<map<int, int>> cities(numNodes, map<int,int>());
    int u, v, w;
    for(int s = 0; s < numEdges; ++s){
        cin >> u >> v >> w;
        cities[u][v] = w;
        cities[v][u] = w;
    }

    tsp(numNodes, cities);

    return 0;
}
