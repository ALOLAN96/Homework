#include <stdio.h>

int main(int argc, const char *argv[])
{
	int num, single_digits, ten_digit, hundreds_digit;


	printf("Enter a number: ");
	scanf("%d",&num);

	single_digits = num % 10;
	ten_digit = (num / 10) % 10;
	hundreds_digit = num / 100;
	
	
	if ((num < 1000) && (num > 99))
	{
		if ((single_digits * single_digits * single_digits + ten_digit * ten_digit * ten_digit + hundreds_digit * hundreds_digit * hundreds_digit) == num)
		{
			printf("输入的数为水仙花数\n");
		}
		else 
		{
			printf("输入的数不是水仙花数\n");
		}

	}
	else if ((num >= 10) && (num < 100))
	{
		if (ten_digit % single_digits == 0)
		{
			printf("能被个位数整除\n");
		}
		else
		{
			printf("不能被个位数整除\n");
		} 
	}
	else if ((num >= 0) && (num <= 9))
	{
		if (num % 2 == 0)
		{
			printf("输入的为偶数\n");
		}
		else
		{
			printf("输入的为奇数\n");
		}


	}



	return 0;
}
