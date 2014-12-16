#ifndef _adventure_cpp_
#define _adventure_cpp_

#include "defs.h"

//your code should be after that directive
#define MAX_NUM_NODE	1000
#define MARK_HIRGON_STRENGTH 1000

WarriorTree *g_pList, *g_pLastNode;
WarriorTree g_nodeHigon, g_nodeLithariel;
bool g_bHirgon, g_bLithariel;


//Kiểm tra số nguyên tố
bool IsAtomic(int n)
{
	double d;
	d = sqrt(1.0 * n);
	for (int i = 2; i <= d; i++)
		if (n % i == 0)
			return false;
	return true;
}

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

//Tạo nút cho cây từ 2 tham số: khóa và chỉ số sức mạnh
WarriorTree* MakeNodeWithPoint(int nFirstParam, int nSecondParam)
{
	WarriorTree* pNode;
	
	pNode = new WarriorTree;

	pNode->pLeftChild = NULL;
	pNode->pRightChild = NULL;
	pNode->token = nFirstParam;
	pNode->strength = nSecondParam;
	pNode->balance = 0;

	return pNode;
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
WarriorTree* InsertNodeToBST(WarriorTree* pTree, WarriorTree* pNode)
{
	if (pTree == NULL)//cây chưa có nút nào
	{
		pTree = pNode;

		return pTree;
	}
	else//cây đã có một số nút
	{
		if (pTree->token == pNode->token)//nếu tìm được một node có khóa bằng khóa của nút mới
		{
			pNode->token = (pNode->token + 1) % MAX_NUM_NODE;//tăng khóa lên 1

			return InsertNodeToBST(pTree, pNode);//Thực hiện lại việc chèn với nút có giá trị khóa mới
		}
		else if (pNode->token > pTree->token)
		{
			//Chèn vào cây con phải
			pTree->pRightChild = InsertNodeToBST(pTree->pRightChild, pNode);
			return pTree;
		}
		else if (pNode->token < pTree->token)
		{
			//Chèn vào cây con trái
			pTree->pLeftChild = InsertNodeToBST(pTree->pLeftChild, pNode);
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

WarriorTree* ReleaseTree(WarriorTree* pTree)
{
	if (pTree == NULL)
		return NULL;

	ReleaseTree(pTree->pLeftChild);
	ReleaseTree(pTree->pRightChild);

	delete (pTree);
	
	return NULL;
}

//Hàm tạo danh sách duyệt LNR từ cây
void MakeListLNR(WarriorTree* pTree)
{
	WarriorTree* pNewNode;

	if (pTree == NULL)
		return;

	MakeListLNR(pTree->pLeftChild);

	pNewNode = MakeNodeWithPoint(pTree->token, pTree->strength);
	
	if (g_pList == NULL)
	{
		g_pList = pNewNode;
		g_pLastNode = pNewNode;
	}
	else
	{
		g_pLastNode->pRightChild = pNewNode;
		g_pLastNode = pNewNode;
	}

	MakeListLNR(pTree->pRightChild);
	
}

WarriorTree* ProcessEvent1(WarriorTree* pTree, int nFirstParam, int nSecondParam)
{
	WarriorTree* pNode;
	
	pNode = MakeNodeWithPoint(nFirstParam, nSecondParam);

	return InsertNodeToBST(pTree, pNode);
}

WarriorTree* ProcessEvent2(WarriorTree* pTree, int nTokenSearch, int nNewStrength)
{
	WarriorTree* pNodeNearest;

	pNodeNearest = FindNearestNode(pTree, nTokenSearch);
	if (pNodeNearest != NULL)
	{
		pNodeNearest->strength = nNewStrength;
		if (pNodeNearest->token == g_nodeHigon.token)
			g_nodeHigon.strength = nNewStrength;
	}

	return pTree;
}

WarriorTree* ProcessEvent3(WarriorTree* pTree, int nTokenSearch, int nStrengthEnemy)
{
	WarriorTree* pNodeNearest;

	pNodeNearest = FindNearestNode(pTree, nTokenSearch);
	if (pNodeNearest != NULL)
	{
		if ((pNodeNearest->strength >= nStrengthEnemy)
			|| (g_bHirgon && (pNodeNearest->strength == g_nodeHigon.strength))
			|| IsAtomic(pNodeNearest->token))//Chiến binh không bị loại
		{//không làm gì
		}
		else
		{
			if (pNodeNearest->token == g_nodeHigon.token)//Hirgon bị loại
			{
				g_bHirgon = false;
				g_nodeHigon.token = -1;
				g_nodeHigon.strength = -1;
			}
			pTree = DeleteNode(pTree, pNodeNearest);	
		}
	}

	return pTree;
}

WarriorTree* ProcessEvent4(WarriorTree* pTree, int nTokenHirgon, int nStrengthHirgon)
{
	WarriorTree* pNode, *pTemp, *pNewTemp;

	if (!g_bLithariel)
	{
		pNode = MakeNodeWithPoint(nTokenHirgon, nStrengthHirgon);
		
		g_pList = ReleaseTree(g_pList);
		g_pLastNode = NULL;

		MakeListLNR(pTree);
		pTree = ReleaseTree(pTree);

		pTree = pNode;
		
		pTemp = g_pList;
		while (pTemp != NULL)
		{
			pNewTemp = pTemp->pRightChild;
			pTemp->pRightChild = NULL;
			pTemp->pLeftChild = NULL;
			pTree = InsertNodeToBST(pTree, pTemp);
			pTemp = pNewTemp;
		}
	}
	else
	{
		pTree = ProcessEvent1(pTree, nTokenHirgon, nStrengthHirgon);
	}

	g_bHirgon = true;
	g_nodeHigon.token = nTokenHirgon;
	g_nodeHigon.strength = nStrengthHirgon;

	return pTree;
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

	g_pList = NULL;
	g_pLastNode = NULL;

	g_bHirgon = false;
	g_nodeHigon.token = -1;
	g_nodeHigon.strength = -1;

	g_bLithariel = false;
	g_nodeLithariel.token = -1;
	g_nodeLithariel.strength = -1;

	pCurrent = pEvent;
	while (pCurrent != NULL)
	{
		switch (pCurrent->nEventCode)
		{
			case 1:
				pTree = ProcessEvent1(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
			case 2:
				pTree = ProcessEvent2(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
			case 3:
				pTree = ProcessEvent3(pTree, pCurrent->firstArg, pCurrent->secondArg);
				break;
			case 4:
				pTree = ProcessEvent4(pTree, pCurrent->firstArg, pCurrent->secondArg);
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
