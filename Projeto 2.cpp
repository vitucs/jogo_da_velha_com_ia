#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "trash.h"

//http://planetamidi.blogspot.com.br/

char tabuleiro1 [8][8];
char tabuleiro2 [8][8];
char tabuleiroexib1[8][8];
char tabuleiroexib2[8][8];
int matrizjogadas[8][8];
int qtdderrubadaA=0;
int qtdderrubadaB=0;
int i, j, linha, coluna, direitalinha, direitacoluna, baixolinha, baixocoluna, esquerdalinha, esquerdacoluna, cimalinha, cimacoluna, mp, con=0, direcao, atab1=0, atab2=0;
char teste='O';
//int jogadas1[64][2];

enum DOS_COLORS {
        BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
        LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
        LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE };
        
void textcolor (DOS_COLORS iColor){
        HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
        bufferInfo.wAttributes &= 0x00F0;
        SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}

void backcolor (DOS_COLORS iColor){
        HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
        bufferInfo.wAttributes &= 0x000F;
        SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= (iColor << 4));
}
 
struct posicao{
	int li; //linha inicial
	int ci; //coluna inicial
	int lf; //linha final
	int cf; //linha inicial
};

typedef struct embarcacao{
	char nome[30];
	int tamanho=0;
	int certos;
	int vetorposicao[10]={0,0,0,0,0,0,0,0,0,0};
};

embarcacao pa1,sub1,cruz41, cruz31,cou1,pa2,sub2,cruz42,cruz32,cou2;

void verificarembarcacao (int jogador, int linha, int coluna){
	if(jogador==1){
		for(int i=0;i<10;i+=2){
			if(cou2.vetorposicao[i]==linha && cou2.vetorposicao[i+1]==coluna)
				cou2.certos++;
			else if(cruz32.vetorposicao[i]==linha && cruz32.vetorposicao[i+1]==coluna)
				cruz32.certos++;
			else if(cruz42.vetorposicao[i]==linha && cruz42.vetorposicao[i+1]==coluna)
				cruz42.certos++;
			else if(sub2.vetorposicao[i]==linha && sub2.vetorposicao[i+1]==coluna)
				sub2.certos++;
			else if(pa2.vetorposicao[i]==linha && pa2.vetorposicao[i+1]==coluna)
				pa2.certos++;
					}
	}else{
		for(int i=0;i<10;i+=2){
			if(cou1.vetorposicao[i]==linha && cou1.vetorposicao[i+1]==coluna)
				cou1.certos++;
			else if(cruz31.vetorposicao[i]==linha && cruz31.vetorposicao[i+1]==coluna)
				cruz31.certos++;
			else if(cruz41.vetorposicao[i]==linha && cruz41.vetorposicao[i+1]==coluna)
				cruz41.certos++;
			else if(sub1.vetorposicao[i]==linha && sub1.vetorposicao[i+1]==coluna)
				sub1.certos++;
			else if(pa1.vetorposicao[i]==linha && pa1.vetorposicao[i+1]==coluna)
				pa1.certos++;
					}
		
	}
	
}

void impressaoMapa(){
			system("cls");
			imprimirPontilhado();
			imprimirCentralizado("Batalha Naval!");
			imprimirPontilhado();
			printf("\n\n");
			printf("\t\t\t\t\t\t\t TABELA DO JOGADOR 1\t        TABELA DO JOGADOR 2\n");
			for(i=0;i<8;i++){
				printf("\t\t\t\t\t\t\t \xBA");
				for(j=0;j<8;j++){
					printf("%c\xBA", tabuleiroexib1[i][j]);
				}
				if(i==3)
				printf("\tX\t");
				else
				printf("\t \t");
				printf("\xBA");
				for(j=0;j<8;j++){
					printf("%c\xBA", tabuleiroexib2[i][j]);
				}
				printf("\n");
			}
			printf("\n\n");
}

int verificarjogada (int jogador, int linha, int coluna){
	if(matrizjogadas[linha-1][coluna-1]==jogador || matrizjogadas[linha-1][coluna-1]==12)
		return 0;
	else
		return 1;
}

void ImpressaodeTiros(int jogador){
	printf("\n\nTiros Efetuados:\n\n");
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if(matrizjogadas[i][j]==jogador || matrizjogadas[i][j]==12)
				printf("%d-%d ", i+1,j+1);	
}

void preenchertabuleirosdeexibicao(){
	int i, j;
	for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				tabuleiroexib1[i][j]=' ';
				tabuleiroexib2[i][j]=' ';
			}
		}
}

