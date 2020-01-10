#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"
#include <stddef.h>
#include <time.h>


void workloadA();
void workloadB();
void workloadC();
void workloadD();
void workloadE();
void workloadF();

int main ()
{
  int i;
  unsigned int timeA = 0;
  unsigned int timeB = 0;
  unsigned int timeC = 0;
  unsigned int timeD = 0;
  unsigned int timeE = 0;
  unsigned int timeF = 0;

	struct timeval start;
	struct timeval end;
	struct timeval time;
	
	gettimeofday(&time, NULL);
	suseconds_t systime = time.tv_usec;

	for (i = 0; i < 100; i++)
	{
		gettimeofday(&start, NULL);
		workloadA();
		gettimeofday(&end, NULL);
		timeA += (end.tv_usec - start.tv_usec);

		gettimeofday(&start, NULL);
		workloadB();
		gettimeofday(&end, NULL);
		timeB += (end.tv_usec - start.tv_usec);

		gettimeofday(&start, NULL);
		workloadC();
		gettimeofday(&end, NULL);
		timeC += (end.tv_usec - start.tv_usec);

		gettimeofday(&start, NULL);
		workloadD();
		gettimeofday(&end, NULL);
		timeD += (end.tv_usec - start.tv_usec);

		gettimeofday(&start, NULL);
		workloadE();
		gettimeofday(&end, NULL);
		timeE += (end.tv_usec - start.tv_usec);

		gettimeofday(&start, NULL);
		workloadF();
		gettimeofday(&end, NULL);
		timeF += (end.tv_usec - start.tv_usec);

		}
	
		timeA /= 100;
		timeB /= 100;
		timeC /= 100;
		timeD /= 100;
		timeE /= 100;
		timeF /= 100;

		printf("Workload A took %d microseconds\n", timeA);
		printf("Workload B took %d microseconds\n", timeB);
		printf("Workload C took %d microseconds\n", timeC);
		printf("Workload D took %d microseconds\n", timeD);
		printf("Workload E took %d microseconds\n", timeE);
		printf("Workload F took %d microseconds\n", timeF);
return 0;
}

//Malloc 150 bytes, and then free them immediately.
void workloadA()
{
	char *testVar;
	int index;

	for(index = 0; index< 150; index++)
	{	
		testVar = (char*)malloc(sizeof(char));// malloc one byte

                if (testVar ==NULL){ //checks to make sure that malloc did not return null
                  fprintf(stderr, "Error malloc return null in %s at line %d\n", __FILE__, __LINE__);
                  return;
                }
		free(testVar);//frees the one byte allocated
	}
}

void workloadB()
{
	char *testVar[150];
	int index1;
	int index2;
	int j;

	for(j = 0; j < 3; j++)
	{
		for(index1 = 0; index1 < 50; index1++)// allocates one byte at a time until it has 50 bytes allocated
		{
			testVar[index1] = (char*)malloc(sizeof(char)); 
			if (testVar[index1] ==NULL){//checks to make sure that malloc did not return null
                          fprintf(stderr, "Error malloc return null in %s at line %d\n", __FILE__, __LINE__);
                          return;
                       }
		}
		for(index2 = 0; index2< 50; index2++)//frees the 50th previous allocation
		{
			free(testVar[index2]);
		}
	}
}
	
void workloadC()
{
	char* array[50];
	int mymallocs=0; //# of mymallocs
	int frees=0; //# of frees
	int i=0;
	int random= rand();
	int j=0;
	
        
	while (j !=1){
	        random= rand();//pick a random number
	        if (frees == mymallocs && mymallocs <50){// if we have the same number of mallocs and frees and we have not reach 50 mallocs, just malloc 
	            array[mymallocs] = malloc(1);
	            if (array ==NULL){
                      fprintf(stderr, "Error malloc return null in %s at line %d\n", __FILE__, __LINE__);
                      return;
                    }
		    mymallocs++;
	        }
	        else if(frees < mymallocs && mymallocs <50){
		  if (random % 2 == 1){  // if the random number picked at the begining of the while loop is odd, malloc else free
		      array[mymallocs] = malloc(1);
		      if (array ==NULL){
                         fprintf(stderr, "Error malloc return null in %s at line %d\n", __FILE__, __LINE__);
                         return;
                      }
		      mymallocs++;
		  }
		  
		else 
		 {
		   free(array[frees]);
		   frees++;
		  }
		 }
		else if (frees < mymallocs && mymallocs==50){ //once it mallocs 50 times just free the rest. do not malloc anymore
		   free(array[frees]);
		   frees++;
		}
		
		else 
		j =1;
	  }
}

