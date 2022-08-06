#include <stdio.h>

int main(int argc, const char *argv[])
{
	int arr[]={3, 5, 6, 8, 9, 3, 1, 2, 4, 5};
	int length;
	int sum = 0;

	length = sizeof(arr)/sizeof(arr[0]);

	for (int i = 0; i < (length / 2); i ++)
	{
		if (arr[2 * i + 1] % 2 == 0)
		{
			sum += arr[2 * i + 1];
		}
	}
	
	printf("数组长度为%d\n",length);
	printf("结果是:%d\n",sum);

	return 0;
}
