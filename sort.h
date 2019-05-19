#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
#include "h_file.h"

void sortData (Money *transfer, int nr);
extern void sortsIBAN (Money *transfer, int nr);
extern void sortrIBAN (Money *transfer, int nr);
extern void sortSum (Money *transfer, int nr);
void sortDate (Money *transfer, int nr);

#endif // SORT_H_INCLUDED