void AIdeconhecimento(int caso, int tmp, int li, int ci){
	if(caso==1){
		if(tmp==2){
			strcpy(cou1.nome, "Couracado");
			cou1.tamanho=2;
			cou1.certos=0;
			for(int i=0;i<cou1.tamanho*2;i++){
				if(i%2==0){
				cou1.vetorposicao[i]=li;
				
				}else{
				cou1.vetorposicao[i]=ci+(i/2);
				}
			}
		}else if(tmp==3 && cruz31.tamanho!=3){
			strcpy(cruz31.nome, "Cruzador3");
			cruz31.tamanho=3;
			cruz31.certos=0;
			for(int i=0;i<cruz31.tamanho*2;i++){
				if(i%2==0){
				cruz31.vetorposicao[i]=li;
				}else{
				cruz31.vetorposicao[i]=ci+(i/2);
				}
			}
		}else if(tmp==3 && sub1.tamanho!=3){
			strcpy(sub1.nome, "Submarino");
			sub1.tamanho=3;
			sub1.certos=0;
			for(int i=0;i<sub1.tamanho*2;i++){
				if(i%2==0){
				sub1.vetorposicao[i]=li;
				}else{
				sub1.vetorposicao[i]=ci+(i/2);
				}
			}	
		}else if(tmp==4){
			strcpy(cruz41.nome, "Cruzador4");
			cruz41.tamanho=4;
			cruz41.certos=0;
			for(int i=0;i<cruz41.tamanho*2;i++){
				if(i%2==0){
				cruz41.vetorposicao[i]=li;
				}else{
				cruz41.vetorposicao[i]=ci+(i/2);
				}
			}
		}else{
			strcpy(pa1.nome, "PortaAvioes");
			pa1.tamanho=5;
			pa1.certos=0;
			for(int i=0;i<pa1.tamanho*2;i++){
				if(i%2==0){
				pa1.vetorposicao[i]=li;
				}else{
				pa1.vetorposicao[i]=ci+(i/2);
				}
			}	
		} 

	}else if(caso==2){
		if(tmp==2){
			strcpy(cou1.nome, "Couracado");
			cou1.tamanho=2;
			cou1.certos=0;
			for(int i=0;i<cou1.tamanho*2;i++){
				if(i%2==0){
				cou1.vetorposicao[i]=li;
				}else{
				cou1.vetorposicao[i]=ci-(i/2);
				}
			}
		}else if(tmp==3 && cruz31.tamanho!=3){
			strcpy(cruz31.nome, "Cruzador3");
			cruz31.tamanho=3;
			cruz31.certos=0;
			for(int i=0;i<cruz31.tamanho*2;i++){
				if(i%2==0){
				cruz31.vetorposicao[i]=li;
				}else{
				cruz31.vetorposicao[i]=ci-(i/2);
				}
			}
		}else if(tmp==3 && sub1.tamanho!=3){
			strcpy(sub1.nome, "Submarino");
			sub1.tamanho=3;
			sub1.certos=0;
			for(int i=0;i<sub1.tamanho*2;i++){
				if(i%2==0){
				sub1.vetorposicao[i]=li;
				}else{
				sub1.vetorposicao[i]=ci-(i/2);
				}
			}	
		}else if(tmp==4){
			strcpy(cruz41.nome, "Cruzador4");
			cruz41.tamanho=4;
			cruz41.certos=0;
			for(int i=0;i<cruz41.tamanho*2;i++){
				if(i%2==0){
				cruz41.vetorposicao[i]=li;
				}else{
				cruz41.vetorposicao[i]=ci-(i/2);
				}
			}
		}else{
			strcpy(pa1.nome, "PortaAvioes");
			pa1.tamanho=5;
			pa1.certos=0;
			for(int i=0;i<pa1.tamanho*2;i++){
				if(i%2==0){
				pa1.vetorposicao[i]=li;
				}else{
				pa1.vetorposicao[i]=ci-(i/2);
				}
			}	
		}

	}else if(caso==3){
		if(tmp==2){
			strcpy(cou1.nome, "Couracado");
			cou1.tamanho=2;
			cou1.certos=0;
			for(int i=0;i<cou1.tamanho*2;i++){
				if(i%2==0){
				cou1.vetorposicao[i]=ci;
				}else{
				cou1.vetorposicao[i]=li+(i/2);
				}
			}
		}else if(tmp==3 && cruz31.tamanho!=3){
			strcpy(cruz31.nome, "Cruzador3");
			cruz31.tamanho=3;
			cruz31.certos=0;
			for(int i=0;i<cruz31.tamanho*2;i++){
				if(i%2==0){
				cruz31.vetorposicao[i]=ci;
				}else{
				cruz31.vetorposicao[i]=li+(i/2);
				}
			}
		}else if(tmp==3 && sub1.tamanho!=3){
			strcpy(sub1.nome, "Submarino");
			sub1.tamanho=3;
			sub1.certos=0;
			for(int i=0;i<sub1.tamanho*2;i++){
				if(i%2==0){
				sub1.vetorposicao[i]=ci;
				}else{
				sub1.vetorposicao[i]=li+(i/2);
				}
			}	
		}else if(tmp==4){
			strcpy(cruz41.nome, "Cruzador4");
			cruz41.tamanho=4;
			cruz41.certos=0;
			for(int i=0;i<cruz41.tamanho*2;i++){
				if(i%2==0){
				cruz41.vetorposicao[i]=ci;
				}else{
				cruz41.vetorposicao[i]=li+(i/2);
				}
			}
		}else{
			strcpy(pa1.nome, "PortaAvioes");
			pa1.tamanho=5;
			pa1.certos=0;
			for(int i=0;i<pa1.tamanho*2;i++){
				if(i%2==0){
				pa1.vetorposicao[i]=ci;
				}else{
				pa1.vetorposicao[i]=li+(i/2);
				}
			}	
		}
	}else if(caso==4){
		if(tmp==2){
			strcpy(cou1.nome, "Couracado");
			cou1.tamanho=2;
			cou1.certos=0;
			for(int i=0;i<cou1.tamanho*2;i++){
				if(i%2==0){
				cou1.vetorposicao[i]=ci;
				}else{
				cou1.vetorposicao[i]=li-(i/2);
				}
			}
		}else if(tmp==3 && cruz31.tamanho!=3){
			strcpy(cruz31.nome, "Cruzador3");
			cruz31.tamanho=3;
			cruz31.certos=0;
			for(int i=0;i<cruz31.tamanho*2;i++){
				if(i%2==0){
				cruz31.vetorposicao[i]=ci;
				}else{
				cruz31.vetorposicao[i]=li-(i/2);
				}
			}
		}else if(tmp==3 && sub1.tamanho!=3){
			strcpy(sub1.nome, "Submarino");
			sub1.tamanho=3;
			sub1.certos=0;
			for(int i=0;i<sub1.tamanho*2;i++){
				if(i%2==0){
				sub1.vetorposicao[i]=ci;
				}else{
				sub1.vetorposicao[i]=li-(i/2);
				}
			}	
		}else if(tmp==4){
			strcpy(cruz41.nome, "Cruzador4");
			cruz41.tamanho=4;
			cruz41.certos=0;
			for(int i=0;i<cruz41.tamanho*2;i++){
				if(i%2==0){
				cruz41.vetorposicao[i]=ci;
				}else{
				cruz41.vetorposicao[i]=li-(i/2);
				}
			}
		}else{
			strcpy(pa1.nome, "PortaAvioes");
			pa1.tamanho=5;
			pa1.certos=0;
			for(int i=0;i<pa1.tamanho*2;i++){
				if(i%2==0){
				pa1.vetorposicao[i]=ci;
				}else{
				pa1.vetorposicao[i]=li-(i/2);
				}
			}	
		}
	}else if(caso==5){
		if(tmp==2){
			strcpy(cou2.nome, "Couracado");
			cou2.tamanho=2;
			cou2.certos=0;
			for(int i=0;i<cou2.tamanho*2;i++){
				if(i%2==0){
				cou2.vetorposicao[i]=li;
				}else{
				cou2.vetorposicao[i]=ci+(i/2);
				}
			}
		}else if(tmp==3 && cruz32.tamanho!=3){
			strcpy(cruz32.nome, "Cruzador3");
			cruz32.tamanho=3;
			cruz32.certos=0;
			for(int i=0;i<cruz32.tamanho*2;i++){
				if(i%2==0){
				cruz32.vetorposicao[i]=li;
				}else{
				cruz32.vetorposicao[i]=ci+(i/2);
				}
			}
		}else if(tmp==3 && sub2.tamanho!=3){
			strcpy(sub2.nome, "Submarino");
			sub2.tamanho=3;
			sub2.certos=0;
			for(int i=0;i<sub2.tamanho*2;i++){
				if(i%2==0){
				sub2.vetorposicao[i]=li;
				}else{
				sub2.vetorposicao[i]=ci+(i/2);
				}
			}	
		}else if(tmp==4){
			strcpy(cruz42.nome, "Cruzador4");
			cruz42.tamanho=4;
			cruz42.certos=0;
			for(int i=0;i<cruz42.tamanho*2;i++){
				if(i%2==0){
				cruz42.vetorposicao[i]=li;
				}else{
				cruz42.vetorposicao[i]=ci+(i/2);
				}
			}
		}else{
			strcpy(pa2.nome, "PortaAvioes");
			pa2.tamanho=5;
			pa2.certos=0;
			for(int i=0;i<pa2.tamanho*2;i++){
				if(i%2==0){
				pa2.vetorposicao[i]=li;
				}else{
				pa2.vetorposicao[i]=ci+(i/2);
				}
			}	
		}
	}else if(caso==6){
		if(tmp==2){
			strcpy(cou2.nome, "Couracado");
			cou2.tamanho=2;
			cou2.certos=0;
			for(int i=0;i<cou2.tamanho*2;i++){
				if(i%2==0){
				cou2.vetorposicao[i]=li;
				}else{
				cou2.vetorposicao[i]=ci-(i/2);
				}
			}
		}else if(tmp==3 && cruz32.tamanho!=3){
			strcpy(cruz32.nome, "Cruzador3");
			cruz32.tamanho=3;
			cruz32.certos=0;
			for(int i=0;i<cruz32.tamanho*2;i++){
				if(i%2==0){
				cruz32.vetorposicao[i]=li;
				}else{
				cruz32.vetorposicao[i]=ci-(i/2);
				}
			}
		}else if(tmp==3 && sub2.tamanho!=3){
			strcpy(sub2.nome, "Submarino");
			sub2.tamanho=3;
			sub2.certos=0;
			for(int i=0;i<sub2.tamanho*2;i++){
				if(i%2==0){
				sub2.vetorposicao[i]=li;
				}else{
				sub2.vetorposicao[i]=ci-(i/2);
				}
			}	
		}else if(tmp==4){
			strcpy(cruz42.nome, "Cruzador4");
			cruz42.tamanho=4;
			cruz42.certos=0;
			for(int i=0;i<cruz42.tamanho*2;i++){
				if(i%2==0){
				cruz42.vetorposicao[i]=li;
				}else{
				cruz42.vetorposicao[i]=ci-(i/2);
				}
			}
		}else{
			strcpy(pa2.nome, "PortaAvioes");
			pa2.tamanho=5;
			pa2.certos=0;
			for(int i=0;i<pa2.tamanho*2;i++){
				if(i%2==0){
				pa2.vetorposicao[i]=li;
				}else{
				pa2.vetorposicao[i]=ci-(i/2);
				}
			}	
		}
	}else if(caso==7){
		if(tmp==2){
			strcpy(cou2.nome, "Couracado");
			cou2.tamanho=2;
			cou2.certos=0;
			for(int i=0;i<cou2.tamanho*2;i++){
				if(i%2==0){
				cou2.vetorposicao[i]=ci;
				}else{
				cou2.vetorposicao[i]=li+(i/2);
				}
			}
		}else if(tmp==3 && cruz32.tamanho!=3){
			strcpy(cruz32.nome, "Cruzador3");
			cruz32.tamanho=3;
			cruz32.certos=0;
			for(int i=0;i<cruz32.tamanho*2;i++){
				if(i%2==0){
				cruz32.vetorposicao[i]=ci;
				}else{
				cruz32.vetorposicao[i]=li+(i/2);
				}
			}
		}else if(tmp==3 && sub2.tamanho!=3){
			strcpy(sub2.nome, "Submarino");
			sub2.tamanho=3;
			sub2.certos=0;
			for(int i=0;i<sub2.tamanho*2;i++){
				if(i%2==0){
				sub2.vetorposicao[i]=ci;
				}else{
				sub2.vetorposicao[i]=li+(i/2);
				}
			}	
		}else if(tmp==4){
			strcpy(cruz42.nome, "Cruzador4");
			cruz42.tamanho=4;
			cruz42.certos=0;
			for(int i=0;i<cruz42.tamanho*2;i++){
				if(i%2==0){
				cruz42.vetorposicao[i]=ci;
				}else{
				cruz42.vetorposicao[i]=li+(i/2);
				}
			}
		}else{
			strcpy(pa2.nome, "PortaAvioes");
			pa2.tamanho=5;
			pa2.certos=0;
			for(int i=0;i<pa2.tamanho*2;i++){
				if(i%2==0){
				pa2.vetorposicao[i]=ci;
				}else{
				pa2.vetorposicao[i]=li+(i/2);
				}
			}	
		}
	}else if(caso==8){
		if(tmp==2){
			strcpy(cou2.nome, "Couracado");
			cou2.tamanho=2;
			cou2.certos=0;
			for(int i=0;i<cou2.tamanho*2;i++){
				if(i%2==0){
				cou2.vetorposicao[i]=ci;
				}else{
				cou2.vetorposicao[i]=li-(i/2);
				}
			}
		}else if(tmp==3 && cruz32.tamanho!=3){
			strcpy(cruz32.nome, "Cruzador3");
			cruz32.tamanho=3;
			cruz32.certos=0;
			for(int i=0;i<cruz32.tamanho*2;i++){
				if(i%2==0){
				cruz32.vetorposicao[i]=ci;
				}else{
				cruz32.vetorposicao[i]=li-(i/2);
				}
			}
		}else if(tmp==3 && sub2.tamanho!=3){
			strcpy(sub2.nome, "Submarino");
			sub2.tamanho=3;
			sub2.certos=0;
			for(int i=0;i<sub2.tamanho*2;i++){
				if(i%2==0){
				sub2.vetorposicao[i]=ci;
				}else{
				sub2.vetorposicao[i]=li-(i/2);
				}
			}	
		}else if(tmp==4){
			strcpy(cruz42.nome, "Cruzador4");
			cruz42.tamanho=4;
			cruz42.certos=0;
			for(int i=0;i<cruz42.tamanho*2;i++){
				if(i%2==0){
				cruz42.vetorposicao[i]=ci;
				}else{
				cruz42.vetorposicao[i]=li-(i/2);
				}
			}
		}else{
			strcpy(pa2.nome, "PortaAvioes");
			pa2.tamanho=5;
			pa2.certos=0;
			for(int i=0;i<pa2.tamanho*2;i++){
				if(i%2==0){
				pa2.vetorposicao[i]=ci;
				}else{
				pa2.vetorposicao[i]=li-(i/2);
				}
			}	
		}
	}
	
	
}

