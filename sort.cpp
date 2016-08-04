#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void bubbleSort(vector<int>& container){
	int length = container.size();
	bool swapped = false;
	for(int i = 0; i < length; ++i){
		swapped = false;
		for(int j = 1; j < length; ++j){
			if(container[j] < container[j-1]){
				//cout << "j is " << container[j] << "j+1 is " << container[j+1] << endl;
				swap(container[j], container[j-1]);
				swapped = true;
			}
		}
		if(!swapped){
			break;
		}
	}
}

void insertSort(vector<int>& container){

}

void mergeSort(vector<int>& container){
	
}

void quickSort(vector<int>& container){
	
}

void selectSort(vector<int>& container){
	cout << "Choose the sorting algorithm from below options\n"
	"1. Bubble Sort\n"
	"2. Insert Sort\n"
	"3. Merge Sort \n"
	"4. Quick Sort\n"
	"5. Exit\n";

	int option;
	cin >> option;

	switch(option){
		case 1 :	bubbleSort(container);
					break;
		case 2:		insertSort(container);
					break;
		case 3: 	mergeSort(container);
					break;
		case 4: 	quickSort(container);
					break;
		case 5:		exit(0);
		default:	cout << "Invalid choice\n Try Again\n" << endl;
					selectSort(container);
					break;	
		};
}

void printContainer(vector<int>& container){
	for(auto& c : container){
		cout << c << ' ';
	}
	cout << endl;
}

int main(){
	int size;
	cin >> size;
	vector<int> container(size);
	for(int i = 0; i <  container.size(); ++i){
		cin >> container[i];
	}

	printContainer(container);
	selectSort(container);

	printContainer(container);

	
	return 0;
}