#ifndef _adventure_cpp_
#define _adventure_cpp_

#include "defs.h"

//your code should be after that directive
#define MAX_NUM_NODE	1000
//Hàm chèn một nút vào cây nhị phân, nút có thể là gốc của một cây
//Trả lại giá trị là con trỏ tới nút gốc của cây mới
WarriorTree* InsertNodeToBST(WarriorTree* pTree, WarriorTree node)
{
	static int nCount = 0;
	
	if (pTree == NULL)//cây chưa có nút nào
	{
		pTree = new WarriorTree;
		pTree->pLeftChild = node.pLeftChild;
		pTree->pRightChild = node.pRightChild;
		pTree->balance = node.balance;
		pTree->token = node.token;
		pTree->strength = node.strength;

		return pTree;
	}
	else//cây đã có một số nút
	{
		if (pTree->token == node.token)//nếu tìm được một node có khóa bằng khóa của nút mới
		{
			node.token = (node.token + 1) % MAX_NUM_NODE;//tăng khóa lên 1
			
			nCount++;
			if (nCount > MAX_NUM_NODE)
				//kiểm tra số lần tăng giá trị khóa, nếu quá giới hạn thì coi như đề bài sai vì cây sẽ có quá 1000 nút
			{
				printf("input file's format is not correct \n");
				return NULL;
			}

			return InsertNodeToBST(pTree, node);//Thực hiện lại việc chèn với nút có giá trị khóa mới
		}
		else if (pTree->token < node.token)
		{
			//Chèn vào cây con phải
			pTree->pRightChild = InsertNodeToBST(pTree->pRightChild, node);
			return pTree;
		}
		else if (pTree->token > node.token)
		{
			//Chèn vào cây con trái
			pTree->pLeftChild = InsertNodeToBST(pTree->pLeftChild, node);
			return pTree;
		}
	}
}

WarriorTree* ProcessEvent1(WarriorTree* pTree, int nFirstParam, int nSecondParam)
{
	WarriorTree node;
	
	node.pLeftChild = NULL;
	node.pRightChild = NULL;
	node.token = nFirstParam;
	node.strength = nSecondParam;
	node.balance = 0;

	return InsertNodeToBST(pTree, node);
}

void ProcessEvent2(WarriorTree* pTree, int nFirstParam, int nSecondParam)
{
	
}

void ProcessEvent3(WarriorTree* pTree, int nFirstParam, int nSecondParam)
{

}
void ProcessEvent4(WarriorTree* pTree, int nFirstParam, int nSecondParam)
{

}
void ProcessEvent5(WarriorTree* pTree, int nFirstParam, int nSecondParam)
{

}
void ProcessEvent6(WarriorTree* pTree, int nFirstParam, int nSecondParam)
{

}
void ProcessEvent7(WarriorTree* pTree, int nFirstParam, int nSecondParam)
{

}
void ProcessEvent8(WarriorTree* pTree, int nFirstParam, int nSecondParam)
{

}
void ProcessEvent9(WarriorTree* pTree, int nFirstParam, int nSecondParam)
{

}


WarriorTree*  revenge(eventList* pEvent)
{
	WarriorTree* pTree = NULL; 
	//to do
	eventList* pCurrent;

	pCurrent = pEvent;
	while (pCurrent != NULL)
	{
		switch (pCurrent->nEventCode)
		{
			case 1:
				pTree = ProcessEvent1(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
			case 2:
				ProcessEvent2(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
			case 3:
				ProcessEvent3(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
			case 4:
				ProcessEvent4(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
			case 5:
				ProcessEvent5(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
			case 6:
				ProcessEvent6(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
			case 7:
				ProcessEvent7(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
			case 8:
				ProcessEvent8(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
			case 9:
				ProcessEvent9(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
		}
		pCurrent = pCurrent->pNext;
	}
	return pTree;
}

//your code should be before that directive
#endif