void CorreEmbarcacoes (int jogador){
	qtdderrubadaA=0;
	qtdderrubadaB=0;
	if(jogador==1){
			if(cou2.certos==cou2.tamanho)
				qtdderrubadaA++;
			if(cruz32.certos==cruz32.tamanho)
				qtdderrubadaA++;	
			if(cruz42.certos==cruz42.tamanho)
				qtdderrubadaA++;
			if(sub2.certos==sub2.tamanho)
				qtdderrubadaA++;
			if(pa2.certos==pa2.tamanho)
				qtdderrubadaA++;
	}else{
			if(cou1.certos==cou1.tamanho)
				qtdderrubadaB++;
			if(cruz31.certos==cruz31.tamanho)
				qtdderrubadaB++;
			if(cruz41.certos==cruz41.tamanho)
				qtdderrubadaB++;
			if(sub1.certos==sub1.tamanho)
				qtdderrubadaB++;
			if(pa1.certos==pa1.tamanho)
				qtdderrubadaB++;
	}
}

void ImpressaodeEmbarcacoes(int jogador){
	if(jogador==1){
		qtdderrubadaA=0;
		qtdderrubadaB=0;
		printf("Embarcacoes do oponente encontradas: \n\n");
			if(cou2.certos==cou2.tamanho){
				printf("[X] %s\n", cou2.nome);
				qtdderrubadaA++;
			}else{
				printf("[ ] %s\n", cou2.nome);
			}
			if(cruz32.certos==cruz32.tamanho){
				qtdderrubadaA++;
				printf("[X] %s\n", cruz32.nome);	
			}else{
				printf("[ ] %s\n", cruz32.nome);
			}
			if(cruz42.certos==cruz42.tamanho){
				qtdderrubadaA++;
				printf("[X] %s\n", cruz42.nome);				
			}else{
				printf("[ ] %s\n", cruz42.nome);
			}
			if(sub2.certos==sub2.tamanho){
				qtdderrubadaA++;
				printf("[X] %s\n", sub2.nome);
			}else{
				printf("[ ] %s\n", sub2.nome);
			}
			if(pa2.certos==pa2.tamanho){
				qtdderrubadaA++;
				printf("[X] %s\n", pa2.nome);	
			}else{
				printf("[ ] %s\n", pa2.nome);
			}
	}
	else{
		printf("Embarcacoes do oponente encontradas: \n\n");
			if(cou1.certos==cou1.tamanho){
				qtdderrubadaB++;
				printf("[X] %s\n", cou1.nome);
			}else{
				printf("[ ] %s\n", cou1.nome);
			}
			if(cruz31.certos==cruz31.tamanho){
				qtdderrubadaB++;
				printf("[X] %s\n", cruz31.nome);	
			}else{
				printf("[ ] %s\n", cruz31.nome);
			}
			if(cruz41.certos==cruz41.tamanho){
				qtdderrubadaB++;
				printf("[X] %s\n", cruz41.nome);				
			}else{
				printf("[ ] %s\n", cruz41.nome);
			}
			if(sub1.certos==sub1.tamanho){
				qtdderrubadaB++;
				printf("[X] %s\n", sub1.nome);
			}else{
				printf("[ ] %s\n", sub1.nome);
			}
			if(pa1.certos==pa1.tamanho){
				qtdderrubadaB++;
				printf("[X] %s\n", pa1.nome);	
			}else{
				printf("[ ] %s\n", pa1.nome);
			}
	}
}

