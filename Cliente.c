#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "cliente.h"


#define TAMANHONOMECLIENTE 30
#define TAMANHOCOD 3
#define TAMANHOTEL 20
#define NOMEARQUIVOCADASTROCLIENTE "CadastrosDeCliente.txt"


void Cliente(){
	system("cls");
	char opc = 'a';
	do{
		
	system("cls");
	printf(" ------------ GERENCIAMENTO DE CLIENTES ------------  ");
	printf("\nDIGITE P PARA CADASTRAR UM CLIENTE. ");
	printf("\nDIGITE A PARA ALTERAR UM CLIENTE. ");
	printf("\nDIGITE E PARA EXCLUIR UM CLIENTE. ");
	printf("\nDIGITE R PARA VERIFICAR UMA LISTA DOS CLIENTES CADASTRADOS. \n");
	printf("\nDIGITE V PARA VOLTAR Ã€ TELA INICIAL. \n");
		//printf("\nDIGITE P PARA CADASTRAR UM PRODUTO: ");		
		scanf("%c", &opc);
		if(tolower(opc) == 'p'){
			while(tolower(opc)=='p')
			{	
			    CadastroDeCliente();	  
			    
			    system("cls");
			    printf("Insira P para cadastrar um cliente novamente ou informe qualquer informação para sair\n");
			    scanf("%c", &opc);   
			}
		}	
		
		if(tolower(opc) == 'r'){
		    while(tolower(opc)=='r')
			{	
				ListarCadastroDeCliente(0);	  
			    getchar();
			    getchar();
			    
			    system("cls");
			    printf("Insira R verificar novamente a lista de clientes cadastrados ou informe qualquer informação para sair\n");//voltar ao menu inicial.\n");
			    scanf("%c", &opc);   
			}
		}
		if(tolower(opc) == 'e'){
			while(tolower(opc)=='e')
			{	
				ExcluirCadastroDeCliente();	  
			    
			    system("cls");
			    printf("Insira E verificar novamente a lista de clientes cadastrados para exclusao ou informe qualquer informação para sair\n");//voltar ao menu inicial.\n");
			    scanf("%c", &opc);            
			}
		}
		if (tolower(opc)=='x'){
		
		}
		if (tolower(opc)=='a'){
			while(tolower(opc)=='a')
			{	
				AlterarCliente();
				printf("Insira A verificar novamente a lista de clientes cadastrados para alteração ou informe qualquer informação para sair\n");//voltar ao menu inicial.\n");
				scanf("%c", &opc);
			}
		}
		
	}while(tolower(opc) != 'v');
}

//--------------------------------------
//------ CLIENTE  ----------------------

void ImprimirDadosDoCliente(dados_cliente C){
	int i;
	//Verifica o tamanho da string, pora ajustar na exibição, nomes embaixo de nomes e valores embaixo de valores/
	if(strlen(C.nome)<TAMANHONOMECLIENTE)
	{
    //Como o tamanho máximo é 30, ele calcula o tamanho da string, e subtrai de 30 para ver quanto espaÃ§o falta/				
		int diflen = TAMANHONOMECLIENTE - strlen(C.nome);
    //ele soma os espaÃ§os necessários na string do nome para alinhar com o valor/				
		for(i=0; i<diflen;i++){
			strcpy(C.nome, strcat(C.nome, "."));
		}
	}
	printf("\nCodigo: %i | Nome : %s | Telefone: %s | CPF: %s", C.cod, C.nome, C.tel,C.cpf);		
}

dados_cliente LeituraDoClienteNoArquivo(FILE *farq){
	
	dados_cliente C;
	fscanf(farq,"%i;%30[^;];%20[^;];%16[^;];%i\n", &C.cod, C.nome, C.tel, C.cpf, &C.inativo);
	return C;
}

int EscreveOClienteNoArquivo(dados_cliente C, FILE *farq){
	
	int escreveuComSucesso;	
	
	escreveuComSucesso = fprintf(farq,"%i;%s;%s;%s;%i\n", C.cod, C.nome, C.tel, C.cpf, C.inativo);
	
	return escreveuComSucesso;
}

