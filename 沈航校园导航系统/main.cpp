#include <iostream>
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#include<cstring>
using namespace std;
#define INFINITY 10000
#define MAX_VERTEX_NUM 40
#define MAX 40
typedef struct Arcell
{
    int adj;
}Arcell,Adj[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
    char name[100];
    int num;
    char introduct[100];
}infotype;
typedef struct
{
    infotype vexs[MAX_VERTEX_NUM];
    Adj arcs;
    int v,a;
}Mgraph;
Mgraph b;
void cmd();
//Mgraph Init();
void Init(Mgraph&G);
void Menu();
void Browser(Mgraph&G);
void Shortpath(Mgraph&G);
void Search(Mgraph&G);
void map();
int main()
{
    system("color B0");
    system("mode con:cols=100 lines=200");
    cmd();
}
void cmd()
{
    char i;
    int flag=1;
    //b=Init();
    Menu();
    scanf("%c",&i);
    while(flag)
    {
        switch(i)
        {
            case 'f':Init(b);Menu();break;
            case 'a':Browser(b);Menu();break;
            case 'b':map();Menu();break;
            case 'c':Shortpath(b);Menu();break;
            case 'd':Search(b);Menu();break;
            case 'e':exit(0);break;
            default:break;
        }
        scanf("%c",&i);
    }

}
//Mgraph Init()
void Init(Mgraph&G)
{
    FILE*fp,*fq;
    fp=fopen("apple.txt","r");//打开已有文件
    fq=fopen("orange.txt","r");//打开已有文件
    //Mgraph G;
    int i,j;
    G.v=16;G.a=17;
    for(i=0;i<G.v;i++)
      {G.vexs[i].num=i;}
    for(i=0;i<G.v;i++)
    {
        fscanf(fp,"%s     %s",G.vexs[i].name,G.vexs[i].introduct);
        if(feof(fp))
          break;
    }
    fclose(fp);
    int a,b,c;
    for(i=0;i<G.v;i++)
    {
        for(j=0;j<G.v;j++)
            G.arcs[i][j].adj=INFINITY;
    }
    for(j=0;j<G.a;j++)
        {
            fscanf(fq,"%d %d %d",&a,&b,&c);
                G.arcs[a][b].adj=c;
                G.arcs[b][a].adj=c;
        }
    fclose(fq);
    printf("学校里有%d个景点,%d条路径\n",G.v,G.a);
    printf("初始化完成！\n");
//return G;
}
void Menu()
{
    printf("\n");
    printf("**************************************\n");
    printf("*   Welcome to 沈阳航空航天大学      *\n");
    printf("*                                    *\n");
    printf("*f: 校园初始化                       *\n");
    printf("*a：校园所有景点介绍                 *\n");
    printf("*b：校园平面图                       *\n");
    printf("*c：查看两地点间的游览路线           *\n");
    printf("*d：查看该景点信息                   *\n");
    printf("*e：退出系统                         *\n");
    printf("**************************************\n");
    printf("Option(输入你将要执行的操作):");
}
void Browser(Mgraph&G)
{
    int v;
    printf("------------------------------------------------------------\n");
    printf("|编号|            名称|                                简介|\n");
    for(v=0;v<G.v;v++)
        {printf("------------------------------------------------------------\n");
            printf("|%4d|%16s|%36s|\n",G.vexs[v].num,G.vexs[v].name,G.vexs[v].introduct);
        }
    printf("------------------------------------------------------------\n");
}
void Shortpath(Mgraph&G)
{
        int v,w,i,min,x,v0,v1,have[100],k=0;
        int final[20],D[20],p[20][20];
            printf("请输入起始景点的编号：");
            scanf("%d",&v0);
            if(v0<0||v0>G.v)
            {
                printf("景点编号不存在!请重新输入起始景点的编号：");
                scanf("%d",&v0);
            }
            printf("请输入终止景点的编号：");
            scanf("%d",&v1);
            if(v1<0||v1>G.v)
            {
                printf("景点编号不存在!请重新输入终止景点的编号：");
                scanf("%d",&v1);
            }
        for(v=0;v<G.v;v++)
        {
            final[v]=0;
            D[v]=G.arcs[v0][v].adj;
            for(w=0;w<G.v;w++)
                {p[v][w]=INFINITY;}
            if(D[v]<INFINITY)
            {
                p[v][v0]=1;p[v][v]=1;
            }
        }
        D[v0]=0;final[v0]=1;have[0]=v0;
        for(i=0;i<G.v;i++)
        {
            min=INFINITY;
            for(w=0;w<G.v;w++)
                if(!final[w])
                if(D[w]<min)
                    {v=w;min=D[w];}
                final[v]=1;
                have[k]=v;
                k++;
                for(w=0;w<G.v;w++)
                    if(!final[w]&&((min+G.arcs[v][w].adj)<D[w]))
                   {
                    D[w]=min+G.arcs[v][w].adj;
                    for(x=0;x<G.v;x++)
                        p[w][x]=p[v][x];
                        p[w][w]=1;
                    }
        }
        printf("%s",G.vexs[v0].name);
        for(i=0;i<G.v;i++)
        {
          if(p[v1][have[i]]==1)
          {
              printf("-->%s",G.vexs[have[i]].name);
          }
        }
        if((v1-v0)==1)
            printf("   总路线长为：%dm\n",G.arcs[v0][v1]);
        else
            printf("   总路线长为：%dm\n",D[v1]);
}
void Search(Mgraph&G)
{
    int k;
    printf("请输入要查询的景点编号：");
    scanf("%d",&k);
    while(k<0||k>G.v)
    {
        printf("景点编号不存在！请重新输入：");
        scanf("%d",&k);
    }
    printf("-------------------------------------------------------------------------------\n");
    printf("|编号|            名称|                                                    简介|\n");
        printf("|%4d|%16s|%56s|\n",G.vexs[k].num,G.vexs[k].name,G.vexs[k].introduct);
    printf("-------------------------------------------------------------------------------\n");
}
void map()
{
printf("           沈阳航空航天大学平面图\n");
printf("                                             男寝(8)\n");
printf("                                              ||\n");
printf("                                              ||\n");
printf("    艺术馆(2)==体育馆(3)=足球场(7)         北区澡堂(9)=北区食堂(10)\n");
printf("      ||                   ||                 ||\n");
printf("    图书馆(1)==青阳湖(4)=大学生活动中心(6)==网球场(11)\n");
printf("     //         //                            ||\n");
printf("    //       教学楼(5)                        ||\n");
printf("   //          ||                             //\n");
printf("  //           ||                            //\n");
printf("行政楼(0)      ||                           ||\n");
printf("               ||                         校医院(12)\n");
printf("               ||                           ||\n");
printf("           创新创业楼(15)===南区食堂(14)==女寝(13)\n");
}
