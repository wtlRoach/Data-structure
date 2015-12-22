#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*================================================================================================*/
/* Test field. */
/*================================================================================================*/

#define MOVE_POS (0x1u <<8)
#define TEST_AREA 0

/*================================================================================================*/

/*================================================================================================*/
/* Maze and Mouse. */
/*================================================================================================*/

int pathRec[12][12];
int maze[12][12]={

/*Static exit*/
/*
{1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,1,0,0,0,0,0,0,1},
{0,0,1,0,1,0,1,1,1,1,0,1},
{1,1,1,0,1,0,0,0,0,1,0,1},
{1,0,0,0,0,1,1,1,0,1,0,0},
{1,1,1,1,0,1,0,1,0,1,0,1},
{1,0,0,1,0,1,0,1,0,1,0,1},
{1,1,0,1,0,1,0,1,0,1,0,1},
{1,0,0,0,0,0,0,0,0,1,0,1},
{1,1,1,1,1,1,0,1,1,1,0,1},
{1,0,0,0,0,0,0,1,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1}
};
*/
/*Dynamic exit*/

{1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,1,0,0,0,0,0,0,1},
{0,0,1,0,1,0,1,1,1,1,0,1},
{1,1,1,0,1,0,0,0,0,1,0,1},
{1,0,0,0,0,1,1,1,0,1,0,1},
{1,1,1,1,0,1,0,1,0,1,0,1},
{1,0,0,1,0,1,0,1,0,1,0,1},
{1,1,0,1,0,1,0,1,0,1,0,1},
{1,0,0,0,0,0,0,0,0,1,0,1},
{1,1,1,1,1,1,0,1,1,1,0,1},
{1,0,0,0,0,0,0,1,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1}
};
int* mouseMove(int PosY, int PosX){
    int buf[2] = {PosY, PosX};
	if(maze[buf[0]-1][(buf[1])] != 1 && pathRec[buf[0]-1][(buf[1])] < 1)
	{
		buf[0] = buf[0]-1;
	}
	else if (maze[(buf[0])][buf[1]+1] != 1 && pathRec[buf[0]][(buf[1]+1)] < 1)
	{
		buf[1] = buf[1]+1;
	}
	else if (maze[buf[0]+1][(buf[1])] != 1 && pathRec[buf[0]+1][(buf[1])] < 1)
	{
		buf[0] = buf[0]+1;
	}
	else if (maze[(buf[0])][buf[1]-1] != 1 && pathRec[buf[0]][(buf[1]-1)] < 1)
	{
		buf[1] = buf[1]-1;
	}
	else /*沒路可走退回之前走過的地方*/
    {
        pathRec[buf[0]][(buf[1])] = 2;
        if(pathRec[buf[0]-1][(buf[1])] == 1)
        {
            buf[0] = buf[0]-1;
        }
        else if(pathRec[buf[0]][(buf[1]+1)] == 1)
        {
            buf[1] = buf[1]+1;
        }
        else if(pathRec[buf[0]+1][(buf[1])] == 1)
        {
            buf[0] = buf[0]+1;
        }
        else if(pathRec[buf[0]][(buf[1]-1)] == 1)
        {
            buf[1] = buf[1]-1;
        }
        else
        {
            printf("No way.\n");
        }
    }
    return buf;
}
void MouseGO(){
    int nowPosX = 0;
	int nowPosY = 2;
    int endPosY = 9;        /* Using for dynamic exit. */
    int endPosX = 11;       /* Using for dynamic exit. */

	int *buf;
	int isEnd = 0;
	int prtIndexX = 0;
	int prtIndexY = 0;
	memset(pathRec, 0, sizeof(pathRec));
	maze[endPosY][endPosX] = 0;

	pathRec[nowPosY][nowPosX] = 1;

	while(!isEnd)
	{
		buf = mouseMove(nowPosY, nowPosX);
		nowPosY = buf[0];
		nowPosX = buf[1];
		if(pathRec[buf[0]][buf[1]] == 0)
		{
			pathRec[buf[0]][buf[1]] = 1;
		} else {}
		if(buf[0] == endPosY && buf[1] == endPosX )
		{
			isEnd = 1;
		} else {}
		printf("Mouse through X:%d, Y:%d\n",nowPosX,nowPosY);
	}

    for(prtIndexY = 0;prtIndexY<12;prtIndexY++)
    {
        for(prtIndexX =0;prtIndexX<12;prtIndexX++)
        {
            if(pathRec[prtIndexY][prtIndexX] == 2)
            {
                pathRec[prtIndexY][prtIndexX]=0;
            } else {}
            printf(" %d ",pathRec[prtIndexY][prtIndexX]);
        }
        printf("\n");
    }
}