//Método de cadastro de Clientes
void CadastroDeCliente(){
	
	dados_cliente P;
	dados_cliente R;	
	FILE *farq;
	int result, novocod, j, a = 0;
	char c;
	memset(P.tel,'\0', TAMANHOTEL);
	memset(P.cpf,'\0', 16);
	P.inativo = 0;
	
	//LIMPA A APRESENTAçãO NO CMD E INICIA O CADASTRO DE CLIENTE
    //PEDE AS INFORMAÃ‡Ã•ES NECESSÃRIAS PARA O CADASTRO DE CLIENTE
	system("cls");
	printf("--------------------CADASTRO DE CLIENTES------------------");
	
	printf("\nDigite o nome do cliente: ");
	getchar();
	fgets(P.nome, TAMANHONOMECLIENTE, stdin);
	ToUpperString(P.nome);
	printf("\nDigite o telefone do cliente: ");
	
	//gerar máscara 
	do{
		if(a==0){
			P.tel[a]='(';
			printf("(");
			a++;
		}
        c=getch();
        if(isprint(c)){       //Analisa se o valor da variável c é imprimivel
			P.tel[a]=c;  		//Se for, armazena o caractere
	        printf("%c", c);
	        a++;	
           	
           	if(a==3){
           		printf(") ");
           		P.tel[a]=')';
           		a++;
		   	}
		   	if(strlen(P.tel)==9){
           		printf("-");
           		P.tel[a]='-';
           		a++;
		   	}
		   		
		   	if(strlen(P.tel)==14){
		   		c=13;
			}	
        }
        else if(c==8&&a){     //8 é o caractere BackSpace na tabela ASCII, && a analisa se a é diferente de 0
        	P.tel[a]='\0';
        	a--;
        	printf("\b \b");       //Apagando o caractere digitado
        }
    }while(c!=13);   
       
	printf("\nDigite o CPF: ");
	
	c = "";
	a=0;
	do{
        c=getch();
        if(isprint(c)){       //Analisa se o valor da variável c é imprimivel
        	P.cpf[a]=c;	
			a++;	 				//Se for, armazena o caractere
        	printf("%c", c);
           	if(a==3){
           		printf(".");
           		P.cpf[a]='.';
           		a++;
		   	}
		   	if(strlen(P.cpf)==7){
           		printf(".");
           		P.cpf[a]='.';
           		a++;
		   	}
		   	if(strlen(P.cpf)==11){
           		printf("-");
           		P.cpf[a]='-';
           		a++;
		   	}	
		   	if(strlen(P.cpf)==14){
		   		c=13;
			}
           }
           else if(c==8&&a){     //8 é o caractere BackSpace na tabela ASCII, && a analisa se a é diferente de 0
           P.cpf[a]='\0';
           a--;
           printf("\b \b");       //Apagando o caractere digitado
           }
    }while(c!=13);
	
	//REMOVE A QUEBRA DE LINHA DO FGETS
	P.nome[strcspn(P.nome, "\n")] = 0;
	P.tel[strcspn(P.tel, "\n")] = 0;
	P.cpf[strcspn(P.cpf, "\n")] = 0;

	//INICIA A GRAVAçãO DOS DADOS DO PRODUTO NO ARQUIVO	
	
	//Verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADASTROCLIENTE,"a")) == NULL)
	{
		printf("Houve um inconveniente ao realizar o cadastro do cliente. Verifique sua conexÃ£o com o Computador principal e inicie o cadastro do produto novamente.");               
    }
    else
    {
    	P.cod = GeraCod("CodCliente.txt");
    	//Imprimi os dados no arquivo
		result = EscreveOClienteNoArquivo(P, farq);
		//Valida se conseguiu imprimir os dados no aquivos
		if (result != EOF && result > 1)
		{
			printf("\nO cliente cadastrado foi cadastrado com sucesso.\n");
		}
		else
		{
			printf("\nHouve um inconveniente na execução do cadastro do cliente.\n");
		}	
	}
	fclose(farq);
	
	//LEITURA DO ARQUIVO E CAPTURA DA INFORMAçãO DA ULTIMA LINHA
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADASTROCLIENTE,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do cliente cadastrado. Verifique sua conexÃ£o com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R = LeituraDoClienteNoArquivo(farq);
		}
				
		//imprimi os dados da ultima linha do arquivo
		printf("\n----------Dados do Cliente----------");
		ImprimirDadosDoCliente(R);
	}
    fclose(farq);
    
	printf("\n");
	system("pause");	
}

