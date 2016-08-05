#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
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
	int key, i;
	int length = container.size();
	for(int j = 1; j < length; ++j){
		key = container[j];
		i = j - 1;
		while(i >= 0 && container[i] > key){
			container[i+1] = container[i];
			--i;
		}
		container[i+1] = key;
	}
}

void merge(vector<int>& container, vector<int>& helper, int begin, int mid, int end){
	for(int i = begin; i <= end; ++i){
		helper[i] = container[i];
	}

	int helpLeft = begin;
	int helpRight = mid + 1;
	int current = begin;

	while(helpLeft <= mid && helpRight <= end){
		if(helper[helpLeft] <= helper[helpRight]){
			container[current] = helper[helpLeft++];
		}
		else{
			container[current] = helper[helpRight++];
		}
		current++;
	}

	int remaining = mid - helpLeft;	// As helpRight is default move
	for(int i = 0; i <= remaining; ++i){
		container[current + i] = helper[helpLeft + i];
	}
}

void mergeSort(vector<int>& container, vector<int>& helper, int left, int right){
	if(left < right){
		int mid = (left + right) / 2;
		mergeSort(container, helper, left, mid);
		mergeSort(container, helper, mid+1, right);
		merge(container, helper, left, mid, right);
	}	
}

int partition(vector<int>& container, int left, int right){
	int pivot = container[(left + right)/2];
	while(left <= right){
		//  Move left pointer forwards as long as less than pivot
		while(container[left] < pivot){
			left++;
		}
		// Move right pointer backwards as long as more than pivot
		while(container[right] > pivot){
			right++;
		}
		// If left and right pointers have not crossed then swap and
		// move pointers
		if(left <= right){
			swap(container[left], container[right]);
			left++;
			right--;
		}
	}
	return left;
}

void quickSort(vector<int>& container, int left, int right){
	int index = partition(container, left, right);
	if(left < index - 1){
		quickSort(container, left, index - 1);
	}
	else{
		quickSort(container, index, right);
	}
}

void printContainer(vector<int>& container){
	for(auto& c : container){
		cout << c << ' ';
	}
	cout << endl << endl;
}

void selectSort(vector<int>& container){
	cout << "Choose the sorting algorithm from below options\n"
	"1. Bubble Sort\n"
	"2. Insert Sort\n"
	"3. Merge Sort \n"
	"4. Quick Sort\n"
	"5. Exit\n\n";

	clock_t start, end;
	
	int option;
	cin >> option;

	switch(option){
		case 1 :{
			start = clock();
			bubbleSort(container);
			end = clock();
			break;
		}	
		case 2:{
			start = clock();
			insertSort(container);
			end = clock();
			break;
		}		
		case 3:{
			vector<int> helper(container.size());
			start = clock();
			mergeSort(container, helper, 0, container.size()-1);
			end = clock();
			break;
		}
		case 4:{
			start = clock();
			quickSort(container, 0, container.size()-1);
			end = clock();
			break;
		}
		case 5:		exit(0);
		default:	cout << "Invalid choice\n Try Again\n" << endl;
					selectSort(container);
					break;	
	};
	printContainer(container);

	cout << fixed << setprecision(4) << "Time taken using option "  << option << ": " 
		<< 1000.0*(end-start) / CLOCKS_PER_SEC << " ms\n" << endl;
}



void generateContainer(vector<int>& container, int size){
	for(auto& n : container){
		n = rand() % 1000 - 500;
	}
}

int main(int argc, char* argv[]){
	int size;
	switch(argc){
		case 1:{
			size = rand() % 101;
			break;
		}
		case 2:{
			size = atoi(argv[1]);
			break;
		}
		default:{
			cerr << "Please enter the size of the container you want to test as an"
				" single numerical argument. If one is is not provided a random "
				"integer will be generated from the range 0 - 100." << endl;
				return 0;
		}
	}

	vector<int> container(size);

	generateContainer(container, size);

	printContainer(container);

	selectSort(container);

	
	return 0;
}