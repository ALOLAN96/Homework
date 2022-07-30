#include <stdio.h>
int main(int argc, const char *argv[])
{
	
	int year, month, day, date;

	printf("请输入年月日: ");
	scanf("%d %d %d", &year, &month, &day);


	if (year % 4 == 0)
	{
		if (month == 1)
		{
			date = day;
		}
		else if (month == 2)
		{
			date = 31 + day;
		}
		else if (month == 3)
		{
			date = 31 + 29 + day;
		}
		else if (month == 4)
		{
			date = 31 + 29 + 31 + day;
		}
		else if (month == 5)
		{
			date = 31 + 29 + 31 + 30 + day;
		}
		else if (month == 6)
		{
			date = 31 + 29 + 31 + 30 + 31 + day;		
		}
		else if (month == 7)
		{
			date = 31 + 29 + 31 + 30 + 31 + 30 + day;
		}
		else if (month == 8)
		{
			date = 31 + 29 + 31 + 30 + 31 + 30 + 31 + day;
		}
		else if (month == 9)
		{
			date = 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + day;
		}
		else if (month ==10)
		{
			date = 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + day;
		}
		else if (month ==11)
		{
			date = 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + day;
		}
		else if (month ==12)
		{
			date = 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 +day;
		}
	}
	else 
	{
		if (month == 1)
		{
			date = day;
		}
		else if (month == 2)
		{
			date = 31 + day;
		}
		else if (month == 3)
		{
			date = 31 + 28 + day;
		}
		else if (month == 4)
		{
			date = 31 + 28 + 31 + day;
		}
		else if (month == 5)
		{
			date = 31 + 28 + 31 + 30 + day;
		}
		else if (month == 6)
		{
			date = 31 + 28 + 31 + 30 + 31 + day;		
		}
		else if (month == 7)
		{
			date = 31 + 28 + 31 + 30 + 31 + 30 + day;
		}
		else if (month == 8)
		{
			date = 31 + 28 + 31 + 30 + 31 + 30 + 31 + day;
		}
		else if (month == 9)
		{
			date = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + day;
		}
		else if (month ==10)
		{
			date = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + day;
		}
		else if (month ==11)
		{
			date = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + day;
		}
		else if (month ==12)
		{
			date = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 +day;
		}
	}
	printf("这是第%d天\n",date);
	return 0;
}
