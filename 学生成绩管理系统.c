/*

课题内容：
实现一个学生管理系统，能够对学生的成绩进行基本的增删改查操作。

功能分解：
1.	为了能够对学生的成绩进行更好的操作，我们增添了文件保存和导入操作，能够对操作之后的学生信息列表进行报错产生随机数。
2.	为了能够方便用户能够时刻选择自己的操作方案，我们设计了一个主菜单界面，列出所有的基本操作方案，用户可以通过主菜单进行到子菜单，来进行完成的针对性操作。

函数设计
1.  pstu askload()
   输入参数：无
   输出参数：学生数据链表
   实现功能：询问是否导入学生数据
2.	void selectionmenu()
   输入参数：无
   输出参数：无
   实现功能：主菜单，可以通过主菜单进入相应的子菜单。
3.	pstu add(pstu q)
   输入参数：学生链表
   输出参数：更新后的学生链表
   实现功能：在学生链表 q 中增添一个学生节点。
4.	pstu delete(pstu q)
   输入参数：学生链表
   输出参数：更新后的学生链表
   实现功能：在学生链表 q 中删除一个学生节点。
5.	pstu update(pstu q)
   输入参数：学生链表
   输出参数：更新后的学生链表
   实现功能：在学生链表 q 中修改一个学生节点。
6.	int check(pstu q)
   输入参数：学生链表
   输出参数：是否查询成功
   实现功能：在学生链表 q 中查询一个学生节点的信息。
7.	void savelist(pstu q)
   输入参数：学生链表
   输出参数：更新后的学生链表
   实现功能：以文件的形式保存学生链表中的信息到本地计算机。

 */


#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct student {
	char stuID[20];
	char stuName[20];
	float chineseQ;
	float englishQ;
	float mathQ;
	struct student *next;
}stu, *pstu;

pstu askload();
void selecetionmenu();
pstu add(pstu q);
pstu delete(pstu q);
pstu update(pstu q);
int check(pstu q);
void savelist(pstu q);


/*
可以进行输入数据选择， 从本地文件中加载初始值或者初始值为空。

*/

int main() {
	int opt;
	pstu head, ptr;

	head = askload();   //加载数据
	ptr = head->next;

	while (1) {
		selecetionmenu();
		scanf("%d", &opt);
		switch (opt) {
		case 0: savelist(head); exit(0);  break;
		case 1: head = add(head); break;
		case 2: head = delete(head); break;
		case 3: head = update(head)	; break;
		case 4: check(head); break;
		default: printf("你的输入有误，请重新输入："); break;
		}
	}

}

// 询问是否从本地加载数据
pstu askload() {
	int opt;

	char id[20];
	char name[20];
	float chinese;
	float english;
	float math;

	pstu head, ptr;
	// 创建链表的表头节点
	head = (pstu)malloc(sizeof(stu));
	ptr = head;
	ptr->next = NULL;

	printf("是否需要从本地加载初始学生信息数据集？\n");
	printf("0：否\n1：是\n");
	scanf("%d", &opt);

	//从本地加载数据
	if (opt == 1) {
		char filename[] = "D:/data.txt";
		FILE *fp;

		//加载 data 数据集，存入到数据链表中
		if ((fp = fopen(filename, "r")) == NULL) {
			printf("文件为空!");
			exit(0);  //正常退出
		}

		while (!feof(fp)) {
			fscanf(fp, "%s %s %f %f %f", &id, &name, &chinese, \
				&english, &math); //整行格式化读取

			ptr->next = (pstu)malloc(sizeof(stu));
			ptr = ptr->next;
			ptr->next = NULL;

			strcpy(ptr->stuID, id);
			strcpy(ptr->stuName, name);
			ptr->chineseQ = chinese;
			ptr->englishQ = english;
			ptr->mathQ = math;
		}

		fclose(fp);
	}

	//创建空白表头
	else if (opt == 0) {
		//// 创建链表的表头节点
		//head = (pstu)malloc(sizeof(stu));
		//ptr = head;
		//ptr->next = NULL;
	}

	return head;
}

