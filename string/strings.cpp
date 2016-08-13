#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;

//	Naive-----------------------------------------------------------------------
void naive(string& pattern, string& text, vector<int>& matches){
	int pLen = pattern.length();
	int shifts = text.length() - pLen + 1;
	bool match;
	for(int s = 0; s < shifts; ++s){
		match = true;
		for(int j = 0; j < pLen; ++j){
			if(text[s + j] != pattern[j]){
				match = false;
			}
		}
		if(match){
			matches.push_back(s);
		}
	}
}

//	rabinKarp-------------------------------------------------------------------
//  assumes pattern is a word that can be compared in constant time
void rabinKarp(string& pattern, string& text, vector<int>& matches){
	int num = 0;
	// big prime
	int q = 105943;
	int pLen = pattern.length();
	for(int i = 0; i < pLen; ++i){
		num = num * 10 + (pattern[i] - '0');
		//cout << "num is " << num << endl;
	}
	num = num % q;
	//cout << "num is " << num << endl;
	// alternate is num = stoi(pattern);
	int part = 0;
	for(int i = 0; i < pLen-1; ++i){
		part = part * 10 + (text[i] - '0');
	}

	int shifts = text.length() - pLen + 1;

	for(int s = 0; s < shifts; ++s){
		// Up date the word interpeted as a number
		part = (part % int(pow(10, pLen -1))) * 10 + (text[s + pLen - 1] - '0');
		if(part%q == num){
			matches.push_back(s);
		}
	}
}

// Knuth-Morris-Pratt-----------------------------------------------------------
void kmp(string& pattern, string& text, vector<int>& matches){
	int pLen = pattern.length();
	vector<int> prefix(pLen + 1, 0);
	prefix[0] = -1;
	for(int i = 0; i < pLen; ++i){
		int index = prefix[i];
		cout << "index is " << prefix[i] << endl;
		while(index > -1 && pattern[index] != pattern[i]){
			index = prefix[index];
			cout << "in while loop index is " << index << " and pattern[index] is "<< pattern[index] << " while pattern[i] is " << pattern[i] << endl; 
		}
		prefix[i+1] = ++index;
		cout << "prefix[i+1] is " << index << endl;
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
	}
}



void bm(string& pattern, string& text, vector<int>& matches){

}

void selectPatternMatch(string& pattern, string& text, vector<int>& matches){
	cout << "Choose the sorting algorithm from below options\n"
	"1. Naive\n"
	"2. Rabin-Karp (general)\n"
	"3. Knuth-Morris-Pratt\n"
	"4. Boyer-Moore\n"
	"5. Exit\n\n";

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
		case 5:		exit(0);
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