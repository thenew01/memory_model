#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define M (1<<14) //15
#define N M

int a[M][N];

/* $begin sumarraycols */
int sumarraycols(int a[M][N]) 
{  	
    int i, j, sum = 0;

    for (j = 0; j < N; j++)
	for (i = 0; i < M; i++) 
	    sum += a[i][j];
    return sum;	
}
/* $end sumarraycols */


int main()
{
    int i, j;

    for (j = 0; j < N; j++)
        for (i = 0; i < M; i++) 
	    a[i][j] = ((j%2 == 0) ? 1 : -1);

    /* should sum to zero */
	DWORD dwBegin = GetTickCount();
    printf("sum=%d\n", sumarraycols(a));
	printf("%d", GetTickCount() - dwBegin);
    exit(0);
}
