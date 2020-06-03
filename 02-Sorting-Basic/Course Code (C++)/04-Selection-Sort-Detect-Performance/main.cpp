#include <iostream>
#include "SortTestHelper.h"

using namespace std;

// Selection Sort

//时间复杂度 o(n^2)
template<typename T>
void selectionSort(T arr[], int n){

    for(int i = 0 ; i < n ; i ++){

        int minIndex = i;
        for( int j = i + 1 ; j < n ; j ++ )
            if( arr[j] < arr[minIndex] )
                minIndex = j;

        swap( arr[i] , arr[minIndex] );
    }
}

int main() {

    int n = 20000;
    int *arr = SortTestHelper::generateRandomArray(n,0,n);
    // SortTestHelper::printArray(arr, n);

    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    delete[] arr; //删除释放arr

    return 0;
}