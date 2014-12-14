#ifndef _adventure_cpp_
#define _adventure_cpp_

#include "defs.h"

//your code should be after that directive
#define MAX_NUM_NODE	1000

//Tạo nút cho cây từ 2 tham số: khóa và chỉ số sức mạnh
WarriorTree MakeNode(int nFirstParam, int nSecondParam)
{
	WarriorTree node;

	node.pLeftChild = NULL;
	node.pRightChild = NULL;
	node.token = nFirstParam;
	node.strength = nSecondParam;
	node.balance = 0;

	return node;
}

//Hàm tìm cha của một nút
WarriorTree* FindFather(WarriorTree* pTree, WarriorTree* pNode)
{
	if (pTree == NULL)
		return NULL;

	if (pTree->token == pNode->token)
		return NULL;

	if (pTree->pLeftChild != NULL)
	{
		if (pTree->pLeftChild->token == pNode->token)
			return pTree;
	}

	if (pTree->pRightChild != NULL)
	{
		if (pTree->pRightChild->token == pNode->token)
			return pTree;
	}

	if (pNode->token < pTree->token)
		//Tìm tiếp theo cây con trái
		return FindFather(pTree->pLeftChild, pNode);

	if (pNode->token > pTree->token)
		//Tìm tiếp theo cây con phải
		return FindFather(pTree->pRightChild, pNode);

	return NULL;
}

//Hàm tìm giá trị khóa gần với tham số đầu vào nhất
WarriorTree* FindNearestNode(WarriorTree* pTree, int nTokenSearch)
{
	WarriorTree* pNodeResult, *pNodeTemp;

	if (pTree == NULL)
		return NULL;

	if (pTree->token == nTokenSearch)
		return pTree;

	pNodeResult = pTree;
	
	if (nTokenSearch < pTree->token)
	{
		pNodeTemp = FindNearestNode(pTree->pLeftChild, nTokenSearch);
		if (pNodeTemp != NULL)
		{
			if (abs(pNodeTemp->token - nTokenSearch) <= abs(pNodeResult->token - nTokenSearch))
				//dùng dấu <= vì ưu tiên khóa nhỏ hơn
			{
				pNodeResult = pNodeTemp;
			}
		}
	}

	if (nTokenSearch > pTree->token)
	{
		pNodeTemp = FindNearestNode(pTree->pRightChild, nTokenSearch);
		if (pNodeTemp != NULL)
		{
			if (abs(pNodeTemp->token - nTokenSearch) < abs(pNodeResult->token - nTokenSearch))
				//dùng dấu < vì nếu khóa lớn hơn thì khoảng cách phải nhỏ hơn thực sự thì mới chọn
			{
				pNodeResult = pNodeTemp;
			}
		}
	}

	return pNodeResult;
}

//Hàm chèn một nút vào cây nhị phân, nút có thể là gốc của một cây
//Trả lại giá trị là con trỏ tới nút gốc của cây mới
WarriorTree* InsertNodeToBST(WarriorTree* pTree, WarriorTree node)
{
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

			return InsertNodeToBST(pTree, node);//Thực hiện lại việc chèn với nút có giá trị khóa mới
		}
		else if (node.token > pTree->token)
		{
			//Chèn vào cây con phải
			pTree->pRightChild = InsertNodeToBST(pTree->pRightChild, node);
			return pTree;
		}
		else if (node.token < pTree->token)
		{
			//Chèn vào cây con trái
			pTree->pLeftChild = InsertNodeToBST(pTree->pLeftChild, node);
			return pTree;
		}
	}
	return pTree;
}
//Hàm tìm nút lớn nhất trong cây
WarriorTree* FindMax(WarriorTree* pTree)
{
	WarriorTree* pTemp;

	if (pTree == NULL)
		return NULL;

	pTemp = pTree;
	while (pTemp->pRightChild != NULL)
		pTemp = pTemp->pRightChild;

	return pTemp;
}

//Hàm tìm nút nhỏ nhất trong cây
WarriorTree* FindMin(WarriorTree* pTree)
{
	WarriorTree* pTemp;

	if (pTree == NULL)
		return NULL;

	pTemp = pTree;
	while (pTemp->pLeftChild != NULL)
		pTemp = pTemp->pLeftChild;

	return pTemp;
}

//Hàm xóa nút của cây
WarriorTree* DeleteNode(WarriorTree* pTree, WarriorTree* pNode)
{
	WarriorTree* pTemp;

	if ((pTree == NULL) || (pNode == NULL))
		return NULL;

	if (pNode->token < pTree->token)
		//đi tiếp theo cây con trái
	{
		pTree->pLeftChild = DeleteNode(pTree->pLeftChild, pNode);
		return pTree;
	}

	if (pNode->token > pTree->token)
		//đi tiếp theo cây con phải
	{
		pTree->pRightChild = DeleteNode(pTree->pRightChild, pNode);
		return pTree;
	}

	//Đây là trường hợp pTree chính là nút cần xóa
	if ((pTree->pLeftChild == NULL) || (pTree->pRightChild == NULL))
		//trường hợp 1, 2, 3
	{
		pTemp = pTree;

		if (pTree->pLeftChild != NULL)
		{
			pTree = pTree->pLeftChild;
		}
		else
		{
			pTree = pTree->pRightChild;
		}

		delete pTemp; 
		return pTree;
	}
	else
		//trường hợp 4: nút có 2 con
	{
		pTemp = FindMax(pTree->pLeftChild);
		pTree->token = pTemp->token;
		pTree->strength = pTemp->strength;
		pTree->pLeftChild = DeleteNode(pTree->pLeftChild, pTemp);

		return pTree;
	}
	
	return pTree;
}

WarriorTree* ProcessEvent1(WarriorTree* pTree, int nFirstParam, int nSecondParam)
{
	WarriorTree node;
	
	node = MakeNode(nFirstParam, nSecondParam);

	return InsertNodeToBST(pTree, node);
}

void ProcessEvent2(WarriorTree* pTree, int nTokenSearch, int nNewStrength)
{
	WarriorTree* pNodeNearest;

	pNodeNearest = FindNearestNode(pTree, nTokenSearch);
	if (pNodeNearest != NULL)
	{
		pNodeNearest->strength = nNewStrength;
	}
}

void ProcessEvent3(WarriorTree* pTree, int nTokenSearch, int nStrengthEnemy)
{
	WarriorTree* pNodeNearest;

	pNodeNearest = FindNearestNode(pTree, nTokenSearch);
	if (pNodeNearest != NULL)
	{
		if (pNodeNearest->strength >= nStrengthEnemy)//Chiến binh không bị loại
			return;
		else
		{
			DeleteNode(pTree, pNodeNearest);	
		}
	}
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
