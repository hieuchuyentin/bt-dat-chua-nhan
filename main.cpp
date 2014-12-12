#include "defs.h"

//read data from input file to corresponding variables
//return 1 if successfully done, otherwise return 0
int readFile(FILE* f, eventList*& pEvent)
{
	char c = ' ';
	int eventCode;
	int firstArg=0;
	int secondArg=0;
	eventList* tail = NULL;

	while (c != -1 && !feof(f))
	{
		while (c < '0' || c > '9')
		{
			c = fgetc(f);
		}

		eventCode = c - '0';
		firstArg=secondArg=0;

		//first '_'
		c = fgetc(f);
		if(c!='_')
			return 0;

		switch(eventCode)
		{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 8:
				//XYZ param
				for(int i =0;i<3;i++)
				{
					c = fgetc(f);
					if(c < '0' || c > '9')
						return 0;
					firstArg = firstArg*10 + c-'0';
				}
				//the second '_'
				c = fgetc(f);
				if(c!='_')
					return 0;

				//the second param
				c = fgetc(f);
				if(c < '0' || c > '9')
						return 0;
				secondArg = c-'0';
				break;
			case 6:
			case 7:
				c = fgetc(f);
				if(c < '0' || c > '9')
						return 0;
				firstArg = c-'0';
				break;
			case 9:
				//XYZ param
				for(int i =0;i<3;i++)
				{
					c = fgetc(f);
					if(c < '0' || c > '9')
						return 0;
					firstArg = firstArg*10 + c-'0';
				}
				break;
			default:
				return 0;
		}

		//create new Event
		eventList* current_event = new eventList();
		current_event->nEventCode = eventCode;
		current_event->firstArg = firstArg;
		current_event->secondArg = secondArg;
		current_event->pNext = NULL;
		
		//add to tail of the list
		if (pEvent == NULL)
			pEvent = current_event;
		if (tail != NULL)
			tail->pNext = current_event;
		tail = current_event;

		//check for next event
		c = fgetc(f);
		if(c != -1 && !feof(f))
		{
			if(c!='\r'&&c!='\n'&&c!=' ')
				return 0;
		}
	}
	return 1;
}

void display(WarriorTree* pTree, int n)
{
	cout.flush();
	if (pTree)
	{ 
		cout<<"(";
		cout << setw(3) << setfill('0') << pTree->token;
		cout<<"_";
		cout << pTree->strength; 
		cout<<" ";
		display(pTree->pLeftChild,++n);
		cout<<" ";
		display(pTree->pRightChild,++n);
		cout<<")";
	}
	else
		cout<<"N";
}


int main()
{
   // initialize the input file
	char* file_name = (char*)"input.txt";
	FILE* f = fopen(file_name, "r");
	if (f == NULL)	//file not found or cannot read
	{
		printf("File not found \n");
		return 0;
	}

	eventList* pEvent = NULL;
	WarriorTree* pFinalTree = NULL;     
	
	if(readFile(f, pEvent)==0)
	{
		printf("input file's format is not correct \n");
		return 0;
	}

	// your main implemented code is called here
	pFinalTree = revenge(pEvent);

	//display the final result tree
	display(pFinalTree,0);
   
   return 0;
}
