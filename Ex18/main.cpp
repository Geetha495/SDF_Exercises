#include <algorithm>
#include <fmt/format.h>
#include <vector>
#include <memory>
#include <queue>
#include <algorithm>
#include <numeric>
#include<cmath>


class searching_algorithmt
{

public:
  virtual int search(int a[], int n,int x ) = 0;
};

class linear_search : public searching_algorithmt
{
	public:
	int search(int arr[],int n, int x)
	{
		int i;
		for (i = 0; i < n; i++)
			if (arr[i] == x)
				return i;
		return -1;
	}
};



class binarysearch: public searching_algorithmt
{
	public:
	bool check(int dig, int arr[],int x)
	{
	
		int ele=arr[dig];
		
		if(x<=ele)
		{
			return 1;
		}
		else
		{
			return 0;
		}
}
int search(int arr[],int n,int x)
{
	int lo=0,hi=n-1;
	while(lo<hi)
	{
		int mid=(lo+hi)/2;
		if(check(mid,arr,x))
		{
			hi=mid;
		}
		else
		{
			lo=mid+1;
		}
	}
   
	if(arr[lo]==x)
		return lo;
	else
		return -1;
  
}

};



int main()
{
	int arr[] = {1,4,-2,4,5};
	searching_algorithmt* s1 = new linear_search;
	searching_algorithmt* s2 = new binarysearch;
	int find =s1->search(arr,5,-2);
	if(find!=-1)
		fmt::print("{}\n",find);
	else
		fmt::print("Not found\n");
	return 0;
}