void carregarposicoes(){
	int con=0, i, j;
	struct posicao navios[10];
	FILE *arq;
	int tmp=0;
	int caso;
	arq = fopen("entrada1.txt", "r");
	printf("Carregando arquivos de jogador 1 no sistema!\n");
	if(arq==NULL){
		printf("Opa, encontramos alguma falha, favor verificar arquivos!");
		exit(1);
		system("pause");
	}else{
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				tabuleiro1[i][j]='W';
				tabuleiro2[i][j]='W';
			}
		}
		for(i=0;i<8;i++)
			for(j=0;j<8;j++)
				matrizjogadas[i][j]=0;
		while(con<5){
			fscanf(arq,"%d %d %d %d\n", &navios[con].li, &navios[con].ci, &navios[con].lf, &navios[con].cf);
			tmp=0;
			navios[con].li--;
			navios[con].ci--;
			navios[con].lf--;
			navios[con].cf--;
			if(navios[con].li==navios[con].lf){
				if(navios[con].ci<navios[con].cf){
					for(j=navios[con].ci; j<=navios[con].cf; j++){
						tabuleiro1[navios[con].li][j]='X';
						tmp++;
					}
					caso=1;
				}else{
					for(j=navios[con].cf; j<=navios[con].ci; j++){
						tabuleiro1[navios[con].li][j]='X';
						tmp++;
					}
					caso=2;
				}
			}
			else if(navios[con].ci==navios[con].cf){
				if(navios[con].li<navios[con].lf){
					for(i=navios[con].li; i<=navios[con].lf; i++){
						tabuleiro1[i][navios[con].ci]='X';
						tmp++;
					}
					caso=3;
				}else{
					for(i=navios[con].lf; i<=navios[con].li; i++){
						tabuleiro1[i][navios[con].ci]='X';
						tmp++;
					}
					caso=4;
				}
			}
			AIdeconhecimento(caso, tmp, navios[con].li, navios[con].ci);
			con++;
		}
		fclose(arq);
		printf("Base de jogador 1 carregada com sucesso!\n");
		printf("Carregando arquivos de jogador 2 no sistema!\n");
		arq = fopen("entrada2.txt", "r");
		if(arq==NULL){
			printf("Opa, encontramos alguma falha, favor verificar arquivos!");
			exit(1);
			system("pause");
		}else{
			while (con<10){
			fscanf(arq,"\n%d %d %d %d", &navios[con].li, &navios[con].ci, &navios[con].lf, &navios[con].cf);
				tmp=0;
				navios[con].li--;
				navios[con].ci--;
				navios[con].lf--;
				navios[con].cf--;
				if(navios[con].li==navios[con].lf){
					if(navios[con].ci<navios[con].cf){
						for(j=navios[con].ci; j<=navios[con].cf; j++){
							tabuleiro2[navios[con].li][j]='X';
							tmp++;
						}
					caso=5;
					}
					else{
						for(j=navios[con].cf; j<=navios[con].ci; j++){
							tabuleiro2[navios[con].li][j]='X';
							tmp++;
						}
					caso=6;
					}
				}
				else if(navios[con].ci==navios[con].cf){
					if(navios[con].li<navios[con].lf){
						for(i=navios[con].li; i<=navios[con].lf; i++){
							tabuleiro2[i][navios[con].ci]='X';
							tmp++;
						}
					caso=7;
					}
					else{
						for(i=navios[con].lf; i<=navios[con].li; i++){
							tabuleiro2[i][navios[con].ci]='X';
							tmp++;
						}
					caso=8;
					}
				}
				AIdeconhecimento(caso, tmp, navios[con].li, navios[con].ci);
				con++;
			}
		}
	}
	fclose(arq);
	printf("Base de jogador 2 carregada com sucesso!\n");
}