void ListarCadastroDeCliente(int mostraInativo){
	
	dados_cliente R[100];	
	FILE *farq;
	int result;
	int i = 0, j= 0;
	
	//LIMPA A APRESENTAçãO NO CMD E INICIA O CADASRO DE CLIENTE
    system("cls");
	printf("--------------------CLIENTES CADASTRADOS------------------");

	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADASTROCLIENTE,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do cliente cadastrado. Verifique sua conexÃ£o com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R[i] = LeituraDoClienteNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    //imprimi os dados da ultima linha do arquivo
	printf("\nDados dos Clientes Cadastrados:");
		
	if (mostraInativo == 0)
	{	
		for (j = 0; j < i; j++)
		{	
			if (R[j].inativo == 0)
			{
				ImprimirDadosDoCliente(R[j]);	
			}			
		}
	}
	else	
	{	
		for (j = 0; j < i; j++)
		{	
			ImprimirDadosDoCliente(R[j]);				
		}
	}
	printf("\n");	
}

void ExcluirCadastroDeCliente(){
	
	dados_cliente R[100];	
	FILE *farq;
	int codClienteExcluir;
	int result;
	int i = 0, j= 0;
	
	//LIMPA A APRESENTAçãO NO CMD E INICIA O CADASRO DE PRODUTO
    system("cls");
	printf("--------------------EXCLUSÃƒO DE CLIENTES CADASTRADOS------------------");
	
	ListarCadastroDeCliente(0);
	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADASTROCLIENTE,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do cliente cadastrado. Verifique sua conexÃ£o com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha
		while(result == feof(farq))
		{			
			R[i] = LeituraDoClienteNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    printf("\nInforme o código do cliente que deseja excluir:\n");
	scanf("%i", &codClienteExcluir);

	for (j =0; j < i; j++)
	{
		
		if (R[j].cod == codClienteExcluir)
		{
		
			printf("teste %i", j);
			
			break;
			
		}
	}
	//imprimi os dados da ultima linha do arquivo
	char simOuNao;
		
	printf("\n Deseja realmente excluir o Cliente? (S/N) Codigo: %i Nome : %s Telefone: %s  CPF: %s\n", R[j].cod, R[j].nome, R[j].tel, R[j].cpf);	
	getchar();
	
	simOuNao = getchar();
	
	if (tolower(simOuNao) == 's')
	{
		int k = 0;
		R[j].inativo = 1;
		
		farq = fopen(NOMEARQUIVOCADASTROCLIENTE,"w");
	
		while(k < i)
		{			
			EscreveOClienteNoArquivo(R[k], farq);
			k++;
		}
		fclose(farq);
		printf("\nCliente excluido com sucesso!\n");
	}
	
	system("pause");	
}

void AlterarCliente(){
	
	dados_cliente R[100];	
	FILE *farq;
	int codClienteAlt;
	int result;
	int i = 0, j= 0, a = 0, opc;
	char c;
	
	//LIMPA A APRESENTAçãO NO CMD E INICIA O CADASRO DE PRODUTO
    system("cls");
	printf("--------------------ALTERACAO DE CLIENTES CADASTRADOS------------------");
	
	ListarCadastroDeCliente(0);	
	
	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADASTROCLIENTE,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do cliente cadastrado. Verifique sua conexÃ£o com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha
		while(result == feof(farq))
		{			
			R[i] = LeituraDoClienteNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    printf("\nInforme o código do cliente que deseja Alterar:\n");
	scanf("%i", &codClienteAlt);
	
	//encontrar a linha do item
	for (j =0; j < i; j++)
	{
		
		if (R[j].cod == codClienteAlt)
		{			
			break;			
		}
	}
	//imprimi os dados da ultima linha do arquivo
	char simOuNao;
			
	printf("\n Deseja realmente alterar o Cliente? (S/N) Codigo: %i Nome : %s Telefone: %s CPF: %s\n", R[j].cod, R[j].nome, R[j].tel, R[i].cpf);	
	getchar();
	
	simOuNao = getchar();
	
	if (tolower(simOuNao) == 's')
	{
	printf("\nPara alterar:");
	printf("\nNome  - 1");
	printf("\nTelefone - 2\n");
	printf("\nCPF - 3 ");
	scanf("%i", &opc);
		int k = 0;
		int novoCod;
		
		//alterando o campo escolhido pelo usuário
		if(opc == 1){
			
			printf("Insira o novo nome: ");
			getchar();
			fgets(R[j].nome, TAMANHONOMECLIENTE, stdin);
			//REMOVE A QUEBRA DE LINHA DO FGETS
			R[j].nome[strcspn(R[j].nome, "\n")] = 0;
			
		}else{
			if(opc == 2){
			printf("Insira o novo telefone: ");
			do{
				if(a==0){
					R[j].tel[a]='(';
					printf("(");
					a++;
				}
           		c=getch();
           		if(isprint(c)){       //Analisa se o valor da variável c é imprimivel
	           		R[j].tel[a]=c;  		//Se for, armazena o caractere
	           		printf("%c", c);
	           		a++;	
	           		if(a==3){
	           			printf(") ");
	           			R[j].tel[a]=')';
	           			a++;
			   		}
			   		if(strlen(R[j].tel)==9){
	           			printf("-");
	           			R[j].tel[a]='-';
	           			a++;
			   		}
			   		if(strlen(R[j].tel)==14){
			   			c=13;
					}
           		}
           		else if(c==8&&a){     //8 é o caractere BackSpace na tabela ASCII, && a analisa se a é diferente de 0
           			R[j].tel[a]='\0';
           			a--;
           			printf("\b \b");       //Apagando o caractere digitado
           		}
			}while(c!=13);
			
			//REMOVE A QUEBRA DE LINHA DO FGETS
			R[j].tel[strcspn(R[j].tel, "\n")] = 0;
			
			}else{
				printf("Insira o novo CPF: ");
				c="";
				a=0;
				do{
			        c=getch();
			        if(isprint(c)){       //Analisa se o valor da variável c é imprimivel
			        	R[j].cpf[a]=c;	
						a++;	 				//Se for, armazena o caractere
			        	printf("%c", c);
			           	if(a==3){
			           		printf(".");
			           		R[j].cpf[a]='.';
			           		a++;
					   	}
					   	if(strlen(R[j].cpf)==7){
			           		printf(".");
			           		R[j].cpf[a]='.';
			           		a++;
					   	}
					   	if(strlen(R[j].cpf)==11){
			           		printf("-");
			           		R[j].cpf[a]='-';
			           		a++;
					   	}	
					   	if(strlen(R[j].cpf)==14){
					   		c=13;
						}
			        }
			        else if(c==8&&a){     //8 é o caractere BackSpace na tabela ASCII, && a analisa se a é diferente de 0
			        	R[j].cpf[a]='\0';
			        	a--;
			        	printf("\b \b");       //Apagando o caractere digitado
			        }
    			}while(c!=13);
    			
    			R[j].cpf[strcspn(R[j].cpf, "\n")] = 0;
			}
		}
		
		farq = fopen(NOMEARQUIVOCADASTROCLIENTE,"w");
	
		while(k < i)
		{			
			EscreveOClienteNoArquivo(R[k], farq);
			k++;
		}
		fclose(farq);
		printf("\nCliente alterado com sucesso!\n");
		printf("Dados do Cliente alterado: \n");
		printf("Codigo: %i Nome : %s Telefone: %s CPF: %s\n", R[j].cod, R[j].nome, R[j].tel, R[j].cpf);
	}
	
	system("pause");
 
}
