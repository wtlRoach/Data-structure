#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*================================================================================================*/
/* Test field. */
/*================================================================================================*/

#define MOVE_POS (0x1u <<8)

void testField(unsigned int testVar)
{
    unsigned int testResult = testVar;
    testResult &= MOVE_POS;
    printf(" testVar = %d\n", testVar);
    printf(" testResult = %d\n", testResult);
}

/*================================================================================================*/

/*================================================================================================*/
/* Maze and Mouse. */
/*================================================================================================*/

int pathRec[12][12];
int maze[12][12]=

/*Static exit*/
/*{
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
{
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

int* mouseMove(int PosY, int PosX)
{
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

void MouseGO()
{
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
/* AddNode can't run correctly, but AddNodeTest can show the correct result if we used debug */
/* step-by-step when function is executing. */
/*================================================================================================*/

typedef enum t_BinaryMethodType
{
    m_inOrder,
    m_preOrder,
    m_postOrder,
    m_levelOrder
}t_BinaryMethodType;


typedef struct tree{
    int m_nodeData;
    int m_leftNull;       /*For test*/
    int m_rightNull;      /*For test*/
    struct tree * m_leftPtr;
    struct tree * m_rightPtr;
}t_TreeNode;

typedef t_TreeNode* btTree;        /* For convenience of pointer operation. */

btTree g_DataTree;                /*The value here is not zero inside the function.*/


/*======================================Binary tree create========================================*/

btTree AddNode(btTree dataTree, int nodeData)               /* Null is illegal in this IDE, so this function seems correct but it can't be worked. */
{
    btTree previousNode;
    btTree currentNode = dataTree;
    btTree outputTreeBuf;

    btTree newNode = (btTree)malloc(sizeof(btTree));
    newNode -> m_nodeData = nodeData;
    if(currentNode == NULL)
    {
        currentNode = newNode;
        printf("Null currentNode->data = %d, nodeData = %d\n", currentNode -> m_nodeData, newNode -> m_nodeData);

        return currentNode;                     /* tarTree can't be rewritten in this function, so here we return currentNode if tarTree is a tree with only one element.*/
    }
    else
    {
        printf("tarTree Data : %d, currentNdoe Data : %d \n",dataTree -> m_nodeData, currentNode -> m_nodeData);
        outputTreeBuf = currentNode;
        while(currentNode != NULL)
        {
            previousNode = currentNode;
            if(currentNode -> m_nodeData < nodeData)
            {
                printf("Left, NowData : %d\n", currentNode -> m_nodeData);
                printf("currentNode : %x\n", currentNode);
                currentNode = currentNode -> m_leftPtr;
                printf("Left, NewData : %d\n", nodeData);
                printf("currentNode : %x\n", currentNode);
            }
            else if (currentNode -> m_nodeData > nodeData)
            {
                printf("Right, NowData : %d\n", currentNode -> m_nodeData);
                printf("currentNode : %x\n", currentNode);
                currentNode = currentNode -> m_rightPtr;
                printf("Right, NewData : %d\n", nodeData);
                printf("currentNode : %x\n", currentNode);
            } else {}
        }
        printf("End While\n");
        if(previousNode -> m_nodeData < nodeData)
        {
            previousNode -> m_leftPtr = newNode;
            printf("Left, previousNode->data = %d, tarTree = %d\n", previousNode -> m_nodeData, (previousNode -> m_leftPtr) -> m_nodeData);
        }
        else if (previousNode -> m_nodeData > nodeData)
        {
            previousNode -> m_rightPtr = newNode;
            printf("Right previousNode->data = %d, tarTree = %d\n", previousNode -> m_nodeData, (previousNode -> m_rightPtr) -> m_nodeData);
        } else {}
        return outputTreeBuf;
    }
}