void jogarpvp(){
	int jogada=2;
	atab1=0;
	atab2=0;
	int x;
	while(1){
		if(jogada%2==0){			//jogador 1
			impressaoMapa();
			ImpressaodeEmbarcacoes(1);
			ImpressaodeTiros(1);
			printf("\n\nJogador 1: ");
			scanf("%d""%d", &linha, &coluna);
			x=verificarjogada(1, linha,coluna);
			if(x==1){
				linha--;
				coluna--;
				if(matrizjogadas[linha][coluna]==2){
					matrizjogadas[linha][coluna]=12;
				}else{
					matrizjogadas[linha][coluna]=1;
				}
				if(tabuleiro1[linha][coluna]=='X'){
					atab1++;
					tabuleiroexib1[linha][coluna]='X';
					imprimirPontilhado();
					printf("\t\t General do oponente avisa: *Tiro em alvo.\n");
					imprimirPontilhado();
					verificarembarcacao(1,linha,coluna);
					setbuf(stdin, NULL);
					getchar();
					
				}
				else if(tabuleiro1[linha][coluna]=='W'){
					tabuleiroexib1[linha][coluna]='W';
					imprimirPontilhado();
					printf("\t\t General do oponente avisa: *Tiro em agua.\n");
					imprimirPontilhado();
					setbuf(stdin, NULL);
					getchar();
				}
			}else{
				imprimirPontilhado();
				printf("Tiro errado!\n");
				imprimirPontilhado();
				setbuf(stdin, NULL);
				getchar();
				jogada--;
			}
			CorreEmbarcacoes(1);
			if(qtdderrubadaA==5)
				break;
		}else{			//jogador 2

			system("cls");
			impressaoMapa();
			ImpressaodeEmbarcacoes(2);
			ImpressaodeTiros(2);
			printf("\n\nJogador 2: ");
			scanf("%d""%d", &linha, &coluna);
			x=verificarjogada(2, linha,coluna);
			if(x==1){
				linha--;
				coluna--;
				if(matrizjogadas[linha][coluna]==1){
					matrizjogadas[linha][coluna]=12;
				}else{
					matrizjogadas[linha][coluna]=2;
				}
				if(tabuleiro2[linha][coluna]=='X'){
					atab2++;
					tabuleiroexib2[linha][coluna]='X';
					imprimirPontilhado();
					printf("\t\t General do oponente avisa: *Tiro em alvo.\n");
					imprimirPontilhado();
					verificarembarcacao(2,linha,coluna);
					setbuf(stdin, NULL);
					getchar();
					
				}
				else if(tabuleiro2[linha][coluna]=='W'){
					tabuleiroexib2[linha][coluna]='W';
					imprimirPontilhado();
					printf("\t\t General do oponente avisa: *Tiro em agua.\n");
					imprimirPontilhado();	
					setbuf(stdin, NULL);
					getchar();
				}
			}else{
				imprimirPontilhado();
				printf("Tiro errado!\n");
				imprimirPontilhado();
				setbuf(stdin, NULL);
				getchar();
				jogada--;
			}
			CorreEmbarcacoes(2);
			if(qtdderrubadaB==5)
				break;
		}
		jogada++;
	}
	if(qtdderrubadaA==5){
		system("cls");
		imprimirPontilhado();
			imprimirCentralizado("Batalha Naval!");
			imprimirPontilhado();
		printf("Jogador 1 venceu!\n");
		
	}
	else if(qtdderrubadaB==5){
		system("cls");
		imprimirPontilhado();
		imprimirCentralizado("Batalha Naval!");
		imprimirPontilhado();
		printf("Jogador 2 venceu!\n");
	}
	getche();
}

