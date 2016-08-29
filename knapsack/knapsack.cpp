#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int knapSackMulti(vector<int>& weights, vector<int>& values,
        vector<int>& counts, int capacity){

    int items = weights.size();
    vector<int> indicies(items);
    for(int i = 0; i < items; ++i){
        indicies[i] = i;
    }

    sort(indicies.begin(), indicies.end(), [&weights, &values](int lhs, int rhs){
        return ((float)values[lhs]/(float)weights[lhs]) >
            ((float)values[rhs]/(float)weights[rhs]);
    });

    // Fill sack
    int item = 0;
    int totalValue = 0;
    int currItem = 0;
    while(capacity > 0 && item < items){
        currItem = indicies[item];
        if(counts[currItem] > 0 && weights[currItem] <= capacity){
            //cout << "item being used is " << currItem << endl;
            //cout << "capacity before is " << capacity << endl;
            capacity -= weights[currItem];
            //cout << "capacity after is " << capacity << endl;
            totalValue += values[currItem];
            //cout << "total value is " << totalValue << endl;
            counts[currItem]--;
        }
        else{
            ++item;
        }
    }
    return totalValue;
}

int knapSackFraction(vector<int>& weights, vector<int>& values, int capacity){
    int items = weights.size();
    vector<int> indicies(items);
    for(int i = 0; i < items; ++i){
        indicies[i] = i;
    }

    sort(indicies.begin(), indicies.end(), [&weights, &values](int lhs, int rhs){
        return ((double)values[lhs]/(double)weights[lhs]) >
            ((double)values[rhs]/(double)weights[rhs]);
    });

    int totalValue = 0;
    int currWeight = 0;
    int currItem = 0;
    for(int i = 0; i < items; ++i){
        currItem = indicies[i];
        if(currWeight + weights[currItem] <= capacity){
            currWeight += weights[currItem];
            totalValue += values[currItem];
        }
        else{
            totalValue += values[currItem] * ((double)(capacity - currWeight)/weights[currItem]);
            break;
        }
    }
    return totalValue;
}

int knapSack01(vector<int>& weights, vector<int>& values, int capacity){
    // vector<int> sack(capacity + 1, 0);
    // int items = weights.size();
    // // iterate through each item
    // for(int i = 0; i < items; ++i){
    //     // iterate through capcity backwards
    //     for(int c = capacity; c >= 0; --c){
    //         // if the current item <= what we can afford
    //         if(weights[i] <= c){
    //             // if can afford
    //             // put item in sack at this capacity
    //             // remove weight of the current item, add current values
    //             // store value for item in this index
    //             sack[c] = max(sack[c], sack[c - weights[i]] + values[i]);
    //         }
    //     }
    //     cout << "item " << i << endl;
    //     for(auto& s : sack){
    //         cout << s << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // return sack[capacity];



    int items = weights.size();
    vector<vector<int>> memTable(capacity + 1, vector<int>(items + 1, 0));

    for(int i = 1; i <= items; ++i){
        for(int c = 1; c <= capacity; ++c){
            //cout << "current cap = " << c <<  " weight of item " << i-1 << " is = " << weights[i-1]  << " and value is " << values[i-1] << endl;
            if(weights[i-1] > c){
                //cout << "item too heavy, skip item" << endl;
                memTable[i][c] = memTable[i-1][c];
            }
            else{
                //cout << "use this item " << endl;
                memTable[i][c] = max(memTable[i-1][c], memTable[i-1][c - weights[i-1]] + values[i-1]);
            }
        }
    }

    // for(int i = 0; i < items + 1; ++i){
    //     for(int j = 0; j < capacity + 1; ++j){
    //         cout << memTable[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;


    return memTable[items][capacity];
}

int main(){
    int numItems, sackCapacity;
    cin >> numItems >> sackCapacity;

    vector<int> weights(numItems);
    vector<int> values(numItems);
    vector<int> counts(numItems);

    cout << "Sack Capacity = " << sackCapacity << endl;

    cout << "weights = " << endl;
    for(auto& w : weights){
        cin >> w;
        cout << w << ' ';
    }
    cout << endl;
    cout << "values = " << endl;
    for(auto& v : values){
        cin >> v;
        cout << v << ' ';
    }
    cout << endl;
    cout << "counts = " << endl;
    for(auto& c : counts){
        cin >> c;
        cout << c << ' ';
    }
    cout << endl;

    cout << "Using Knapsack 01, most value attained is: " <<
        knapSack01(weights, values, sackCapacity) << endl << endl;

    cout << "Using Knapsack fraction, most value attained is: " <<
        knapSackFraction(weights, values, sackCapacity) << endl;

    return 0;
}
