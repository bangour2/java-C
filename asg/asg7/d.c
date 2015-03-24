#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


main()
{
    srand(0);
    int i;
    
    for(i = 0; i< 10; i++){
    double x = (double) rand()/(double)RAND_MAX*1;
    printf("%f \n", x);}
    
return 0;

}
