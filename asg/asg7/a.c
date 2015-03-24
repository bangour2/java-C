# include <stdio.h>
# include <math.h>
# define MAX 10
void main()
{
int i,j,n,k;
float mat[MAX][MAX],x[MAX],temp,pivot,sum=0;

printf("\t\t\t GAUSS ELIMINITION METHOD\n");
printf("-------------------------------------------------------------------\n");
printf("Enter No of Equtions : ");
scanf("%d",&n);
printf("Enter Coefficients of Eqution \n");
for(i=1;i<=n;i++)
for(j=1;j<=n;j++)
scanf("%f",&mat[i][j]);
printf("Enter Constant value\n");
for(i=1;i<=n;i++)
{
scanf("%f",&mat[i][n+1]);
x[i]=mat[i][n+1];
}
for(i=2;i<=n;i++)
{
for(j=i;j<=n;j++)
{
pivot=mat[j][i-1]/mat[i-1][i-1];
for(k=i-1;k<=n+1;k++)
mat[j][k]=mat[j][k]-pivot*mat[i-1][k];
}
}
printf("Eliminated matrix as :- \n");
for(i=1;i<=n;i++)
{
for(j=1;j<=n+1;j++)
printf("\t%.2f",mat[i][j]);
printf("\n");
}
for(i=1;i<=n;i++)
{
if(mat[i][i]==0)
{
printf("Since diagonal element become zero\n Hence solution is not possible\n");
exit(1);
}
}
printf("Solution : \n");
for(i=0;i <n; i++){
sum=0;
for(j=n;j>n-i;j--)
sum=sum+mat[n-i][j];

x[n-i]=(mat[n-i][n+1]-sum*x[n])/mat[n-i][n-i];
printf("X%d = %4.2f\n",n-i,x[n-i]);
}

}