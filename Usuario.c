#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "Usuario.h"

#define NOMEARQUIVOUSUARIO "CadastrosDeUsuario.txt"
	
void GerenciarUsuarios(){
	system("cls");
	char opc = 'a';
	do{		
		system("cls");
		printf(" ------------ GERENCIAMENTO DE USUARIOS ------------  ");
		printf("\nDIGITE P PARA CADASTRAR UM USUARIO. ");
		printf("\nDIGITE E PARA EXCLUIR UM USUARIO. ");
		printf("\nDIGITE A PARA ALTERAR A SENHA DE UM USUARIO. ");
		printf("\nDIGITE R PARA VERIFICAR UMA LISTA DOS USUARIO CADASTRADOS. \n");
		printf("\nDIGITE V PARA VOLTAR À TELA INICIAL. \n");
	
		scanf("%c", &opc);
		if(tolower(opc) == 'p'){
			while(tolower(opc)=='p')
			{	
			    CadastroDeUsuario();	  
			    
			    system("cls");
	            printf("Insira P para cadastrar um usuário novamente ou informe qualquer informação para sair\n");
	            scanf("%c", &opc);  
			}
		}	
		
		if(tolower(opc) == 'r'){
			while(tolower(opc)=='r')
			{	
			    ListarCadastroDeUsuario(0);	  
			    getchar();
			    getchar();
			    
			    system("cls");
			    printf("Insira R verificar novamente a lista de usuários cadastrados ou informe qualquer informação para sair\n");//voltar ao menu inicial.\n");
			    scanf("%c", &opc);  
			}
		}		
	}while(tolower(opc) != 'v');
}

void CadastroDeUsuario(){

	dados_usuario P;
	dados_usuario R;	
	FILE *farq;
	int result;
	int j;
	
	//LIMPA A APRESENTAÇÃO NO CMD E INICIA O CADASTRO DE PRODUTO
    //PEDE AS INFORMAÇOES NECESSÁRIAS PARA O CADASTRO DE PRODUTO
	system("cls");
	printf("--------------------CADASTRO DE USUÁRIOS------------------");
	
	printf("\nDigite o nome de usuário: ");
	getchar();
	fgets(P.username, TAMANHONOME, stdin);
	
	
	printf("\nDigite a senha: ");
	
	fgets(P.senha, TAMANHONOME, stdin);
	
	//REMOVE A QUEBRA DE LINHA DO FGETS
	P.username[strcspn(P.username, "\n")] = 0;
	P.senha[strcspn(P.senha, "\n")] = 0;
	P.inativo = 0;
	P = Criptografar(P);
	P.cod = GeraCod("CodLogin.txt");

	//INICIA A GRAVAÃ‡ÃƒO DOS DADOS DO PRODUTO NO ARQUIVO	
	
	//Verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOUSUARIO,"a")) == NULL)
	{
		printf("Houve um inconveniente ao realizar o cadastro do usuário. Verifique sua conexão com o Computador principal e inicie o cadastro do produto novamente.");               
    }
    else
    {
    	//Imprimi os dados no arquivo
		result = EscreveOUsuarioNoArquivo(P, farq);
		//Valida se conseguiu imprimir os dados no aquivo
		if (result != EOF && result > 1)
		{
			printf("\nO usuário cadastrado foi cadastrado com sucesso.\n");
		}
		else
		{
			printf("\nHouve um inconveniente na execução do cadastro do usuário.\n");
		}	
	}
	fclose(farq);
	
	//LEITURA DO ARQUIVO E CAPTURA DA INFORMAÃ‡ÃƒO DA ULTIMA LINHA
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOUSUARIO,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do usuário cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R = LeituraDoUsuarioNoArquivo(farq);
		}
				
		//imprimi os dados da ultima linha do arquivo
		printf("\n----------Dados do Usuario Cadastrado----------");
		ImprimirDadosDoUsuario(R);
	}
    fclose(farq);
	
	printf("\n");
	getchar();	
 
}

