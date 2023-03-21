#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "AdptArray.h" 
struct AdptArray_ 
{
int ArrSize ; 
PElement* pElemArr; 
DEL_FUNC delFunc; 
COPY_FUNC copyFunc; 
PRINT_FUNC printFunc; 
}; 

PAdptArray CreateAdptArray(COPY_FUNC copyFunc , DEL_FUNC delFunc , PRINT_FUNC  printFunc){
    PAdptArray n_arr = (PAdptArray)malloc(sizeof( struct AdptArray_)); 
    if(n_arr == NULL){
        return NULL; 
    }
    n_arr->ArrSize = 0 ; 
    n_arr->copyFunc = copyFunc; 
    n_arr->delFunc = delFunc; 
    n_arr->printFunc = printFunc;
    n_arr->pElemArr=NULL;  

    return n_arr; 
}

void DeleteAdptArray(PAdptArray PArr){
    if( PArr == NULL){
        return;
    }
    for ( int i=0; i< PArr->ArrSize; i++){
        if(PArr->pElemArr[i]!=NULL)
        PArr->delFunc(PArr->pElemArr[i]); 
    }
    free(PArr->pElemArr); 
    free( PArr); 
}
PElement GetAdptArrayAt(PAdptArray PArr, int idx){
    if(PArr==NULL){
        return NULL; 
    }
    if( idx<0 || idx >= PArr->ArrSize ){
        return NULL; 
    }
    if( PArr->pElemArr[idx]!=NULL){
        return (PArr->copyFunc(PArr->pElemArr[idx])); 
    }
    else
    {
        return NULL; 
    }
    
    //if( PArr->pElemArr[idx]== NULL){
    //    return NULL; 
    //}
   // PElement elemnt = PArr->copyFunc(PArr->pElemArr[idx]); 
   // return elemnt; 
}
int GetAdptArraySize(PAdptArray PArr){
    if( PArr==NULL){
        return -1;  
    }
    return PArr->ArrSize;

}
void PrintDB(PAdptArray PArr){
    if(PArr == NULL)
        return; 
    for(int i=0; i<PArr->ArrSize; i++){
        if(PArr->pElemArr[i]!=NULL){
            PArr->printFunc(PArr->pElemArr[i]);
        }
    }
}

Result SetAdptArrayAt(PAdptArray PArr, int idx, PElement PNewElement){
    PElement *newElemArr= NULL;
    if( PArr== NULL){
        return FAIL; 
    } 
    if( idx >= PArr->ArrSize){
        if( (newElemArr = (PElement* )calloc((idx+1), sizeof(PElement)))==NULL){
        return FAIL; 
        }
        memcpy(newElemArr, PArr->pElemArr, (PArr->ArrSize) * sizeof(PElement)); 
        if(PArr->pElemArr!=NULL){
            free(PArr->pElemArr); 
        } 
        PArr->pElemArr = newElemArr; 
    }
    if(PArr->pElemArr[idx]!=NULL){
        PArr->delFunc((PArr->pElemArr)[idx]); 
    }
    (PArr->pElemArr)[idx]= PArr->copyFunc(PNewElement); 
    PArr->ArrSize =(idx >=PArr->ArrSize) ? (idx +1) : PArr->ArrSize;  
    return SUCCESS; 

}

