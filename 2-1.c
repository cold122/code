#include <stdio.h>
#include <stdlib.h>
int n,st,flr[30],go[30],t[30],num[30],tim,ctup,ctdn,mu,m[30],ct,temp,mi;
//n 呼叫电梯的楼层数目
//st 电梯起始位置
//flr 呼叫电梯的楼层 go 该层的人目标楼层 t 该层的人在何时按下呼叫
//num 每层楼的剩余的人数
//tim 当前耗时
//ctup 比初始楼层高的楼层数 ctdn 比初始楼层低的楼层数
//mu 当前的电梯首要目标楼层  m 标记当前电梯的所有目标楼层
//ct 记录电梯内的人数
//temp 记录当前楼层是否为特殊楼层
int min(int a,int b) {return a>b?b:a;}
void check(int cen)//电梯当前层数
{
    tim++;temp=0;
    if(m[cen])//该层有人到达
    {
        m[cen]=0;
        ct--;n--;temp=1;
    }
    if(num[cen]&&ct<4&&tim>=t[cen]) //该层有人已经呼叫 且 电梯人数小于4 就接上电梯
    {
        m[go[cen]]=1;
        num[cen]=0,ct++;temp=1;
    }
    if(temp) printf("%d %d %d\n",cen,tim,ct);
    //楼层 耗时 电梯人数
}
int main()
{
    freopen("temp","r",stdin);
    scanf("elevator %d",&st);
    scanf("%d",&flr[1]);scanf("%d%d",&go[flr[1]],&t[flr[1]]);n=1;
    mu=flr[1];num[flr[1]]=1;
    while(~scanf("%d",&flr[n+1]))
    {
        ++n;//记录有多少层呼叫
        scanf("%d%d",&go[flr[n]],&t[flr[n]]);
        num[flr[n]]=1;
        t[flr[n]]+=t[flr[n-1]];//将间隔时间转换为累积时间
    }
    printf("%d %d %d\n",st,tim,ct);//初始情况
    while(n)//循环，直到所有人都送到为止
    {
        if(st==mu&&num[st]&&t[st]<=tim)//可能出现电梯停止一段时间后，原地有人呼叫的情况
        {
            mu=go[st],m[mu]=1;
            num[st]=0,ct++;
        }
        if(st<mu)//判断电梯运行方向
        {
            for(int i=st+1;i<=mu;i++)//向上，优先执行当前的运送任务，过程捎带其他人
                check(i);   
        }
        else 
        {
            for(int i=st-1;i>=mu;i--)//向下，优先执行当前的运送任务，过程捎带其他人
                check(i);
        }
        st=mu;mi=99999999;
        for(int i=10;i>st;i--) if(m[i])//继续当前电梯剩余人中继续上升的需求(电梯通常先上后下)
        {
            mu=i;break;
        }
        if(mu==st) for(int i=st+1,zt=0;i<=10;i++)//接楼上呼叫的人
        {
            if(num[i]&&(tim>=t[i]||zt>=t[i]))//有一种可能是：接楼上人的过程中，更高层的人发出呼叫
                mu=i,zt=tim+(i-st);
            if(num[i]) mi=min(t[i],mi);
        }
        if(mu==st&&ct!=0) for(int i=st;i>=1;i--) if(m[i])//仍然没有目标，继续当前电梯剩余人中下降的需求(电梯通常先上后下)
        {
            mu=i;break;
        }
        if(mu==st&&ct==0) for(int i=st;i>=1;i--)//向下接人
        {
            if(num[i]&&(tim>=t[i]))//有一种可能是：接楼上人的过程中，更高层的人发出呼叫
                mu=i;
            if(num[i]) mi=min(t[i],mi);
        }
        if(mu==st) tim+=mi;//此时没有人呼叫，直接快进到有人呼叫的时候
    }
    return 0;
}
