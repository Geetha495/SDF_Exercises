#include <algorithm>
#include <fmt/format.h>
#include <vector>
#include <memory>
#include <queue>
#include <algorithm>
#include <numeric>
#include<cmath>


class sorting_algorithmt
{

public:
  virtual void sort(int a[], int n ) = 0;
};

class insertion_sort : public sorting_algorithmt
{
	public:
	void sort(int arr[], int n)
	{
		int i, key, j;
		for (i = 1; i < n; i++)
		{
			key = arr[i];
			j = i - 1;
		
			while (j >= 0 && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				j = j - 1;
			}
			arr[j + 1] = key;
		}
	}
};

int partition(int arr[], int l, int h)
{
    int x = arr[h];
    int i = (l - 1);
 
    for (int j = l; j <= h - 1; j++) {
        if (arr[j] <= x) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[h]);
    return (i + 1);
}

class quicksort: public sorting_algorithmt
{
	public:
	void sort(int arr[],int n)
	{
		int l=0,h=n-1;
		int stack[h - l + 1];
		
		int top = -1;
		
		stack[++top] = l;
		stack[++top] = h;
 
		while (top >= 0) 
		{
			h = stack[top--];
			l = stack[top--];
		
			int p = partition(arr, l, h);
		
			if (p - 1 > l) {
			stack[++top] = l;
			stack[++top] = p - 1;
			}
 
			if (p + 1 < h) {
			stack[++top] = p + 1;
			stack[++top] = h;
			}
		}
	}

};

class merge_sort : public sorting_algorithmt
{
	void merge(int arr[], int l, int m, int r)
	{
		int i, j, k;
		int n1 = m - l + 1;
		int n2 = r - m;

		int L[n1], R[n2];
		for (i = 0; i < n1; i++)
			L[i] = arr[l + i];
		for (j = 0; j < n2; j++)
			R[j] = arr[m + 1+ j];

		i = 0;
		j = 0;
		k = l;
		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j])
			{
				arr[k] = L[i];
				i++;
			}
			else
			{
				arr[k] = R[j];
				j++;
			}
			k++;
		}

		while (i < n1)
		{
			arr[k] = L[i];
			i++;
			k++;
		}

		while (j < n2)
		{
			arr[k] = R[j];
			j++;
			k++;
		}
	}

	void sort(int arr[], int n)
	{
		int curr_size; 
		int left_start; 
		for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
		{
			
			for (left_start=0; left_start<n-1; left_start += 2*curr_size)
			{
				int mid = std::min(left_start + curr_size - 1, n-1);

				int right_end = std::min(left_start + 2*curr_size - 1, n-1);

				merge(arr, left_start, mid, right_end);
			}
		}
	}


};

int main()
{
	int arr[] = {1,4,-2,4,5};
	sorting_algorithmt* s1 = new insertion_sort;
	sorting_algorithmt* s2 = new quicksort;
	sorting_algorithmt* s3 = new merge_sort;
	s3->sort(arr,5);
	for(int i=0;i<5;i++)
	{
		fmt::print("{} ",arr[i]);
	}
	fmt::print("\n");
	return 0;
}