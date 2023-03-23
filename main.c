#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "Produto.h"
#include "Cliente.h"
#include "Adm.h"
#include "Login.h"
#include "Relatorio.h"

#define TAMANHONOMEUSUARIO 30
#define TAMANHOCOD 3
#define TAMANHOTEL 15
#define CODUSUARIOONLINE 0
void ToUpperString(char nome[]) {
   int i;

   for (i = 0; nome[i]!='\0'; i++) {
      if(nome[i] >= 'a' && nome[i] <= 'z') {
         nome[i] = nome[i] -32;
      }
   }
}

int GeraCod(char AqruivoDeGeraCod[]){
	FILE *farq;
	
	int result, cod, novocod, i;

		if((farq = fopen(AqruivoDeGeraCod,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados.");               
    }
    else
    {
    	result = 0;
		while(result == feof(farq))//ve o ab quivo até chegar na ultima linha e guarda o valor da ultima linha
		{
			fscanf(farq,"%i\n",  &cod);
		}
		novocod = cod+1;
		
		fclose(farq);
		farq = fopen(AqruivoDeGeraCod,"w");
		result = fprintf(farq,"%i", novocod);
	}
	
    fclose(farq);
    return novocod;
}

void main(){

int codUsuarioOnline = 0;

setlocale(LC_ALL, "portuguese");	

	Login();


}