/*================================================================================================*/

/*================================================================================================*/
/* AddNode can't run correctly, but AddNode can show the correct result if we used debug */
/* step-by-step when function is executing. Using leftNull prevent bugs from CodeBlocks, they'll */
/* be removed when I figure out what's going with the error of NULL. */
/*================================================================================================*/

typedef enum t_BinaryMethodType{
    m_inOrder,
    m_preOrder,
    m_postOrder,
    m_levelOrder
}t_BinaryMethodType;
typedef struct t_TreeNode{
    int m_nodeData;
    int m_leftNull;       /*For test*/
    int m_rightNull;      /*For test*/
    struct tree * m_leftPtr;
    struct tree * m_rightPtr;
}t_TreeNode;
typedef enum t_HeapType{
    m_MAX,
    m_MIN
}t_HeapType;

typedef t_TreeNode* btTree;        /* For convenience of pointer operation. */

static btTree g_DataTree;                /*The value here is not zero inside the function.*/
static btTree g_CopyTree;
static btTree g_threadTree;

/*======================================Binary tree create========================================*/

btTree AddNode(btTree addDataTree, int nodeData){    /* Using flag replace NULL pointer. */

    btTree previousNode;
    btTree currentNode = addDataTree;
    btTree outputTreeBuf;

    btTree newNode = (btTree)malloc(sizeof(btTree));
    newNode -> m_nodeData = nodeData;
    newNode -> m_leftNull = 1;
    newNode -> m_rightNull = 1;

    if(currentNode == NULL)
    {
        currentNode = newNode;
        printf("Null currentNode->data = %d, nodeData = %d\n", currentNode -> m_nodeData, newNode -> m_nodeData);
        return currentNode;                     /* tarTree can't be rewritten in this function, so here we return currentNode if tarTree is a tree with only one element. */
    }
    else
    {
        outputTreeBuf = currentNode;
        previousNode = currentNode;
        while(currentNode != NULL)
        {
            previousNode = currentNode;
            if(currentNode -> m_nodeData < nodeData && !(currentNode -> m_leftNull))
            {
                currentNode = currentNode -> m_leftPtr;
            }
            else if (currentNode -> m_nodeData > nodeData && !(currentNode -> m_rightNull))
            {
                currentNode = currentNode -> m_rightPtr;
            } else {break;}
        }

        if(previousNode -> m_nodeData < nodeData)
        {
            previousNode -> m_leftPtr = newNode;
            previousNode -> m_leftNull = 0;
            printf("Left Data: %d\n", newNode -> m_nodeData);
        }
        else if (previousNode -> m_nodeData > nodeData)
        {
            previousNode -> m_rightPtr = newNode;
            previousNode -> m_rightNull = 0;
            printf("Right Data: %d\n", newNode -> m_nodeData);
        } else {}
        return outputTreeBuf;
    }
}

void BinaryTreeCreate(void){             /* Create binary tree which only has left side. */

    int index = 0;
    int dataLen = 8;
    int dataTest[8] = {1,5,4,3,2,6,7,8};
    for(index = 0; index < dataLen; index ++)
    {
        g_DataTree = AddNode(g_DataTree, dataTest[index]);    /* Insert data from beginning. */
        printf("Index : %d\n", index);
    }

}

