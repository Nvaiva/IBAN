#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "h_file.h"
#include "sort.h"
#define MAXI 30
#define MAXD 10
#define MEM 10

int main ()
{
    if(atexit(endProgram)!=0){
        puts("Something's wrong\n");
    }
    //
    Money *transfer;
    transfer=malloc(MEM*sizeof(Money*));
    if(transfer==NULL){
        printf("Memory allocation problem\n");
    }
    //
    FILE *f;
    f=fopen("statistics.log","a");
    assert(f);
    fprintf(f,"\nProgram execution time - ");
    fclose(f);
    //
    int choice=0;
    int nr=0;
    int uNumber=0;//update number
    //
    testingFunctions();
    readFromFile(transfer,&nr);
    while((choice=enterChoice())){
        switch (choice){
        case 1:
            if(MEM>=nr){
                transfer=realloc(transfer,sizeof(transfer)*(MEM+1));
                if(transfer!=NULL){
                    inputsIBAN(&transfer[nr]);
                    inputrIBAN(&transfer[nr]);
                    inputDate(&transfer[nr]);
                    inputSum(&transfer[nr]);
                    nr++;
                    break;
                }
                else{
                    printf("Memory alloation error\n");
                    return 0;
                }
            }
            else
            {
            inputsIBAN(&transfer[nr]);
            inputrIBAN(&transfer[nr]);
            inputDate(&transfer[nr]);
            inputSum(&transfer[nr]);
            nr++;
            break;
            }
        case 2:
            printf("Enter a number of recording that you want to update\n");
            scanf("%u",&uNumber);
            if(uNumber-1<=nr)
            {
                updateRecord(&transfer[uNumber-1]); //function for changing data stored in the structure/file
                break;
            }
            else{
                printf("There is no record %d in this file\n",uNumber);
                break;
            }
        case 3:
            deleteRecord(transfer,&nr);
            break;
        case 4:
            reviewRecord(transfer,nr);
            break;
        case 5:
            saveToFile(transfer,nr);
            free(transfer);
            return 0;
        case 6:
            filterData(transfer,nr);
            break;
        case 7:
            sortData(&transfer,nr);
            break;
        }
    }
}