btTree AddNodeTest(btTree addDataTree, int nodeData)    /* Using flag replace NULL pointer. */
{
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
                /*printf("Left, NowData : %d\n", currentNode -> m_nodeData);*/
                currentNode = currentNode -> m_leftPtr;
                /*printf("Left, NewData : %d\n", currentNode -> m_nodeData);*/
            }
            else if (currentNode -> m_nodeData > nodeData && !(currentNode -> m_rightNull))
            {
                /*printf("Right, NowData : %d\n", currentNode -> m_nodeData);*/
                currentNode = currentNode -> m_rightPtr;
                /*printf("Right, NewData : %d\n", currentNode -> m_nodeData);*/
            } else {break;}
        }
        /*printf("Tree data : %d\n",currentNode -> m_nodeData);*/

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

void BinaryTreeCreate(void)             /* Create binary tree which only has left side. */
{
    int index = 0;
    int dataLen = 8;
    int dataTest[8] = {1,5,4,3,2,6,7,8};
    for(index = 0; index < dataLen; index ++)
    {
        g_DataTree = AddNodeTest(g_DataTree, dataTest[index]);    /* Insert data from beginning. */
        printf("Index : %d\n", index);
    }

}

/*======================================Binary tree visit=========================================*/

void inorderPrintTree(btTree inorderDataTree)    /* Root in the middle. */
{
    if (inorderDataTree != NULL)
    {
        if (!(inorderDataTree -> m_leftNull))
        {
            inorderPrintTree(inorderDataTree -> m_leftPtr);
        } else {}
        printf("Element : %d\n", inorderDataTree -> m_nodeData);
        if (!(inorderDataTree -> m_rightNull))
        {
            inorderPrintTree(inorderDataTree -> m_rightPtr);
        } else {}
    } else {}
}

void preorderPrintTree(btTree preorderDataTree)    /* Root in the first place. */
{
    if (preorderDataTree != NULL)
    {
        printf("Element : %d\n", preorderDataTree -> m_nodeData);
        if (!(preorderDataTree -> m_leftNull))
        {
            preorderPrintTree(preorderDataTree -> m_leftPtr);
        }
        else if(!(preorderDataTree -> m_rightNull))
        {
            preorderPrintTree(preorderDataTree -> m_rightPtr);
        } else {}
    } else {}
}

void postorderPrintTree(btTree postorderDataTree)    /* Root in the last place. */
{
    if(postorderDataTree != NULL)
    {
        if (!(postorderDataTree -> m_leftNull))
        {
            postorderPrintTree(postorderDataTree -> m_leftPtr);
            printf("Element : %d\n", postorderDataTree -> m_nodeData);
        } else {}
        if(!(postorderDataTree -> m_rightNull))
        {
            postorderPrintTree(postorderDataTree -> m_rightPtr);
            printf("Element : %d\n", postorderDataTree -> m_nodeData);
        } else {}
        if((postorderDataTree -> m_leftNull) && (postorderDataTree -> m_rightNull))
        {
            printf("Element : %d\n", postorderDataTree -> m_nodeData);
        } else {}
    } else {}
}

void levelorderPrintTree(btTree levelorderDataTree) /* Using the continuity of pointer data set to visit all nodes. */
{
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

void VisitBinaryTree(btTree dataTree, t_BinaryMethodType visitType)
{
    switch(visitType)
    {
        case 0:
            inorderPrintTree(dataTree);
            break;
        case 1:
            preorderPrintTree(dataTree);
            break;
        case 2:
            postorderPrintTree(dataTree);
            break;
        case 3:
            levelorderPrintTree(dataTree);
            break;
    };
}

/*======================================Binary tree copy==========================================*/


/*================================================================================================*/
/* Main program */
/*================================================================================================*/

int main(int argc, char *argv[]) {
    /* Maze with Mouse */
    /*MouseGO();*/

    /* Binary tree */
    BinaryTreeCreate();
    VisitBinaryTree(g_DataTree, m_inOrder);

    /*testField(1);*/

	system("pause");
	return 0;
}


