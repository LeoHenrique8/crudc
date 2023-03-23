#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "Adm.h"
#include "Login.h"
#include "Usuario.h"

void Login(){
	int a,b=1,d=3;
	char c="";
	char usuario[30]="";
	char senha[30]="";
	int opc, i;
	dados_usuario P;
	
	for(i=0; i < 4; i++){
		a = 0;
		
		printf("\n\n\n\t\t\t LOGIN: ");
		fgets(usuario, TAMANHONOME, stdin);
		
		printf("\n\n\n\t\t\t SENHA: ");
		
			  do{
                   c=getch();
                   if(isprint(c)){      //Analisa se o valor de c é imprimível
                   senha[a]=c;
                   a++;
                   printf("*");      	//Imprimindo apenas o asterisco *
                   }
                   else if(c==8&&a){
                   senha[a]='\0';
                   a--;
                   printf("\b \b");     //Apagando os caracteres digitados
                   }
               }while(c!=13);           //13 é o valor de ENTER na tabela ASCII
        senha[a]='\0';

		usuario[strcspn(usuario, "\n")] = 0;
		senha[strcspn(senha, "\n")] = 0;
		opc = Logar(usuario, senha);

		if (opc == 2){
			Adm();
		}else{
			if(opc ==1 ){
				Funcionario();
			}else{
				printf("\n \t\t\t senha inválida! Pressione qualquer tecla e digite novamente");
				getchar();
				system("cls");
			}
		}
	}	
}
