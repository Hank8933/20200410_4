#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100
#include <string.h>

void carry(int *a, int n)
{
    for (; n > 1; n--){
        *(a+n-2) += *(a+n-1) / 10;
        *(a+n-1) %= 10;
    }
}

void clearArray(int *a)
{
    for (int i = 0; i < 4*(MAX+1); i++) *(a + i) = 0;
}

void computeMid(int *a, int *b, int *c, int n)
{
    double temp, fractpart, intpart;
    for (int i = 0; i < n; i++){
        temp = (*(a + i) + *(b + i)) / 2.0;
        fractpart = modf(temp, &intpart);
        *(c + i) += (int)intpart;
        *(c + 1 + i) += (int)(fractpart*10);
        }
        carry(c, n);
    //for (int i = 0; i < 4*(MAX+1); i++) printf("%d",*(c + i));
    //printf("\n");
}

void computePow(const int *a, int *c, int n)
{
    for (int i = n-1; i >= 0; i--){
	    for (int j = n-1; j >=0; j--){
	        *(c+i+j) += *(a+i) * *(a+j);
	        carry(c, 2*n);
        }
    }
    /*printf("pow = ");
    for (int i = 0; i <= MAX; i++) printf("%d",*(c + i));
    printf("\n");*/
}

int main()
{
    int l[4*(MAX+1)] = {0};
    int r[4*(MAX+1)] = {2};
    int mid[4*(MAX+1)];
    int pow[8*(MAX+1)];

    for (int n = 1; n < 4*(MAX+1); n++){
        clearArray(mid);
        clearArray(pow);
        /*
        printf("l = ");
        for (int i = 0; i <= MAX; i++) printf("%d",*(l + i));
        printf("\nr = ");
        for (int i = 0; i <= MAX; i++) printf("%d",*(r + i));
        printf("\n");
        */
        computeMid(l, r, mid, n);
        computePow(mid, pow, n);
        if (*pow >= 2) memcpy(r, mid, n*4);
        else memcpy(l, mid, n*4);
    }

    printf("ANS: %d.", *mid);
    for (int i = 0; i < MAX; i++) printf("%d",*(mid + 1 + i));
    return 0;
}
