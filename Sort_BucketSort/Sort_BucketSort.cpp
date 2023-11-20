#include <iostream>
#include <vector>

using namespace std;

void Print(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << "\t";
		if ((i + 1) % 5 == 0)
			cout << endl;
	}
}

void RandomFill(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 100;
	}
}

void BucketSort(int* arr, int size)
{
	int minValue = arr[0];
	int maxValue = arr[0];

	for (int i = 1; i < size; i++)
	{
		if (arr[i] > maxValue)
			maxValue = arr[i];
		if (arr[i] < minValue)
			minValue = arr[i];
	}

	int bucketLength = maxValue - minValue + 1;
	vector<int>* bucket = new vector<int>[bucketLength];

	for (int i = 0; i < bucketLength; i++)
	{
		bucket[i] = vector<int>();
	}

	for (int i = 0; i < size; i++)
	{
		bucket[arr[i] - minValue].push_back(arr[i]);
	}

	int k = 0;
	for (int i = 0; i < bucketLength; i++)
	{
		int bucketSize = bucket[i].size();

		if (bucketSize > 0)
		{
			for (int j = 0; j < bucketSize; j++)
			{
				arr[k] = bucket[i][j];
				k++;
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	const int SIZE = 100;

	int data[SIZE];
	RandomFill(data, SIZE);
	Print(data, SIZE);

	BucketSort(data, SIZE);
	cout << endl;
	Print(data, SIZE);

	int a = 0;
}