void anexo1(){
	int qtdjogadas1;
	int x;
	impressaoMapa();
	ImpressaodeEmbarcacoes(1);
	ImpressaodeTiros(1);
	qtdjogadas1++;
	printf("\n\nJogador 1: ");
	scanf("%d""%d", &linha, &coluna);
	x=verificarjogada(1, linha,coluna);
	if(x==1){
		linha--;
		coluna--;
		if(matrizjogadas[linha][coluna]==2){
					matrizjogadas[linha][coluna]=12;
				}else{
					matrizjogadas[linha][coluna]=1;
				}
		if(tabuleiro1[linha][coluna]=='X'){
			atab1++;
			tabuleiroexib1[linha][coluna]='X';
			imprimirPontilhado();
			printf("\t\t General do oponente avisa: *Tiro em alvo.\n");
			imprimirPontilhado();
			verificarembarcacao(1,linha,coluna);
			setbuf(stdin, NULL);
			getchar();
		}else if(tabuleiro1[linha][coluna]=='W'){
			tabuleiroexib1[linha][coluna]='W';
			imprimirPontilhado();
			printf("\t\t General do oponente avisa: *Tiro em agua.\n");
			imprimirPontilhado();
			setbuf(stdin, NULL);
			getchar();
		}
	}else{
				imprimirPontilhado();
				printf("Tiro errado!\n");
				imprimirPontilhado();
				setbuf(stdin, NULL);
			}
}

