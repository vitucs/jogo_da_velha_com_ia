#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void imprimirPontilhado(){
	for(int i=0;i<168;i++)
		printf("-");
}

void imprimirCentralizado(char* s){
    int len=strlen(s);
    int pos=(int)((168-len)/2);
    for (int i=0; i<pos; i++)
        printf(" ");
    printf("%s\n", s);
}

