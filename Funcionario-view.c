#include<stdlib.h>
#include<string.h>
#include<stdio.h>

void Funcionario(){
char opc;
do {
	system("cls");
	 printf(  "|--------------------EMPRESA------------------");
	 printf("\n| Digite v para acessar o gerenciamento de venda: ");
	 printf("\n| Digite P para acessar o gerenciamento de produto: ");
	 printf("\n| Digite C para acessar o gerenciamento de cliente: ");
	 printf("\n| Digite L para voltar à tela de login: ");
	 
	 scanf("%c", &opc);

	 if(tolower(opc) == 'v'){
	 	Venda(); 
	 }	 
	 if(tolower(opc) == 'p'){
	 	Produto(); 
	 }
	 if(tolower(opc)=='c'){
	 	Cliente();
	 }
	 if(tolower(opc)=='l'){
	 	system("cls");
	 	getchar();
	 	Login();
	}	
	if(tolower(opc)=='x'){
	 	exit(0);
	}
	} while (tolower(opc) != 'x');
	
}
