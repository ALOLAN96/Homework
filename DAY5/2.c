#include <stdio.h>

int main(int argc, const char *argv[])
{
	int arr[]={1, 2, 3, 4, 5, 6, 7, 8};
	int count;
	count = sizeof(arr) / sizeof(arr[0]); 

	printf("数组长度为%d\n", count);

	for (int i = 0; i < count / 2; i ++)
	{
		arr[2 * i + 1] *= 3;
		arr[2 * i] += 2;
	}

	for (int i = 0; i < count; i++)
	{
		printf("%d\t",arr[i]);
	}



	return 0;
}
