#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include "Venda.h"
#include "Cliente.h"
#include "CategoriaProduto.h"
#include "Produto.h"
#include "Usuario.h"

#define DESCRICAOVENDA 30
#define NOMEARQUIVOCADVENDA "CadastroVenda.txt"
#define NOMEARQUIVOCADITEMVENDA "CadastroItemVenda.txt"
#define NOMEARQUIVOCADASTROCLIENTE "CadastrosDeCliente.txt"
#define NOMEARQUIVOCAT "CategoriaDeProduto.txt"
#define NOMEARQUIVOPRODUTO "CadastrosDeProduto.txt"

void ImprimirDadosDaVenda(dados_venda T){
	
	int i;
	//Verifica o tamanho da string, pora ajustar na exibiçao, nomes embaixo de nomes e valores embaixo de valores/
	if(strlen(T.nomeVendedor)<TAMANHONOMEVENDEDOR)
	{
    	//Como o tamanho máximo TAMANHONOME, ele calcula o tamanho da string, e subtrai de TAMANHONOME para ver quanto espaço falta/				
		int diflen = TAMANHONOMEVENDEDOR - strlen(T.nomeVendedor);
    	//ele soma os espaços necessários na string do nome para alinhar com o valor/				
		for(i=0; i<diflen;i++){
			strcpy(T.nomeVendedor, strcat(T.nomeVendedor, "."));
		}
	}
	
	if(strlen(T.descricao)<DESCRICAOVENDA)
	{
    	//Como o tamanho máximo TAMANHONOME, ele calcula o tamanho da string, e subtrai de TAMANHONOME para ver quanto espaço falta/				
		int diflen = DESCRICAOVENDA - strlen(T.descricao);
    	//ele soma os espaços necessários na string do nome para alinhar com o valor/				
		for(i=0; i<diflen;i++){
			strcpy(T.descricao, strcat(T.descricao, "."));
		}
	}
	
	if(strlen(T.nomeCliente)<TAMANHONOMECLIENTE)
	{
		int diflen = TAMANHONOMECLIENTE - strlen(T.nomeCliente);
		for(i=0; i<diflen;i++){
			strcpy(T.nomeCliente, strcat(T.nomeCliente, "."));
		}
	}
	
	printf("\nCodigo da Venda: %i | Cliente: %s | Descrição : %s | Valor Total da Venda: R$ %.2f ", T.codVenda, T.nomeCliente, T.descricao, T.valorVenda);		
}

void ImprimirDadosItemDaVenda(dados_itemVenda T){
	
	int i;
	//Verifica o tamanho da string, pora ajustar na exibiçao, nomes embaixo de nomes e valores embaixo de valores/
	if(strlen(T.nomeProduto)<TAMANHONOME)
	{
    	//Como o tamanho máximo TAMANHONOME, ele calcula o tamanho da string, e subtrai de TAMANHONOME para ver quanto espaço falta/				
		int diflen = TAMANHONOME - strlen(T.nomeProduto);
    	//ele soma os espaços necessários na string do nome para alinhar com o valor/				
		for(i=0; i<diflen;i++){
			strcpy(T.nomeProduto, strcat(T.nomeProduto, "."));
		}
	}
	
	printf("\nCodigo da Venda: %i | Nome Produto: %s | Quantidade : %i | Valor Unitário: R$ %.2f | Valor Total: R$ %.2f ", T.codVenda, T.nomeProduto, T.quantidadeVenda, T.valorUnitario, T.valorTotal);		
}

dados_venda LeituraDaVendaNoArquivo(FILE *farq){
	
	dados_venda T;
	fscanf(farq,"%i;%30[^;];%i;%30[^;];%f;%i;%30[^;];%i\n",  &T.codVenda, T.descricao, &T.codCliente, T.nomeCliente, &T.valorVenda, &T.codVendedor, T.nomeVendedor, &T.inativo);
	return T;
}

dados_itemVenda LeituraDoItemVendaNoArquivo(FILE *farq){
	
	dados_itemVenda T;
	fscanf(farq,"%i;%i;%100[^;];%i;%30[^;];%i;%f;%f\n",  &T.codVenda, &T.codProduto, T.nomeProduto, &T.codCategoria, T.nomeCategoriaDoProduto, &T.quantidadeVenda, &T.valorUnitario, &T.valorTotal);
	return T;
}

int EscreveAVendaNoArquivo(dados_venda T, FILE *farq){
	
	int escreveuComSucesso;	
	escreveuComSucesso = fprintf(farq,"%i;%s;%i;%s;%.2f;%i;%s;%i\n",  T.codVenda, T.descricao, T.codCliente, T.nomeCliente, T.valorVenda, T.codVendedor, T.nomeVendedor, T.inativo);
	
	return escreveuComSucesso;
}

