#include <stdio.h>
#define N 7
int main(int argc, const char *argv[])
{
	int arr[N]={52, 13, 45, 9, 61, 2, 6};
	int temp;

	for (int i = 1; i < N; i ++)
	{
		for (int j = 0; j < N - i; j ++)
		{
			if (arr[j] < arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		printf("%d\t", arr[i]);
	}
	return 0;
}
