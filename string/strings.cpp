#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <sstream>
using namespace std;

//	Naive-----------------------------------------------------------------------
void naive(string& pattern, string& text, vector<int>& matches){
	int pLen = pattern.length();
	int shifts = text.length() - pLen;
	// Loop through all possible shifts of window size pattern.length() in text
	for(int s = 0; s <= shifts; ++s){
		int i = 0;
		// Check if each window == pattern
		for(i = 0; i < pLen; ++i){
			if(text[s + i] != pattern[i]){
				// If a character doesn't match then stop checking
				break;
			}
		}
		// if loop did not stop checking prematurely, add the index of the
		// window to the result
		if(i == pLen){
			matches.push_back(s);
		}
	}
}

//	rabinKarp-------------------------------------------------------------------
//  assumes pattern is a word that can be compared in constant time
void rabinKarp(string& pattern, string& text, vector<int>& matches){
	/*int bigPrime = 101;
	int pLen = pattern.length();
	int shifts = text.length() - pLen;

	int hashPattern = 0;
	int hashText = 0;
	int digit = 1;
	int dictionarySize = 10;	// ascii characters

	for(int i = 0; i < pLen-1; ++i){
		digit = (digit * dictionarySize) % bigPrime;
		cout << "digit in loop " << digit << endl;
	}

	// Find hashed values of pattern and first window in text
	for(int i = 0; i < pLen; ++i){
		hashPattern = (dictionarySize * hashPattern + pattern[i]) % bigPrime;
		hashText = (dictionarySize * hashText + text[i]) % bigPrime;
		cout << "hashPattern preprocess = " << hashPattern << endl;
		cout << "hashText preprocess = " << hashText << endl;
	}

	// Shift window over text
	for(int s = 0; s <= shifts; ++s){
		// Check if hash is equivalent
		if(hashText == hashPattern){
			int j = 0;
			// Double check that non spurious
			for(j = 0; j < pLen; ++j){
				if(text[s+j] != pattern[j]){
					break;
				}
			}
			if(j == pLen){
				matches.push_back(s);
			}
		}
	// Calculate next hashed window, may be negative so get abs
		if(s < shifts){
			hashText = abs((dictionarySize * (hashText - text[s]*digit) +
				text[s + pLen]) % bigPrime);
		}
		cout << "hashText refresh is = " << hashText << endl;
	}*/


	int pLen = pattern.length();
	int num = 0;
	int bigPrime = 101;
	int tLen = text.length();


	for(int i = 0; i < pLen; ++i){
		num = num * 10 + (pattern[i] - '0');
		//cout << "num is " << num << endl;
	}
	num = num % bigPrime;
	//cout << "num is " << num << endl;
	// alternate is num = stoi(pattern);
	int window = 0;
	for(int i = 0; i < pLen-1; ++i){
		window = window * 10 + (text[i] - '0');
	}

	int shifts = tLen - pLen + 1;

	for(int s = 0; s < shifts; ++s){
		// Up date the word interpeted as a number
		window = (window % int(pow(10, pLen -1))) * 10 + (text[s + pLen - 1] - '0');
		if(window%bigPrime == num){
			matches.push_back(s);
		}
	}
}

// Knuth-Morris-Pratt-----------------------------------------------------------
void getProperSuffixes(string& pattern, vector<int>& suffixes){
	int len = 0;
	suffixes[0] = 0;
	int pLen = pattern.length();

	int i = 1;
	while(i < pLen){
		if(pattern[i] == pattern[len]){
			suffixes[i] = ++len;
			++i;
		}
		// else pattern[i] != pattern[len]
		else{
			if(len != 0){
				len = suffixes[len-1];
				// don't increment i
			}
			else{	// if len == 0
				suffixes[i] = 0;
				++i;
			}
		}
	}
}

