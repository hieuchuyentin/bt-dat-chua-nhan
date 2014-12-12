#ifndef _defs_h_
#define _defs_h_
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>
using namespace std;

struct eventList 
{
	int nEventCode; /* 1~9*/
	int firstArg; /*XYZ or S(in s6) or H (in s7)*/
	int secondArg; /*S in s1, s2, s3, s4, s5 ,s8*/
	eventList* pNext; /*pointer to next event*/
};

struct WarriorTree 
{
	int token;
	int strength; 
	int balance;			//will be used in AVL only, and be ignored in other cases.
	WarriorTree* pLeftChild;
	WarriorTree* pRightChild;
};

WarriorTree* revenge(eventList* pEvent);
#endif