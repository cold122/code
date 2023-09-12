#include <stdio.h>
#include <stdlib.h>
int n,st,flr[30],num[30],tim,ctup,ctdn;
//n 呼叫电梯的楼层数目
//st 电梯起始位置
//flr 呼叫电梯的楼层
//num 每层楼的剩余的人数
//tim 当前耗时
//ctup 比初始楼层高的楼层数 ctdn 比初始楼层低的楼层数
int main()
{
    freopen("temp","r",stdin);
    printf("请输入呼叫电梯的楼层数目\n");
    scanf("%d",&n);
    // printf("请输入电梯的初始楼层数目\n");
    // scanf("%d",&st);
    // printf("请输入呼叫电梯的楼层，请以空格分割\n");
    // for(int i=1;i<=n;i++)
    // {
    //     scanf("%d",&flr[i]);num[i]=1;
    //     //每层楼一个人
    //     if(flr[i]>st) ctup++;
    //     else ctdn++;
    // }
    //小剪枝：向乘客多的那边出发
    return 0;
}
