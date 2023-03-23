#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include "Venda.h"
#include "Cliente.h"
#include "CategoriaProduto.h"
#include "Produto.h"
#include "Usuario.h"

#define NOMEARQUIVOCADVENDA "CadastroVenda.txt"
#define NOMEARQUIVOCADITEMVENDA "CadastroItemVenda.txt"
#define NOMEARQUIVOCADASTROCLIENTE "CadastrosDeCliente.txt"
#define NOMEARQUIVOCAT "CategoriaDeProduto.txt"
#define NOMEARQUIVOPRODUTO "CadastrosDeProduto.txt"
#define NOMEARQUIVOUSUARIO "CadastrosDeUsuario.txt"

void Relatorio(){
	char opc;
	do{
		
		system("cls");
		printf(" ------------  GERENCIAMENTO DE RELATÓRIOS ------------  ");
		printf("\nDIGITE C PARA VISUALIZAR O RELATÓRIO DE VENDAS POR CLIENTE.");
		printf("\nDIGITE P PARA VISUALIZAR O RELATÓRIO DE VENDAS POR PRODUTO.");
		printf("\nDIGITE U PARA VISUALIZAR O RELATÓRIO DE VENDAS POR USUÁRIO.");
		printf("\nDIGITE A PARA VISUALIZAR O RELATÓRIO DE LISTAGEM DE CLIENTE.");
		printf("\nDIGITE S PARA VISUALIZAR O RELATÓRIO DE LISTAGEM DE PRODUTO.");
		printf("\nDIGITE D PARA VISUALIZAR O RELATÓRIO DE LISTAGEM DE CATEGORIA DE PRODUTO.");
		printf("\nDIGITE V PARA VOLTAR À TELA INICIAL. \n");
			
		scanf("%c", &opc);
		
		if(tolower(opc) == 'c'){
	    	while(tolower(opc)=='c')
			{	
	            RelatorioPorCliente();	  
	                
	            system("cls");
	            printf("Insira C para visualizar o relatório novamentee ou informe qualquer informação para sair\n");
	            scanf("%c", &opc);            
        	}
		}	
		
		if(tolower(opc) == 'p'){
            while(tolower(opc)=='p')
			{	
	            RelatorioPorProduto();	  
	                
	            system("cls");
	            printf("Insira P para visualizar o relatório novamentee ou informe qualquer informação para sair\n");
	            scanf("%c", &opc); 
            }
		}
		
		if(tolower(opc) == 'u'){
			while(tolower(opc)=='u')
			{	
	            RelatorioPorVendedor();	  
	                
	            system("cls");
	            printf("Insira U para visualizar o relatório novamentee ou informe qualquer informação para sair\n");
	            scanf("%c", &opc); 
            }
		}
		if(tolower(opc) == 'a'){
	    	while(tolower(opc)=='a')
			{	
	            ListarCadastroDeCliente(0);	  
	            getchar();
				getchar();
				    
	            system("cls");
	            printf("Insira A para visualizar o relatório novamentee ou informe qualquer informação para sair\n");
	            scanf("%c", &opc);            
        	}
		}	
		
		if(tolower(opc) == 's'){
            while(tolower(opc)=='s')
			{	
	            system("cls");
				ListarCategoriaDeProduto(0);	  
	            getchar();
				getchar();
				    
	            system("cls");
	            printf("Insira S para visualizar o relatório novamentee ou informe qualquer informação para sair\n");
	            scanf("%c", &opc); 
            }
		}
		
		if(tolower(opc) == 'd'){
			while(tolower(opc)=='d')
			{	
	            ListarCadastroDeUsuario(0);	  
	            getchar();
				getchar();
				    
	            system("cls");
	            printf("Insira D para visualizar o relatório novamentee ou informe qualquer informação para sair\n");
	            scanf("%c", &opc); 
            }
		}
	} while(tolower(opc) != 'v');
    system("cls");
}