void ListarCadastroDeUsuario(int mostraInativo){
	
	char ArquivoDeCadUser[] = "CadastrosDeUsuario.txt";
	dados_usuario R[100];	
	FILE *farq;
	int result;
	int i = 0, j= 0;
	
	
	//LIMPA A APRESENTAÃ‡ÃƒO NO CMD E INICIA O CADASRO DE USUARIO
    system("cls");
	printf("--------------------USUÁRIOS------------------");

	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOUSUARIO,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do usuário cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo atÃ© chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R[i] = LeituraDoUsuarioNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    //imprimi os dados da ultima linha do arquivo
	printf("\nDados dos Usuários Cadastrados:");
	
	if (mostraInativo == 0)
	{	
		for (j = 0; j < i; j++)
		{	
			if (R[j].inativo == 0)
			{
				ImprimirDadosDoUsuario(R[j]);	
			}			
		}
	}
	else	
	{	
		for (j = 0; j < i; j++)
		{	
			ImprimirDadosDoUsuario(R[j]);				
		}
	}
	
	printf("\n");
}

void ImprimirDadosDoUsuario(dados_usuario T){
	
	int i;
	//Verifica o tamanho da string, pora ajustar na exibiçao, nomes embaixo de nomes e valores embaixo de valores/
	if(strlen(T.username)<TAMANHONOME)
	{
    	//Como o tamanho máximo TAMANHONOME, ele calcula o tamanho da string, e subtrai de TAMANHONOME para ver quanto espaço falta/				
		int diflen = TAMANHONOME - strlen(T.username);
    	//ele soma os espaços necessários na string do nome para alinhar com o valor/				
		for(i=0; i<diflen;i++){
			strcpy(T.username, strcat(T.username, "."));
		}
	}
	printf("\nCodigo: %i | Usuário : %s | ", T.cod, T.username);		
}

dados_usuario LeituraDoUsuarioNoArquivo(FILE *farq){
	
	dados_usuario T;
	fscanf(farq,"%i;%30[^;];%10[^;];%i\n",  &T.cod, T.username, T.senha, &T.inativo);
	return T;
}

int EscreveOUsuarioNoArquivo(dados_usuario P, FILE *farq){
	P.username[strcspn(P.username, "\n")] = 0;
	P.senha[strcspn(P.senha, "\n")] = 0;
		
	int escreveuComSucesso;	
	
	escreveuComSucesso = fprintf(farq,"%i;%s;%s;%i\n", P.cod, P.username, P.senha, P.inativo);
	
	return escreveuComSucesso;
}

dados_usuario LeituraDoUsuarioOnlineNoArquivo(){
	
	FILE *farq;
	dados_usuario T;
	
	if((farq = fopen("UsuarioOnline.txt","r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do usuário cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
		fscanf(farq,"%i;%30[^;]",  &T.cod, T.username);
	}
    fclose(farq);

	return T;
}

void EscreveOUsuarioOnlineNoArquivo(int codUsuario, char nomeUsuario[]){
	
	FILE *farq;
	int result;
	
	if((farq = fopen("UsuarioOnline.txt","w")) == NULL)
	{
		printf("Houve um inconveniente ao realizar o cadastro do usuário. Verifique sua conexão com o Computador principal e inicie o cadastro do produto novamente.");               
    }
    else
    {
    	//Imprimi os dados no arquivo
		result = fprintf(farq,"%i;%s;", codUsuario, nomeUsuario);
		//Valida se conseguiu imprimir os dados no aquivo
		if (result != EOF && result > 1)
		{
			printf("\nO usuário online foi cadastrado com sucesso.\n");
		}
		else
		{
			printf("\nHouve um inconveniente na execução do cadastro do usuário.\n");
		}	
	}
	fclose(farq);
}

dados_usuario Criptografar(dados_usuario U){
	int i;
	
	for(i = 0 ; i < strlen(U.senha) ; i++){
		if(U.senha[i] == 'z'){
			U.senha[i] = 'c';
        }
        else  if(U.senha[i] == 'y'){
        	U.senha[i] = 'b';
        }
        else if (U.senha[i] == 'x'){
   			U.senha[i] = 'a';
        }
        else {
        	U.senha[i] = U.senha[i] + 3 ; 
        }
	}
	return U;
}

dados_usuario Descriptografar(dados_usuario U){
     int i;
	 for(i = 0; i < strlen(U.senha); ++i){
    	U.senha[i] = (char)((int)U.senha[i] - 3);
    } 
    return U;
}