void kmp(string& pattern, string& text, vector<int>& matches){
	int pLen = pattern.length();
	int tLen = text.length();

	vector<int> properSuffixes(pLen);
	getProperSuffixes(pattern, properSuffixes);

	int i = 0;
	int j = 0;
	while(i < tLen){
		// If characters the same move forward
		if(pattern[j] == text[i]){
			++j;
			++i;
		}
		// If at the end of pattern length, have found the index at i -j
		if(j == pLen){
			matches.push_back(i - j);
			// Move j back to properSuffixes -1 to check if next character also
			// matches word
			j = properSuffixes[j-1];
		}
		// mismatch after j matches
		else if(i < tLen && pattern[j] != text[i]){
			// skip matching properSuffixes 0 .. propersuffixes[j-1]
			if(j != 0){
				// go back to previous position in array
				j = properSuffixes[j-1];
			}
			else{
				++i;
			}
		}
	}


	/*int pLen = pattern.length();
	vector<int> prefix(pLen + 1, 0);
	prefix[0] = -1;
	for(int i = 0; i < pLen; ++i){
		int index = prefix[i];
		cout << "i is " << i <<  " and index is " << index << endl;
		cout << "pattern[index] = " << pattern[index] << " and pattern[i] =  " << pattern[i] << endl;
		while(index > -1 && pattern[index] != pattern[i]){
			index = prefix[index];
			cout << "pattern[index] = " << pattern[index] << " and pattern[i] =  " << pattern[i] << endl;
			cout << "index is now prefix[index] = " << index << endl;
			//cout << "in while loop index is " << index << " and pattern[index] is "<< pattern[index] << " while pattern[i] is " << pattern[i] << endl;
		}
		prefix[i+1] = ++index;
		//cout << "prefix[i+1] is " << index << endl;
		cout << "i = " << i << " index = " << index << endl;
		cout << "prefix[i] = " << prefix[i] << " prefix[i + 1] = " << prefix[i+1] << endl << endl;
	}
	for(auto& a : prefix){
		cout << a << ' ';
	}
	cout << endl;

	int tLen = text.length();
	int seen = 0;
	for(int i = 0; i < tLen; ++i){
		while(seen > -1 && pattern[seen] != text[i]){
			seen = prefix[seen];
		}
		if(++seen == pLen){
			matches.push_back(i - pLen + 1);
			seen = prefix[pLen];
		}
	}*/
}

// Boyer Moore------------------------------------------------------------------
void bm(string& pattern, string& text, vector<int>& matches){
	int dictionarySize = 256;
	vector<int> badCharacter(dictionarySize, -1);

	int pLen = pattern.length();
	int tLen = text.length();

	// dictionary is indexed
	// important to give characters not in the pattern a value of -1 as required
	// when doing table lookup, alternatively could use an unordered_set
	for(int i = 0; i < pLen; ++i){
		badCharacter[(int) pattern[i]] = i;
	}
	int shifts = tLen - pLen;
	int s = 0;
	while(s <= shifts){
		int j = pLen -1;
		// Check from right to left if window == pattern
		cout << "checking text = " << text[s+j] << " with pattern = " <<
			pattern[j] << endl;
		while(j >= 0 && pattern[j] == text[s+j]){
			cout << "checking from right to left does " << text[s+j] << " == "
			<< pattern[j] << endl;
			--j;
		}
		// If window == pattern then j should be -1
		if(j < 0){
			cout << "pattern matched" << endl;
			matches.push_back(s);
			// Move s forward so that the next occurrence in the text of the
			// character in the pattern is the next one
			// As long as s + pLen would be less than the length of the text,
			// otherwise just move forward 1.
			cout << "move forward by " << pLen - badCharacter[text[s+pLen]] <<
				endl;
			s += (s + pLen < tLen) ? pLen - badCharacter[text[s + pLen]] : 1;
		}
		else{
			// Shift the pattern so that bad character in text aligns with the
			// last occurrence of it in pattern, use max to get a positive shift
			// badcharacter gives j + 1, where j was the erroneous character
			cout << "s = " << s << " and j = " << j << endl;
			cout << "pattern not matched, move forward by " << max(1, j -
				badCharacter[text[s + j]]) << endl;
			s += max(1, j - badCharacter[text[s + j]]);
		}
	}
}

