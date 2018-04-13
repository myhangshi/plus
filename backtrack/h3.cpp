#include<iostream>  
#include <iomanip>  
#include <queue>  
using namespace std;  
  
//在某一格子的八种走法  
int fx[]= {2,1,-1,-2,-2,-1,1,2};  
int fy[]= {-1,-2,-2,-1,1,2,2,1};  
  
typedef struct  
{  
    int x,y; //坐标  
    int number; //序号  
} Point; //棋盘中的格子  
  
//马周游的棋盘，注意使用的时候是从下表为1开始  
Point board[10000][10000];  
  
int n; //棋盘大小  
int step =1; //序号  
  
//输出结果  
void outputResult(int n)  
{  
    for(int i=1; i<=n; i++)  
    {  
        cout<<endl<<endl;  
        for(int j=1; j<=n; j++)  
        {  
            cout<<setw(3)<<board[i][j].number<<" ";  
        }  
    }  
    cout<<endl<<endl;  
}  
  
bool check(int x,int y)  
{  
    if(x<1 || y<1 || x>n || y>n || board[x][y].number != 0)  
        return false;  
    return true;  
}  
  
//下一位置有多少种走法  
int nextPosHasSteps(int x, int y)  
{  
    int steps = 0;  
    for (int i = 0; i < 8; ++i)  
    {  
        if (check(x + fx[i], y + fy[i]))  
            steps++;  
    }  
    return steps;  
}  
  
//非递归的走法  
void horseRun(Point point)  
{  
    queue<Point> pointQueue;  
    pointQueue.push(point);  
  
    Point temp;  
  
    while(!pointQueue.empty())  
    {  
        temp = pointQueue.front();  
        pointQueue.pop();  
  
        board[temp.x][temp.y].number = step++;  
  
        int minStep = 8;  
  
        int flag = 0;  
  
        for(int i=0; i<8; i++) //出下一位置走法最少的进入对列  
        {  
            int x=temp.x + fx[i];  
            int y=temp.y + fy[i];  
  
            if(check(x,y))  
            {  
                if(nextPosHasSteps(x,y) <= minStep)  
                {  
                    minStep = nextPosHasSteps(x,y);  
  
                    Point t;  
                    t.x = x;  
                    t.y = y;  
  
                    if(flag) pointQueue.pop();  
  
                    pointQueue.push(t);  
                    flag = 1;  
                }  
            }  
        }  
    }  
}  
  
int main()  
{  
    cout<<"输入棋盘大小n:";  
    cin>>n;  
  
    Point startPoint;  
    cout<<"输入马周游起始位置x(1~n),y(1~n):";  
    cin>>startPoint.x>>startPoint.y;  
  
    horseRun(startPoint);  
    //输出结果  
    outputResult(n);  
    return 0;  
}  
