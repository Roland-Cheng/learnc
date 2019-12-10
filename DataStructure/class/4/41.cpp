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
    int adjvex;//������һ���
    struct ArcNode *nextarc;//������һ����
    int info;
}ArcNode;
typedef struct VNode
{
    ArcNode *firstarc;//���ĵ�һ����
    ElemType data;//�������
    GElemType key;//���Ĺؼ�ֵ
}VNode,NodeList[MAX_GRAPH_SIZE];
typedef struct
{
    NodeList vert;//ͼ�Ľ�㼯
    int vexnum,arcnum;//ͼ�Ľ������������Ŀ
    char name[30];
}Graph;
typedef struct
{
    Graph *elem;
    int length;
    int graphsize;
}AGraph;

status CreateGraph(Graph &G,GElemType V[],GElemType VR[][4]);//����ͼ�Ľ�㼯�ͻ�������һ������ͼ
status DestroyGraph(Graph &G);//����Ŀ��ͼ
status LocateVex(Graph G,GElemType u);//��λĿ����
status PutVex(Graph &G,GElemType u,ElemType value);//��㸳ֵ
status FirstAdjVex(Graph G,ElemType u);//���ĵ�һ����
status NextAdjVex(Graph G,ElemType v,ElemType w);//Ŀ�����������һ������һ����
status InsertVex(Graph &G,GElemType v);//������
status DeleteVex(Graph &G,GElemType v);//ɾ�����
status InsertArc(Graph &G,GElemType v,GElemType w);//���뻡
status DeleteArc(Graph &G,GElemType v,GElemType w);//ɾ����
status DFSTraverse(Graph G,status(*visit)(GElemType e,ElemType data));//����ű���ͼ
status BFSTraverse(Graph G,status(*visit)(GElemType e,ElemType data));//������ȱ���ͼ
status OpenFile(Graph &G);//���ļ��ж�ȡ����
status SaveFile(Graph G);//�����ݴ����ļ�
int find(AGraph &G,char names[]);//����Ŀ��ͼ
status visit(GElemType e,ElemType data);//�����������
void meset(int flag[]);//�������
int len(char V[]);//�����鳤��
void DFS(Graph G,ElemType v);//����������ȱ�������
void Print(Graph G);//��ӡͼ���ڽӱ�

int flag[100],isvisit[100],num[100];//������飬�Ƿ�������飬ɾ���������
GElemType vnode[MAX_GRAPH_SIZE+1];//��㼯1
GElemType vr[MAX_GRAPH_SIZE][4];//����
int graphnum;//ͼ������
AGraph G1;//ͼ��

