/*
# ���Ŀ�ģ�
��дһ������������ģ������Ĺ������Ե��ӵ���ʽʵ�������Ļ������ܡ�

# ���������


# ������ƣ�

## ������ƣ�
���һ����ӭ���˵����û�����ͨ�����˵��������������Ӳ˵����棺
- ��ʾĳһ�������
- ��ʾĳ��ĳ�µ�����
- ��ʾĳ��ĳ��ĳ�������
������Ӳ˵�����󣬿��Լ����˳��ص����˵������к���ѭ��������
�����˵������˳��������еĽӿڡ�

## ������ƣ�
�����ж�����Ƿ�Ϊ���ꡣ
�����ж�ÿ���·ݵ�����������ʶ��������ж��µ������仯��
������ʾĳһ�������
������ʾĳһ����ĳһ���µ�����
������ʾָ����ĳ��ĳ��ĳ�������


# ��ϸ��ƣ�

# �����ж��㷨
�ܱ�4����ͬʱ���ܱ�100��������ݣ������ܱ�400��������ݡ�
```c
if(((year%4 == 0)&&(year%100 != 0)) || (year%400 == 0))
```
�ο����ϣ�[C�����ж�������㷨](https://wenku.baidu.com/view/8bea455643323968011c9281.html)


# �����ж��㷨
���ù�ʽ��W = [Y-1] + [(Y-1)/4] - [(Y-1)/100] + [(Y-1)/400] + D
�ο����ϣ�[�����κ�һ�������ڼ��ļ����㷨](http://blog.csdn.net/whz_zb/article/details/7425260)



ʵ�֣�

����ܽ᣺

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
		welcome_interface();    //���뻶ӭ����
		scanf_s("%i", &user_mode);
		switch (user_mode) {
		case 1: mode_one(); break;
		case 2: mode_two(); break;
		case 3: mode_three(); break;
		case 0: exit(0);
		default: printf("��������������������룡");
		}
	}



	return 0;
}

// ��ʼ����
void welcome_interface() {
	printf("**************************************\n");
	printf("**************************************\n");
	printf("************   Calendar   ************\n");
	printf("**************************************\n");
	printf("*   �밴������ʾ����ָ���ַ�����:       *\n");
	printf("*   1: ��ʾĳһ�������                *\n");
	printf("*   2: ��ʾĳ��ĳ�µ�����              *\n");
	printf("*   3: ��ʾĳ��ĳ��ĳ�������           *\n");
	printf("*   0: �˳�ϵͳ                       *\n");
	printf("**************************************\n");
	printf("**************************************\n");
}

// ģʽһ����ʾĳһ�������
void mode_one() {
	int year;
	printf("��������Ҫ��ѯ����ݣ�");
	scanf_s("%i", &year);
	prt_year(year);
}

// ģʽ������ʾĳ��ĳ�µ�����
void mode_two() {
	int year;
	int month;
	printf("��������Ҫ��ѯ����ݺ��·ݣ�");
	scanf_s("%d%d", &year, &month);
	prt_month(year, month);
}

// ģʽ������ʾĳ��ĳ��ĳ�������
void mode_three() {
	int year;
	int month;
	int day;
	int weekday;
	printf("��������Ҫ��ѯ����ݡ��·ݺ�������");
	scanf_s("%d%d%d", &year, &month, &day);
	weekday = calc_weekday(year, month, day);
	printf("\nThis day is %s.\n\n", WEEKDAY_ALLNAME[(weekday + 1) % 7]);
}

// ��ӡ����
void prt_year(int year) {
	int month;
	printf("\n");
	for (month = 1; month <= 12; month++) {
		prt_month(year, month);
	}
}

// ��ӡ����
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

// ���ڼ���
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

// �����ж�
int is_runnian(int year) {
	if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
		return 1;
	else
		return 0;
}



