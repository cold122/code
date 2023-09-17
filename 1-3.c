#include <stdio.h>
#include <stdlib.h>
int n,st,flr[30],go[30],num[30],tim,ctup,ctdn,mu,m[30],ct,temp;
//n 呼叫电梯的楼层数目
//st 电梯起始位置
//flr 呼叫电梯的楼层 go 该层的人目标楼层
//num 每层楼的剩余的人数
//tim 当前耗时
//ctup 比初始楼层高的楼层数 ctdn 比初始楼层低的楼层数
//mu 当前的电梯首要目标楼层  m 标记当前电梯的所有目标楼层
//ct 记录电梯内的人数
//temp 记录当前楼层是否为特殊楼层
void check(int cen)//电梯当前层数
{
    tim++;temp=0;
    if(m[cen])//该层有人到达
    {
        m[cen]=0;
        ct--;n--;temp=1;
    }
    if(num[cen]&&ct<4) //该层有人呼叫 且 电梯人数小于4 就接上电梯
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
    printf("请输入呼叫电梯的楼层数目\n");
    scanf("%d",&n);
    printf("请输入电梯的初始楼层数目\n");
    scanf("%d",&st);
    printf("请输入呼叫电梯的楼层和他们呢要去的楼层，请以空格分割\n");
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&flr[i]);num[flr[i]]=1;
        scanf("%d",&go[flr[i]]);
        //每层楼一个人
        if(flr[i]>st) ctup++;
        else if(flr[i]<st) ctdn++;
    }
    printf("%d %d %d\n",st,tim,ct);//初始情况
    // 小剪枝：向乘客多的那边出发
    if(num[st]) mu=go[st],m[mu]=1,num[st]=0,ct++;//人被接走，计数为0
    else if(ctup>ctdn)
    {
        for(int i=st+1;i<=10;i++)//寻找最近的目标
        {
            tim++;
            if(num[i])
            {
                mu=go[i],m[mu]=1;
                num[i]=0,ct++;
                st=i;
                break;
            }
        }
    }
    else
    {
        for(int i=st-1;i>=0;i--)//寻找最近的目标
        {
            tim++;
            if(num[i]) 
            {
                mu=go[i],m[mu]=1;
                num[i]=0,ct++;
                st=i;
                break;
            }
        } 
    }
    printf("%d %d %d\n",st,tim,ct);
    while(n)//循环，直到所有人都送到为止
    {
        if(st<mu)//判断电梯运行方向
        {
            for(int i=st+1;i<=mu;i++)//优先执行当前的运送任务，过程捎带其他人
                check(i);   
        }
        else 
        {
            for(int i=st-1;i>=mu;i--)//优先执行当前的运送任务，过程捎带其他人
                check(i);
        }
        st=mu;
        for(int i=10;i>=1;i--) if(m[i])//继续当前电梯剩余人的需求(电梯通常先上后下)
        {
            mu=i;
            break;
        }
        if(ct==0) for(int i=1;i<=10;i++)//电梯没人了，向最近的呼叫出进发
        {
            if(num[st+i])//两边搜索，寻找最近的人
            {
                tim+=i;
                st+=i;
                mu=go[st],m[mu]=1,num[st]=0,ct++;
                printf("%d %d %d\n",st,tim,ct);
                break;
            }
            else if(st-i>=1)//防止越界
            {
                if(num[st-i])
                {
                    tim+=i;
                    st-=i;
                    mu=go[st],m[mu]=1,num[st]=0,ct++;
                    printf("%d %d %d\n",st,tim,ct);
                    break;
                }
            }
        }
    }
    return 0;
}
