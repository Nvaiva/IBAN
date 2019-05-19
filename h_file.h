#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#define MAXI 30
#define MAXD 10
#define MEM 10

typedef struct moneyTransferData{
    char sIBAN[MAXI]; //sender's international bank account number
    char rIBAN[MAXI]; //receiver's international bank account number
    double sum; //Money for transfer
    char date[MAXD];//date of the transfer
}Money;

unsigned int enterChoice (void);
int IBANValidation (char IBAN[]);
void inputsIBAN (Money *transfer);
void inputrIBAN (Money *transfer);
void inputSum (Money *transfer);
void inputDate (Money *transfer);
int dateValidation (char date[]);
void updateRecord(Money *transfer);
void deleteRecord(Money *transfer, int *nr);
void reviewRecord (Money *transfer, int nr);
void filterData(Money *transfer, int nr);
void endProgram ();
void testingFunctions (void);

void readFromFile (Money *transfer, int *nr);
void saveToFile (Money *transfer, int nr);

#endif // FILE_H_INCLUDED
