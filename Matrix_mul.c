//Roll No: 33158

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

//Global variables
#define SIZE 10
int **A, **B, **C;
void *thread_function(void *arg);
pthread_t P[SIZE][SIZE];
int thread_no=1;

//function for accpeting elements
void accept_matrix(int **M, int rows, int cols) {
	int i, j;
	printf("\nEnter matrix elements :\n");
    for(i=0;i<rows;i++){
       printf("\n");
       for(j=0;j<cols;j++){
         printf("Value : [%d][%d] : ",i,j);
         scanf("%d",&M[i][j]);

       }
    }
}

//Function for displaying matrix
void display_matrix(int **M, int rows, int cols)
{
	int i, j;
	printf("\n");
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			printf("%d  ",M[i][j]);
		}
		printf("\n");
	}
}
//Thread create function
void *mul_thread(void *arg)
{
	int i, k, row, col, *rcArgs, z;
	int sum_val=0;
	rcArgs = (int *) arg;  //Converting str arg to int

	row = rcArgs[0];
	col = rcArgs[1];
	k= rcArgs[2];

	//printf("\n\tThread No %d-%d joined",row+1,col+1);

	for(i=0;i<k;i++)                  //3rd loop for multiplication
	{
		sum_val = sum_val + A[row][i] * B[i][col];
		printf("\n%d - Thread No %d-%d - Thread id :%d \n",thread_no,row+1,col+1,pthread_self());

		printf("Calculated %d * %d = %d --> %d ",A[row][i],B[i][col],A[row][i]*B[i][col],sum_val);
		z=rand()%10;
		printf("\n%d - Thread No %d-%d Paused -- Sleeping for %d units",thread_no, row+1,col+1,z);
		sleep(z);
		printf("\n%d - Thread No %d-%d .......Resumed",thread_no, row+1,col+1);
		thread_no++;
	}

	printf("\n...........Thread No %d-%d ............................exits", row+1,col+1);
	pthread_exit((int *) sum_val);
}

//Main Function
int main(){
    int i,j,k,r1,r2,c1,c2;
    int rcArgs[3];
	int  *status;

    while(1){
    printf("\n--------Matrix :1---------- \n");
    printf("\nEnter number of rows : ");
    scanf("%d",&r1);
     printf("\nEnter number of columns : ");
    scanf("%d",&c1);

    printf("\n--------Matrix :2----------\n ");
    printf("\nEnter number of rows : ");
    scanf("%d",&r2);
    printf("\nEnter number of columns : ");
    scanf("%d",&c2);

    if(c1 == r2) break;
    else printf("\nInvalid Input : Enter again :\n");
    }

    //Dynamic Memory Allocation
    A = (int**) malloc(r1*sizeof(int*));
	for(i=0;i<r1;i++)
		A[i] = (int*) malloc(c1*sizeof(int));

	B = (int**) malloc(r2*sizeof(int*));
	for(i=0;i<r2;i++)
		B[i] = (int*) malloc(c2*sizeof(int));

	C = (int**) malloc(r1*sizeof(int*));
	for(i=0;i<r1;i++)
		C[i] = (int*) malloc(c2*sizeof(int));

	//accpeting array elements
	printf("\n--------Matrix :1----------\n ");
    accept_matrix(A, r1, c1);
    printf("\n--------Matrix :2----------\n ");
	accept_matrix(B, r2, c2);

	//Matrix multiplication
	printf("\n Multiplication Process :");
	for(i=0;i<r1;i++) {
			for(j=0;j<c2;j++) {
				rcArgs[0] = i;
				rcArgs[1] = j;
				rcArgs[2] = c1;

				if(pthread_create(&P[i][j], NULL, mul_thread, rcArgs) != 0)  //Pthread_create calling function : mul_thread
					printf("\n\tCannot create thread.\n");
				else{
					printf("\n\tThread No %d-%d : created \n",i+1,j+1);
					sleep(2);
				}

			}
		}


	//Display Matrix
	printf("\n\nMatrix A : \n");
	display_matrix(A, r1, c1);
	printf("\nMatrix B : \n");
	display_matrix(B, r2, c2);

	//Thread join
	for(i=0;i<r1;i++) {
		for(j=0;j<c2;j++) {
                        {
				if(pthread_join(P[i][j],(void **) &status) != 0)
					perror("\nThread join failed.\n");
				C[i][j] = (int*)status;
			}
		}
	}

	printf("\n\nResultant Matrix:\n");
	for(i=0;i<r1;i++){
		for(j=0;j<c2;j++){
			printf("%d  ",C[i][j]);
		}
		printf("\n");
	}

return 0;
}



