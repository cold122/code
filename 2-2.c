#include <stdio.h>
#include <stdlib.h>
int pos[3],dir[3],n,flr[30],go[30],t[30],ji[100000][11],tim;
int wat[3][20][20],elevator[3][5],temp;
//pos 电梯的位置 dir 电梯的方向
//n 呼叫的数目
//flr 呼叫的楼层 go目的楼层 t呼叫时间
//ji 不同时间呼叫的楼层
//tim 时间记录
//wat 呼叫后等待的人
//elevator 电梯里等待的人
void add(int mo,int wn)
{
    wat[mo][flr[wn]][0]++;
    wat[mo][flr[wn]][wat[mo][flr[wn]][0]]=wn;
}
void check(int mo)
{
    temp=0;
    for(int i=1;i<=4;i++) if(elevator[mo][i]&&go[elevator[mo][i]]==pos[mo])//下人
    {
        elevator[mo][0]--,elevator[mo][i]=0;
        temp=1,n--;
    }
    for(int i=wat[mo][pos[mo]][0];i>=1&&elevator[mo][0]<4;i--)//上人
    {
        elevator[mo][0]++;wat[mo][pos[mo]][0]--;
        for(int j=1;j<=4;j++) if(!elevator[mo][j])
        {
            elevator[mo][j]=wat[mo][pos[mo]][i];
            break;
        }
        temp=1;
    }
    //关键楼层判读
    if(temp) printf("elevator%d: FLOOR:%d TIME:%d LOAD:%d\n",mo,pos[mo],tim,elevator[mo][0]);
}
int main()
{
    freopen("temp","r",stdin);
    scanf("elevator %d %d",&pos[1],&pos[2]);
    while(~scanf("%d",&flr[n+1]))
    {
        ++n;//记录有多少层呼叫
        scanf("%d%d",&go[n],&t[n]);
        t[n]+=t[n-1];//将间隔时间转换为累积时间
        ji[t[n]][0]++;
        ji[t[n]][ji[t[n]][0]]=n;
    }
    if(pos[1]<=pos[2]) dir[1]=1,dir[2]=-1;
    else dir[1]=-1,dir[2]=1;
    while(n)
    {
        for(int i=1;i<=ji[tim][0];i++)
            if(flr[ji[tim][i]]>go[ji[tim][i]]) add(2,ji[tim][i]);
            else add(1,ji[tim][i]);
        check(1);check(2);//该层楼上人下人
        ++tim;
        if(pos[1]==1) dir[1]=1;//触底触顶转换方向
        else if(pos[1]==10) dir[1]=-1;
        if(pos[2]==1) dir[2]=1;
        else if(pos[2]==10) dir[2]=-1;
        pos[1]+=dir[1];//楼层变换
        pos[2]+=dir[2];
    }
    return 0;
}
