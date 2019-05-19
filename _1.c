#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "h_file.h"

void saveToFile (Money *transfer,int nr)
{
    FILE *fPtr;
    fPtr=fopen("transfer.bin","wb");
    fwrite(&nr,sizeof(int),1,fPtr);
    for (int i=0;i<nr;i++){
        fwrite(&(transfer[i]),sizeof(Money),1,fPtr);
    }
    fclose(fPtr);//closing the file
}
//___________________________________________________
void readFromFile (Money *transfer,int *nr)
{
    FILE *fPtr;
    while(1){
        fPtr=fopen("transfer.bin","rb");
        if(fPtr==NULL){
            fPtr=fopen("transfer.bin","wb"); //create binary file if it has not been created yet
            fclose(fPtr);
        }
        else{
            fread(nr,sizeof(int),1,fPtr); //if file has been created - read from binary file
            if(*nr>=MEM){
                transfer=realloc(transfer,sizeof(transfer)*(MEM+(*nr-MEM)));
                assert(transfer);
            }
            for (int i=0;i<(*nr);i++){
                fread(&(transfer[i]),sizeof(Money),1,fPtr);
            }
        break;
        }
    }
    fclose(fPtr);
}