void endProgram (void)
{
    clock_t theEnd=clock();
    double total=((double)(theEnd))/CLOCKS_PER_SEC;
    puts("Program was successfully terminated\n");
    //
    FILE *fPtr;
    fPtr=fopen("statistics.log","a");
    assert(fPtr);
    fprintf(fPtr,"%f",total);
    fclose(fPtr);
    //
}
//__________________________________________________________________________
void filterData (Money *transfer, int nr)
{
    Money transfer_new;
    unsigned int choice=0;
    unsigned int n=0; //to check if any matches was found
    printf("%s","Which of the recordings you want to see?\n"
           "1 - Specific sender's IBAN\n"
           "2 - Specific receiver's IBAN\n"
           "3 - Specific sum of the transfer\n"
           "4 - Specific date of the transfer\n");
    scanf("%u",&choice);

    switch (choice){
        case 1:
            inputsIBAN(&transfer_new);
            for (int i=0;i<nr;i++)
                if(strcmp(transfer_new.sIBAN,transfer[i].sIBAN)==0){
                    transfer_new=transfer[i];
                    reviewRecord(&transfer_new,1);
                    n++;
                }
            if(n==0){
                printf("Transfer from %s has not been done\n",transfer_new.sIBAN);
            }
        break;
        case 2:
            inputrIBAN(&transfer_new);
            for (int i=0;i<nr;i++){
                if(strcmp(transfer_new.rIBAN,transfer[i].rIBAN)==0){
                    transfer_new=transfer[i];
                    reviewRecord(&transfer_new,1);
                    n++;
                }
            }
            if(n==0){
                printf("Transfer to %s has not been done\n",transfer_new.rIBAN);
            }
        break;
        case 3:
            inputSum(&transfer_new);
            for (int i=0;i<nr;i++){
                if(transfer_new.sum==transfer[i].sum){
                    transfer_new=transfer[i];
                    reviewRecord(&transfer_new,1);
                    n++;
                }
            }
            if(n==0){
                printf("Transfer with sum %.2lf has not been done\n",transfer_new.sum);
            }
        break;
        case 4:
            inputDate(&transfer_new);
            for (int i=0;i<nr;i++){
                if(strcmp(transfer_new.date,transfer[i].date)==0){
                    transfer_new=transfer[i];
                    reviewRecord(&transfer_new,1);
                    n++;
                }
            }
            if(n==0){
                printf("Transfer at %s has not been done\n",transfer_new.sIBAN);
            }
        break;
    }
}
//__________________________________________________________________________
void deleteRecord(Money *transfer, int *nr)
{
    int n=*nr;
    char letter;
    unsigned int dNumber;
    printf("Do you want to delete all existing files? (y or n)\n ");
    scanf(" %c",&letter);
    if(letter=='y'){
        *nr=0;
    }
    else{
        printf("Please input a number of recording that you want to delete\n");
        scanf("%u",&dNumber);
        if(dNumber-1<=n){
            for (int i=dNumber-1;i<n; ++i){
                transfer[i]=transfer[i+1];
            }
        *nr=(*nr-1);
        }
    }
}
//_______________________________________________________________________________________________
void testingFunctions (void)
{
    //______(sort testing)_________________
    Money A[]={
        [0].sIBAN="AAAAB",
        [0].rIBAN="BBBBA",
        [0].sum=10,
        [0].date="2011-01-01",
        [1].sIBAN="AAAAA",
        [1].rIBAN="BBBBB",
        [1].sum=20,
        [1].date="2011-01-02"};
    sortsIBAN(A,2);
    assert(strcmp(A[0].sIBAN,"AAAAA")==0);
    sortrIBAN(A,2);
    assert(strcmp(A[0].rIBAN,"BBBBA")==0);
    sortSum(A,2);
    assert(A[0].sum==20);
    sortDate(A,2);
    assert(strcmp(A[0].date,"2011-01-01")==0);
    //_________(IBAN validation testing)__________
    int answer;
    char B[]="LT123456";
    answer=IBANValidation(B);
    assert(answer==1);
    //
    char C[]="Batvinis11";
    answer=IBANValidation(C);
    assert(answer==0);
    //
    char D[]="LT 123";
    answer=IBANValidation(D);
    assert(answer==0);
    //_________(Date validation testing)__________
    char E[]="2011-01-03";
    answer=dateValidation(E);
    assert(answer==1);
    //
    char F[]="2011-13-13";
    answer=dateValidation(F);
    assert(answer==0);
    //
    char H[]="Hello";
    answer=dateValidation(H);
    assert(answer==0);

}
//_______________________________________________________________________________________________
void updateRecord(Money *transfer)
{
    char letter;//user's choice whether to update all recording
    unsigned int number; //user's choice in switch function

    printf("Do you want to update all information in a record? (y or n)\n");
    scanf(" %c",&letter);
        if(letter=='y'){
            inputsIBAN(transfer);
            inputrIBAN(transfer);
            inputDate(transfer);
            inputSum(transfer);
        }
        else{
            printf("Select a record that you want to update\n"
                "1 - Sender's IBAN\n"
                "2 - Receiver's IBAN\n"
                "3 - Date of the transfer\n"
                "4 - Sum of the transfer\n");
            scanf("%u",&number);
            switch(number){
            case 1:
                strcpy(transfer->sIBAN,"");
                inputsIBAN(transfer);
                break;
            case 2:
                strcpy(transfer->rIBAN,"");
                inputrIBAN(transfer);
                break;
            case 3:
                strcpy(transfer->date,"");
                inputDate(transfer);
                break;
            case 4:
                transfer->sum=0.0;
                inputSum(transfer);
                break;
            default:
                printf("Wrong choice\n");
            }
        }
}
//_______________________________________________________________________________________________
void reviewRecord (Money *transfer, int nr)
{
    if(nr==0){
        printf("There is no records in this file\n");
    }
    else{
        for (int i=0;i<nr;i++)
        {
            printf("Sender's IBAN is %s\n",transfer[i].sIBAN);
            printf("Receiver's IBAN is %s\n",transfer[i].rIBAN);
            printf("Sum of the transfer is %.2f\n",transfer[i].sum);
            printf("Date of the transfer is %s\n",transfer[i].date);
            printf("------------------------------------------------\n");
        }
    }

}
//_________________________________________________________________________________________________
int IBANValidation (char IBAN[])
{
    int nodigit=0;
    if(IBAN[0]>='A'&&IBAN[0]<='Z'&&IBAN[1]>='A'&&IBAN[1]<='Z'){//checking if letters are uppercase
        for (int i=2;i<strlen(IBAN);i++){
            if(isdigit(IBAN[i])!=1){ //checking if IBAN consists of digits
                nodigit++;
            }
        }
    }
            else{
                return 0;
            }
        if(nodigit>0){
        return 0;
    }
    else{
        return 1;
    }
}
//______________________________________________________________________________________________________________
int dateValidation (char date[])
{
    for (int i=0;i<4;i++)
    if(isdigit(date[i])==1&&(isdigit(date[i])>0)){
        if(date[4]=='-'&&date[7]=='-'){
            if((isdigit(date[5])==1)&&(isdigit(date[6])==1)&&(isdigit(date[8])==1)&&(isdigit(date[9])==1)){
                if((date[5]==48&&(date[6]!=48)) || ((date[5]==49)&&(date[6]==49)) || ((date[5]==49)&&(date[6]==48)) || ((date[5]==49)&&(date[6]==50))){
                    if((date[8]==48&&date[9]!=48)|| (date[8]==49) ||(date[8]==50 )|| ((date[8]==51)&&(date[9]==48)) || ((date[8]==51)&&(date[9]==49))){
                        return 1;
                        break;
                    }
                    else{
                        return 0;
                    }
                }
                else {
                    return 0;
                }
                }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
    return 0;
}
//______________________________________________________________________________
void inputDate (Money *transfer)
{
    int answer=0;
     while(1){
       printf("%s","Enter date of the transfer in format yyyy-mm-dd\n");
            if((scanf("%s",transfer->date)==1)&&(getchar()=='\n')&&(strlen(transfer->date)<=10)){
                answer=dateValidation(transfer->date);
                if(answer==1){
                    printf("Date input was correct\n");
                    break;
                }
                else{
                    printf("Date input was not correct\n");
                }
            }
            else{
                printf("Enter only one date\n");
                }
    }
}
//________________________________________________________________________________
void inputSum (Money *transfer)
{
    while(1){
        printf("Enter the sum of money that will be transfered\n");
            if((scanf("%lf",&transfer->sum)==1)&&(getchar()=='\n')&&(transfer->sum>0)){
                break;
            }
            else{
                printf("Error:Please input valid sum for the transfer\n");
                while(getchar()!='\n');
            }
    }
}
//___________________________________________________________________________________
void inputrIBAN (Money *transfer)
{
    int answer=0;
  while(1){
    printf("%s","Enter receiver's IBAN (International bank account number)\n");
        if((scanf("%s",transfer->rIBAN)==1)&&(getchar()=='\n')){
                if(strlen(transfer->rIBAN)<=30){
                    answer=IBANValidation(transfer->rIBAN);
                    if(answer==1){
                        printf("IBAN's input was correct\n");
                        break;
                    }
                    else{
                    printf("IBAN's input was not correct (press any key to enter IBAN again)\n");
                    getchar();
                    }
                }
                else{
                    printf("IBAN consists no more than 30 symbols\n");
                    strcmp(transfer->rIBAN,"");
                }

        }
        else{
            printf("IBAN consists of one line.\n");
            while(getchar()!='\n');
        }
    }
}
//___________________________________________________________________________________
void inputsIBAN (Money *transfer)
{
    int answer=0;
    while(1){
    printf("%s","Enter sender's IBAN (International bank account number)\n");
       if((scanf("%s",transfer->sIBAN)==1)&&(getchar()=='\n')){
            if(strlen(transfer->sIBAN)<=30){
                answer=IBANValidation(transfer->sIBAN);
                if(answer==1){
                    printf("IBAN's input was correct\n");
                    break;
                }
                else{
                printf("IBAN's input was not correct(press any key to enter IBAN again\n");
                getchar();
                }
            }
            else{
                printf("IBAN consists no more than 30 symbols\n");
                strcmp(transfer->rIBAN,"");
            }
        }
       else{
            printf("IBAN consists of one line.\n");
            while(getchar()!='\n');

        }
  }
}
//__________________________________________________________________________________________________
unsigned int enterChoice (void) //void in parentheses makes explicit that no parameters are expected
{
    unsigned int menuChoice; //variable to store user's choices
    printf("%s","\nEnter your choice\n"
           "1 - Input information about money transfer\n"
           "2 - Update transfer data\n"
           "3 - Delete all transfer records or the whole file\n"
           "4 - Review money transfer record\n"
           "5 - End program and save records\n"
           "6 - Filter out specific recordings\n"
           "7 - Sort out recordings\n");
    scanf("%u",&menuChoice); //receive choice from user
    return menuChoice;
}
