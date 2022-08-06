#include <stdio.h>
#define N 5

int main(int argc, const char *argv[])
{
	int arr[N];
	int temp;
	for (int i = 0; i < N; i++)
	{
		printf("请输入第%d个元素: ",i + 1);
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < N / 2; i ++)
	{
		temp = arr[i];
		arr[i] = arr [N - i - 1];
		arr[N - i - 1] = temp;
	}

	for (int i = 0; i < N; i++)
	{
		printf("%d\t", arr[i]);
	}

	printf("\n");
	

	/*for (int i = N - 1; i >= 0; i --)
	{
		printf("%d\t", arr[i]);
	}
	*/


	return 0;
}
