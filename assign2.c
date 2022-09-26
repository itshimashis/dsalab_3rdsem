#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define Data int

struct pair{
	int a;
	int b;
};

int findMin(Data A[], int size, Data *minP){
	*minP = INT_MAX;
	int count = 0;
	for(int i = 0; i < size; i++){
		if(*minP > A[i]){
			*minP = A[i];
			count = i + 1;
		}
	}
	return count;
}

struct pair findMaxMin(Data A[], int size, Data *maxP, Data *minP){
	*minP = INT_MAX;
	*maxP = INT_MIN;
	int mxcount = 0, mncount = 0;
	for(int i = 0; i < size; i++){
		if(*minP > A[i]){
			*minP = A[i];
			mncount = i + 1;
		}
		if(*maxP < A[i]){
			*maxP = A[i];
			mxcount = i + 1;
		}
	}
	struct pair p;
	p.a = mncount;
	p.b = mxcount;

	return p;

}

int count = 0;
int max = 0, min = 0;
int findMaxMinDnQ(Data A[], int s, int e){
	
	int mid = s + (e - s)/2;

	if(s == e){
		return A[s];
	}
	int first = findMaxMinDnQ(A, s, mid);
	int late = findMaxMinDnQ(A, mid + 1, e);
	if(first >= late){
		max = first;
		min = late;
		count++;
		return first;
	}
	else{
		max = late;
		min = first;
		count++;
		return late;
	}

}



void main()
{
	int A[] = {4, 6, 7, 2, 5, 10, 3};
	int min = 0;
	int max = 0;
	struct pair p;
	p = findMaxMin(A, 7, &max, &min);
	printf("The number of comparions in 2.1 is %d, and min is %d. \n", findMin(A, 7, &min), min);
	printf("The number of compartison:\nMax: %d and max is %d.\nMin: %d and min is %d.\n", p.b, max, p.a, min);
	int garbadge = findMaxMinDnQ(A, 0, 6);
	printf("The number of comparison is: %d.\nMax: %d, Min: %d.\n", count, max, min);
}
