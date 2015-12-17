#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int maze[12][12]={
{1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,1},
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
int pathRec[12][12];


void mouseMove(int *nowPosX, int *nowPosY){ 

	if(!maze[(*nowPosX)][(*nowPosY)-1])
	{
		(*nowPosY)=(*nowPosY)-1;
	}
	else if (!maze[(*nowPosX)+1][(*nowPosY)])
	{
		(*nowPosX) =(*nowPosX)+1;
	}
	else if (!maze[(*nowPosX)][(*nowPosY)+1])
	{
		(*nowPosY) =(*nowPosY)+1;
	}
	else if (!maze[(*nowPosX)-1][(*nowPosY)])
	{
		(*nowPosX) =(*nowPosX)-1;
	} else {}

}



int main(int argc, char *argv[]) {
	memset(pathRec, 0, sizeof(pathRec));
	int *nowPosX;
	int *nowPosY;
	int bufPosX = 0;
	int bufPosY = 0;
	int isEnd = 0;
	*nowPosX =0;
	*nowPosY =2;
	while(!isEnd)
	{
		mouseMove(nowPosX,nowPosY);
		
		if(!pathRec[*nowPosX][*nowPosY])
		{
			pathRec[*nowPosX][*nowPosY] = 1;
		} else {}
		if((*nowPosX)==0 || (*nowPosY)==0 )
		{
			isEnd = 1;
		} else {}
	}	

	system("pause");
	return 0;
}
