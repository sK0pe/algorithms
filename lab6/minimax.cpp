#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
using namespace std;

bool turnResult(bool playerSide, vector<int>& playerHouses, vector<int>& opponentHouses,
    int finalIndex){
    // If last house was empty before last seed was sown
    if(playerSide and playerHouses[finalIndex] == 1 and finalIndex < 6){
        // Final seed and opponent's seeds are scored into store
        playerHouses[6] += opponentHouses[5-finalIndex] + 1;
        // Put captured seeds into store
        opponentHouses[5 - finalIndex] = 0;
        playerHouses[finalIndex] = 0;
        return false;
    }
    if(playerSide and finalIndex == 6){
        // play again
        return true;
    }
    return false;
}

bool sowSeeds(vector<int>& playerHouses, vector<int>& opponentHouses, int sowSource, bool playerOne){
    //cout << ">>>>>>>>>>>>>>running sow seed" << endl;
    // Take all seeds from source
    int seeds = playerHouses[sowSource];
    playerHouses[sowSource] = 0;
    bool playerSide = true;
    sowSource++;
    // Place seeds in counter clockwise manner i.e. increasing
    while(seeds > 0){
        while(sowSource < 7 and seeds > 0){
            playerSide = true;
            playerHouses[sowSource] += 1;
            sowSource++;
            seeds--;
        }
        if(seeds > 0){
            sowSource = 0;
        }
        while(sowSource < 6 and seeds > 0){
            playerSide = false;
            opponentHouses[sowSource] += 1;
            sowSource++;
            seeds--;
        }
    }
    return turnResult(playerSide, playerHouses, opponentHouses, sowSource-1);
}



void printGameState(vector<int>& playerHouses, vector<int>& opponentHouses, bool playerOne){
    cout << "Opponent Store = " << opponentHouses[6] << endl;
    cout << "Opponent Houses: " << endl;
    for(int i = opponentHouses.size()-2; i >= 0 ; --i){
        cout << opponentHouses[i] << ' ';
    }
    cout << endl;
    cout << "Player Houses: " << endl;
    for(int j = 0; j < (int)playerHouses.size()-1; ++j){
        cout << playerHouses[j] << ' ';
    }
    cout << endl;
    cout << "Player Store = " << playerHouses[6] << endl;
    cout << endl;
    if(playerOne){
        cout << "Player One's Turn." << endl;
    }
    else{
        cout << "Player Two's Turn." << endl;
    }
}

void playGame(vector<int>& playerHouses, vector<int>& opponentHouses, bool playerOne){
    (playerOne)? printGameState(playerHouses, opponentHouses, playerOne) : printGameState(playerHouses, opponentHouses, playerOne);


    if(accumulate(playerHouses.begin(), playerHouses.end() - 1, 0) == 0 and accumulate(opponentHouses.begin(), opponentHouses.end() - 1, 0) == 0){
        // Game ended;
        cout << "----Game ended----" << endl;
        if(playerHouses[6] > opponentHouses[6]){
            cout << "----Player One wins with score " << playerHouses[6] << "----" << endl;
        }
        else if(playerHouses[6] < opponentHouses[6]){
            cout << "Player Two wins " << opponentHouses[6] << endl;
        }
        else{
            cout << "Draw" << endl;
        }
        return;
    }
    // If play again.
    int playerChoice;
    cout << "Enter index of house to sow seeds from:\n";
    cin >> playerChoice;
    cout << endl;

    bool playAgain = sowSeeds(playerHouses, opponentHouses, playerChoice, playerOne);
    if(playAgain){
        playGame(playerHouses, opponentHouses, playerOne);
    }
    else{
        playGame(opponentHouses, playerHouses, !playerOne);
    }
}

int main(){
    // houses and store for each player
    vector<int> playerHouses(7, 4);
    vector<int> opponentHouses(7,4);
    // Stores start at 0
    playerHouses[6] = 0;
    opponentHouses[6] = 0;

    // Player one starts
    playGame(playerHouses, opponentHouses, true);
    return 0;
}
