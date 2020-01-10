#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <stddef.h>


void splitNode (Metadata* node, size_t sizeToAllocate){

   Metadata * newNode = (void*)((void*)node+sizeToAllocate+sizeof(Metadata));//allocate space for new node
   newNode ->blockSize = (node->blockSize)-sizeToAllocate-sizeof(Metadata); // subtract memory requested by user and size of metadata from remaining memory
   
   newNode ->free = 't'; // set new to used status
   newNode ->next = node->next;
   node ->blockSize = sizeToAllocate;
   node->free ='f';// set last node that hold free memory to be free
   node ->next = newNode;
}



void *mymalloc(size_t sizeToAllocate, const char *File,int lineNumber){
  Metadata * head = (void *)memoryBlock; 
  
  if (sizeToAllocate <= 0 ){//check to make sure not trying to allocate negative bytes
      fprintf(stderr,"sorry you are trying to allocate invalid amount bytes of memory in %s at line %d\n", File,lineNumber);
      return NULL;
  }
  

  if((sizeof (Metadata)+sizeToAllocate)>4096){//check to make sure not trying to allocate bytes greater than given memory
   fprintf(stderr,"Sorry you are trying to allocate bytes more than the given memory in %s at line %d\n", File,lineNumber);
   return NULL;
  }
  short * magicNumberTest = (short*)memoryBlock; // cast the number character that is initially in the memory block to be a short
  short magicNumber = 3;
  void *chunckToReturn;
  Metadata* currentNode;
  

  if(*magicNumberTest == magicNumber)// checks to see if it is the first time calling malloc
     nodeCreator();

  currentNode = head;
  while ((currentNode ->blockSize <sizeToAllocate || currentNode->free =='f')&&currentNode ->next!=NULL){ 
      currentNode = currentNode -> next;
  }//end of while loop
  
   if (currentNode->blockSize == sizeToAllocate){//if the requested memory == to corresponding size
      currentNode ->free = 'f';// set node to be occupied
      currentNode->blockSize = sizeToAllocate;      
      chunckToReturn =  (void*)(++currentNode);// cast returning memory to void so  that it can take any data type

      return chunckToReturn;
   }//end of if statement

   else if (currentNode ->blockSize >(sizeToAllocate +sizeof(Metadata))){
//if the requested memory is less than block of memory where it should be stored split it.
   splitNode(currentNode, sizeToAllocate);
   chunckToReturn = (void *)(++currentNode);
   return chunckToReturn;   
   }//end of else if
   else   
     return NULL;
}

void nodeCreator(){
   Metadata * head = (void *)memoryBlock;
   head->free ='t';
   head->blockSize = 4096-sizeof(Metadata);
   head ->next = NULL;
} //end of node creator

void myfree(void* memoryToFree,const char *File,int lineNumber){
  Metadata * head = (void *)memoryBlock;
   short * magicNumberTest = (short*)memoryBlock; // cast the number character that is initially in the memory block to be a short
  short magicNumber = 3;
  
  if(*magicNumberTest == magicNumber){ // checks to see memory was allocated at least once
     fprintf(stderr,"sorry you are trying to free empty memory in %s at line %d\n", File,lineNumber); 
     return;
 }//end of if statement
  
  //if (((void*)memoryBlock<=memoryToFree)&&(memoryToFree<=(void*)memoryBlock+4096)){// check to see if the memory the user is trying to free is within the interval of block of memory that was given initially
  
    Metadata * current = head;
    Metadata *freeingMemory;
    freeingMemory = memoryToFree;
    freeingMemory = freeingMemory-1;

    while (current !=NULL){// loop through the block of memory
       if (current == freeingMemory){ //check to see if the current block of memory is the memory that the user is trying to free

          if (freeingMemory->free== 't'){// check to see if the memory was not freed already
            fprintf(stderr,"sorry you are trying to free already freed memory in %s at line %d\n", File,lineNumber); 
            return;
          }

          freeingMemory->free = 't';// sets usage status to be unused
          combineFreeSpace();
          break;
      }
     current = current->next;
   }//end of while loop

   if (current == NULL){ //if the memory the user is trying to free is in the block of memory that was given but is not allocated
    fprintf(stderr, "Error you are trying to free memory that was not dynamically allocated in %s at line %d\n", File, lineNumber);
   }
                                                                                       
  //}
  //else //if the memory the user is trying to free is not within the interval of block of memory that was given initially
   // fprintf(stderr, " free memory that was not dynamically allocated in %s at line %d\n", File, lineNumber);

}

//this function combine consecutive space
void combineFreeSpace(){
  Metadata * head = (void *)memoryBlock;
  Metadata* nextNode;
  Metadata* currentNode;
  currentNode=head;
  nextNode = head->next;
  while ( nextNode!=NULL){
    if(currentNode ->free =='t' && nextNode->free =='t'){//chek to see if two consecutive blocks are free
     while (nextNode ->free =='t'&& nextNode !=NULL){//loop until it does not see any free space to combine or reaches the end of blocks
        currentNode ->blockSize = currentNode ->blockSize + nextNode->blockSize + sizeof(Metadata);
        currentNode -> next = nextNode->next;
        nextNode = nextNode->next;
        if (nextNode == NULL)
        return;
     }//end of inner while

   }
  nextNode = nextNode->next;
  currentNode =currentNode->next;
 }//end of while loop

}