/*======================================Binary tree visit=========================================*/

void InorderPrintTree(btTree inorderDataTree){    /* Root in the middle. */

    if (inorderDataTree != NULL)
    {
        if (!(inorderDataTree -> m_leftNull))
        {
            InorderPrintTree(inorderDataTree -> m_leftPtr);
        } else {}
        printf("Element : %d\n", inorderDataTree -> m_nodeData);
        if (!(inorderDataTree -> m_rightNull))
        {
            InorderPrintTree(inorderDataTree -> m_rightPtr);
        } else {}
    } else {}
}

void PreorderPrintTree(btTree preorderDataTree){    /* Root in the first place. */

    if (preorderDataTree != NULL)
    {
        printf("Element : %d\n", preorderDataTree -> m_nodeData);
        if (!(preorderDataTree -> m_leftNull))
        {
            PreorderPrintTree(preorderDataTree -> m_leftPtr);
        } else {}
        if(!(preorderDataTree -> m_rightNull))
        {
            PreorderPrintTree(preorderDataTree -> m_rightPtr);
        } else {}
    } else {}
}

void PostorderPrintTree(btTree postorderDataTree){    /* Root in the last place. */

    if(postorderDataTree != NULL)
    {
        if (!(postorderDataTree -> m_leftNull))
        {
            PostorderPrintTree(postorderDataTree -> m_leftPtr);
            printf("Element : %d\n", postorderDataTree -> m_nodeData);
        } else {}
        if(!(postorderDataTree -> m_rightNull))
        {
            PostorderPrintTree(postorderDataTree -> m_rightPtr);
            printf("Element : %d\n", postorderDataTree -> m_nodeData);
        } else {}
        if((postorderDataTree -> m_leftNull) && (postorderDataTree -> m_rightNull))
        {
            printf("Element : %d\n", postorderDataTree -> m_nodeData);
        } else {}
    } else {}
}

void LevelorderPrintTree(btTree levelorderDataTree){ /* Using the continuity of pointer data set to visit all nodes. */

    int printedF = -1;
    int printedB = -1;
    t_TreeNode* treeBuf[80];

    if(levelorderDataTree -> m_leftNull && levelorderDataTree -> m_rightNull)
    {
        printf("Empty tree.\n");
        return;
    } else {}

    ++ printedB;
    treeBuf[printedB] = levelorderDataTree; /* Put first tree data in the buffer. */

    while(printedB != printedF)
    {
        ++printedF;
        if(treeBuf[printedF] != NULL)
        {
            printf("Data : %d\n",(treeBuf[printedF]) -> m_nodeData); /* Print previous data. */
            if(!(treeBuf[printedF] -> m_leftNull)) /* Still has left child. */
            {
                treeBuf[++printedB] = treeBuf[printedF] -> m_leftPtr; /* Empty space in buffer point to left. */
            } else {}
            if(!(treeBuf[printedF] -> m_rightNull)) /* Still has left child. */
            {
                treeBuf[++printedB] = treeBuf[printedF] -> m_rightPtr; /* Empty space in buffer point to right. */
            } else {}
        } else {}
    }
}

void VisitBinaryTree(btTree dataTree, t_BinaryMethodType visitType){

    switch(visitType)
    {
        case 0:
            InorderPrintTree(dataTree);
            break;
        case 1:
            PreorderPrintTree(dataTree);
            break;
        case 2:
            PostorderPrintTree(dataTree);
            break;
        case 3:
            LevelorderPrintTree(dataTree);
            break;
    };
}

/*======================================Binary tree copy==========================================*/