//选择菜单
void selecetionmenu() {
	printf("\n**** 欢迎进入学生管理系统 ****\n");
	printf("0. 退出操作\n");
	printf("1. 添加学生\n");
	printf("2. 删除学生\n");
	printf("3. 修改学生\n");
	printf("4. 查询学生\n");
	printf("请输入你需要进行的操作编号：\n");
}

//添加学生
pstu add(pstu q) {
	char id[20];
	char name[20];
	pstu head, ptr;

	head = q;
	ptr = head;

	//遍历到链表尾部
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}

	//在队尾插入一个节点
	ptr->next = (pstu)malloc(sizeof(stu));
	ptr = ptr->next;
	ptr->next = NULL;

	printf("请输入学生的学号：");
	scanf("%s", &id);
	strcpy(ptr->stuID, id);

	printf("请输入学生的姓名：");
	scanf("%s", &name);
	strcpy(ptr->stuName, name);

	printf("请输入学生的语文成绩：");
	scanf("%f", &ptr->chineseQ);

	printf("请输入学生的英语成绩：");
	scanf("%f", &ptr->englishQ);

	printf("请输入学生的数学成绩：");
	scanf("%f", &ptr->mathQ);

	return head;
}

//删除学生
pstu delete(pstu q) {
	char id[20];
	pstu head, ptr, qtr;

	head = q;
	ptr = q->next;
	qtr = head;


	printf("请输入你想要删除的学生的学号：");
	scanf("%s", &id);

	while (ptr != NULL) {
		if (strcmp(id, ptr->stuID) == 0) {
			ptr = ptr->next;
			qtr->next = ptr;
			printf("该同学的信息已经删除！\n");
			return head;
		}
		else {
			ptr = ptr->next;
			qtr = qtr->next;
		}
	}

	printf("未找到该同学，请检查学号是否输入有误！\n");
	return head;
}

//修改学生
pstu update(pstu q) {
	char id[20];
	char name[20];
	pstu head, ptr;

	head = q;
	ptr = head->next;

	printf("请输入你想要修改的学生的学号:");
	scanf("%s", &id);

	while (ptr != NULL) {
		if (strcmp(id, ptr->stuID) == 0) {
			printf("请输入修改学生的姓名:");
			scanf("%s", &name);
			strcpy(ptr->stuName, name);
			
			printf("请输入修改学生的语文成绩:");
			scanf("%f", &ptr->chineseQ);

			printf("请输入修改学生的英语成绩:");
			scanf("%f", &ptr->englishQ);

			printf("请输入修改学生的数学成绩:");
			scanf("%f", &ptr->mathQ);

			return head;
		}
		else {
			ptr = ptr->next;
		}
	}

	printf("\n找不到该学生，请检查是否学号输入有误！\n");
	return head;
}

//查询学生
int check(pstu q) {
	char id[20];
	pstu head, ptr;

	head = q;
	ptr = head->next;

	printf("请输入你想要修改的学生的学号:");
	scanf("%s", &id);

	while (ptr != NULL) {
		if (strcmp(id, ptr->stuID) == 0) {
			printf("\n该学生信息如下：\n");
			printf("%s %s %5.2f %5.2f %5.2f\n", ptr->stuID, \
				ptr->stuName, ptr->chineseQ, ptr->englishQ, ptr->mathQ);
			return 1; //查找成功
		}
		else {
			ptr = ptr->next;
		}	
	}	
		
	printf("找不到该学生，请检查是否学号输入有误！\n");
	return 0; //查找失败
}

void savelist(pstu q) {
	pstu head, ptr;
	FILE *fp;
	char filename[] = "D:/data.txt";

	head = q;
	ptr = head->next;

	if ((fp = fopen(filename, "w")) == NULL) {
		printf("文件打开错误!");
		exit(0);  //正常退出
	}
	
	while (ptr != NULL) {
		fprintf(fp, "%s %s %5.2f %5.2f %5.2f\n", ptr->stuID, ptr->stuName, \
			ptr->chineseQ, ptr->englishQ, ptr->mathQ); //整行格式化读取

		ptr = ptr->next;
	}

	fclose(fp);
	
}