void RelatorioPorCliente(){
	dados_cliente   C[100];
	dados_venda V;
	
	FILE *farq;
	int result;
	int j, codCliente;
	int k = 0, i = 0, Localizado = 0;
	
	printf("--------------------RELATÓRIO DE VENDAS POR CLIENTE------------------");

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
			C[i] = LeituraDoClienteNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    	
	while (Localizado == 0) {
    	printf("\nInforme o código do cliente para gerar o relatório:\n");
        scanf("%i", &codCliente);
        
        //encontrar a linha do item
        for (j =0; j < i; j++)
        {	
            if (C[j].cod == codCliente)
            {		
                Localizado = 1;
                break;	
            }
        }

        if(Localizado == 0)
        {
            printf("Cliente não localizado.\n");
        }
    }
	
	printf("\nDados do cliente selecionado:\n");
    ImprimirDadosDoCliente(C[j]);	

	printf("\nDeseja utilizar o cliente selecionado? (S/N)\n");
	getchar();
	
	char simOuNao; 
	simOuNao = getchar();	
	if (tolower(simOuNao) == 'n')
    {
        printf("Processo de geração de relatório Cancelado!\n");
        getchar();
        getchar();
        exit(1);
    } 
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADVENDA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			V = LeituraDaVendaNoArquivo(farq);
		}				
	}
    fclose(farq);
	
	system("cls");
	printf("-------------------- RELATÓRIO DE VENDAS POR CLIENTE ------------------");
	
	ListarCadastroDeVendaPorCliente(codCliente);

	printf("\n");	
    getchar();
    getchar();
}

void RelatorioPorProduto(){
	dados_produto   C[100];
	dados_venda V;
	
	FILE *farq;
	int result;
	int j, codProduto;
	int k = 0, i = 0, Localizado = 0;
	
	printf("--------------------RELATÓRIO DE VENDAS POR PRODUTO------------------");

	ListarCadastroDeProduto(0);
	
	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOPRODUTO,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do cliente cadastrado. Verifique sua conexÃ£o com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha
		while(result == feof(farq))
		{			
			C[i] = LeituraDoProdutoNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    	
	while (Localizado == 0) {
    	printf("\nInforme o código do produto para gerar o relatório:\n");
        scanf("%i", &codProduto);
        
        //encontrar a linha do item
        for (j =0; j < i; j++)
        {	
            if (C[j].cod == codProduto)
            {		
                Localizado = 1;
                break;	
            }
        }

        if(Localizado == 0)
        {
            printf("Produto não localizado.\n");
        }
    }
	
	printf("\nDados do produto selecionado:\n");
    ImprimirDadosDoProduto(C[j]);	

	printf("\nDeseja utilizar o produto selecionado? (S/N)\n");
	getchar();
	
	char simOuNao; 
	simOuNao = getchar();	
	if (tolower(simOuNao) == 'n')
    {
        printf("Processo de geração de relatório Cancelado!\n");
        getchar();
        getchar();
        exit(1);
    } 
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADVENDA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			V = LeituraDaVendaNoArquivo(farq);
		}				
	}
    fclose(farq);
	
	system("cls");
	printf("-------------------- RELATÓRIO DE VENDAS POR PRODUTO ------------------");
	
	ListarCadastroDeItemDaVendaPorProduto(codProduto);

	printf("\n");	
    getchar();
    getchar();
}

void RelatorioPorVendedor(){
	dados_usuario   C[100];
	dados_venda V;
	
	FILE *farq;
	int result;
	int j, codVendedor;
	int k = 0, i = 0, Localizado = 0;
	
	printf("--------------------RELATÓRIO DE VENDAS POR VENDEDOR------------------");

	ListarCadastroDeUsuario(0);
	
	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOUSUARIO,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do cliente cadastrado. Verifique sua conexÃ£o com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha
		while(result == feof(farq))
		{			
			C[i] = LeituraDoUsuarioNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    	
	while (Localizado == 0) {
    	printf("\nInforme o código do produto para gerar o relatório:\n");
        scanf("%i", &codVendedor);
        
        //encontrar a linha do item
        for (j =0; j < i; j++)
        {	
            if (C[j].cod == codVendedor)
            {		
                Localizado = 1;
                break;	
            }
        }

        if(Localizado == 0)
        {
            printf("Vendedor não localizado.\n");
        }
    }
	
	printf("\nDados do vendedor selecionado:\n");
    ImprimirDadosDoUsuario(C[j]);	

	printf("\nDeseja utilizar o vendedor selecionado? (S/N)\n");
	getchar();
	
	char simOuNao; 
	simOuNao = getchar();	
	if (tolower(simOuNao) == 'n')
    {
        printf("Processo de geração de relatório Cancelado!\n");
        getchar();
        getchar();
        exit(1);
    } 
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADVENDA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			V = LeituraDaVendaNoArquivo(farq);
		}				
	}
    fclose(farq);
	
	system("cls");
	printf("-------------------- RELATÓRIO DE VENDAS POR VENDEDOR ------------------");
	
	ListarCadastroDeVendaPorVendedor(codVendedor);

	printf("\n");	
    getchar();
    getchar();
}