btTree InorderCopyTree(btTree inorderSourceTree){

    if(inorderSourceTree == NULL)
    {
        printf("Data tree is empty.\n");
        return;
    } else {}
    if(!inorderSourceTree -> m_leftNull)
    {
        g_CopyTree -> m_leftPtr = InorderCopyTree(inorderSourceTree -> m_leftPtr);
        g_CopyTree -> m_leftNull = 0;
    } else {}
    g_CopyTree -> m_nodeData = inorderSourceTree -> m_nodeData;
    printf("Data from InorderCopyTree : %d\n", g_CopyTree -> m_nodeData);

    if(!inorderSourceTree -> m_rightNull)
    {
        g_CopyTree -> m_rightPtr = InorderCopyTree(inorderSourceTree -> m_rightPtr);
        g_CopyTree -> m_rightNull = 0;
    } else {}
    return g_CopyTree;
}

btTree PreorderCopyTree(btTree preorderSourceTree){

    if(preorderSourceTree == NULL)
    {
        printf("Data tree is empty.\n");
        return;
    } else {}
    g_CopyTree -> m_nodeData = preorderSourceTree -> m_nodeData;
    printf("Data from PreorderCopyTree : %d\n", g_CopyTree -> m_nodeData);
    if(!preorderSourceTree -> m_leftNull)
    {
        g_CopyTree -> m_leftPtr = PreorderCopyTree(preorderSourceTree -> m_leftPtr);
        g_CopyTree -> m_leftNull = 0;
    } else {}

    if(!preorderSourceTree -> m_rightNull)
    {
        g_CopyTree -> m_rightPtr = PreorderCopyTree(preorderSourceTree -> m_rightPtr);
        g_CopyTree -> m_rightNull = 0;
    } else {}
    return g_CopyTree;
}

btTree PostorderCopyTree(btTree postorderSourceTree){

    if(postorderSourceTree == NULL)
    {
        printf("Data tree is empty.\n");
        return;
    } else {}

    if(!postorderSourceTree -> m_leftNull)
    {
        g_CopyTree -> m_leftPtr = PreorderCopyTree(postorderSourceTree -> m_leftPtr);
        g_CopyTree -> m_leftNull = 0;
    } else {}

    if(!postorderSourceTree -> m_rightNull)
    {
        g_CopyTree -> m_rightPtr = PreorderCopyTree(postorderSourceTree -> m_rightPtr);
        g_CopyTree -> m_rightNull = 0;
    } else {}

    g_CopyTree -> m_nodeData = postorderSourceTree -> m_nodeData;
    printf("Data from PostorderCopyTree : %d\n", g_CopyTree -> m_nodeData);

    return g_CopyTree;
}

void CopyBinaryTree(btTree dataTree, t_BinaryMethodType visitType){

    g_CopyTree = malloc(sizeof(t_TreeNode));                /* Initialize memory space for operating. */
    switch(visitType)
    {
        case 0:
            InorderCopyTree(dataTree);
            break;
        case 1:
            PreorderCopyTree(dataTree);
            break;
        case 2:
            PostorderCopyTree(dataTree);
            break;
    };
}

/*=====================================Binary tree compare=========================================*/

int CompareBinaryTree(btTree dataTreeOne, btTree dataTreeTwo){
    int compareResult = 0;
    compareResult = ((dataTreeOne && dataTreeTwo) || (!dataTreeOne && !dataTreeTwo)) ||                                                      /* Same address in memory. */
                        (((dataTreeOne -> m_nodeData && dataTreeTwo -> m_nodeData)) &&                                                       /* Same data. */
                            ((CompareBinaryTree(dataTreeOne -> m_leftPtr, dataTreeTwo -> m_leftPtr))) &&              /* Compare the left node. */
                                ((CompareBinaryTree(dataTreeOne -> m_rightPtr, dataTreeTwo -> m_rightPtr))));       /* Compare the right node. */
    return compareResult;
}

/*=====================================Thread binary tree==========================================*/

#if TEST_AREA

