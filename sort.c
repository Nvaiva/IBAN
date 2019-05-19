#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "h_file.h"
#include "sort.h"
void sortData (Money *transfer, int nr)
{
    unsigned int choice=0;
    printf("Select a criteria on which you want to sort the recordings:\n"
           "1 - Alphabetically sort senders IBANs\n"
           "2 - Alphabetically sort receivers IBANs\n"
           "3 - Sort by transfer amount\n"
           "4 - Sort by date\n");
    while(1){
    if(scanf("%u",&choice)==1&&(getchar()=='\n')){
        break;
    }
    else{
        printf("Wrong input.Please enter a number\n");
        while(getchar()!='\n');
    }
    }
     switch(choice){
        case 1:
            sortsIBAN(transfer,nr);
            reviewRecord(transfer,nr);
            break;
        case 2:
            sortrIBAN(transfer,nr);
            reviewRecord(transfer, nr);
            break;
        case 3:
            sortSum(transfer,nr);
            reviewRecord(transfer,nr);
            break;
        case 4:
            sortDate(transfer,nr);
            reviewRecord(transfer, nr);
            break;
        default:
            printf("Incorrect choice\n");
            break;
    }

}
//__________________________________________________________
void sortsIBAN (Money *transfer, int nr)
{
    Money c;
    Money b;
  for (int i=0;i<nr-1;i++){
    for (int j=0;j<nr-i-1;j++){
        if(strcmp(transfer[j].sIBAN,transfer[j+1].sIBAN)>0){
            c=transfer[j];
            b=transfer[j+1];
            transfer[j]=b;
            transfer[j+1]=c;
        }
    }
  }
}
//______________________________________________________________
void sortrIBAN (Money *transfer, int nr)
{
    Money c;
    Money b;
  for (int i=0;i<nr-1;i++){
    for (int j=0;j<nr-i-1;j++){
        if(strcmp(transfer[j].rIBAN,transfer[j+1].rIBAN)>0){
            c=transfer[j];
            b=transfer[j+1];
            transfer[j]=b;
            transfer[j+1]=c;
        }
    }
  }
}
//________________________________________________________________
void sortSum (Money *transfer, int nr)
{
    Money a;
    Money b;
    for (int i=0;i<nr-1;i++){
        for (int j=0;j<nr-i-1;j++){
            if(transfer[j].sum<transfer[j+1].sum){
                a=transfer[j];
                b=transfer[j+1];
                transfer[j]=b;
                transfer[j+1]=a;

            }
        }
    }
}
//_________________________________________________________________
void sortDate (Money *transfer, int nr)
{
    Money c;
    Money b;
  for (int i=0;i<nr-1;i++){
    for (int j=0;j<nr-i-1;j++){
        if(strcmp(transfer[j].date,transfer[j+1].date)>0){
            c=transfer[j];
            b=transfer[j+1];
            transfer[j]=b;
            transfer[j+1]=c;
        }
    }
  }
}

