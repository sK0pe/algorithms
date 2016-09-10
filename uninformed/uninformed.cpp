#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include<queue>
#include<stack>
#include<map>
#include<unordered_map>
using namespace std;

class item{
    public:
        string word;
        int links;

        item(string w, int num){
            word = w;
            links = num;
        }
};

bool isAdjacent(string& a, string& b){
    int count = 0;
    for(int i = 0; i < (int)a.length(); ++i){
        if(a[i] != b[i]){
            ++count;
        }
        if(count > 1){
            return false;
        }
    }
    return (count == 1)? true:false;
}

int shortestChainDFS(string& start, string& end, map<string, set<string>>& grid){
    // visited container
    unordered_map<string, bool> visited;
    // populate visited
    for(auto& d : grid){
        visited.insert(make_pair(d.first, false));
    }
    stack<pair<string, int>> wordStack;
    visited[start] = true;
    pair<string, int> item = make_pair(start, 0);
    wordStack.push(item);
    pair<string, int> current;
    while(!wordStack.empty()){
        current = wordStack.top();
        wordStack.pop();
        if(current.first == end){
            return current.second;
        }

        for(auto& w : grid[current.first]){
            if(!visited[w]){
                visited[w] = true;
                wordStack.push(make_pair(w, current.second + 1));
            }
        }
    }
    return 0;
}


int shortestChainBFS(string& start, string& end, set<string>& dictionary){
    queue<pair<string, int>> line;
    // string is the word, chain length is the int
    pair<string, int> item = make_pair(start, 0);
    line.push(item);
    pair<string, int> current;
    while(!line.empty()){
        current = line.front();
        //cout << current.first << endl;
        line.pop();
        for(auto i = dictionary.begin(); i != dictionary.end(); i++){
            // Check if word is adjacent (1 change difference)
            string temp = *i;
            if(isAdjacent(temp, current.first)){
                // Add word to queue, increment chain
                item.first = temp;
                item.second = current.second + 1;
                line.push(item);
                // Remove word from dictionary, similar to visited
                dictionary.erase(temp);
                // If found end
                if(temp == end){
                    return item.second;
                }
            }
        }
    }
    return 0;
}


int main(){
    set<string> dictionary;
    // start and end words
    string start, end;
    cin >> start >> end;
    dictionary.insert(start);
    dictionary.insert(end);
    // read in dictionary
    string temp;
    ifstream dicFile("corncob_caps.txt");
    int dicSize = 0;
    if(dicFile.is_open()){
        while(dicFile >> temp){
            if(dicFile.eof()){
                break;
            }
            if(temp.length() == start.length()){
                ++dicSize;
                dictionary.insert(temp);
            }
        }
        dicFile.close();
    }
    else{
        cerr << "Can't open file." << endl;
        return 1;
    }

    map<string, set<string>> grid;
    for(auto i = dictionary.begin(); i != dictionary.end(); ++i){
        for(auto j = i; j != dictionary.end(); ++j){
            string tempI = *i;
            string tempJ = *j;
            if(isAdjacent(tempI, tempJ)){
                grid[tempI].insert(tempJ);
                grid[tempJ].insert(tempI);
            }
        }
    }

    // for(auto& a : grid){
    //     cout << a.first << " : ";
    //     for(auto & d : a.second){
    //         cout << a.first << " : " << d << ' ';
    //     }
    //     cout << endl;
    // }



    cout << "Shortest number of changes required are " << shortestChainDFS(start, end, grid) << endl;
    return 0;
}
