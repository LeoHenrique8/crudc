#include<stdlib.h>
#include<string.h>
#include<stdio.h>

void Adm(){
char opc;
do {
	system("cls");
	 printf(  "|--------------------EMPRESA (MODO ADMINISTRADOR)------------------");
	 printf("\n| Digite P para acessar o gerenciamento de produto: ");
	 printf("\n| Digite C para acessar o gerenciamento de cliente: ");
	 printf("\n| Digite U para acessar o gerenciamento de usuarios: ");
	 printf("\n| Digite T para acessar o gerenciamento de categorias: ");
	 printf("\n| Digite R para acessar o gerenciamento de relatórios: ");
	 printf("\n| Digite L para voltar à tela de login: ");
	 
	 scanf("%c", &opc);
	 
	 if(tolower(opc) == 'p'){
	 	Produto(); 
	 }
	 if(tolower(opc)=='c'){
	 	Cliente();
	 }
	 if(tolower(opc)=='u'){
	 	GerenciarUsuarios();
	 }
	 if(tolower(opc)=='l'){
	 	system("cls");
	 	getchar();
	 	Login();
	}	
	 if(tolower(opc)=='t'){
	 	Categoria();
	}
	if(tolower(opc)=='r'){
	 	Relatorio();
	}
	if(tolower(opc)=='x'){
	 	exit(0);
	}
	 
	} while (tolower(opc) != 'x');
	
}
