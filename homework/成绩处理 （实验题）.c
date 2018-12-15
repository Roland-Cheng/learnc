#include<stdio.h>
#define M 5
#define N 5
#define p 100

int main()
{
    char name[N][p], class[M][p], *cp=class[0], *np=name[0];
    double grade[N][M], * gp[N];
    double sum[N], csum[M], *csp = csum;
    int i;
    for(i=0;i<N;i++) gp[i] = grade[i];
    for(i=0;i<M;i++,cp+=p) scanf(" %s",cp);
    cp = class[0];
    for(i=0;i<N;i++,np+=p)
    {
        scanf(" %s",np);
        for (;gp[i]<grade[i]+M;gp[i]++) scanf("%le",gp[i]);
        gp[i]-=M;
    }

    np = name[0];
    for(i=0;i<N;i++)
    {
        for (;gp[i]<grade[i]+M;gp[i]++) sum[i]+=*gp[i];
        gp[i]-=M;
        printf("Average score of %s is %.2f\n",name[i],sum[i]/M);
    }
    for(;csp<csum+M;cp+=p,csp++) 
    {
        for(i=0;i<N;*csp+=*gp[i],gp[i]++,i++);
        printf("Average score of %s is %.2f\n",cp,*csp/N);
    }

    for(i=0;i<N;i++) gp[i] = grade[i];
    cp = class[0];
    csp = csum;
    for(;csp<csum+M;cp+=p,csp++) 
    {
        int j=0;
        for(i=0;i<N;gp[i]++,i++) if(*gp[i]<*csp/N) j++;
        printf("Number of students lower than avg of %s is %d\n",cp,j);
    }

    for(i=0;i<N;i++) gp[i] = grade[i];
    cp = class[0];
    for(;cp<class[0]+p*M;cp+=p)
    {
        int j=0;
        for(i=0;i<N;gp[i]++,i++) if(*gp[i]<60) j++;
        printf("Number of students %s fail is %d\n",cp,j);
    }

    for(i=0;i<N;i++) gp[i] = grade[i];
    cp = class[0];
    for(;cp<class[0]+p*M;cp+=p)
    {
        int j=0;
        for(i=0;i<N;gp[i]++,i++) if(*gp[i]>=90) j++;
        printf("Number of students %s perfect is %d\n",cp,j);
    }
}