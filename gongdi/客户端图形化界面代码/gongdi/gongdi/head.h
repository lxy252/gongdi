#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<map>
#include<locale.h>

using namespace std;

map<CString, CString>nameid;

typedef struct node {
	TCHAR number[30];
	int setnum;
	int mon;
	int day;
	int hour;
	int min;
	struct node *next;
}Gongdi;

Gongdi *gonghead;

void trans(Gongdi *node, char *s)
{
	char time[4];

	//mon
	time[0] = s[4];
	time[1] = s[5];
	node->mon = atoi(time);
	//day
	time[0]=s[6];
	time[1] = s[7];
	node->day = atoi(time);
	//hour
	time[0] = s[8];
	time[1] = s[9];
	node->hour = atoi(time);
	//min
	time[0] = s[10];
	time[1] = s[11];
	node->min = atoi(time);
}

void readfile()
{
	FILE *fp = freopen("gongdi.txt", "r", stdin);
	gonghead = NULL;
	Gongdi *newnode;
	TCHAR num[30];
	//char sid[30];
	while (wscanf(L"%ls", num) == 1)
	{
		newnode = (Gongdi *)malloc(sizeof(Gongdi));
		wcscpy(newnode->number, num);
		scanf("%d", &newnode->setnum);
		
		char time[20];
		scanf("%s", time);
		trans(newnode, time);

		if (gonghead == NULL)
		{
			gonghead = newnode;
			newnode->next = NULL;
		}
		else
		{
			newnode->next = gonghead;
			gonghead = newnode;
		}
		
	}

	fclose(fp);
}

void readname()
{
	FILE *fp = freopen("name.txt", "r", stdin);
	TCHAR s1[30],s2[30];
	while (wscanf(L"%ls", s1) == 1)
	{
		setlocale(LC_ALL, "chs");
		wscanf(L"%ls", s2);
		nameid[s1] = s2;
	}
}

const int month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

int minus1(Gongdi *t1,Gongdi *t2)
{
	int mo1 = t1->mon, d1 = t1->day, h1 = t1->hour, m1 = t1->min;
	int mo2 = t2->mon, d2 = t2->day, h2 = t2->hour, m2 = t2->min;
	int i;

	int tempd = 0;
	int tempd1 = 0;
	int tempd2 = 0;

	int	temph = 0;
	int tempm = 0;

	for (i = 0; i < mo1 - 1; i++)
		tempd1 += month[i];
	for (i = 0; i < mo2 - 1; i++)
		tempd2 += month[i];

	tempd1 += d1;
	tempd2 += d2;
	tempd = tempd2 - tempd1;

	temph = tempd * 24 + h2 - h1;

	if (m2 < m1)
		tempm = 60 - m1 + m2;
	else
		tempm = m2 - m1;

	return temph * 60 + tempm;
}

