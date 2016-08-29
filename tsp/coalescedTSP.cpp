#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

class edge{
	public:
		int source;
		int destination;
		int weight;
		bool operator < (edge other) const{
			return weight < other.weight;
		}
};

class subset{
	public:
		int parent;
		int rank;
};

// finds the set of an element i
int findSubset(vector<subset>& subs, int i){
	// find the root and make root parent of i
	if(subs[i].parent != i){
		subs[i].parent = findSubset(subs, subs[i].parent);
	}
	return subs[i].parent;
}

void unify(vector<subset>& subs, int x, int y){
	int xroot = findSubset(subs, x);
	int yroot = findSubset(subs, y);

	// Add smaller rank tree to higher rank treets
	if(subs[xroot].rank > subs[yroot].rank){
		subs[yroot].parent = xroot;
	}
	else if(subs[xroot].rank < subs[yroot].rank){
		subs[xroot].parent = yroot;
	}
	else{
		subs[yroot].parent = xroot;
		subs[xroot].rank++;
	}

}


void kruskals(int numNodes, vector<edge>& grid, vector<edge>& minPath){
	vector<subset> subs(numNodes);
	vector<int> degree(numNodes, 0);
	for(int v = 0; v < numNodes; ++v){
		subs[v].parent = v;
		subs[v].rank = 0;
	}

	// Sort edges by weight in ascending order
	sort(grid.begin(), grid.end());

	int e = 0;
	int i = 0;
	while(e < numNodes - 1){
		// get smallest available edge
		edge currCheapest = grid[i];
		i++;	// go to next edge in sorted edges

		int x = findSubset(subs, currCheapest.source);
		int y = findSubset(subs, currCheapest.destination);

		// Checking degrees for coalesced simple paths
		if(x != y && degree[currCheapest.source] != 2 && degree[currCheapest.destination] != 2){
			minPath[e] = currCheapest;
			e++;	// go to next edge in MST
			unify(subs, x, y);
			degree[currCheapest.source]++;
			degree[currCheapest.destination]++;
		}
	}

	// Remove random 0, 0
	for(int i = 0; i < numNodes; ++i){
		if(minPath[i].source == minPath[i].destination){
			minPath.erase(minPath.begin() + i);
		}
	}
}

void tsp(int numNodes, int numEdges, vector<edge>& grid){
    vector<edge> minPath(numNodes);
    kruskals(numNodes, grid, minPath);
    for(auto& s : minPath){
        cout << "Node u = " << s.source << " Node v = " << s.destination << " Weight = " << s.weight << endl;
    }
}

int main(){
    int numNodes, numEdges;
    cin >> numNodes >> numEdges;
    // construct graph

    vector<edge> cities(numEdges);
    for(int s = 0; s < numEdges; ++s){
        cin >> cities[s].source >> cities[s].destination >> cities[s].weight;
    }

    tsp(numNodes, numEdges, cities);

    return 0;
}