int EscreveOItemVendaNoArquivo(dados_itemVenda T, FILE *farq){
	
	int escreveuComSucesso;	
	escreveuComSucesso = fprintf(farq,"%i;%i;%s;%i;%s;%i;%.2f;%.2f\n",  T.codVenda, T.codProduto, T.nomeProduto, T.codCategoria, T.nomeCategoriaDoProduto, T.quantidadeVenda, T.valorUnitario, T.valorTotal);
	
	return escreveuComSucesso;
}

void CadastroDeVenda(){
	
	dados_cliente   C[100];
	dados_categoria CP[100];
	dados_produto   P[100];
	dados_venda V;
	dados_venda V2;
	dados_itemVenda IV[100];
	dados_usuario U;
	//
	U = LeituraDoUsuarioOnlineNoArquivo();
	V.codVendedor = U.cod;
	strcpy(V.nomeVendedor, U.username);
	V.valorVenda = 0;
	//---
	int codCliente;
	int Localizado = 0;
	int codCategoria;
	int codProduto;
	int qtde;
	//---
		
	FILE *farq;
	int result;
	int j;
	int k = 0, i = 0;
	
	//LIMPA A APRESENTAÇÃO NO CMD E INICIA O CADASTRO DE PRODUTO
    //PEDE AS INFORMAÇOES NECESSÁRIAS PARA O CADASTRO DE PRODUTO
	system("cls");
	printf("--------------------CADASTRO DE VENDA------------------");
	
	
	// 1 - CLIENTE - INICIO --------------------------------------------------------------
	//------------------------------------------------------------------------------------
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
			fscanf(farq,"%i;%30[^;];%20[^;];%20[^;];%i\n", &C[i].cod, C[i].nome, C[i].tel, C[i].cpf, &C[i].inativo);
			i++;
		}
	}
    fclose(farq);
    	
	while (Localizado == 0) {
    	printf("\nInforme o código do cliente para iniciar a venda:\n");
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
        printf("Processo de Venda Cancelado!\n");
        getchar();
        getchar();
        exit(1);
    } 
    
    V.codCliente = C[j].cod;
    strcpy(V.nomeCliente, C[j].nome);
    
    printf("\nInforme a descrição da venda: ");
    getchar();
	fgets(V.descricao, TAMANHONOME, stdin);
    V.descricao[strcspn(V.descricao, "\n")] = 0;
    
    // 1 - CLIENTE - FIM -----------------------------------------------------------------
	//------------------------------------------------------------------------------------
    
    int VendaFinalizada = 0;
    while (VendaFinalizada == 0) {
	   	// 2 - CATEGORIA - INICIO ------------------------------------------------------------
		//------------------------------------------------------------------------------------
		system("cls");
		ListarCategoriaDeProduto(0);
		
		//Le e verifica se conseguiu abrir o arquivo corretamente
		i = 0;
		if((farq = fopen(NOMEARQUIVOCAT,"r")) == NULL)
		{
			printf("Houve um inconveniente ao visualizar os dados da categoria de produto cadastrado. Verifique sua conexão com o Computador principal.");               
	    }
	    else
	    {
	    	result = 0;
			//ve o aquivo atÃ© chegar na ultima linha
			while(result == feof(farq))
			{			
				CP[i] = LeituraDaCategoriaNoArquivo(farq);
				i++;
			}
		}
	    fclose(farq);
	    
		Localizado = 0;
	    while (Localizado == 0) {
	        printf("\nInforme o código da categoria de produto que deseja escolher:\n");
	        scanf("%i", &codCategoria);
	        
	        //encontrar a linha do item
	        for (j =0; j < i; j++)
	        {	
	            if (CP[j].cod == codCategoria)
	            {		
	                Localizado = 1;
	                break;	
	            }
	        }
	
	        if(Localizado == 0)
	        {
	            printf("Categoria de produto não localizada.\n");
	        }
	    }
		
		printf("\nDados da categoria de produto selecionado:\n");
	    ImprimirDadosDaCategoriaDoProduto(CP[j]);	
	
		printf("\nDeseja verificar a lista de produtos da categoria selecionada? (S/N)\n");
		getchar();
		
		simOuNao = getchar();
		if (tolower(simOuNao) == 'n')
	    {
	        printf("Processo de Venda Cancelado!\n");
	        getchar();
	        getchar();
	        exit(1);
	    } 
	    
	    IV[k].codCategoria = codCategoria;
    	strcpy(IV[k].nomeCategoriaDoProduto, CP[j].nome);
	    
	    // 2 - CATEGORIA - FIM -------------------------------------------------------------
		//----------------------------------------------------------------------------------
		
		// 3 - PRODUTO - INICIO ------------------------------------------------------------
		//----------------------------------------------------------------------------------
	    
	 	ListarCadastroDeProdutoPorCategoria(codCategoria);
		
		//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
		
		//Le e verifica se conseguiu abrir o arquivo corretamente
		if((farq = fopen(NOMEARQUIVOPRODUTO,"r")) == NULL)
		{
			printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
	    }
	    else
	    {
	    	result = 0;
			//ve o aquivo atÃ© chegar na ultima linha
			while(result == feof(farq))
			{			
				P[i] = LeituraDoProdutoNoArquivo(farq);
				i++;
			}
		}
	    fclose(farq);
	    
	    Localizado = 0;
	    while (Localizado == 0) {
	        printf("\nInforme o código do produto:\n");
	        scanf("%i", &codProduto);
	        
	        //encontrar a linha do item
	        for (j =0; j < i; j++)
	        {	
	            if (P[j].cod == codProduto)
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
	    ImprimirDadosDoProduto(P[j]);	
	
		printf("\nDeseja realmente vender este produto? (S/N)\n");
		getchar();
		
		simOuNao = getchar();
		
		if (tolower(simOuNao) == 'n')
	    {
	        printf("Processo de Venda Cancelado!\n");
	        getchar();
	        getchar();
	        exit(1);
	    } 
	    
	    printf("\nInforme a quantidade a ser vendida deste produto:\n");
		scanf("%i", &IV[k].quantidadeVenda);
		
		IV[k].codProduto = codProduto;
    	strcpy(IV[k].nomeProduto, P[j].nome);
    	IV[k].valorUnitario = P[j].valor;
    	IV[k].valorTotal =  IV[k].quantidadeVenda * IV[k].valorUnitario;
    	V.valorVenda = V.valorVenda + IV[k].valorTotal;
		
		printf("\nItem adicionado a venda com sucesso.\n");
		printf("\nDeseja adicionar mais itens para a venda? (S/N) .\n");
		getchar();
		
		simOuNao = getchar();
		
		k++;
		if (tolower(simOuNao) == 'n')
	    {
	        VendaFinalizada = 1;
			printf("Processo de Venda Finalizado!\n");
	        getchar();
	        getchar();
	    } 
	}
	
	// PRODUTO- FIM
	
	// IMPRESSÃO
	
	//INICIA A GRAVAÇÃO DA VENDA NO ARQUIVO	
	
	V.codVenda = GeraCod("CodVenda.txt");
	
	//Verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADVENDA,"a")) == NULL)
	{
		printf("Houve um inconveniente ao realizar o cadastro do produto. Verifique sua conexão com o Computador principal e inicie o cadastro do produto novamente.");               
    }
    else
    {
    	//Imprimi os dados no arquivo
		result = EscreveAVendaNoArquivo(V, farq);
		//Valida se conseguiu imprimir os dados no aquivo
		if (result != EOF && result > 1)
		{
			//printf("\nA venda foi realizada com sucesso.\n");
		}
		else
		{
			printf("\nHouve um inconveniente na execução do cadastro do cabeçalho da venda.\n");
		}	
	}
	fclose(farq);
	
	//LEITURA DO ARQUIVO E CAPTURA DA INFORMAÃ‡ÃƒO DA ULTIMA LINHA
	
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
			V2 = LeituraDaVendaNoArquivo(farq);
		}				
	}
    fclose(farq);

	// ITEM VENDA

	//Verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADITEMVENDA,"a")) == NULL)
	{
		printf("Houve um inconveniente ao realizar o cadastro do produto. Verifique sua conexão com o Computador principal e inicie o cadastro do produto novamente.");               
    }
    else
    {
    	for (i = 0; i< k; i++)
    	{		
			IV[i].codVenda = V.codVenda;
			//Imprimi os dados no arquivo
			result = EscreveOItemVendaNoArquivo(IV[i], farq);
			//Valida se conseguiu imprimir os dados no aquivo
			if (result != EOF && result > 1)
			{
				//printf("\nA venda foi realizada com sucesso.\n");
			}
			else
			{
				printf("\nHouve um inconveniente na execução do cadastro do cabeçalho da venda.\n");
			}
		}
	}
	fclose(farq);
	
	system("cls");
	printf("--------------------DADOS DA VENDA REALZIADA------------------");
	
	ImprimirDadosDaVenda(V2);
	ListarCadastroDeItemDaVenda(V.codVenda);
	
	printf("\n");	
    getchar();
}

