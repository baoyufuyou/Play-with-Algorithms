#include <iostream>
#include <algorithm>
//The algorithms library defines functions for a variety of purposes 
//(e.g. searching, sorting, counting, manipulating) that operate on 
//ranges of elements. Note that a range is defined as [first, last) 
//where last refers to the element past the last element to inspect or modify.
using namespace std;
void selectionSort(int arr[], int n){
    for(int i = 0; i < n ; i++){
        int minIndex = i;
        for(int j = i+1; j<n; j++){ // 对于每一个初始位置，用后面的进行比较， 如果需要变幻顺序，进行swap替换
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);
    }
}

// int main(){
//     int a[7] = {10，9，8，7，6，5，4，3}；
//     selectionSort(a, 7);
//     for(int i=0, i<7, i++){
//         cout << a[i] << cend；
//     }
// }