btTree ThreadLoop(btTree originalDataTree){             /* Declare function before using.*/
    btTree treeBuf = originalDataTree;
    if(!(originalDataTree -> m_leftNull))
    {
        treeBuf -> m_leftPtr  = ThreadLoop(originalDataTree -> m_leftPtr);
        printf("Thread direction: %d, Root : %d\n",(treeBuf -> m_leftPtr) -> m_nodeData, originalDataTree -> m_nodeData);
        return treeBuf;
    }
    else
    {
        treeBuf = originalDataTree;
        return treeBuf;
    }
    if(!(originalDataTree -> m_rightNull))
    {
        treeBuf -> m_rightPtr = ThreadLoop(originalDataTree -> m_rightPtr);
        return treeBuf;
    }
    else
    {
        treeBuf = originalDataTree;
        return treeBuf;
    }
}

void ThreadBinaryTree(btTree originalDataTree){
    g_threadTree = malloc(sizeof(t_TreeNode));                /* Initialize memory space for operating. */
    g_threadTree = ThreadLoop(originalDataTree);
}

#endif

/*===========================================Heap=================================================*/

void ExchangeNodes(t_TreeNode* nodeOne, t_TreeNode* nodeTwo) {
    t_TreeNode* treeBuf = malloc(sizeof(t_TreeNode));
    treeBuf = nodeOne;
    nodeOne = nodeTwo;
    nodeTwo = treeBuf;
}

btTree CheckNodeMax(btTree dataTree) {
    t_TreeNode* treeBuf = dataTree;
    if(!(treeBuf -> m_leftNull))
    {
        treeBuf = CheckNodeMax(treeBuf -> m_leftPtr);
        if(treeBuf -> m_nodeData > dataTree -> m_nodeData)
        {
            ExchangeNodes(treeBuf, dataTree);
        }
        else {}
    }
    else
    {
        return treeBuf;
    }
    if(!(treeBuf -> m_rightNull))
    {
        treeBuf = CheckNodeMax(treeBuf -> m_rightPtr);
        if(treeBuf -> m_nodeData > dataTree -> m_nodeData)
        {
            ExchangeNodes(treeBuf, dataTree);
        }
        else {}
    }
    else
    {
        return treeBuf;
    }
}

btTree CheckNodeMin(btTree dataTree) {
    t_TreeNode* treeBuf = dataTree;
    if(!(treeBuf -> m_leftNull))
    {
        treeBuf = CheckNodeMin(treeBuf -> m_leftPtr);
        if(treeBuf -> m_nodeData < dataTree -> m_nodeData)
        {
            ExchangeNodes(treeBuf, dataTree);
        }
        else {}
    }
    else
    {
        return treeBuf;
    }
    if(!(treeBuf -> m_rightNull))
    {
        treeBuf = CheckNodeMin(treeBuf -> m_rightPtr);
        if(treeBuf -> m_nodeData < dataTree -> m_nodeData)
        {
            ExchangeNodes(treeBuf, dataTree);
        }
        else {}
    }
    else
    {
        return treeBuf;
    }
}

void BinaryTreeHeap(btTree dataTree, t_HeapType heapType){
    t_TreeNode* treeBuf = dataTree;
    treeBuf = heapType? CheckNodeMin(treeBuf):CheckNodeMax(treeBuf);
}

/*================================================================================================*/

/*================================================================================================*/
/* Main program */
/*================================================================================================*/

int main(int argc, char *argv[]) {
    /* Maze with Mouse */
    /*MouseGO();*/

    /* Binary tree */
    BinaryTreeCreate();
    /*VisitBinaryTree(g_DataTree, m_inOrder);*/
    /*CopyBinaryTree(g_DataTree, m_inOrder);*/
    /*ThreadBinaryTree(g_DataTree);*/
    BinaryTreeHeap(g_DataTree, m_MAX);
    VisitBinaryTree(g_DataTree, m_preOrder);

	system("pause");
	return 0;
}


