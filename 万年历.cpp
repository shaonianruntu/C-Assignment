/*
# 设计目的：
编写一个万年历程序，模拟生活的挂历，以电子的形式实现日历的基本功能。

# 需求分析：


# 总体设计；

## 界面设计：
设计一个欢迎主菜单，用户可以通过主菜单进入如下三种子菜单界面：
- 显示某一年的年历
- 显示某年某月的月历
- 显示某年某月某天的星期
才完成子菜单任务后，可以继续退出回到主菜单，进行后续循环操作。
在主菜单保留退出程序运行的接口。

## 功能设计：
可以判断年份是否为闰年。
可以判断每个月份的天数。可以识别出闰年中二月的天数变化。
可以显示某一年的日历
可以显示某一年中某一个月的日历
可以显示指定的某年某月某天的星期


# 详细设计：

# 闰年判断算法
能被4整除同时不能被100整除的年份，或者能被400整除的年份。
```c
if(((year%4 == 0)&&(year%100 != 0)) || (year%400 == 0))
```
参考资料：[C语言判断闰年的算法](https://wenku.baidu.com/view/8bea455643323968011c9281.html)


# 星期判断算法
常用公式：W = [Y-1] + [(Y-1)/4] - [(Y-1)/100] + [(Y-1)/400] + D
参考资料：[计算任何一天是星期几的几种算法](http://blog.csdn.net/whz_zb/article/details/7425260)



实现：

设计总结：

*/


# include "stdio.h"
# include "stdlib.h"

char *WEEKDAY_NAME[] = { "Sun", "Mon", "Tue", "Wen", "Thu", "Fri", "Sat" };
char *WEEKDAY_ALLNAME[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };


void welcome_interface();
void mode_one();
void mode_two();
void mode_three();
void prt_year(int year);
void prt_month(int year, int month);
int MONTH_DAY_NUM(int year, int month);
int calc_weekday(int year, int month, int day);
int is_runnian(int year);

// main
int main() {
	int user_mode;
	while (1) {
		welcome_interface();    //进入欢迎界面
		scanf_s("%i", &user_mode);
		switch (user_mode) {
		case 1: mode_one(); break;
		case 2: mode_two(); break;
		case 3: mode_three(); break;
		case 0: exit(0);
		default: printf("你的输入有误，请重新输入！");
		}
	}



	return 0;
}

// 开始界面
void welcome_interface() {
	printf("**************************************\n");
	printf("**************************************\n");
	printf("************   Calendar   ************\n");
	printf("**************************************\n");
	printf("*   请按如下提示输入指定字符代号:       *\n");
	printf("*   1: 显示某一年的年历                *\n");
	printf("*   2: 显示某年某月的月历              *\n");
	printf("*   3: 显示某年某月某天的星期           *\n");
	printf("*   0: 退出系统                       *\n");
	printf("**************************************\n");
	printf("**************************************\n");
}

// 模式一：显示某一年的年历
void mode_one() {
	int year;
	printf("输入你想要查询的年份：");
	scanf_s("%i", &year);
	prt_year(year);
}

// 模式二：显示某年某月的月历
void mode_two() {
	int year;
	int month;
	printf("输入你想要查询的年份和月份：");
	scanf_s("%d%d", &year, &month);
	prt_month(year, month);
}

// 模式三：显示某年某月某天的星期
void mode_three() {
	int year;
	int month;
	int day;
	int weekday;
	printf("输入你想要查询的年份、月份和天数：");
	scanf_s("%d%d%d", &year, &month, &day);
	weekday = calc_weekday(year, month, day);
	printf("\nThis day is %s.\n\n", WEEKDAY_ALLNAME[(weekday + 1) % 7]);
}

// 打印年历
void prt_year(int year) {
	int month;
	printf("\n");
	for (month = 1; month <= 12; month++) {
		prt_month(year, month);
	}
}

// 打印月历
void prt_month(int year, int month) {
	int i;
	int weekday;
	weekday = calc_weekday(year, month, 1);

	printf("              %i     %i\n\n", year, month);
	printf("**************************************\n");
	for (i = 0; i < 7; i++) {
		printf("%5s", WEEKDAY_NAME[i]);
	}
	printf("\n");
	for (i = 0; i < weekday; i++) {
		printf("     ");
	}
	for (i = 1; i <= MONTH_DAY_NUM(year, month); i++) {
		printf("%5d", i);
		if ((i + weekday) % 7 == 0)
			printf("\n");
	}
	printf("\n\n");
}

int MONTH_DAY_NUM(int year, int month) {
	int MONTH_DAY_NUM[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if(is_runnian(year) > 0)
		MONTH_DAY_NUM[2] = 29;
	return MONTH_DAY_NUM[month];
}

// 星期计算
int calc_weekday(int year, int month, int day) {
	int weekday;
	int sum_day;
	int i;
	sum_day = day;
	for (i = 1; i < month; i++) {
		sum_day += MONTH_DAY_NUM(year, i);
	}
	weekday = ((year - 1) - (year - 1) / 100 + (year - 1) / 400 + sum_day) % 7;
	return weekday;
}

// 闰年判断
int is_runnian(int year) {
	if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
		return 1;
	else
		return 0;
}