void workloadD()
{	

	char* array[50];
	int mymallocs=0; //# of mymallocs
	int frees=0; //# of frees
	int i=0;
	int random=0;
	int mallocRand=0;
	
	
	
		while (i !=1){
	        random= rand();//pick a random number
	        
	        if (frees == mymallocs && mymallocs <50){ // if we have the same number of mallocs and frees and we have not reach 50 mallocs, just malloc 
	        
	            mallocRand = rand()%64+1;  //pick a random number between 1 and 64 for the byte to be allocated
	            array[mymallocs] = (char*)malloc(sizeof (char)*mallocRand);  //allocate amount of bytes picked randomly between 1 and 64
	            
	            if (array ==NULL){  //checks to make sure that malloc did not return null
                         fprintf(stderr, "Error malloc return null in %s at line %d\n", __FILE__, __LINE__);
                         return;
                      }
		    mymallocs++;
	        }
	        else if(frees < mymallocs && mymallocs <50){
		   if (random %2 == 1){ // if the random number picked at the begining of the while loop is odd, malloc else free.
		        mallocRand = rand()%64+1;
		        array[mymallocs] = malloc(sizeof(char)*mallocRand);
		        if (array ==NULL){
                         fprintf(stderr, "Error malloc return null in %s at line %d\n", __FILE__, __LINE__);
                         return;
                      }
		        mymallocs++;
		    }
		  
		  else 
		   {
		     free(array[frees]);
		     frees++;
		   }
		 }
		else if (frees < mymallocs && mymallocs==50){ //once it mallocs 50 times just free the rest. do not malloc anymore
		   free(array[frees]);
		   frees++;
		}
		
		else 
		i =1;
	  }
}		


void workloadE(){
   int mallocs=0;
   int memoryAllocated =0;
   int memoryLeft = 4096;
   int random;
   char *testVar[170];
   random = rand()%10+1;//pick random number between 1 and 10
   //memoryAllocated = memoryAllocated + random + sizeof(Metadata); //increment memory allocated by memory allocated and sizeof of metadata
   //memoryAllocated =memoryAllocated -random - sizeof (Metadata);//substract memory left from the memory allocated and sizeof of metadata
   
   
   while (memoryAllocated < memoryLeft){// keep looping to until we do not have enough space to allocate something.
      testVar[mallocs] = malloc(sizeof(char)*random);
      
      if (testVar ==NULL){//checks to make sure that malloc did not return null
         fprintf(stderr, "Error malloc return null in %s at line %d\n", __FILE__, __LINE__);
         return;
     }
      mallocs = mallocs +1;
      
      memoryAllocated = memoryAllocated + random + sizeof(Metadata);
      memoryLeft =memoryAllocated -random - sizeof (Metadata);//substract memory left from the memory allocated and sizeof of metadata
      random = rand()%10+1;
   }
   mallocs=mallocs -1;
   while (mallocs >=0){//frees allocted memory backward from the one that was lastly allocated to the one that was first allocated
      free(testVar[mallocs]);
      mallocs = mallocs-1;
   }
   
}

void workloadF(){
//declaration of variables
  int freedPosition[15];
  char * testVar[15];
  int frees = 0;
  int index;
  int i;
  int random;
  int j;
  int x;
  
  for (index=0; index<15; index++){
      frees = 0;
      for (i=0; i<15; i++)
      freedPosition[i]=-1;//sets all values in array to be -1
 
     for (j=0; j<15; j++){
       testVar[j] = (char*)malloc(sizeof(char));
       if (testVar ==NULL){//checks to make sure that malloc did not return null
         fprintf(stderr, "Error malloc return null in %s at line %d\n", __FILE__, __LINE__);
         return;
     }
       
     }
   
     while (frees < 15){
        random = rand()%15;
        for (x =0 ; x <15;x++){//checks to see if any given position has already been freed
           if (random == freedPosition[x]){
              j =-1;
              break;
              }
              else 
              j =0;
       }
        if (j !=-1){//if the position was not freed, free it
           free(testVar[random]);
           freedPosition[frees] = random;//sets 
           frees = frees +1;
           
        }
        
     }
   }
}