void ListarCadastroDeVenda(int mostraInativo){
	
	dados_venda R[100];	
	FILE *farq;
	int result;
	int i = 0, j= 0;
	
	//LIMPA A APRESENTAÃ‡ÃƒO NO CMD E INICIA O CADASRO DE PRODUTO
    system("cls");
	printf("--------------------VENDAS CADASTRADAS------------------");

	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADVENDA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo atÃ© chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R[i] = LeituraDaVendaNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    //imprimi os dados da ultima linha do arquivo
	printf("\nDados das Vendas Cadastradas:");
	
	if (mostraInativo == 0)
	{	
		for (j = 0; j < i; j++)
		{	
			if (R[j].inativo == 0)
			{
				ImprimirDadosDaVenda(R[j]);	
			}			
		}
	}
	else	
	{	
		for (j = 0; j < i; j++)
		{	
			ImprimirDadosDaVenda(R[j]);				
		}
	}
	
	printf("\n");
}

void ListarCadastroDeVendaPorCliente(int codCliente){
	
	dados_venda R[100];	
	FILE *farq;
	int result;
	int i = 0, j= 0;
	
	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADVENDA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo atÃ© chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R[i] = LeituraDaVendaNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);

	
	for (j = 0; j < i; j++)
	{	
		if (R[j].inativo == 0 && R[j].codCliente == codCliente)
		{
			ImprimirDadosDaVenda(R[j]);	
		}			
	}
	
	printf("\n");
}