int main()
{
    int op,i,t,w=0,n,flag1=0;
    char name1[50],e,c;;
    G1.length=0;
    G1.graphsize=GRAPHINCREMENT;
    G1.elem=(Graph*)malloc(G1.graphsize*sizeof(Graph));//����һ���յ�ͼ��
    putchar('\n');
    while(op)
    {
        putchar('\n');
        printf("\tWelcome to use Menu for Graph Building!\n\n\n");
        printf("---------------------------------------------------------\n");
        printf("\t1.CreateGraph\t\t  2.DestroyGraph\n");
        printf("\t3.LocateVex\t\t  4.PutVex\n");
        printf("\t5.FirstAdjVex\t\t  6.NextAdjVex\n");
        printf("\t7.InsertVex\t\t  8.DeleteVex\n");
        printf("\t9.InsertArc\t\t  10.DeleteArc\n");
        printf("\t11.DFSTraverse\t\t  12.BFSTraverse\n");
        printf("\t13.OpenFile\t\t  14.SaveFile\n");
        printf("\t15.GraphList\t\t  0.Exit\n");
        printf("\t16.PrintGraph\n");
        printf("---------------------------------------------------------\n");//��ӡ���˵�
        printf("��ѡ����Ĳ���(0~16)\n");//����˵�
        scanf("%d",&op);
        getchar();
        switch(op)//����op�ж��û�ִ�в���
        {
        case 0://Ϊ0�˳�ѭ��
            break;
        case 1:
            printf("������ͼ�����ơ�Ĭ��Ϊ��������ͼ��\n");
            scanf("%s",G1.elem[graphnum].name);//��ȡͼ������
            printf("��ѡ���ȡ��ʽ��1.���̸�ֵ 2.�ļ���ȡ\n");//ѡ���ȡ��ʽ
            scanf("%d",&t);
            while(t!=1&&t!=2)//�������ֲ�����������
            {
                printf("���ٴ�������ȷ�����֡�\n");
                scanf("%d",&t);
            }
            if(t==1)//���̶�ȡ
            {
                printf("������ͼ�Ľ��������\n");
                scanf("%d",&n);//��ý������
                while(n<=0||n>MAX_GRAPH_SIZE)//����������ںϷ���Χ����ʾ������������
                {
                    printf("������������0-100��Χ�ڵ����֣�\n");
                    scanf("%d",&n);
                }
                printf("������ͼ�Ľ��ؼ�ֵ(��дӢ����ĸ)��\n");
                getchar();
                for(i=0;i<n;i++)
                {
                    scanf("%c",&vnode[i]);//��ý��ؼ�ֵ
                    if(flag[vnode[i]-'A'])//���������Ӧλ�ò�Ϊ0����ùؼ�ֵ�Ѿ������
                    {
                        printf("�����ظ�������ʧ�ܣ�\n");
                        flag1=1;//flag��Ϊ1��֮��ֱ���˳�
                        break;
                    }
                    flag[vnode[i]-'A']++;//���������Ӧλ�ü�1
                    getchar();
                }
                if(flag1)//flagΪ1֤������ֱ���˳�
                {
                    meset(flag),getchar();//��ձ������
                    break;
                }
                vnode[i]='\0';
                printf("���������ϣ���ʼ����ͼ�ıߡ�\n");
                printf("������ߵ��������Ĺؼ�ֵ������ֵ֮���Կո��������� # �Խ�����������ĵ�һ�����ֵΪ��β��\n");
                i=0;
                while(1)
                {
                    scanf("%c",&vr[i][0]);//���ܻ�β�ؼ�ֵ
                    getchar();
                    if(vr[i][0]=='#')//�ؼ�ֵΪ#����������ϣ�����
                        break;
                    scanf("%c",&vr[i][1]);//���ܵڶ����ؼ�ֵ
                    while(!flag[vr[i][0]-'A']||!flag[vr[i][1]-'A'])//���������Ӧλ��Ϊ0����������Ĺؼ�ֵ������
                    {
                        printf("������Ĺؼ�ֵ�����ڣ����������롣\n");
                        getchar();
                        scanf("%c %c",&vr[i][0],&vr[i][1]);//��������
                    }
                    i++;getchar();
                }
                if(!CreateGraph(G1.elem[graphnum],vnode,vr))//����ͼʧ��
                {
                    printf("����ʧ�ܣ�\n");//��ʾʧ��
                    getchar();
                    break;
                }
                printf("�����ɹ���\n");//��ʾ�����ɹ�
                graphnum++;//ͼ��������һ
                meset(flag);//��ձ������
                break;
            }
            else//�ļ�����
            {
                if(!OpenFile(G1.elem[graphnum]))//������ʧ��
                    printf("�ļ���ȡʧ�ܣ�\n");
                else
                    printf("��ȡ��ɣ�\n"),graphnum++;//ͼ��������һ
                getchar();
                break;
            }
        case 2:
            printf("������Ҫ���ٵ�ͼ�����ơ�\n");
            scanf("%s",name1);//���ͼ������
            t=find(G1,name1);
            if(t==-1)//û���ҵ�ͼ��ʾ����
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            if(!DestroyGraph(G1.elem[t]))//����ʧ����ʾ������
            {
                printf("����ʧ�ܣ�\n");
                break;
            }
            printf("���ٳɹ���\n");
            for(i=t;i<graphnum-1;i++)//ͼ��Ԫ�ظ���ԭɾ����Ԫ��
                G1.elem[i]=G1.elem[i+1];
            graphnum--;//ͼ��������һ
            break;
        case 3:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            printf("������Ҫ��λ�Ķ���Ĺؼ�ֵ��\n");
            getchar();
            scanf("%c",&e);//���Ŀ����ؼ�ֵ
            w=LocateVex(G1.elem[t],e);//��ý���λ��
            if(w==-1)//-1�����㲻����
                printf("û���ҵ��ö��㣡\n");
            else
                printf("�ö����ǵ�%d�����㡣\n",w+1);//������λ��
            getchar();
            break;
        case 4:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            printf("������Ҫ��ֵ���Ĺؼ�ֵ��\n");
            getchar();
            scanf("%c",&e);//���Ŀ����ؼ�ֵ
            if(LocateVex(G1.elem[t],e)==-1)//-1����û���ҵ�Ŀ����
                printf("û���ҵ��ý�㣡\n");
            else
            {
                printf("������Ҫ����ֵ��\n");
                scanf("%d",&w);//��ý���ֵ
                if(!PutVex(G1.elem[t],e,w))//��ֵʧ����ʾ����
                    printf("��ֵʧ�ܣ�\n");
                else
                    printf("��ֵ�ɹ���\n");
            }
            getchar();
            break;
        case 5:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            printf("������Ҫ��ѯ�Ľ���λ��\n");
            getchar();
            scanf("%d",&w);//���Ŀ����λ��
            if(w<0||w>G1.elem[t].vexnum)//λ���ںϷ���Χ��
                printf("û���ҵ��ý�㣡\n");
            else
            {
                i=FirstAdjVex(G1.elem[t],w);
                if(i==-1)//-1����û���ҵ�Ŀ����
                    printf("û���ҵ�Ŀ���㣡\n");
                else
                    printf("�ý��Ĺؼ�ֵΪ%c�����һ���ڽӽ�����Ϊ%d,�ؼ�ֵΪ%c��\n",G1.elem[t].vert[w].key,i,G1.elem[t].vert[i].key);//������ڸý��ͻ�����Ϣ
            }
            getchar();
            break;
        case 6:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            printf("������Ҫ��ѯ�Ľ���λ��\n");
            getchar();
            scanf("%d",&w);//��õ�һ��Ŀ����λ��
            if(LocateVex(G1.elem[t],G1.elem[t].vert[w].key)==-1)//-1����û���ҵ�Ŀ����
            {
                printf("û���ҵ��ý�㣡\n");
                break;
            }
            scanf("%d",&n);//��õڶ���Ŀ����λ��
            if(LocateVex(G1.elem[t],G1.elem[t].vert[n].key)==-1)
            {
                printf("û���ҵ��ý�㣡\n");
                break;
            }
            getchar();
            i=NextAdjVex(G1.elem[t],w,n);//��ý����һ����
            if(i==-1)
                printf("Ŀ����Ϊ�ա�\n");
            else
                printf("�ý��Ĺؼ�ֵΪ%c������ڽ��%c��һ���ڽӶ���λ��Ϊ%d���ؼ�ֵΪ%c��\n",G1.elem[t].vert[w].key,G1.elem[t].vert[n].key,i,G1.elem[t].vert[i].key);//������ڸý��ͻ��Ĺؼ���Ϣ
            break;
        case 7:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            printf("������Ҫ����Ľ��Ĺؼ�ֵ��\n");
            getchar();
            scanf("%c",&e);//��ý��ؼ�ֵ
            w=0;
            for(i=0;i<G1.elem[t].vexnum;i++)//����Ŀ�����Ƿ��Ѿ�������ͼ��
                if(e==G1.elem[t].vert[i].key)
                printf("�ý���Ѿ���ͼ�д��ڡ�\n"),w=1;
            if(w)//wΪ1��������˳�
                break;
            if(!InsertVex(G1.elem[t],e))//������ʧ����ʾ
                printf("����ʧ�ܣ�\n");
            else
                printf("������ɣ�\n");//ɾ��������Ӧλ�ü�һ
            getchar();
            break;
        case 8:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            printf("������Ҫɾ���Ľ��Ĺؼ�ֵ��\n");
            getchar();
            scanf("%c",&e);//���Ҫɾ�����Ĺؼ�ֵ
            if(!DeleteVex(G1.elem[t],e))//ɾ��ʧ����ʾ
                printf("ɾ��ʧ�ܣ�\n");
            else
                printf("ɾ���ɹ���\n"),num[t]++;//ɾ���ɹ���ʾ
            getchar();
            break;
        case 9:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            printf("������Ҫ���뻡��������㣬��һ��Ϊ��β���ڶ���Ϊ��ͷ���ո������\n");
            getchar();
            scanf("%c %c",&e,&c);//��û�β�ͻ�ͷ
            if(!InsertArc(G1.elem[t],e,c))//���뻡ʧ����ʾ
                printf("������ʧ�ܣ�\n");
            else
                printf("������ɹ���\n");//���뻡�ɹ���ʾ
            getchar();
            break;
        case 10:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            printf("������Ҫɾ���Ļ��Ļ�β�ͻ�ͷ��\n");
            getchar();
            scanf("%c %c",&e,&c);//���Ŀ�껡β�ͻ�ͷ
            if(!DeleteArc(G1.elem[t],e,c))//ɾ����ʧ����ʾ
                printf("��ɾ��ʧ�ܣ�\n");
            else
                printf("��ɾ���ɹ���\n");//ɾ�����ɹ���ʾ
            getchar();
            break;
        case 11:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);//���Ҫ������ͼ��λ��
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            if(!DFSTraverse(G1.elem[t],visit))//������ȱ���ʧ����ʾ
                printf("����ʧ�ܣ�\n");
            else
                printf("�������\n");//������ȱ����ɹ���ʾ
            getchar();
            break;
        case 12:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);//���Ҫ������ͼ��λ��
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            if(!BFSTraverse(G1.elem[t],visit))//������ȱ���ʧ����ʾ
                printf("����ʧ�ܣ�\n");
            else
                printf("�������\n");//������ȱ����ɹ���ʾ
            getchar();
            break;
        case 13:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            printf("ȷ��Ҫ���ļ���ȡ��������ͼԭ�е����ݣ���Y/N��\n");//��ֹ�û���ʧ������һ��ȷ��
            getchar();
            scanf("%c",&e);
            if(e=='n'||e=='N')//�û�����ֹͣ�������˳�
                break;
            DestroyGraph(G1.elem[t]);//����ԭ����ͼ
            if(!OpenFile(G1.elem[t]))//�ļ���ȡʧ����ʾ
                printf("�ļ���ȡʧ�ܣ�\n");
            else
                printf("��ȡ��ɣ�\n");//�ļ���ȡ�ɹ���ʾ
            getchar();
            break;
        case 14:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            if(!SaveFile(G1.elem[t]))//�ļ�����ʧ����ʾ
                printf("�ļ�����ʧ�ܣ�\n");
            else
                printf("�ļ�����ɹ���\n");//�ļ�����ɹ���ʾ
            getchar();
            break;
        case 15:
            printf("��ǰ�������µ�ͼ��\n");
            for(i=0;i<graphnum;i++)//���������ǰ���ڵ�ͼ������
                printf("%s ",G1.elem[i].name);
            putchar('\n');
            break;
        case 16:
            printf("������Ҫ������ͼ\n");
            scanf("%s",name1);
            t=find(G1,name1);
            if(t==-1)
            {
                printf("û���ҵ����ͼ��\n");
                getchar();
                break;
            }
            Print(G1.elem[t]);//��ӡ��Ŀ��ͼ���ڽӱ�
            break;
        default:
            printf("��������ȷ�����֣�\n");//������������������ֳ�����ʾ��������
        }
        printf("---------------------------------------------------------\n");
        if(op)for(i=0;i<1499999999;i++);//�ӻ�������ת
        system("cls");//������ת
    }
    printf("�����������лʹ�ã�\n");
    return 0;
}
status CreateGraph(Graph &G,GElemType V[],GElemType VR[][4])
{
    int i,j,k;
    ArcNode *p;
    G.vexnum=len(V);//ͼ�Ľ����Ϊ�������ĳ���
    for(i=0;i<G.vexnum;i++)//ÿһ����㿪ʼ��û�л�������
        G.vert[i].key=V[i],G.vert[i].firstarc=NULL,G.vert[i].data=0;
    for(k=0;VR[k][0]!='#';k++)//��ʼ������
    {
        i=LocateVex(G,VR[k][0]);//�ҵ���β���λ��
        j=LocateVex(G,VR[k][1]);//�ҵ���ͷ���λ��
        p=G.vert[i].firstarc;//pָ�����һ����
        if(!p)//�ý�㻹û�л�������һ����
        {
            G.vert[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));//����ռ�
            G.vert[i].firstarc->adjvex=j;//��ָ��ͷ���λ��
            G.vert[i].firstarc->nextarc=NULL;//��һ����ΪNULL
        }
        else//����Ѿ��л�
        {
            while(p->nextarc)
                p=p->nextarc;//p�ƶ���������һ����
            p->nextarc=(ArcNode*)malloc(sizeof(ArcNode));//����ռ�
            p->nextarc->adjvex=j;//��ָ��ͷ���λ��
            p->nextarc->nextarc=NULL;//��һ����ΪNULL
        }
    }
    G.arcnum=k;//ͼ�Ļ���Ϊk
    return OK;
}
status DestroyGraph(Graph &G)
{
    int i,j;
    ArcNode *p,*q;
    for(i=0;i<G.vexnum;i++)//�����������н��
    {
        if(G.vert[i].firstarc)//����л�
        {
            p=G.vert[i].firstarc;
            q=G.vert[i].firstarc->nextarc;//qָ��ǰ������һ����
            while(q)
                free(p),p=q,q=q->nextarc;//ɾ��q��p��q���κ���
            free(p);//ɾ�����һ����
        }
    }
    return OK;
}
status LocateVex(Graph G,GElemType u)
{
    int i;
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)//��������ÿһ�����
    {
        if(G.vert[i].key==u)//���ؼ�ֵ��Ŀ��ؼ�ֵ��ͬ�����ҵ����
        {
            if(G.vert[i].firstarc&&G.vert[i].firstarc->adjvex==-1)//��㴢�����ɾ����Ϣ�����Ѿ���ɾ��
            {
                printf("���%c�ѱ�ɾ����\n",u);
                return -1;//���ش���
            }
            return i;//���ؽ��λ��
        }
    }
    return -1;//û���ҵ����ش���
}
status PutVex(Graph &G,GElemType u,ElemType value)
{
    int i=LocateVex(G,u);//��λ���
    if(i==-1)//��λʧ�ܴ�����δ�ҵ�
    {
        printf("�Ҳ����ý�㡣\n");
        return FALSE;
    }
    G.vert[i].data=value;//��Ŀ���㸳ֵ
    return OK;
}
status FirstAdjVex(Graph G,ElemType u)
{
    if(!G.vert[u].firstarc)//���û�л�
        return -1;
    return G.vert[u].firstarc->adjvex;//���ػ�ָ���λ��
}
status NextAdjVex(Graph G,ElemType v,ElemType w)
{
    ArcNode *p;
    p=G.vert[v].firstarc;//pָ�����һ����
    while(p&&p->nextarc)//pһֱ������
    {
        if(p->adjvex==w)//����λ��ΪĿ����λ��
            return p->nextarc->adjvex;//����Ŀ�껡��λ��
        p=p->nextarc;//p����
    }
    return -1;
}
status InsertVex(Graph &G,GElemType v)
{
    G.vert[G.vexnum+num[find(G1,G.name)]].key=v;//�����������Ԫ��
    G.vert[num[find(G1,G.name)]+G.vexnum++].firstarc=NULL;//���һ��ʼû�л�
    return OK;
}
status DeleteVex(Graph &G,GElemType v)
{
    int i=LocateVex(G,v),j;//��λҪɾ�����
    ArcNode *p,*q;
    if(G.vert[i].firstarc)//ɾ������л�������ջ�
    {
        p=G.vert[i].firstarc;
        if(p->nextarc)//����ж�����
        {
            p=p->nextarc;
            while(p->nextarc)//����ɾ�����еĻ�
            {
                q=p->nextarc;
                free(p);//�ͷŻ��Ŀռ�
                p=q;
                G.arcnum--;//ͼ�Ļ�������
            }
            if(p)free(p),G.arcnum--;//ɾ�����һ����
        }
        G.vert[i].firstarc->adjvex=-1;//���Ϊ�����
        G.vert[i].firstarc->nextarc=NULL;
        G.vert[i].key='#';
    }
    else//û�л����贴��һ�������ǻ�
    {
        G.vert[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
        G.vert[i].firstarc->adjvex=-1;
        G.vert[i].firstarc->nextarc=NULL;
        G.vert[i].key='#';
    }
    for(j=0;j<G.vexnum;j++)//��������ڽӱ����й�ɾ���������б���
    {
        if(j==i)continue;//��ɾ��������
        if(!G.vert[j].firstarc)//���û�л�������
            continue;
        p=G.vert[j].firstarc;
        if(G.vert[j].firstarc->adjvex==i)//������ӵ�һ������ΪҪɾ���Ľ��
        {
            G.vert[j].firstarc=G.vert[j].firstarc->nextarc;//ɾ����һ����
            free(p);//�ͷſռ�
            G.arcnum--;//ͼ�Ļ�������
            continue;
        }
        q=p->nextarc;//qָ����һ����
        while(q)
        {
            if(q->adjvex==i)//��ΪҪɾ���Ļ�
            {
                p->nextarc=q->nextarc;//p����һ����Ϊq����һ����
                free(q);//�ͷ�q
                G.arcnum--;//ͼ�Ļ�������
                break;
            }
            p=q,q=q->nextarc;//p��q����
        }
    }
    G.vexnum--;
    return OK;
}
status InsertArc(Graph &G,GElemType v,GElemType w)
{
    ArcNode *p,*q;
    int i=LocateVex(G,v),j=LocateVex(G,w);//��λ�������λ��
    if(!G.vert[i].firstarc)//��β���û�л���ֱ�ӽ������һ����
    {
        G.vert[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));//����ռ�
        G.vert[i].firstarc->adjvex=j;//ָ��ָ��λ��
        G.vert[i].firstarc->nextarc=NULL;//��һ�����ÿ�
    }
    p=G.vert[i].firstarc;
    while(p->nextarc)
        p=p->nextarc;//p���Ƶ����һ����
    p->nextarc=(ArcNode*)malloc((sizeof(ArcNode)));//����ռ����һ����
    p->nextarc->adjvex=j;//ָ��ָ��λ��
    p->nextarc->nextarc=NULL;
    G.arcnum++;//����������һ
    return OK;
}
status DeleteArc(Graph &G,GElemType v,GElemType w)
{
    ArcNode *p,*q;
    int i=LocateVex(G,v),j=LocateVex(G,w);//��λĿ����
    p=G.vert[i].firstarc;
    if(!p||G.vert[i].firstarc->adjvex==-1)//��һ���������ڻ��߽���ѱ�ɾ������
    {
        printf("û�������ߣ�\n");
        return ERROR;
    }
    G.arcnum--;
    if(p->adjvex==j)//��һ����ΪҪɾ���Ļ�
    {
        G.vert[i].firstarc=G.vert[i].firstarc->nextarc;//ɾ��Ŀ�껡
        free(p);//�ͷſռ�
        return OK;
    }
    q=p->nextarc;
    while(q)//���μ��֮��Ļ�
    {
        if(q->adjvex==j)//����Ŀ�껡
        {
            p->nextarc=q->nextarc;//ɾ������
            free(q);//�ͷſռ�
            break;
        }
        p=q;
        q=q->nextarc;//p��q����
    }
    if(q)
        return OK;
    else
        return FALSE;
}
status DFSTraverse(Graph G,status(*visit)(GElemType e,ElemType data))
{
    meset(isvisit);//��շ�������
    int i;
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)//���α������н��
    {
        if(!isvisit[i])//���û�б�����
        {
            if(G.vert[i].firstarc&&G.vert[i].firstarc->adjvex==-1)//�ж��Ƿ�Ϊ������
                continue;
            DFS(G,i);//������ȱ���
        }
    }
    putchar('\n');
    return OK;
}
void DFS(Graph G,ElemType v)
{
    int w;
    isvisit[v]++;//���Ϊ�Ѿ����ʹ�
    visit(G.vert[v].key,G.vert[v].data);//���ʽ��
    for(w=FirstAdjVex(G,v);w!=-1;w=NextAdjVex(G,v,w))//˳�Ž��Ļ����±���
    {
        if(!isvisit[w])
        {
            if(G.vert[w].firstarc&&G.vert[w].firstarc->adjvex==-1)//�ж��Ƿ�Ϊ������
                continue;
            DFS(G,w);//�ݹ������һ�����
        }
    }
}
status BFSTraverse(Graph G,status(*visit)(GElemType e,ElemType data))
{
    meset(isvisit);//��շ�������
    int queue[100];//�������
    int front=0,tail=0,i,j,k;
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)//���α������н��
    {
        if(isvisit[i]||(G.vert[i].firstarc&&G.vert[i].firstarc->adjvex==-1))//�ж��Ƿ���ʹ����Ƿ��Ѿ������
            continue;
        isvisit[i]++;//���Ϊ�Ѿ����ʹ�
        visit(G.vert[i].key,G.vert[i].data);//���ʽ��
        queue[(tail++)%100]=i;//������
        while(front!=tail)//�ж϶����Ƿ�Ϊ��
        {
            j=queue[front%100];
            front=(++front)%100;//����
            for(k=FirstAdjVex(G,j);k+1;k=NextAdjVex(G,j,k))//�ӳ���Ԫ�صĵ�һ������ʼ����
            {
                if(!isvisit[k]&&G.vert[i].firstarc&&G.vert[i].firstarc->adjvex!=-1)//�жϽ���Ƿ���ʹ��Ƿ��ѱ�ɾ��
                {
                    isvisit[k]++;
                    visit(G.vert[k].key,G.vert[k].data);//���ʽ��
                    queue[tail++]=k;//������
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
    meset(flag);//��ձ������
    printf("�������ļ�����\n");
    scanf("%s",filename);//����ļ���
    if(!(fp=fopen(filename,"r")))//���ļ�ʧ����ʾ
    {
        printf("�ļ���ʧ�ܣ�\n");
        return ERROR;
    }
    fscanf(fp,"%d",&num);//����������
    if(num<0||num>MAX_GRAPH_SIZE)//����������ںϷ���Χ��
    {
        printf("�����������\n");//��ʾ����
        fclose(fp);
        return ERROR;
    }
    for(i=0;i<num;i++)//���ζ������н��
        fscanf(fp,"%c",&vnode[i]),flag[vnode[i]]++;
    i=0;
    fscanf(fp,"%c",&c);//����س���
    while(1)
    {
        fscanf(fp,"%c",&vr[i][0]);//���뻡β
        if(vr[i][0]=='#')//�ж��Ƿ��Ѿ�����
            break;
        fscanf(fp,"%c",&c);
        fscanf(fp,"%c",&vr[i][1]);//���뻡ͷ
        fscanf(fp,"%c",&c);
        i++;
    }
    fclose(fp);//�ر��ļ�
    CreateGraph(G,vnode,vr);//���ݶ�������ݴ���ͼ
    return OK;
}
status SaveFile(Graph G)
{
    FILE *fp;
    char filename[30];
    int i;
    ArcNode *p;
    printf("������Ҫ������ļ�����\n");
    scanf("%s",filename);//����ļ���
    if(!(fp=fopen(filename,"w")))//�ļ���ʧ����ʾ
    {
        printf("�ļ���ʧ�ܣ�\n");
        return ERROR;
    }
    fprintf(fp,"%d",G.vexnum);//����ͼ�Ľ����
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)
    {
        if(G.vert[i].key!='#')//���û��ɾ���������ؼ�ֵ
            fprintf(fp,"%c",G.vert[i].key);
    }
    fprintf(fp,"\n");
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)
    {
        if(G.vert[i].key=='#')//������ɾ�����
            continue;
        p=G.vert[i].firstarc;
        while(p)
        {
            if(p->adjvex!=-1)
                fprintf(fp,"%c %c\n",G.vert[i].key,G.vert[p->adjvex].key);//���ζ���ͼ�����л�
            p=p->nextarc;
        }
    }
    fprintf(fp,"#");//���������
    fclose(fp);
    return OK;
}
int find(AGraph &G,char names[])
{
    int i;
    for(i=0;i<graphnum;i++)//���μ��ͼ���е�ͼ�Ƿ�ΪҪ�ҵ�ͼ
    {
        if(!strcmp(G.elem[i].name,names))//������ͬ���ҵ�
            return i;//������λ��
    }
    return -1;
}
status visit(GElemType e,ElemType data)
{
    printf("%c(%d) ",e,data);//������Ĺؼ�ֵ������
    return OK;
}
void meset(int flag[])
{
    int i;
    for(i=0;i<100;i++)//���ΰ��������е�����Ϊ��
        flag[i]=0;
}
int len(char V[])
{
    int i;
    for(i=0;V[i]!='\0';i++);//����ַ�������
    return i;
}
void Print(Graph G)
{
    int i;
    ArcNode *p;
    for(i=0;i<G.vexnum+num[find(G1,G.name)];i++)//�������ÿһ�����ؼ�ֵ������ָ��Ľ��ؼ�ֵ
    {
        p=G.vert[i].firstarc;
        if(p&&p->adjvex==-1)//���û�л����߱�ɾ������
            continue;
        printf("%c->",G.vert[i].key);
        while(p)
            printf("%c ",G.vert[p->adjvex].key),p=p->nextarc;//���������ǰ�����ָ���Ĺؼ�ֵ
        putchar('\n');
    }
}
