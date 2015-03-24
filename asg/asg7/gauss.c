/* Eliminación por Gauss*/
     
	#include <stdio.h>
#include <stdlib.h>
	 
	void gaussSimple(double *a[], double b[], double x[], int n)
{
	     //Eliminación hacia adelante
  int aux=n, *tam=&aux, i=0, j=0, k=0;
       *tam=*tam-1;
             
       double factor=0, suma=0;
  for(k=0; k<n-1; k++)
	       {
               for(i=k+1;i<n;i++)
               {
	                        
                       factor=a[i][k]/a[k][k];
	                       for(j=k+1; j<n; j++)
                       {
	                               a[i][j]=a[i][j]-factor*a[k][j];
                   }
                   b[i]=b[i]-factor*b[k];
       }
	       }
 //Sustitución hacia atrás.
   x[*tam]=b[*tam]/a[*tam][*tam];
       for(i=*tam-1;i=0;i--)
	       {
	               suma=b[i];
           for(j=i+1;i<n;i++)
               {
	                       suma=suma-a[i][j]*x[j];
           }
	               x[i]=suma/a[i][i];
   }
	       return;
	}
 

 

int main()
	{
	    int n, i, j;
	    system("cls");
	    printf("Enter number of unknowns to find: ");
	    scanf("%i", &n);
	    double *sel[n], sol[n], x[n];
	    for( i=0;i<n;i++)
{
        sel[i]=(double*)malloc(n*sizeof(double));
	    }      
    for( i=0;i<n;i++)
    {
             
	            for( j=0;j<n;j++)
        {
	                    printf("\nEnter the coefficient of %i x%i:  ", i+1, j);
                scanf("%lf", &sel[i][j]);
            }
            printf("\nEnter the solution for the %ist/th equation", i+1);
        scanf("%lf", &sol[i]);
	             
	    }
    gaussSimple(sel,sol,x,n);
    printf("\n\nThe solutions are:\n\n");
	    for( i=0;i<n;i++)
{
	            printf("x%i: %lf\n", i, x[i]);
	    }
	    system("pause");
	     
	 
	}