void ListarCadastroDeVendaPorVendedor(int codVendedor){
	
	dados_venda R[100];	
	FILE *farq;
	int result;
	int i = 0, j= 0;
	
	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADVENDA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo atÃ© chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R[i] = LeituraDaVendaNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);

	
	for (j = 0; j < i; j++)
	{	
		if (R[j].inativo == 0 && R[j].codVendedor == codVendedor)
		{
			ImprimirDadosDaVenda(R[j]);	
		}			
	}
	
	printf("\n");
}

void ListarCadastroDeItemDaVenda(int codigoVenda){
	
	dados_itemVenda R[500];	
	FILE *farq;
	int result;
	int i = 0, j= 0;

	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADITEMVENDA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo atÃ© chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R[i] = LeituraDoItemVendaNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    //imprimi os dados da ultima linha do arquivo
	printf("\nDados dos Itens da Venda Realizada:");
		
	for (j = 0; j < i; j++)
	{	
		if (R[j].codVenda == codigoVenda)
		{
			ImprimirDadosItemDaVenda(R[j]);	
		}			
	}
	
	printf("\n");
}

void ListarCadastroDeItemDaVendaPorProduto(int codProduto){
	
	dados_itemVenda R[500];	
	FILE *farq;
	int result;
	int i = 0, j= 0;

	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCADITEMVENDA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo atÃ© chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R[i] = LeituraDoItemVendaNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    //imprimi os dados da ultima linha do arquivo
	printf("\nDados dos Itens da Venda Realizada:");
		
	for (j = 0; j < i; j++)
	{	
		if (R[j].codProduto == codProduto)
		{
			ImprimirDadosItemDaVenda(R[j]);	
		}			
	}
	
	printf("\n");
}

void Venda(){
	dados_usuario U;
	U = LeituraDoUsuarioOnlineNoArquivo();			

	system("cls");
	char opc;
	do{
		
		system("cls");
		printf(" ------------  GERENCIAMENTO DE VENDAS ------------  ");
		printf("\nDIGITE V PARA REALIZAR UMA VENDA. ");
		printf("\nDIGITE R PARA VERIFICAR UMA LISTA DAS VENDAS REALIZADAS. \n");
		printf("\nDIGITE X PARA VOLTAR À TELA INICIAL. \n");
			
		scanf("%c", &opc);
		
		if(tolower(opc) == 'v'){
	    	while(tolower(opc)=='v')
			{	
	            CadastroDeVenda();	  
	                
	            system("cls");
	            printf("Insira V para realizar uma nova venda ou informe qualquer informação para sair\n");
	            scanf("%c", &opc);            
        	}
		}	
		if(tolower(opc) == 'r'){
            while(tolower(opc)=='r')
			{	  	
				system("cls");
				printf("--------------------VENDAS REALIZADAS------------------");
				ListarCadastroDeVendaPorVendedor(U.cod);	  
                getchar();
                getchar();
                
                system("cls");
                printf("Insira R verificar novamente o histórico de vendas ou informe qualquer informação para sair\n");//voltar ao menu inicial.\n");
                scanf("%c", &opc);
            }
		}
		
	} while(tolower(opc) != 'x');
    system("cls");
}
