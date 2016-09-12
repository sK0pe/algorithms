#include <iostream>
#include <set>
#include <map>
using namespace std;

int main(){
    map<string, set<string>> wow;

    wow["abc"].insert("abd");
    wow["abc"].insert("abe");

    for(auto& s : wow){
        cout << s.first << " holds ";
        for(auto& word : s.second){
            cout << word << ' ';
        }
    }
    cout << endl;

    for(auto &a : wow["abc"]){
        cout << a << ' ';
    }
    cout << endl;


    return 0;
}
