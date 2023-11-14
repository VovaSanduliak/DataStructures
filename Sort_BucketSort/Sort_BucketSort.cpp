#include <iostream>
#include <ctime>
#include <cstdlib>

#define SIZE 100

using namespace std;

void Print(string text) {
    cout << text << endl;
}

void Print(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << "\t";
        if ((i + 1) % 10 == 0)
            cout << endl;
    }
}

void Fill(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1;
    }
}

int GetMax(int a[], int size) {
    int max = a[0];

    for (int i = 1; i < size; i++) {
        if (a[i] > max)
            max = a[i];
    }
    return max;
}

int GetMin(int a[], int size) {
    int min = a[0];

    for (int i = 1; i < size; i++) {
        if (a[i] < min)
            min = a[i];
    }
    return min;
}

void BucketSort(int arr[], int length, int min, int max) {
    if (length < 2 || min == max)
        return;

    int numBuckets = length;
    int** buckets =   new int*[numBuckets];
    int* minBuckets = new int[numBuckets];
    int* maxBuckets = new int[numBuckets];

    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = new int[length];
        minBuckets[i] = max;
        maxBuckets[i] = min;
    }

    int range = max - min;

    for (int i = 0; i < length; i++) {
        int index = static_cast<int>((arr[i] - min) * numBuckets / range);

        buckets[index][i] = arr[i];

        if (buckets[index][i] < minBuckets[index])
            minBuckets[index] = buckets[index][i];

        if (buckets[index][i] > maxBuckets[index])
            maxBuckets[index] = buckets[index][i];
    }

    for (int i = 0; i < numBuckets; i++) {
        BucketSort(buckets[i], length, minBuckets[i], maxBuckets[i]);
    }

    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        for (int j = 0; j < length; j++) {
            if (buckets[i][j] != 0) {
                arr[index++] = buckets[i][j];
            }
        }
    }

    // Звільнення пам'яті
    for (int i = 0; i < numBuckets; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] minBuckets;
    delete[] maxBuckets;
}

int main() {
    srand(time(NULL));

    int* arr = new int[SIZE];
    Fill(arr, SIZE);

    Print("Array: ");
    Print(arr, SIZE);

    int min = GetMin(arr, SIZE);
    int max = GetMax(arr, SIZE);

    BucketSort(arr, SIZE, min, max);

    Print("Sorted array: ");
    Print(arr, SIZE);

    delete[] arr;

    return 0;
}