// LCS--------------------------------------------------------------------------
int lcsRec(string& s1, int x, string& s2, int y, string& sub, string& longest){
	if(x == 0 || y == 0){
		longest = (longest.length() > sub.length())? longest : sub;
		sub = "";
		return 0;
	}
	if(s1[x -1] == s2[y - 1]){
		sub += s1[x-1];
		return 1 + lcsRec(s1, x-1, s2, y-1, sub, longest);
	}
	else{
		return max(lcsRec(s1, x-1, s2, y, sub, longest), lcsRec(s1, x, s2, y-1, sub, longest));
	}
}

void lcsDP(string& s1, string &s2){
	// Make memoization table +1 for each string length
	int length1 = s1.length();
	int length2 = s2.length();
	vector<vector<int>> memTable(length1 + 1, vector<int>(length2 + 1));
	for(int row = 0; row <= length1; ++row){
		for(int col = 0; col <= length2; ++col){
			// Fill zeroes if encountered
			if(row == 0 || col == 0){
				memTable[row][col] = 0;
			}
			else if(s1[row - 1] == s2[col - 1]){
				memTable[row][col] = memTable[row-1][col-1] + 1;
			}
			else{
				memTable[row][col] = max(memTable[row-1][col], memTable[row][col-1]);
			}
		}
	}
	cout << "result is " << memTable[length1][length2] << endl;
}

void selectPatternMatch(string& pattern, string& text, vector<int>& matches){
	cout << "Choose the sorting algorithm from below options\n"
	"1. Naive\n"
	"2. Rabin-Karp (general)\n"
	"3. Knuth-Morris-Pratt\n"
	"4. Boyer-Moore\n"
	"5. LCS (recursive)\n"
	"6. LCS (DP)\n"
	"7. Exit\n\n";

	clock_t start, end;

	int option;
	cin >> option;

	switch(option){
		case 1 :{
			start = clock();
			naive(pattern, text, matches);
			end = clock();
			break;
		}
		case 2:{
			start = clock();
			rabinKarp(pattern, text, matches);
			end = clock();
			break;
		}
		case 3:{
			start = clock();
			kmp(pattern, text, matches);
			end = clock();
			break;
		}
		case 4:{
			start = clock();
			bm(pattern, text, matches);
			end = clock();
			break;
		}
		case 5:{
			start = clock();
			string sub = "";
			string longest = "";
			lcsRec(pattern, pattern.length(), text, text.length(), sub, longest);
			end = clock();
			cout << "lcs is " << longest << " from " << pattern << " and " << text
				<< endl;
			break;
		}
		case 6:{
			start = clock();
			lcsDP(pattern, text);
			end = clock();
			break;
		}
		case 7:		exit(0);
		default:	cout << "Invalid choice\n Try Again\n" << endl;
					selectPatternMatch(pattern, text, matches);
					break;
	};

	cout << fixed << setprecision(4) << "Time taken using option "  << option <<
		": \n" << 1000.0*(end-start) / CLOCKS_PER_SEC << " ms\n" << endl;
}

//	Testing --------------------------------------------------------------------



int main(int argc, char* argv[]){
	string pattern, text;
	cin >> text >> pattern;
	vector<int> matches;
	selectPatternMatch(pattern, text, matches);
	cout << "Text to search: " << text << '\n' << "Pattern to find: " << pattern
	<< "\n\n" << "Indices where match occurred: \n";
	if(matches.empty()){
		cout << "no matches found.";
	}
	else{
		for(auto &match : matches){
			cout << match << ' ';
		}
	}
	cout << endl << endl;;


	return 0;
}
