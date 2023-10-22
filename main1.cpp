#include <iostream>
using namespace std;
//Made some changes


// Prints Array
template<typename T>
void print(T A[], int size){
    for(int i = 0; i < size-1; i++){
        cout << A[i] << ", "; 
    }
    cout << A[size-1] << endl; 
}

/*
Decrease-Conquer Insertion Sort
Input: An Array A[lo...hi]
Output: A[lo...hi] such that A[i] <= A[i+1]
Ex: [3, 4, 1, 2] -> [1, 2, 3, 4]
*/
void decreaseConquerInsertionSort(int A[], int n){
    // base case: reaching the first value of the array 
    if(n == 1)
        return;
    decreaseConquerInsertionSort(A, n-1);
    for(int i = (n-1); i > 0; i--){
        if(A[i] < A[i-1]){
            swap(A[i], A[i-1]);
        }
    }
}

//1 4 6 8 9 14 13 2 5 7 3 10 11 12 15 
void decreaseConquerInsertionSort(int A[], int lo, int hi){
    // base case: reaching the first value of the array
    int n = hi-lo+1;  
    if(n == 1)
        return;
    decreaseConquerInsertionSort(A, lo, hi-1);
    for(int i = (lo + n-1); i > lo; i--){
        if(A[i] < A[i-1]){
            swap(A[i], A[i-1]);
        }
    }
}

/*
Decrease-Conquer Selection Sort
Input: An Array A[lo...hi]
Output: A[lo...hi] such that A[i] <= A[i+1]
Ex: [3, 4, 1, 2] -> [1, 2, 3, 4]
*/
template<typename T> 
void decreaseConquerSelectionSort(T A[], int n ){
    if(n == 1) 
        return; 
    int maxPosition = 0; 
    for(int i = (maxPosition + 1); i <= (n-1); i++){
        if(A[i] > A[maxPosition]){
            maxPosition = i; 
        }
    }
    swap(A[maxPosition], A[n-1]); 
    decreaseConquerSelectionSort(A, n-1); 
}

/*
Decrease-Conquer Polynomial Evaluation 
Input: An Array C[lo...hi] of coefficient of a polynomial, and a real value V
Ouput: p(v)
Ex: C[1, 2, 3], 2 (3x^2 + 3x + 1) -> 17
*/
int decreaseConquerPolynomialEvaluation(int C[], int n, int v){
    int power = n-1; 
    int powerEval = 1; 
    if(n == 1)
        return C[0]; 
    int prev = decreaseConquerPolynomialEvaluation(C, n-1, v);
    for(int i = 0; i < power; i++){
        powerEval *= v; 
    } 
    return prev + C[n-1]*powerEval; 
}

/*
Partition
Input: A[7, 6, 1, 5, 3, 2, 8, 4]
Output: 1, 3, 2, 4, 6, 7, 8, 5
*/
int partition(int A[], int n, int lo, int hi){
    int pivot = A[hi]; 
    int i = lo; 
    for(int j = lo; j <= (hi-1); j++){
        if(A[j] < pivot){
            swap(A[i++], A[j]); 
        }
    }
    swap(A[i], A[hi]); 
    return i; 
}

/*
Divide-Conquer Quick Sort
Input: An Array A[lo...hi]
Output: A[lo...hi] such that A[i] <= A[i+1]
Ex: [7, 6, 1, 5, 3, 2, 8, 4] -> [1, 2, 3, 4, 5, 6, 7, 8]
*/
void divideConquerQuickSort(int A[], int n, int lo, int hi){
    if(hi <= lo){ 
        return; 
    }
    int p = partition(A, n, lo, hi); 
    divideConquerQuickSort(A, n, lo, p-1); 
    divideConquerQuickSort(A, n, p+1, hi);
}

