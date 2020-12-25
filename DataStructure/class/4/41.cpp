#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define MAX_GRAPH_SIZE 100
#define GRAPHINCREMENT 10

typedef int status;
typedef int ElemType;
typedef char GElemType;

typedef struct ArcNode
{
    int adjvex;//弧的下一结点
    struct ArcNode *nextarc;//结点的下一条弧
    int info;
}ArcNode;
typedef struct VNode
{
    ArcNode *firstarc;//结点的第一条弧
    ElemType data;//结点数据
    GElemType key;//结点的关键值
}VNode,NodeList[MAX_GRAPH_SIZE];//NodeList为结点数组
typedef struct
{
    NodeList vert;//图的结点集
    int vexnum,arcnum;//图的结点数，弧的数目
    char name[30];//图名
}Graph;
typedef struct
{
    Graph *elem;//图的数组
    int length;//图组的长度,但是后面没有用,使用了全局变量来记录
    int graphsize;//图组的最大长度
}AGraph;//全部的图

status CreateGraph(Graph &G,GElemType V[],GElemType VR[][4]);//根据图的结点集和弧集创建一个有向图
status DestroyGraph(Graph &G);//销毁目标图
status LocateVex(Graph G,GElemType u);//定位目标结点
status PutVex(Graph &G,GElemType u,ElemType value);//结点赋值
status FirstAdjVex(Graph G,ElemType u);//结点的第一条弧
status NextAdjVex(Graph G,ElemType v,ElemType w);//目标结点相对于另一结点的下一条弧
status InsertVex(Graph &G,GElemType v);//插入结点
status DeleteVex(Graph &G,GElemType v);//删除结点
status InsertArc(Graph &G,GElemType v,GElemType w);//插入弧
status DeleteArc(Graph &G,GElemType v,GElemType w);//删除弧
status DFSTraverse(Graph G,status(*visit)(GElemType e,ElemType data));//深度优遍历图
status BFSTraverse(Graph G,status(*visit)(GElemType e,ElemType data));//广度优先遍历图
status OpenFile(Graph &G);//从文件中读取数据
status SaveFile(Graph G);//把数据存入文件
int find(AGraph &G,char names[]);//查找目标图
status visit(GElemType e,ElemType data);//访问输出数据
void reset(int flag[]);//清空数组
void DFS(Graph G,ElemType v);//辅助深度优先遍历函数
void Print(Graph G);//打印图的邻接表

int flag[100],isvisit[100],num[100];//标记数组，是否访问数组，删除结点数量
GElemType vnode[MAX_GRAPH_SIZE+1];//结点集1
GElemType vr[MAX_GRAPH_SIZE][4];//弧集
int graphnum;//全局变量用来记录图组的长度
AGraph G1;//图组

