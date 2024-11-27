#include <stdio.h>
#include<string.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int ArrayA[10000];
int ArrayB[(sizeof(ArrayA)/sizeof(ArrayA[0]))];

void randomize();
void printA(void);
void printB(void);
void *counting_sort();
void *selection_sort();
int partition(int,int);
void *quick_sort( void *__v1);


void randomize()
{
	
	int c;
	for (c = 0; c < (sizeof(ArrayA)/sizeof(ArrayA[0])); c++) {
	    ArrayA[c] = (rand() % 100) + 1;
	}
	memcpy(ArrayB,ArrayA,sizeof(int)*(sizeof(ArrayA)/sizeof(ArrayA[0])));
	
	
}

void printA(void)
{
	printf("ArrayA:\n");
	int i;
	for(i=0;i<(sizeof(ArrayA)/sizeof(ArrayA[0]));i++)
	{printf("%d  ",ArrayA[i]);
	 if(ArrayA[i]==0)
		printf(" present  ");	
	}printf("\n");
}

void printB(void)
{
	printf("\nArrayB:\n");
	int i;
	for(i=0;i<(sizeof(ArrayA)/sizeof(ArrayA[0]));i++)
	{printf("%d  ",ArrayB[i]);}printf("\n");
}


struct values
{
	
	int first;
	int last;
};


void *counting_sort()
{

    	int n=(sizeof(ArrayA)/sizeof(ArrayA[0]))-1; 
    	int k=ArrayA[0];
        int i, j;
        int B[n];
        

        for (i = 0; i <= n; i++)

        {

            if (ArrayA[i] > k) {

                k = ArrayA[i];

            }

        }
	
	int C[k+1];

        for (i = 0; i <= k; i++)

            C[i] = 0;

        for (j = 0; j <= n; j++)

            C[ArrayA[j]] = C[ArrayA[j]] + 1;

        for (i = 1; i <= k; i++)

            C[i] = C[i] + C[i-1];

        for (j = n; j >=0 ; j--)

        {

            B[C[ArrayA[j]]-1] = ArrayA[j];

            C[ArrayA[j]] = C[ArrayA[j]] - 1;

        }
	memcpy(ArrayA,B,sizeof(int)*(sizeof(ArrayA)/sizeof(ArrayA[0])));
	

}
    
    
void *selection_sort()	
{
   
   int i,j,temp,count;
   count=sizeof(ArrayA)/sizeof(ArrayA[0]);
   for(i=0;i<count;i++){
	int min = i;
      for(j=i+1;j<count;j++){
         if(ArrayA[min]>ArrayA[j]){
		min = j;}       
      }
	temp=ArrayA[i];
	ArrayA[i]=ArrayA[min];
	ArrayA[min]=temp;
   }
	
}
  

int partition(int l,int u)
{
	int v,i,j,temp;
	v=ArrayA[l];
	i=l;
	j=u+1;
	do
	{
	do
	i++;
	while(ArrayA[i]<v&&i<=u);
	do
	j--;
	while(v<ArrayA[j]);
	if(i<j)
	{
	temp=ArrayA[i];
	ArrayA[i]=ArrayA[j];
	ArrayA[j]=temp;
	}
	}while(i<j);
	ArrayA[l]=ArrayA[j];
	ArrayA[j]=v;
	return(j);
}


void *quick_sort( void *__v1)
{
struct values *v1=(struct values*) __v1;
   if(v1->first<v1->last)
  {

      int j = partition(v1->first,v1->last);
      struct values t;
      t.first=v1->first;
      t.last=j-1;
      /*pthread_t tid1,tid2;
      pthread_create(&tid1,NULL,quick_sort,&t);
      pthread_join(tid1, NULL);*/
      quick_sort(&t);
      
      t.first=j+1;
      t.last=v1->last;
      /*pthread_create(&tid2,NULL,quick_sort,&t);
      pthread_join(tid2, NULL);*/
      quick_sort(&t);
				

   }

}



    int main(){
    
    	clock_t t,t1;
   	
	int a;
    	double time_taken;
	struct values val;
	val.first =0;
	val.last=(sizeof(ArrayA)/sizeof(ArrayA[0]))-1;
//---------------------------Serial Compilation STARTS FROM HERE-----------------------------  
	printf("\n\n-------------------------Sorting Serially------------------------\n\n");
	
	randomize();
	
	//printA();
	//printB();
	
	//printA();
	t= clock();
	t1 = clock();
	printf("\n Time for count sort serially in seconds is ");
	counting_sort();
	t1 = clock() - t1; 
	time_taken = ((double)t1)/CLOCKS_PER_SEC;
	printf("%f\n\n",time_taken);
	//printA();	
	

	memcpy(ArrayA,ArrayB,sizeof(int)*(sizeof(ArrayA)/sizeof(ArrayA[0])));
	//printA();
	t= clock();
	t1 = clock();
	printf("\n Time for selection sort serially in seconds is ");
	selection_sort();
	t1 = clock() - t1; 
	time_taken = ((double)t1)/CLOCKS_PER_SEC;
	printf("%f\n\n",time_taken);
	//printA();
    	
    	
	memcpy(ArrayA,ArrayB,sizeof(int)*(sizeof(ArrayA)/sizeof(ArrayA[0])));
	//printA();	
	t= clock();
	quick_sort(&val);
	t = clock() - t; 
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("\n Time for quick sort serially in seconds is %f\n",time_taken);
	//printA();

	printf("\n");


//---------------------------THREADING STARTS FROM HERE-----------------------------  
	printf("\n\n-------------------------Sorting Through Threads------------------------\n\n");
	
	pthread_t tid1,tid2,tid3;
	//pthread_t tid11,tid22,tid33;
	//pthread_t tid111,tid222,tid333;


	memcpy(ArrayA,ArrayB,sizeof(int)*(sizeof(ArrayA)/sizeof(ArrayA[0])));
	//printA();
	printf("\n Time for count sort through pthreads in seconds is ");
	t= clock();
	t1 = clock();
	pthread_create(&tid1,NULL,counting_sort,NULL);
	//pthread_create(&tid11,NULL,counting_sort,&t);
	//pthread_create(&tid111,NULL,counting_sort,&t);
	pthread_join(tid1, NULL);
	t1 = clock() - t1; 
	time_taken = ((double)t1)/CLOCKS_PER_SEC;
	printf("%f\n\n",time_taken);	
	//printA();


	memcpy(ArrayA,ArrayB,sizeof(int)*(sizeof(ArrayA)/sizeof(ArrayA[0])));
	//printA();
	printf("\n Time for selection sort through pthreads in seconds is ");
	t= clock();
	t1 = clock();
	pthread_create(&tid2,NULL,selection_sort,NULL);
	//pthread_create(&tid22,NULL,selection_sort,&t);
	//pthread_create(&tid222,NULL,selection_sort,&t);
	pthread_join(tid2, NULL);
	t1 = clock() - t1; 
	time_taken = ((double)t1)/CLOCKS_PER_SEC;
	printf("%f\n\n",time_taken);
	//printA();
	

	memcpy(ArrayA,ArrayB,sizeof(int)*(sizeof(ArrayA)/sizeof(ArrayA[0])));
	//printA();
	t = clock();
	pthread_create(&tid3,NULL,quick_sort,&val);
	pthread_join(tid3, NULL);
	t= clock() - t; 
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("\n Time for quick sort through pthreads in seconds is %f\n",time_taken);
	//printA();
	printf("\n");



   	return 0;
}
	