/*
Divie-Conquer Quick Select
Input: An Array A[lo...hi], integer k
Output: the kth smallest element in the array 
Ex: [7, 8, 2, 4, 1, 5, 6, 3], 4 -> 4
2 1 3 4 5 6 7 8
*/
int divideConquerQuickSelect(int A[], int n, int k, int lo, int hi){
    //checks the # of elements in the array
    if((hi-lo+1)==1){
        return A[lo]; 
    }
    
    int p = partition(A, n, lo, hi);  
    int pk = p + 1; 

    int reVal; 
    if(pk == k){
        reVal = A[p]; 
    }
    else if(pk < k){
        reVal = divideConquerQuickSelect(A, n, k, p+1, hi); 
    }
    else{
        reVal = divideConquerQuickSelect(A, n, k, lo, p-1);
    }
    return reVal; 
}


/*
Divie-Conquer Linear Select (This is the same as Quick Select but in Linear time)
Input: An Array A[lo...hi], integer k
Output: the kth smallest element in the array 
Ex: [7, 8, 2, 4, 1, 5, 6, 3], 4 -> 4
2 1 3 4 5 6 7 8
*/
int linearSelect(int A[], int n, int k, int lo, int hi){
    /*
        1) divide array into groups of 5
        2) Insertion sort each group 
        3) put median value of each of the groups into a new array M
        4) recursevly find the median of the array M (we are finding the median of the medians)

    */

    int arraySize = hi - lo + 1; 

    //if the array length is less than 5 its faster to just sort the array and return the kth value
    if(arraySize < 5){
        decreaseConquerInsertionSort(A, arraySize);
        return A[k]; 
    } 

    /*
    creates an array M for the medians. sorts each group of size 5 of the array and adds the median to the array M. v is the size of the M array
    */
    int M[arraySize/5];
    int v = 0; 
    for(int s = lo; s + 5 <= (hi+1); s+=5){
        decreaseConquerInsertionSort(A, s, s+4);
        M[v++] = A[s+2]; 
    }  
    
    //Gets the pivot value (not index) from array of Medians (M)
    int pivot = linearSelect(M, v, (v-1)/2, 0, v-1); 

    //puts the pivot (value) in the last spot of the array
    for(int i =lo; i <= hi; i++){
        if(A[i] == pivot){
            swap(A[i], A[hi]); 
        }
    }
    
    //The same as quick select algorithm from this point
    int p = partition(A, n, lo, hi);
    
    int pk = p + 1; 
    int reVal; 
    if(pk == k){
        reVal = A[p]; 
    }
    else if(pk < k){
        reVal = linearSelect(A, n, k, p+1, hi); 
    }
    else{
        reVal = linearSelect(A, n, k-pk, lo, p-1);
    }
    return reVal; 
}





int main(int argc, char const *argv[])
{
    // int A[] = {3, 4, 1, 2};
    // int Asize = 4; 
    // decreaseConquerInsertionSort(A, Asize);
    // decreaseConquerSelectionSort(A, Asize); 
    // print<int>(A, Asize);

    // int B[] = {1, 2, 3}; 
    // int Bsize = 3; 
    // int val = decreaseConquerPolynomialEvaluation(B, Bsize, 2); 
    // cout << "Val: " << val << endl; 

    // int C[] = {7, 6, 1, 5, 3, 2, 8, 4}; 
    // int Csize = 8; 
    // divideConquerQuickSort(C, Csize, 0, Csize-1);
    // print<int>(C, Csize);

    // int D[] = {7, 6, 1, 5, 3, 2, 8, 4};
    // int Dsize = 8; 
    // int val = divideConquerQuickSelect(D, Dsize, 4, 0, Dsize-1); 
    // cout << val << endl; 

    int E[] = {9, 1, 4, 8, 6, 14, 13, 2, 5, 7, 3, 10, 11, 12, 15};
    int Esize = 15; 
    int reVal = linearSelect(E, Esize, 9, 0, Esize-1); 
    cout << "4 smallest: " << reVal << endl;


    return 0;
}



