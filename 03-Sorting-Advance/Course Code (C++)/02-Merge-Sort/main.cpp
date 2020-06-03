#include <iostream>
#include "SortTestHelper.h"
#include "InsertionSort.h"

using namespace std;

// 归并排序: 不断分成两部分，
// 用O(logn) 进行划分排序
// 用O(n)级别算法进行归并

// 将arr[l...mid]和arr[mid+1...r]两部分进行归并

/*
r是最右边元素的位置，不是最后元素下一个
定义前闭合后闭合
merge 为合并两半
*/
template<typename  T>
void __merge(T arr[], int l, int mid, int r){

    //* VS不支持动态长度数组, 即不能使用 T aux[r-l+1]的方式申请aux的空间
    //* 使用VS的同学, 请使用new的方式申请aux空间
    //* 使用new申请空间, 不要忘了在__merge函数的最后, delete掉申请的空间:)
    T aux[r-l+1]; // 创建一个新数组
    //T *aux = new T[r-l+1];

    for( int i = l ; i <= r; i ++ ) // 从左边开始，到右边
        aux[i-l] = arr[i]; 

    // 初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
    int i = l, j = mid+1;
    for( int k = l ; k <= r; k ++ ){

        if( i > mid ){  // 如果左半部分元素已经全部处理完毕
            arr[k] = aux[j-l]; j ++;
        }
        else if( j > r ){  // 如果右半部分元素已经全部处理完毕
            arr[k] = aux[i-l]; i ++;
        }
        else if( aux[i-l] < aux[j-l] ) {  // 左半部分所指元素 < 右半部分所指元素
            arr[k] = aux[i-l]; i ++;
        }
        else{  // 左半部分所指元素 >= 右半部分所指元素
            arr[k] = aux[j-l]; j ++;
        }
    }

    //delete[] aux;
}

// 递归使用归并排序,对arr[l...r]的范围进行排序
/*
__开头的函数可能会和编译器的函数冲突
__开头函数不可以外部调用，表示私有

*/
template<typename T>
void __mergeSort(T arr[], int l, int r){

    if( l >= r ) // 待处理数据为空或者为1 // 
        return;

    int mid = (l+r)/2; // l+r 为无穷大时会溢出
    __mergeSort(arr, l, mid); // 归并排序左边
    __mergeSort(arr, mid+1, r); // 归并排序右边
    __merge(arr, l, mid, r); // 合并
}

template<typename T>
void mergeSort(T arr[], int n){

    __mergeSort( arr , 0 , n-1 );
}


// 比较InsertionSort和MergeSort两种排序算法的性能效率
// 整体而言, MergeSort的性能最优, 对于近乎有序的数组的特殊情况, 见测试2的详细注释
int main() {

    // Merge Sort是我们学习的第一个O(nlogn)复杂度的算法
    // 可以在1秒之内轻松处理100万数量级的数据
    // 注意：不要轻易尝试使用SelectionSort, InsertionSort或者BubbleSort处理100万级的数据
    // 否则，你就见识了O(n^2)的算法和O(nlogn)算法的本质差异：）
    int n = 50000;

    // 测试1 一般性测试
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int* arr1 = SortTestHelper::generateRandomArray(n,0,n);
    int* arr2 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);
    SortTestHelper::testSort("Merge Sort",     mergeSort,     arr2, n);

    delete[] arr1;
    delete[] arr2;

    cout<<endl;


    // 测试2 测试近乎有序的数组
    // 对于近乎有序的数组, 数组越有序, InsertionSort的时间性能越趋近于O(n)
    // 所以可以尝试, 当swapTimes比较大时, MergeSort更快
    // 但是当swapTimes小到一定程度, InsertionSort变得比MergeSort快
    int swapTimes = 10;
    assert( swapTimes >= 0 );

    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes); //对十对元素进行大乱
    arr2 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);
    SortTestHelper::testSort("Merge Sort",     mergeSort,     arr2, n);

    delete[] arr1;
    delete[] arr2;

    return 0;
}

// Test for random array, size = 50000, random range [0, 50000]
// Insertion Sort : 1.24694 s
// Merge Sort : 0.007644 s

// Test for nearly ordered array, size = 50000, swap time = 10
// Insertion Sort : 0.000555 s
// Merge Sort : 0.004555 s
// 插入排序对于近似排序的数组，复杂度可以降到O（N）复杂度