void anexohard2(){
	int repeteounaorepete;
	impressaoMapa();
	ImpressaodeEmbarcacoes(2);
	ImpressaodeTiros(2);
	printf("\n\nJogador 2: ");
	if(teste=='X'){
			if(mp==1){
				if(tabuleiro2[direitalinha][direitacoluna+1]=='X'&&direitacoluna<7){
					tabuleiroexib2[direitalinha][direitacoluna+1]='X';
					if(matrizjogadas[direitalinha][direitacoluna+1]==1){
						matrizjogadas[direitalinha][direitacoluna+1]=12;
					}else{
						matrizjogadas[direitalinha][direitacoluna+1]=2;
					}
					printf("%d-%d\n", direitalinha+1,direitacoluna+2);
					imprimirPontilhado();
					printf("\t\t General do oponente avisa: *Tiro em alvo.\n");
					imprimirPontilhado();
					verificarembarcacao(2,direitalinha,direitacoluna+1);				
					setbuf(stdin, NULL);
					getchar();
					direitacoluna++;
					atab2++;
				}else
				mp=2;
			}
			if(mp==2){
				if(tabuleiro2[baixolinha+1][baixocoluna]=='X'&&baixolinha<7){
					tabuleiroexib2[baixolinha+1][baixocoluna]='X';
					if(matrizjogadas[baixolinha+1][baixocoluna]==1){
						matrizjogadas[baixolinha+1][baixocoluna]=12;
					}else{
						matrizjogadas[baixolinha+1][baixocoluna]=2;
					}
					printf("%d-%d\n", baixolinha+2,baixocoluna+1);
					imprimirPontilhado();
					printf("\t\t General do oponente avisa: *Tiro em alvo.\n");
					imprimirPontilhado();
					verificarembarcacao(2,baixolinha+1,baixocoluna);
					setbuf(stdin, NULL);
					getchar();
					baixolinha++;
					atab2++;
				}
				else
				mp=3;
			}
			if(mp==3){
				if(tabuleiro2[esquerdalinha][esquerdacoluna-1]=='X'&&esquerdacoluna>0){
					tabuleiroexib2[esquerdalinha][esquerdacoluna-1]='X';
					if(matrizjogadas[esquerdalinha][esquerdacoluna-1]==1){
						matrizjogadas[esquerdalinha][esquerdacoluna-1]=12;
					}else{
						matrizjogadas[esquerdalinha][esquerdacoluna-1]=2;
					}
					printf("%d-%d\n", esquerdalinha+1,esquerdacoluna);
					imprimirPontilhado();
					printf("\t\t General do oponente avisa: *Tiro em alvo.\n");
					imprimirPontilhado();
					verificarembarcacao(2,esquerdalinha,esquerdacoluna-1);	
					setbuf(stdin, NULL);
					getchar();
					esquerdacoluna--;
					atab2++;
				}
				else
				mp=4;
			}
			if(mp==4){
				if(tabuleiro2[cimalinha-1][cimacoluna]=='X'&&cimalinha>0){
					tabuleiroexib2[cimalinha-1][cimacoluna]='X';
					if(matrizjogadas[cimalinha-1][cimacoluna]==1){
						matrizjogadas[cimalinha-1][cimacoluna]=12;
					}else{
						matrizjogadas[cimalinha-1][cimacoluna]=2;
					}
					printf("%d-%d\n", cimalinha,cimacoluna+1);
					printf("\t\t General do oponente avisa: *Tiro em alvo.\n");
					imprimirPontilhado();
					verificarembarcacao(2,cimalinha,cimacoluna+1);
					setbuf(stdin, NULL);
					getchar();
					cimalinha--;
					atab2++;
					getche();
				}
				else
				teste='O';
			}
	}
	if(teste=='O'){
		srand((unsigned)time(NULL));
		do{
			linha=rand()%8;
			coluna=rand()%8;
			if(tabuleiroexib2[linha][coluna]=='X'||tabuleiroexib2[linha][coluna]=='W')
				repeteounaorepete=1;
			else
				repeteounaorepete=0;
		}while(repeteounaorepete==1);
		if(matrizjogadas[linha][coluna]==1){
			matrizjogadas[linha][coluna]=12;
		}else{
			matrizjogadas[linha][coluna]=2;
		}
		printf("%d-%d\n", linha+1,coluna+1);
		if(tabuleiro2[linha][coluna]=='X'){
			tabuleiroexib2[linha][coluna]='X';
			atab2++;
			teste='X';
			mp=1;
			direitalinha=linha;
			direitacoluna=coluna;
			baixolinha=linha;
			baixocoluna=coluna;
			esquerdalinha=linha;
			esquerdacoluna=coluna;
			cimalinha=linha;
			cimacoluna=coluna;
			imprimirPontilhado();
			printf("\t\t General do oponente avisa: *Tiro em alvo.\n");
			imprimirPontilhado();
			setbuf(stdin, NULL);
			getchar();
			verificarembarcacao(2,linha,coluna);
			linha++;
			coluna++;
		}else{
			tabuleiroexib2[linha][coluna]='W';
			teste='O';
			linha++;
			coluna++;
			imprimirPontilhado();
			printf("\t\t General do oponente avisa: *Tiro em agua.\n");
			imprimirPontilhado();
			setbuf(stdin, NULL);
			getchar();
		}
	}
}

void anexoeasy2(){
	int repeteounaorepete;
	impressaoMapa();
	ImpressaodeEmbarcacoes(2);
	ImpressaodeTiros(2);
	printf("\n\nJogador 2: ");
	srand((unsigned)time(NULL));
	do{
		linha=rand()%8;
		coluna=rand()%8;
		if(tabuleiroexib2[linha][coluna]=='X'||tabuleiroexib2[linha][coluna]=='W')
			repeteounaorepete=1;
		else
			repeteounaorepete=0;
	}while(repeteounaorepete==1);
	printf("%d-%d\n", linha+1,coluna+1);
	if(matrizjogadas[linha][coluna]==1){
		matrizjogadas[linha][coluna]=12;
	}else{
		matrizjogadas[linha][coluna]=2;
	}
	if(tabuleiro2[linha][coluna]=='X'){
		tabuleiroexib2[linha][coluna]='X';
		atab2++;
		linha++;
		coluna++;
		imprimirPontilhado();
		printf("\t\t General do oponente avisa: *Tiro em alvo.\n");
		imprimirPontilhado();
		verificarembarcacao(2,linha,coluna);
		setbuf(stdin, NULL);
		getchar();
		}
		else{
			tabuleiroexib2[linha][coluna]='W';
			linha++;
			coluna++;
			imprimirPontilhado();
			printf("\t\t General do oponente avisa: *Tiro em agua.\n");
			imprimirPontilhado();
			setbuf(stdin, NULL);
			getchar();
		}
}

void jogarcoophard(){
	int jogada=2;
	atab1=0;
	atab2=0;
	while(1){
		if(jogada%2==0){
			anexo1();
			CorreEmbarcacoes(1);
			if(qtdderrubadaA==5)
				break;
		}else{
			anexohard2();
			CorreEmbarcacoes(2);
			if(qtdderrubadaB==5)
				break;
		}
		jogada++;
	}
	if(qtdderrubadaA==5){
		system("cls");
		imprimirPontilhado();
			imprimirCentralizado("Batalha Naval!");
			imprimirPontilhado();
		printf("Jogador 1 venceu!\n");
		
	}
	else if(qtdderrubadaB==5){
		system("cls");
		imprimirPontilhado();
		imprimirCentralizado("Batalha Naval!");
		imprimirPontilhado();
		printf("Computador venceu!\n");
	}
}

