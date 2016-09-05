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

// class subset{
// 	public:
// 		int parent;
// 		int rank;
// };

// // finds the set of an element i
// int findSubset(vector<subset>& subs, int i){
// 	// find the root and make root parent of i
// 	if(subs[i].parent != i){
// 		subs[i].parent = findSubset(subs, subs[i].parent);
// 	}
// 	return subs[i].parent;
// }

// void unify(vector<subset>& subs, int x, int y){
// 	int xroot = findSubset(subs, x);
// 	int yroot = findSubset(subs, y);

// 	// Add smaller rank tree to higher rank treets
// 	if(subs[xroot].rank > subs[yroot].rank){
// 		subs[yroot].parent = xroot;
// 	}
// 	else if(subs[xroot].rank < subs[yroot].rank){
// 		subs[xroot].parent = yroot;
// 	}
// 	else{
// 		subs[yroot].parent = xroot;
// 		subs[xroot].rank++;
// 	}

// }

int root(int i, vector<int>& parent){
	while(i != parent[i]){
		// make every node that isn't already it's own root, point
		// to the grandparent
		parent[i] = parent[parent[i]];
		i = parent[i];
	}
	return i;
}

bool inSameSet(int p, int q, vector<int>&parent){
	return root(p, parent) == root(q, parent);
}

void unite(int p, int q, vector<int>& parent, vector<int>& elements){
	int i = root(p, parent);
	int j = root(q, parent);
	if(elements[i] < elements[j]){
		parent[i] = j;
		elements[j] += parent[i];
	}
	else{
		parent[j] = i;
		elements[i] += elements[j];
	}
}

void kruskals(int numNodes, vector<edge>& grid, vector<edge>& minPath){
	vector<int> parent(numNodes);
	vector<int> elements(numNodes);
	//vector<subset> subs(numNodes);
	vector<int> degree(numNodes, 0);
	for(int v = 0; v < numNodes; ++v){
		parent[v] = v;
	}

	// Sort edges by weight in ascending order
	sort(grid.begin(), grid.end());

	int e = 0;
	int i = 0;
	while(e < numNodes - 1){
		// get smallest available edge
		edge currCheapest = grid[i];
		i++;	// go to next edge in sorted edges

		// Checking degrees for coalesced simple paths
		// On top of kruskals checking if 2 points are in the same set by checking roots
		if(!inSameSet(currCheapest.source, currCheapest.destination, parent)
			&& degree[currCheapest.source] != 2 && degree[currCheapest.destination] != 2){

			minPath[e] = currCheapest;
			e++;	// go to next edge in MST
			unite(currCheapest.source, currCheapest.destination, parent, elements);
			degree[currCheapest.source]++;
			degree[currCheapest.destination]++;
		}
	}

	//Remove random 0, 0
	for(int i = 0; i < numNodes; ++i){
		if(minPath[i].source == minPath[i].destination){
			minPath.erase(minPath.begin() + i);
			degree[i]--;
		}
	}

	// Insertion???
	// for(int i = 0; i < numNodes; ++i){
	// 	if(degree[i] == 0){
	// 		int x = degree[i];
	// 		// Check each edge that is inside of minPath, add the unused points
	// 		edge minEdge;
	// 		for(int e = 0; e < (int)minPath.size(); ++e){
	// 			// how to determine distance?
	//
	// 		}
	// 	}
	// }


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