int main()
{
    int op,i,t,w=0,n,flag1=0;
    char name1[50],name2[50],e,c;//name1用来记录当前使用的图名
    G1.length=0;//没用到这一个
    G1.graphsize=GRAPHINCREMENT;//将图组的大小初始化为10
    G1.elem=(Graph*)calloc(G1.graphsize*sizeof(Graph),1);//创建一个空的图组
    while(op)
    {
        system("cls");putchar('\n');
        printf("\tWelcome to use Menu for Graph Building!\n");//打印系统的界面
        printf("---------------------------------------------------------\n");
        printf("\t1.CreateGraph\t\t  2.DestroyGraph\n");
        printf("\t3.LocateVex\t\t  4.PutVex\n");
        printf("\t5.FirstAdjVex\t\t  6.NextAdjVex\n");
        printf("\t7.InsertVex\t\t  8.DeleteVex\n");
        printf("\t9.InsertArc\t\t  10.DeleteArc\n");
        printf("\t11.DFSTraverse\t\t  12.BFSTraverse\n");
        printf("\t13.OpenFile\t\t  14.SaveFile\n");
        printf("\t15.Switch\t\t  16.PrintGraph\n");
        printf("\t0.Exit\n");
        printf("---------------------------------------------------------\n");//打印出菜单
        printf("请选择你的操作(0~16)\n");//输出菜单
        scanf("%d",&op);
        getchar();
        switch(op)//根据op判断用户执行操作
        {
        case 0://为0退出循环
            break;
        case 1:
            printf("请输入图的名称(默认为创建有向图):\n");
            scanf("%s",name2);//将图的名字先读入一个暂时变量
            t=find(G1,name2);
            if(t!=-1){
                printf("图的名字重复，自动切换到输入的图\n");//如果发现重复命名,那就切换到刚刚输入的图中
                strcpy(name1,name2);
                getchar();getchar();
                break;
            }
            strcpy(G1.elem[graphnum].name,name2); //如果能够创建,就将图名赋值,开始创建图
            printf("1.键盘赋值 2.文件读取\n请选择读取方式：");//选择读取方式
            scanf("%d",&t);
            while(t!=1&&t!=2)//输入数字不对重新输入
            {
                printf("请再次输入正确的数字。\n");
                scanf("%d",&t);
            }
            if(t==1)//键盘读取
            {
                printf("请输入图的结点数量：\n");
                scanf("%d",&n);//获得结点数量
                while(n<=0||n>MAX_GRAPH_SIZE)//结点数量不在合法范围内提示出错并重新输入
                {
                    printf("请重新输入在0-100范围内的数字！\n");
                    scanf("%d",&n);
                }
                printf("请输入图的结点关键值(大写英文字母):\n");
                getchar();
                int flag2=0;//用来标记是否出现重复的结点
                for(i=0;i<n;i++)
                {
                    scanf(" %c",&vnode[i]);//获得结点关键值
                    if(vnode[i]<'A'||vnode[i]>'Z') {//输入的结点关键值不符合要求
                        flag1=1;
                        continue;
                    }
                    if(flag[vnode[i]-'A'])//标记数组相应位置不为0代表该关键值已经输入过
                    {
                        printf("数据重复，创建失败！\n");
                        flag2=1;//flag2设为1
                        continue;
                    }
                    flag[vnode[i]-'A']++;//标记数组相应位置加1
                }
                if(flag1)//flag1为1证明输入不满足要求，直接退出
                {
                    reset(flag);//清空标记数组
                    printf("请输入大写的字母:\n");
                    getchar();getchar();
                    break;
                }
                if(flag2)//flag2为1证明重复，直接退出
                {
                    reset(flag);//清空标记数组
                    printf("输入了重复的关键字\n");
                    getchar();getchar();
                    break;
                }
                vnode[i]='\0';//将文件尾标记上
                printf("结点输入完毕，开始输入图的边\n");
                printf("请输入边的两个结点的关键值，两个值之间以空格间隔，输入以#结束。则输入的第一个结点值为弧尾\n");
                for(i=0,flag1=0;;)
                {
                    scanf(" %c",&vr[i][0]);//接受弧尾关键值
                    if(vr[i][0]=='#')//关键值为#代表输入完毕，结束
                        break;
                    scanf(" %c",&vr[i][1]);//接受第二个关键值
                    while(!flag[vr[i][0]-'A']||!flag[vr[i][1]-'A'])//标记数组相应位置为0，代表输入的关键值不存在
                    {
                        printf("你输入的关键值不存在！请重新输入。\n");
                        printf("如果想退出，请输入0\n");
                        scanf(" %c",&vr[i][0]);//重新输入
                        if(vr[i][0]=='0') {//如果输入为0就退出
                            flag1=1;
                            break;
                        }
                        scanf(" %c",&vr[i][1]);//重新输入弧头结点 
                    }
                    if(flag1) break;
                    i++;
                }
                if(flag1){
                    printf("退出创建图\n");//中途退出
                    reset(flag);
                    getchar();getchar();
                    break;
                }
                if(!CreateGraph(G1.elem[graphnum],vnode,vr))//创建图失败
                {
                    printf("创建失败！\n");//提示失败
                    strcpy(G1.elem[graphnum].name,"\0");
                    getchar();getchar();
                    break;
                }
                printf("创建成功！\n");//提示创建成功
                strcpy(name1,name2);//将已经创建好的图名字赋值给当前主图
                graphnum++;//图的数量加一
                reset(flag);//清空标记数组
                getchar();getchar();
                break;
            }
            else//文件读入
            {
                if(!OpenFile(G1.elem[graphnum]))//读入若失败
                    printf("文件读取失败！\n");
                else
                    printf("读取完成！\n"),graphnum++,strcpy(name1,name2);//图的数量加一
                getchar();getchar();
                break;
            }
        case 2:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            if(!DestroyGraph(G1.elem[t]))//销毁失败提示窗出错
            {
                printf("销毁失败！\n");
                getchar();getchar();
                break;
            }
            printf("销毁成功！\n");
            for(i=t;i<graphnum-1;i++)//图组元素覆盖原删除的元素
                G1.elem[i]=G1.elem[i+1];//将后面的图向前挪动
            graphnum--;//图的数量减一
            getchar();getchar();
            break;
        case 3:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            printf("请输入要定位的顶点的关键值:");
            scanf(" %c",&e);//获得目标结点关键值
            w=LocateVex(G1.elem[t],e);//获得结点的位置
            if(w==-1)//-1代表结点不存在
                printf("没有找到该顶点！\n");
            else
                printf("该顶点是第%d个顶点。\n",w+1);//输出结点位置
            getchar();getchar();
            break;
        case 4:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            printf("请输入要赋值结点的关键值:");
            scanf(" %c",&e);//获得目标结点关键值
            if(LocateVex(G1.elem[t],e)==-1)//-1代表没有找到目标结点
                printf("没有找到该结点！\n");
            else
            {
                printf("请输入要赋的值:");
                scanf("%d",&w);//获得结点的值
                if(!PutVex(G1.elem[t],e,w))//赋值失败提示出错
                    printf("赋值失败！\n");
                else
                    printf("赋值成功！\n");
            }
            getchar();getchar();
            break;
        case 5:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            printf("请输入要查询的结点的位序:");
            scanf(" %d",&w);//获得目标结点位序
            w--;//将输入值调整为数组的范围
            if(w<0||w>G1.elem[t].vexnum)//位序不在合法范围内
                printf("没有找到该结点！\n");
            else
            {
                i=FirstAdjVex(G1.elem[t],w);//找到下一个结点的位序
                if(i==-1)//-1代表没有找到目标结点
                    printf("没有找到目标结点！\n");
                else
                    printf("该结点的关键值为%c，其第一个邻接结点序号为%d,关键值为%c。\n",G1.elem[t].vert[w].key,i+1,G1.elem[t].vert[i].key);//输出关于该结点和弧的信息
            }
            getchar();getchar();
            break;
        case 6:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            printf("请输入要查询的结点的位序");
            scanf(" %d",&w);//获得第一个目标结点位序
            w--;
            if(LocateVex(G1.elem[t],G1.elem[t].vert[w].key)==-1)//-1代表没有找到目标结点
            {
                printf("没有找到该结点！\n");
                getchar();getchar();
                break;
            }
            scanf(" %d",&n);//获得第二个目标结点位序
            n--;
            if(LocateVex(G1.elem[t],G1.elem[t].vert[n].key)==-1)
            {
                printf("没有找到该结点！\n");
                getchar();getchar();
                break;
            }
            i=NextAdjVex(G1.elem[t],w,n);//获得结点下一条弧指向的位序
            if(i==-1)
                printf("目标结点为空。\n");
            else
                printf("该结点的关键值为%c，相对于结点%c下一个邻接顶点位序为%d，关键值为%c。\n",G1.elem[t].vert[w].key,G1.elem[t].vert[n].key,i+1,G1.elem[t].vert[i].key);//输出关于该结点和弧的关键信息
            getchar();getchar();    
            break;
        case 7:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            printf("请输入要插入的结点的关键值:");
            scanf(" %c",&e);//获得结点关键值
            w=0;
            for(i=0;i<G1.elem[t].vexnum;i++)//检索目标结点是否已经出现在图中
                if(e==G1.elem[t].vert[i].key){
                    printf("该结点已经在图中存在。\n");
                    w=1;
                }
            if(w){//w为1代表出错，退出
                getchar();getchar();
                break;
            }
            if(!InsertVex(G1.elem[t],e))//插入结点失败提示
                printf("插入失败！\n");
            else
                printf("插入完成！\n");//删除数组相应位置加一
            getchar();getchar();
            break;
        case 8:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            printf("请输入要删除的结点的关键值:");
            scanf(" %c",&e);//获得要删除结点的关键值
            w=LocateVex(G1.elem[t],e);//获得结点的位置
            if(w==-1){//-1代表结点不存在
                printf("没有找到该顶点！\n");
                getchar();getchar();
                break;
            }
            if(!DeleteVex(G1.elem[t],e))//删除失败提示
                printf("删除失败！\n");
            else
                printf("删除成功！\n"),num[t]++;//删除成功提示,并将该图删除的结点数量加一
            getchar();getchar();
            break;
        case 9:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            printf("请输入要插入弧的两个结点，第一个为弧尾，第二个为弧头，空格隔开:\n");
            scanf(" %c %c",&e,&c);//获得弧尾和弧头
            w=LocateVex(G1.elem[t],e);//获得结点的位置
            if(w==-1){//-1代表结点不存在
                printf("没有找到弧尾顶点！\n");
                getchar();getchar();
                break;
            }
            w=LocateVex(G1.elem[t],c);//获得结点的位置
            if(w==-1){//-1代表结点不存在
                printf("没有找到弧头顶点！\n");
                getchar();getchar();
                break;
            }
            if(!InsertArc(G1.elem[t],e,c))//插入弧失败提示
                printf("弧插入失败！\n");
            else
                printf("弧插入成功！\n");//插入弧成功提示
            getchar();getchar();
            break;
        case 10:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            printf("请输入要删除的弧的弧尾和弧头:\n");
            scanf(" %c %c",&e,&c);//获得目标弧尾和弧头
            w=LocateVex(G1.elem[t],e);//获得结点的位置
            if(w==-1){//-1代表结点不存在
                printf("没有找到弧尾顶点！\n");
                getchar();getchar();
                break;
            }
            w=LocateVex(G1.elem[t],c);//获得结点的位置
            if(w==-1){//-1代表结点不存在
                printf("没有找到弧头顶点！\n");
                getchar();getchar();
                break;
            }
            if(!DeleteArc(G1.elem[t],e,c))//删除弧失败提示
                printf("弧删除失败！\n");
            else
                printf("弧删除成功！\n");//删除弧成功提示
            getchar();getchar();
            break;
        case 11:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            if(!DFSTraverse(G1.elem[t],visit))//深度优先遍历失败提示
                printf("遍历失败！\n");
            else
                printf("遍历完成\n");//深度优先遍历成功提示
            getchar();getchar();
            break;
        case 12:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            if(!BFSTraverse(G1.elem[t],visit))//广度优先遍历失败提示
                printf("遍历失败！\n");
            else
                printf("遍历完成\n");//广度优先遍历成功提示
            getchar();getchar();
            break;
        case 13:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            printf("确定要从文件读取，这会清空当前图原有的内容？（Y/N）\n");//防止用户丢失数据再一次确认
            scanf(" %c",&e);
            if(e!='Y'){//用户决定停止操作则退出
                getchar();getchar();
                break;
            }
            DestroyGraph(G1.elem[t]);//销毁原来的图
            if(!OpenFile(G1.elem[t])){//文件读取失败提示
                printf("文件读取失败！将删除当前使用的图\n");//读取失败后就会清空图
                for(i=t;i<graphnum-1;i++)//图组元素覆盖原删除的元素
                G1.elem[i]=G1.elem[i+1];
                graphnum--;//图的数量减一
            }
            else
                printf("读取完成！\n");//文件读取成功提示
            getchar();getchar();
            break;
        case 14:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            if(!SaveFile(G1.elem[t]))//文件保存失败提示
                printf("文件保存失败！\n");
            else
                printf("文件保存成功！\n");//文件保存成功提示
            getchar();getchar();
            break;
        case 15:
            printf("当前存在以下的图：\n");
            for(i=0;i<graphnum;i++)//依次输出当前存在的图的名称
                printf("%s ",G1.elem[i].name);
            putchar('\n');
            printf("请选择要切换的图:\n");
            char name2[50];
            scanf("%s",name2);//读入要切换的图
            t=find(G1,name2);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            else {
                strcpy(name1,name2);//如果可以切换就将该图切换到当前主图
                printf("切换成功\n");
            }
            getchar();getchar();
            break;
        case 16:
            t=find(G1,name1);
            if(t==-1)//没有找到图提示出错
            {
                printf("没有找到这个图！图还没有创建\n");
                getchar();getchar();
                break;
            }
            Print(G1.elem[t]);//打印出目标图的邻接表
            getchar();getchar();
            break;
        default:
            printf("请输入正确的数字！\n");//其他情况代表输入数字出错，提示重新输入
            getchar();getchar();
            break;
        }   
    }
    printf("---------------------------------------------------------\n");
    printf("程序结束，感谢使用！\n");system("pause");
    return 0;
}
status CreateGraph(Graph &G,GElemType V[],GElemType VR[][4])
{
    int i,j,k;
    ArcNode *p;
    G.vexnum=strlen(V);//图的结点数为结点数组的长度
    for(i=0;i<G.vexnum;i++)//每一个结点开始都没有弧和数据
        G.vert[i].key=V[i],G.vert[i].firstarc=NULL,G.vert[i].data=0;
    for(k=0;VR[k][0]!='#';k++)//开始建立弧
    {
        i=LocateVex(G,VR[k][0]);//找到弧尾结点位置
        j=LocateVex(G,VR[k][1]);//找到弧头结点位置
        p=G.vert[i].firstarc;//p指向结点第一条弧
        if(!p)//该结点还没有弧则建立第一条弧
        {
            G.vert[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));//分配空间
            G.vert[i].firstarc->adjvex=j;//弧指向弧头结点位序
            G.vert[i].firstarc->nextarc=NULL;//下一条弧为NULL
        }
        else//结点已经有弧
        {
            while(p->nextarc)
                p=p->nextarc;//p移动到结点最后一条弧
            p->nextarc=(ArcNode*)malloc(sizeof(ArcNode));//分配空间
            p->nextarc->adjvex=j;//弧指向弧头结点位序
            p->nextarc->nextarc=NULL;//下一条弧为NULL
        }
    }
    G.arcnum=k;//图的弧数为k
    return OK;
}
status DestroyGraph(Graph &G)
{
    int i,j;
    ArcNode *p,*q;
    for(i=0;i<G.vexnum;i++)//依次销毁所有结点
    {
        if(G.vert[i].firstarc)//结点有弧
        {
            p=G.vert[i].firstarc;
            q=G.vert[i].firstarc->nextarc;//q指向当前弧的下一条弧
            while(q)
                free(p),p=q,q=q->nextarc;//删除q，p，q依次后移
            free(p);//删除最后一条弧
        }
    }
    return OK;
}
status LocateVex(Graph G,GElemType u)
{
    int i;
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)//依次搜索每一个结点,初始元素加上已将删除的元素数量
    {
        if(G.vert[i].key==u)//结点关键值与目标关键值相同代表找到结点
        {
            if(G.vert[i].firstarc&&G.vert[i].firstarc->adjvex==-1)//结点储存的是删除信息代表已经被删除
            {
                printf("结点%c已被删除！\n",u);
                return -1;//返回错误
            }
            return i;//返回结点位序
        }
    }
    return -1;//没有找到返回错误
}
status PutVex(Graph &G,GElemType u,ElemType value)
{
    int i=LocateVex(G,u);//定位结点
    if(i==-1)//定位失败代表结点未找到
    {
        printf("找不到该结点。\n");
        return FALSE;
    }
    G.vert[i].data=value;//给目标结点赋值
    return OK;
}
status FirstAdjVex(Graph G,ElemType u)
{
    if(!G.vert[u].firstarc)//结点没有弧
        return -1;
    return G.vert[u].firstarc->adjvex;//返回弧指向的位序
}
status NextAdjVex(Graph G,ElemType v,ElemType w)
{
    ArcNode *p;
    p=G.vert[v].firstarc;//p指向结点第一条弧
    while(p&&p->nextarc)//p一直往后移
    {
        if(p->adjvex==w)//弧的位序为目标结点位序
            return p->nextarc->adjvex;//返回目标弧的位序
        p=p->nextarc;//p后移
    }
    return -1;
}
status InsertVex(Graph &G,GElemType v)
{
    G.vert[G.vexnum+num[find(G1,G.name)]].key=v;//结点数组填入元素
    G.vert[G.vexnum+num[find(G1,G.name)]].data=0;
    G.vert[num[find(G1,G.name)]+G.vexnum++].firstarc=NULL;//结点一开始没有弧
    return OK;
}
status DeleteVex(Graph &G,GElemType v)
{
    int i=LocateVex(G,v),j;//定位要删除结点
    ArcNode *p,*q;
    if(G.vert[i].firstarc)//删除结点有弧则需清空弧
    {
        p=G.vert[i].firstarc;
        if(p->nextarc)//结点有多条弧
        {
            p=p->nextarc;
            while(p->nextarc)//依次删除所有的弧
            {
                q=p->nextarc;
                free(p);//释放弧的空间
                p=q;
                G.arcnum--;//图的弧数减少
            }
            if(p)free(p),G.arcnum--;//删除最后一条弧
        }
        G.vert[i].firstarc->adjvex=-1;//标记为已清除,若从来没有创建,则firstarc指向NULL
        G.vert[i].firstarc->nextarc=NULL;
        G.vert[i].key='#';//将已将删除结点关键字标记为#
    }
    else//没有弧则需创建一条清除标记弧
    {
        G.vert[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
        G.vert[i].firstarc->adjvex=-1;
        G.vert[i].firstarc->nextarc=NULL;
        G.vert[i].key='#';
    }
    for(j=0;j<G.vexnum;j++)//依次清空邻接表中有关删除结点的所有表结点
    {
        if(j==i)continue;//被删除则跳过
        if(!G.vert[j].firstarc)//结点没有弧则跳过
            continue;
        p=G.vert[j].firstarc;
        if(G.vert[j].firstarc->adjvex==i)//结点链接第一个表结点为要删除的结点
        {
            G.vert[j].firstarc=G.vert[j].firstarc->nextarc;//删除第一条弧
            free(p);//释放空间
            G.arcnum--;//图的弧数减少
            continue;
        }
        q=p->nextarc;//q指向下一条弧
        while(q)
        {
            if(q->adjvex==i)//弧为要删除的弧
            {
                p->nextarc=q->nextarc;//p的下一条弧为q的下一条弧
                free(q);//释放q
                G.arcnum--;//图的弧数减少
                break;
            }
            p=q,q=q->nextarc;//p，q后移
        }
    }
    G.vexnum--;
    return OK;
}
status InsertArc(Graph &G,GElemType v,GElemType w)
{
    ArcNode *p,*q;
    int i=LocateVex(G,v),j=LocateVex(G,w);//定位两个结点位置
    if(!G.vert[i].firstarc)//弧尾结点没有弧则直接建立其第一条弧
    {
        G.vert[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));//分配空间
        G.vert[i].firstarc->adjvex=j;//指定指向位序
        G.vert[i].firstarc->nextarc=NULL;//下一条弧置空
        return OK;
    }
    p=G.vert[i].firstarc;
    while(p->nextarc)
        p=p->nextarc;//p后移到最后一条弧
    p->nextarc=(ArcNode*)malloc((sizeof(ArcNode)));//分配空间给下一条弧
    p->nextarc->adjvex=j;//指向指定位序
    p->nextarc->nextarc=NULL;
    G.arcnum++;//弧的数量加一
    return OK;
}
status DeleteArc(Graph &G,GElemType v,GElemType w)
{
    ArcNode *p,*q;
    int i=LocateVex(G,v),j=LocateVex(G,w);//定位目标结点
    p=G.vert[i].firstarc;
    if(!p||G.vert[i].firstarc->adjvex==-1)//第一条弧不存在或者结点已被删除报错
    {
        printf("没有这条边！\n");
        return ERROR;
    }
    G.arcnum--;
    if(p->adjvex==j)//第一条弧为要删除的弧
    {
        G.vert[i].firstarc=G.vert[i].firstarc->nextarc;//删除目标弧
        free(p);//释放空间
        return OK;
    }
    q=p->nextarc;
    while(q)//依次检测之后的弧
    {
        if(q->adjvex==j)//发现目标弧
        {
            p->nextarc=q->nextarc;//删除操作
            free(q);//释放空间
            break;
        }
        p=q;
        q=q->nextarc;//p，q后移
    }
    if(q)
        return OK;
    else
        return FALSE;
}
status DFSTraverse(Graph G,status(*visit)(GElemType e,ElemType data))
{
    reset(isvisit);//清空访问数组
    int i;
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)//依次遍历所有结点
    {
        if(!isvisit[i])//结点没有被访问
        {
            if(G.vert[i].firstarc&&G.vert[i].firstarc->adjvex==-1)//判断是否为清除结点
                continue;
            DFS(G,i);//深度优先遍历
        }
    }
    putchar('\n');
    return OK;
}
void DFS(Graph G,ElemType v)
{
    int w;
    isvisit[v]++;//标记为已经访问过
    visit(G.vert[v].key,G.vert[v].data);//访问结点
    for(w=FirstAdjVex(G,v);w!=-1;w=NextAdjVex(G,v,w))//顺着结点的弧往下遍历
    {
        if(!isvisit[w])
        {
            if(G.vert[w].firstarc&&G.vert[w].firstarc->adjvex==-1)//判断是否为清除结点
                continue;
            DFS(G,w);//递归遍历下一个结点
        }
    }
}
status BFSTraverse(Graph G,status(*visit)(GElemType e,ElemType data))
{
    reset(isvisit);//清空访问数组
    int queue[100];//创造队列
    int front=0,tail=0,i,j,k;
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)//依次遍历所有结点
    {
        if(isvisit[i]||(G.vert[i].firstarc&&G.vert[i].firstarc->adjvex==-1))//判断是否访问过和是否已经被清空
            continue;
        isvisit[i]++;//标记为已经访问过
        visit(G.vert[i].key,G.vert[i].data);//访问结点
        queue[(tail++)%100]=i;//结点入队
        while(front!=tail)//判断队列是否为空
        {
            j=queue[front%100];
            front=(++front)%100;//出队
            for(k=FirstAdjVex(G,j);k+1;k=NextAdjVex(G,j,k))//从出队元素的第一条弧开始遍历
            {
                if(!isvisit[k]&&G.vert[i].firstarc&&G.vert[i].firstarc->adjvex!=-1)//判断结点是否访问过是否已被删除
                {
                    isvisit[k]++;
                    visit(G.vert[k].key,G.vert[k].data);//访问结点
                    queue[tail++]=k;//结点入队
                }
            }
        }
    }
    putchar('\n');
}
status OpenFile(Graph &G)
{
    FILE *fp;
    char filename[30],c;
    int num,i;
    reset(flag);//清空标记数组
    printf("请输入文件名。\n");
    scanf("%s",filename);//获得文件名
    if(!(fp=fopen(filename,"r")))//打开文件失败提示
    {
        printf("文件打开失败！\n");
        return ERROR;
    }
    fscanf(fp,"%d",&num);//读入结点数量
    fscanf(fp,"%c",&c);
    if(num<0||num>MAX_GRAPH_SIZE)//结点数量不在合法范围内
    {
        printf("结点数量有误。\n");//提示错误
        fclose(fp);
        return ERROR;
    }
    for(i=0;i<num;i++)//依次读入所有结点
        fscanf(fp,"%c",&vnode[i]),flag[vnode[i]]++,fscanf(fp,"%c",&c);;
    i=0;
    fscanf(fp,"%c",&c);//读入回车符
    while(1)
    {
        fscanf(fp,"%c",&vr[i][0]);//读入弧尾
        if(vr[i][0]=='#')//判断是否已经读完
            break;
        fscanf(fp,"%c",&c);
        fscanf(fp,"%c",&vr[i][1]);//读入弧头
        fscanf(fp,"%c",&c);
        i++;
    }
    fclose(fp);//关闭文件
    CreateGraph(G,vnode,vr);//根据读入的数据创建图
    return OK;
}
status SaveFile(Graph G)
{
    FILE *fp;
    char filename[30];
    int i;
    ArcNode *p;
    printf("请输入要保存的文件名。\n");
    scanf("%s",filename);//获得文件名
    if(!(fp=fopen(filename,"w")))//文件打开失败提示
    {
        printf("文件打开失败！\n");
        return ERROR;
    }
    fprintf(fp,"%d\n",G.vexnum);//读入图的结点数
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)
    {
        if(G.vert[i].key!='#')//结点没被删除则读入其关键值
            fprintf(fp,"%c ",G.vert[i].key);
    }
    fprintf(fp,"\n");
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)
    {
        if(G.vert[i].key=='#')//跳过被删除结点
            continue;
        p=G.vert[i].firstarc;
        while(p)
        {
            if(p->adjvex!=-1)
                fprintf(fp,"%c %c\n",G.vert[i].key,G.vert[p->adjvex].key);//依次读入图的所有弧
            p=p->nextarc;
        }
    }
    fprintf(fp,"#");//读入结束符
    fclose(fp);
    return OK;
}
int find(AGraph &G,char names[])
{
    int i;
    for(i=0;i<graphnum;i++)//依次检测图组中的图是否为要找的图
    {
        if(!strcmp(G.elem[i].name,names))//名称相同则找到
            return i;//返回其位序
    }
    return -1;
}
status visit(GElemType e,ElemType data)
{
    printf("%c(%d) ",e,data);//输出结点的关键值与数据
    return OK;
}
void reset(int flag[])
{
    int i;
    for(i=0;i<100;i++)//依次把数组所有的数设为零
        flag[i]=0;
}
void Print(Graph G)
{
    int i;
    ArcNode *p;
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)//依次输出每一个结点关键值和其所指向的结点关键值
    {
        p=G.vert[i].firstarc;
        if(p&&p->adjvex==-1)//结点没有弧或者被删除跳过
            continue;
        printf("%c->",G.vert[i].key);
        while(p)
            printf("%c ",G.vert[p->adjvex].key),p=p->nextarc;//依次输出当前结点所指结点的关键值
        putchar('\n');
    }
}