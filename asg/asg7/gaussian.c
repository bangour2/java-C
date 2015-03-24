#include<stdio.h>
double **matrix;
double *temp;
double **coeff;
double *unknownvar;
int variables;
int row,column,inner;
void setdiagonal(int row)
{//this function exchanges rows in case we have the diagonal entries while tranforming as zero
    int ctr=0;
    while(matrix[row][row]==0)
            {
                if(row+1!=variables)
                {//exchange with the next row until we are not on the last row
                    temp=matrix[row];
                    matrix[row]=matrix[row+1];
                    matrix[row+1]=temp;
                    temp=coeff[row];
                    coeff[row]=coeff[row+1];
                    coeff[row+1]=temp;
                }
                else
                {//exchange the last row with thr first one
                    temp=matrix[row];
                    matrix[row]=matrix[0];
                    matrix[0]=temp;
                    temp=matrix[row];
                    coeff[row]=coeff[0];
                    coeff[0]=temp;
                }
                ctr++;
                if(ctr==variables)
                {//exchanging the row with all others rows doesnot make diagonal entry non-zero then we do not have a solution
                    printf("The system of equations can not be solved by gauss elimination method");
                   // getch();
                    exit(0);
                }
            }
}
void reduceMatrices()
{//this function reduces the matrix in upper triangular form
    double multfactor;
    for(row=0;row<variables;row++)
    {
        if(matrix[row][row]==0)
        setdiagonal(row);//set the diagonal if it's entry is 0
        for(inner=row+1;inner<variables;inner++)
        {
            multfactor=matrix[inner][row]/matrix[row][row];//the multfactor is a factor which is used to multiply with a row to make the next row's some entry 0
            coeff[inner][0]=coeff[inner][0]-multfactor*coeff[row][0];
            for(column=0;column<variables;column++)
            matrix[inner][column]=matrix[inner][column]-multfactor*matrix[row][column];
        }
    }
}
int main()
{
    printf("Enter the number of variables\n");
    scanf("%d",&variables);
    matrix=(double**)malloc(variables*sizeof(double));//declare the matrix to hold the coefficents
    coeff=(double **)malloc(variables*sizeof(double));//declare the matrix to hold the rhs coefficients
    unknownvar=(double*)malloc(variables*sizeof(double));//declare the matrix of the unknown variables
    int i,j;
    for(row=0;row<variables;row++)
    {
        matrix[row]=(double*)malloc(variables*sizeof(double));
        coeff[row]=(double*)malloc(variables*sizeof(double));
    }
    temp=(double*)malloc(variables*sizeof(double));//temporary array used while swapping rows
    printf("Enter the coefficent matrix of the unknown variables\n");
    for(row=0;row<variables;row++)
    for(column=0;column<variables;column++)
        scanf("%lf",&matrix[row][column]);
    printf("Enter the coefficent matrix of the RHS\n");
    for(row=0;row<variables;row++)
        scanf("%lf",&coeff[row][0]);
    reduceMatrices();//We call the function to reduce both coefficent matrices to a form to allow apllication of backward substitution
    double sum;
    for(row=variables-1;row>=0;row--)
    {//This is the coding for the backward substitution
    sum=coeff[row][0];
    for(column=row+1;column<variables;column++)
    sum=sum-matrix[row][column]*unknownvar[column];
    if(matrix[row][row]==0)
    {//If any diagonal entry in the reduced matrix is 0 we can not find solution
        printf("The system of equations can not be solved by gauss elimination method");
        //getch();
        exit(0);
    }
    unknownvar[row]=sum/matrix[row][row];
    }
    printf("The unknowns are\n");//display the unknowns
    for(row=0;row<variables;row++)
    printf("%lf  ",unknownvar[row]);
    for(row=0;row<variables;row++)
    {
        free(matrix[row]);
        free(coeff[row]);
    }
    free(matrix);
    free(temp);
    free(coeff);
    free(unknownvar);
    //getch();
}