void jogarcoopeasy(){
	int jogada=2;
	atab1=0;
	atab2=0;
	while(1){
		if(jogada%2==0){
			anexo1();
			CorreEmbarcacoes(1);
			if(qtdderrubadaA==5)
				break;
		}
		else{
			anexoeasy2();
			CorreEmbarcacoes(2);
			if(qtdderrubadaB==5)
				break;
		}
		jogada++;
	}
	if(qtdderrubadaA==5){
		system("cls");
		imprimirPontilhado();
			imprimirCentralizado("Batalha Naval!");
			imprimirPontilhado();
		printf("Jogador 1 venceu!\n");
		
	}
	else if(qtdderrubadaB==5){
		system("cls");
		imprimirPontilhado();
		imprimirCentralizado("Batalha Naval!");
		imprimirPontilhado();
		printf("Computador venceu!\n");
	}
	getche();
}

int main(){
	keybd_event ( VK_MENU, 0x36, 0, 0 ); 
	keybd_event ( VK_RETURN, 0x1C, 0, 0 ); 
	keybd_event ( VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0 ); 
	keybd_event ( VK_MENU, 0x38, KEYEVENTF_KEYUP, 0 );
	int dificuldade, x, i, j, modo;
	do{
		backcolor(BLUE);
		system("cls");
		imprimirPontilhado();
		imprimirCentralizado("\t\t\tMENU");
		imprimirCentralizado("Jogo Batalha Naval!");
		imprimirPontilhado();
		printf("\n 1-Carregar\n 2-Jogar!\n 3-Sair\n");
		printf("\n Sua opcao: ");
		scanf("%d", &x);
		if(x==1){
			system("cls");
			imprimirPontilhado();
			imprimirCentralizado("Carregamento de Arquivos para Sistema");
			imprimirCentralizado("Jogo Batalha Naval!");
			imprimirPontilhado();
			carregarposicoes();
			printf("\n\n\nDigite qualquer tecla para continuar...");
				
		}
		else if(x==2){
			system("cls");
			imprimirPontilhado();
			imprimirCentralizado("************ Modo de Jogo ************");
			imprimirCentralizado("Jogo Batalha Naval!");
			imprimirPontilhado();
			imprimirCentralizado("Selecionar modalidade de jogo:");
			printf(" 1-PVP\n 2-COOP\n");
			printf("\n Sua opcao: ");
			scanf("%d", &modo);
			switch (modo){
				case 1:
				jogarpvp();
				break;
				case 2:
				imprimirPontilhado();
				imprimirCentralizado("************ Dificuldade do Jogo ************");
				imprimirCentralizado("Jogo Batalha Naval!");
				imprimirPontilhado();
				printf("\n 1-EASY\n 2-HARD\n");
				printf("\n Sua opcao: ");
				scanf("%d", &dificuldade);
				switch(dificuldade){
					case 1:
					jogarcoopeasy();
					break;
					case 2:
					jogarcoophard();
					break;
				}
			}
		}
		else if(x==4){
			imprimirPontilhado();
			imprimirCentralizado("Impressao de Infos. importantes");
			imprimirCentralizado("Jogo Batalha Naval!");
			imprimirPontilhado();
			system("cls");
			printf("%s\t %d %d ", cou1.nome, cou1.tamanho,cou1.certos);
			for(int i=0;i<10;i++){
				printf("%d ", cou1.vetorposicao[i]);
			}
			printf("\n");
			printf("%s\t %d %d ", cou2.nome, cou2.tamanho,cou2.certos);
			for(int i=0;i<10;i++){
				printf("%d ", cou2.vetorposicao[i]);
			}
			printf("\n");
			printf("%s\t %d %d ", cruz31.nome, cruz31.tamanho,cruz31.certos);
			for(int i=0;i<10;i++){
				printf("%d ", cruz31.vetorposicao[i]);
			}
			printf("\n");
			printf("%s\t %d %d ", cruz32.nome, cruz32.tamanho,cruz32.certos);
			for(int i=0;i<10;i++){
				printf("%d ", cruz32.vetorposicao[i]);
			}
			printf("\n");
			printf("%s\t %d %d ", cruz41.nome, cruz41.tamanho,cruz41.certos);
			for(int i=0;i<10;i++){
				printf("%d ", cruz41.vetorposicao[i]);
			}
			printf("\n");
			printf("%s\t %d %d ", cruz42.nome, cruz42.tamanho,cruz42.certos);
			for(int i=0;i<10;i++){
				printf("%d ", cruz42.vetorposicao[i]);
			}
			printf("\n");
			printf("%s\t %d %d ", sub1.nome, sub1.tamanho,sub1.certos);
			for(int i=0;i<10;i++){
				printf("%d ", sub1.vetorposicao[i]);
			}
			printf("\n");
			printf("%s\t %d %d ", sub2.nome, sub2.tamanho,sub2.certos);
			for(int i=0;i<10;i++){
				printf("%d ", sub2.vetorposicao[i]);
			}
			printf("\n");
			printf("%s\t %d %d ", pa1.nome, pa1.tamanho,pa1.certos);
			for(int i=0;i<10;i++){
				printf("%d ", pa1.vetorposicao[i]);
			}
			printf("\n");
			printf("%s\t %d %d ", pa2.nome, pa2.tamanho,pa2.certos);
			for(int i=0;i<10;i++){
				printf("%d ", pa2.vetorposicao[i]);
			}
			printf("\n\n");
			
			//teste
			printf("Matriz Jogador 1\n");
			for(int i=0;i<8;i++){
				printf("\n");
				for (int j=0;j<8;j++){
					printf("%c ", tabuleiro1[i][j]);
				}
			}
			printf("\n\n");
			printf("Matriz Jogador 2\n");
			for(int i=0;i<8;i++){
				printf("\n");
				for (int j=0;j<8;j++){
					printf("%c ", tabuleiro2[i][j]);
				}
			}
			
			//teste	
		}
		getche();
		system("cls");	
	}while(x!=3);

}
