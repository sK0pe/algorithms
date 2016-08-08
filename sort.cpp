#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;


//	Bubble Sort ----------------------------------------------------------------
void bubbleSort(vector<int>& container){
	int length = container.size();
	bool swapped = false;
	for(int i = 0; i < length; ++i){
		swapped = false;
		for(int endIndex = 1; endIndex < length; ++endIndex){
			if(container[endIndex] < container[endIndex-1]){
				//cout << "endIndex is " << container[endIndex] << "endIndex+1 is " << container[endIndex+1] << endl;
				swap(container[endIndex], container[endIndex-1]);
				swapped = true;
			}
		}
		if(!swapped){
			break;
		}
	}
}

//	Insertion Sort--------------------------------------------------------------
void insertSort(vector<int>& container){
	int key, i;
	int length = container.size();
	// start 1 ahead
	for(int endIndex = 1; endIndex < length; ++endIndex){
		// key or pivot is at outer loop index, save in key memory
		key = container[endIndex];
		// inner index loop is 1 behind initially
		i = endIndex - 1;
		// while inner indices still exist and associated values are greater than
		// the key
		while(i >= 0 && container[i] > key){
			// move all values up if greater than the key value, that are less than endIndex
			container[i+1] = container[i];
			--i;
		}
		// place key at position where it is known to be larger than all before it
		// and less than all after it
		container[i+1] = key;
	}
}

//	Merge Sort -----------------------------------------------------------------
void merge(vector<int>& container, vector<int>& helper, int begin, int mid, int end){
	for(int i = begin; i <= end; ++i){
		helper[i] = container[i];
	}

	// Pointers working on helper copy of container
	int helpLeft = begin;
	int helpRight = mid + 1;
	// Receiving pointer working on origianl memory of container
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
	// stop recursion only when split into single element containers
	if(left < right){
		int mid = (left + right) / 2;
		// sort left at each level of recursion
		mergeSort(container, helper, left, mid);
		// sort right at each level of recursion
		mergeSort(container, helper, mid+1, right);
		// merge at each level 
		merge(container, helper, left, mid, right);
	}	
}

// Quick Sort-------------------------------------------------------------------
int partition(vector<int>& container, int left, int right){
	int pivot = container[(left + right)/2];
	while(left <= right){
		//  Move left pointer forwards as long as less than pivot
		while(container[left] < pivot){
			left++;
		}
		// Move right pointer backwards as long as more than pivot
		while(container[right] > pivot){
			right--;
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
	//	sort left part of the container while partition is 
	if(left < index - 1){
		quickSort(container, left, index - 1);
	}
	// 
	if(index < right){
		quickSort(container, index, right);
	}
}

//	Heap Sort ------------------------------------------------------------------

void heapify(vector<int>& container, int length, int index){
	int largest = index;
	int left = 2*index + 1;	// left child
	int right = 2*index + 2; // right child

	if(left < length && container[left] > container[largest]){
		largest = left;
	}
	if(right < length && container[right] > container[largest]){
		largest = right;
	}
	if(largest != index){
		swap(container[index], container[largest]);
		heapify(container, length, largest);
	}
}

void heapSort(vector<int>& container){
	int length = container.size();
	// Make a max heap in place
	for(int i = length/2 -1; i >= 0; --i){
		heapify(container, length, i);
	}
	// Swap largest from heap and resort tree with heapify
	for(int i = length-1; i >= 0; --i){
		swap(container[i], container[0]);
		// heapify reduced heap
		heapify(container, i, 0);
	}
}

//  Radix Sort -----------------------------------------------------------------

void countSort(vector<int> container, int length, int currDigit){
	// Output container
	vector<int> result(length);
	vector<int> count(10, 0);
	// count number of instances that this digit occurs at this space
	// curr digit starts at 1 so it is n/1
	for(int i = 0; i < length; ++i){
		cout << "------at index " << i << " result of count loop digit = " << (container[i]/currDigit)%10 << endl;
		count[(container[i]/currDigit)%10]++;
	}

	for(auto& c : count){
		cout << "count is " << c << endl;
	}
	cout << endl;

	// Note where actual position of the digits is in output[0]
	for(int i = 1; i < 10; ++i){
		count[i] += count[i-1];
	}


	// Build result
	for(int i = length - 1; i >= 0; --i){
		result[count[(container[i] / currDigit) % 10] -1] = container[i];
		count[(container[i] /currDigit) %10]--;
	}

	for(int i = 0; i < length; ++i){
		container[i] = result[i];
	}
}

void radixSort(vector<int>& container){
	// Find max element in container, as will have most digits
	int minElement = abs(*min_element(container.begin(), container.end()));
	for(auto& n : container){
		n += minElement;
	}


	int maxElement = *max_element(container.begin(), container.end());

	int length = container.size();

	for(int currDigit = 1; maxElement/currDigit > 0; currDigit *= 10){
		countSort(container, length, currDigit);
	}

	for(auto& n : container){
		n -= minElement;
	}
}
//	Testing --------------------------------------------------------------------

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
	"5. Heap Sort\n"
	"6. Radix Sort\n"
	"7. Exit\n\n";

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
		case 5:{
			start = clock();
			heapSort(container);
			end = clock();
			break;
		}
		case 6:{
			start = clock();
			radixSort(container);
			end = clock();
			break;
		}
		case 7:		exit(0);
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

void checkSorting(vector<int>& container, vector<int>& original){
	if(original.size() != container.size()){
		cout << "sorting algorithm has changed the number of elements\n" << endl;
		exit(1);
	}
	sort(original.begin(), original.end());
	int length = original.size();
	for(int i = 0; i < length; ++i){
		if(container[i] != original[i]){
			cout << "Sorting algorithm has an incorrect element - index matchup at"
				"index " << i << "where the sorted value should be " << original[i]
				<< " instead of " << container[i] << endl << endl;
				break;
		}
	}
	cout << "Sorting algorithm sorted container in ascending order and is correct." 
		<< endl << endl;
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
	// make copy of generated container
	vector<int> original(container);

	printContainer(container);
	// Sort container
	selectSort(container);
	// Check if container is sorted correctly and contains same elements
	checkSorting(container, original);

	
	return 0;
}