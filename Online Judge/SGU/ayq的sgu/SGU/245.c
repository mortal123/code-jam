#include <stdio.h>
#define oo 1000000000
#define Max(a,b) ((a)>(b)?(a):(b))

struct Case1
{
   long x,y;
}d[90001]={{0,0}},Walk[1201]={{0,0}},Rec_walk[1201]={{0,0}};
long Rx[4]={0,0,-1,1},Ry[4]={1,-1,0,0},Bx[4]={1,1,-1,-1},By[4]={1,-1,1,-1},Mx[8]={-1,0,1,1,1,0,-1,-1},My[8]={1,1,1,0,-1,-1,-1,0},Kx[8]={-1,-2,1,2,1,2,-1,-2},Ky[8]={-2,-1,2,1,-2,-1,2,1},Rec[305][305]={0},Danger[305][305]={0};
char Hash[305][305]={'\0'},Reach[305][305]={'\0'},Finish[305][305]={'\0'},Map[305][305]={'\0'};
long n,m,Vp,Vr,Vk,Vb,Vq,Vm,Lost,Tot,Sum,Sx,Sy,Ptot,Ans=0;

long Value(char Role)
{
   switch (Role)
   {
      case 'P':return Vp;
      case 'R':return Vr;
      case 'K':return Vk;
      case 'B':return Vb;
      case 'Q':return Vq;
      case 'M':return Vm;
   }
   return 0;
}

void Get(long x,long y,char Role,long Flag)
{
   long i,j;
   Tot=0;
   if (Role=='R'||Role=='Q')
      for (i=0;i<4;i++)
      {
         j=0;
         do
         {
            j++;
            if (!Hash[x+j*Rx[i]][y+j*Ry[i]])
               Walk[++Tot]=(struct Case1){x+j*Rx[i],y+j*Ry[i]};
            else if (Flag)
               break;
         }while (Map[x+j*Rx[i]][y+j*Ry[i]]=='.');
      }
   if (Role=='B'||Role=='Q')
      for (i=0;i<4;i++)
      {
         j=0;
         do
         {
            j++;
            if (!Hash[x+j*Bx[i]][y+j*By[i]])
               Walk[++Tot]=(struct Case1){x+j*Bx[i],y+j*By[i]};
            else if (Flag)
               break;
         }while (Map[x+j*Bx[i]][y+j*By[i]]=='.');
      }
   if (Role=='K')
   {
      for (i=0;i<8;i++)
         if (x+Kx[i]>0&&x+Kx[i]<=n&&y+Ky[i]>0&&y+Ky[i]<=m&&!Hash[x+Kx[i]][y+Ky[i]])
            Walk[++Tot]=(struct Case1){x+Kx[i],y+Ky[i]};
   }
   if (Role=='M')
   {
      for (i=0;i<8;i++)
         if (!Hash[x+Mx[i]][y+My[i]])
            Walk[++Tot]=(struct Case1){x+Mx[i],y+My[i]};
   }
   if (Role=='P')
   {
      if (!Hash[x-1][y-1])
         Walk[++Tot]=(struct Case1){x-1,y-1};
      if (!Hash[x-1][y+1])
         Walk[++Tot]=(struct Case1){x-1,y+1};
   }
}

long Solve(long x,long y,char Role)
{
   long i,j,Px,Py,St=1,En=1,Max=0;
   Hash[x][y]=1;
   d[1]=(struct Case1){x,y};
   Sum=0;
   while (St<=En)
   {
      Px=d[St].x;
      Py=d[St++].y;
      if (Map[Px][Py]!='.')
      {
         Sum+=Value(Map[Px][Py]);
         Get(Px,Py,Map[Px][Py],0);
         for (i=1;i<=Tot;i++)
         {
            Danger[Walk[i].x][Walk[i].y]--;
            if (!Danger[Walk[i].x][Walk[i].y]&&Reach[Walk[i].x][Walk[i].y]&&!Hash[Walk[i].x][Walk[i].y])
            {
               d[++En]=Walk[i];
               Hash[Walk[i].x][Walk[i].y]=1;
            }
         }
      }
      Get(Px,Py,Role,1);
      for (i=1;i<=Tot;i++)
      {
         Reach[Walk[i].x][Walk[i].y]=1;
         if (!Danger[Walk[i].x][Walk[i].y])
         {
            d[++En]=Walk[i];
            Hash[Walk[i].x][Walk[i].y]=1;
         }
      }
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (!Hash[i][j]&&Reach[i][j])
            Max=Max(Max,Value(Map[i][j])-Lost);
   Ans=Max(Ans,Sum+Max);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
      {
         Finish[i][j]|=Hash[i][j];
         Danger[i][j]=Rec[i][j];
         Hash[i][j]=(Map[i][j]=='#');
         Reach[i][j]=0;
      }
}

void Work(char Role)
{
   long i,j;
   if (!Rec[Sx][Sy])
      Solve(Sx,Sy,Role);
   else
   {
      Get(Sx,Sy,Role,0);
      for (i=1;i<=Tot;i++)
         Rec_walk[i]=Walk[i];
      Ptot=Tot;
      memset(Finish,'\0',sizeof(Finish));
      for (i=1;i<=Ptot;i++)
         if (Danger[Rec_walk[i].x][Rec_walk[i].y])
            Ans=Max(Ans,Value(Map[Rec_walk[i].x][Rec_walk[i].y])-Lost);
         else if (!Finish[Rec_walk[i].x][Rec_walk[i].y])
           Solve(Rec_walk[i].x,Rec_walk[i].y,Role);
   }
}

int main()
{
   long i,j,k;
   scanf("%ld%ld%ld%ld%ld%ld%ld%ld%ld\n",&n,&m,&Vp,&Vr,&Vk,&Vb,&Vq,&Vm,&Lost);
   for (i=1;i<=n;i++)
      gets(Map[i]+1);
   for (i=0;i<=m+1;i++)
      Hash[0][i]=Hash[n+1][i]=1;
   for (i=1;i<=n;i++)
      Hash[i][0]=Hash[i][m+1]=1;
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (Map[i][j]=='@')
         {
            Sx=i;
            Sy=j;
            Map[i][j]='.';
         }
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (Map[i][j]!='.'&&Map[i][j]!='#')
         {
            Get(i,j,Map[i][j],0);
            for (k=1;k<=Tot;k++)
               Danger[Walk[k].x][Walk[k].y]++;
         }
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
      {
         Rec[i][j]=Danger[i][j];
         Hash[i][j]=(Map[i][j]=='#');
      }
   Work('R');
   Work('M');
   Work('K');
   Work('B');
   printf("%ld\n",Ans);
   return 0;
}
