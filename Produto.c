#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include "produto.h"
#include "CategoriaProduto.h"

#define NOMEARQUIVOPRODUTO "CadastrosDeProduto.txt"
#define NOMEARQUIVOCAT "CategoriaDeProduto.txt"

void ImprimirDadosDoProduto(dados_produto T){
	
	int i;
	//Verifica o tamanho da string, pora ajustar na exibiçao, nomes embaixo de nomes e valores embaixo de valores/
	if(strlen(T.nome)<TAMANHONOMEPRODUTO)
	{
    	//Como o tamanho máximo TAMANHONOME, ele calcula o tamanho da string, e subtrai de TAMANHONOME para ver quanto espaço falta/				
		int diflen = TAMANHONOMEPRODUTO - strlen(T.nome);
    	//ele soma os espaços necessários na string do nome para alinhar com o valor/				
		for(i=0; i<diflen;i++){
			strcpy(T.nome, strcat(T.nome, "."));
		}
	}
	printf("\nCodigo: %i | Nome : %s | Valor: R$ %.2f", T.cod, T.nome, T.valor);		
}

dados_produto LeituraDoProdutoNoArquivo(FILE *farq){
	
	dados_produto T;
	memset(T.nome,'\0', TAMANHONOMEPRODUTO);
	memset(T.nomeCategoriaDoProduto,'\0', TAMANHONOMECATEGORIA);
	
	fscanf(farq,"%i;%100[^;];%f;%i;%30[^;];%i\n",  &T.cod, T.nome, &T.valor, &T.codCategoria, T.nomeCategoriaDoProduto, &T.inativo);
	return T;
}

int EscreveOProdutoNoArquivo(dados_produto T, FILE *farq){
	
	int escreveuComSucesso;	
	
	escreveuComSucesso = fprintf(farq,"%i;%s;%.2f;%i;%s;%i\n", T.cod, T.nome, T.valor, T.codCategoria, T.nomeCategoriaDoProduto, T.inativo);
	
	return escreveuComSucesso;
}

void CadastroDeProduto(){
	
	dados_produto P;
	dados_produto R;
	dados_categoria CP[100];	
	FILE *farq;
	int result;
	int j, codCategoria;
	int i = 0, Localizado = 0;
	char simOuNao;
	
	//LIMPA A APRESENTAÇÃO NO CMD E INICIA O CADASTRO DE PRODUTO
    //PEDE AS INFORMAÇOES NECESSÁRIAS PARA O CADASTRO DE PRODUTO
	system("cls");
	printf("--------------------CADASTRO DE PRODUTO------------------");
	
	printf("\nDigite o nome do produto: ");
	getchar();
	fgets(P.nome, TAMANHONOMEPRODUTO, stdin);
	ToUpperString(P.nome);
	
	printf("\nDigite o valor do produto: ");
	scanf("%f", &P.valor);
	
	//REMOVE A QUEBRA DE LINHA DO FGETS
	P.nome[strcspn(P.nome, "\n")] = 0;
	P.inativo = 0;
	
	printf("\n");
	ListarCategoriaDeProduto(0);
		
	//Le e verifica se conseguiu abrir o arquivo corretamente
	
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
	
	printf("\nDeseja adicionar o produto a ser cadastrado na lista de produtos da categoria selecionada? (S/N)\n");
	getchar();
		
	simOuNao = getchar();
	if (tolower(simOuNao) == 'n')
	{
	    printf("Processo de Cadastro de Produto Cancelado!\n");
	    getchar();
	    getchar();
	    exit(0);
	} 
	    
	P.codCategoria = codCategoria;
    strcpy(P.nomeCategoriaDoProduto, CP[j].nome);
	
	P.cod = GeraCod("CodProduto.txt");

	//INICIA A GRAVAÃ‡ÃƒO DOS DADOS DO PRODUTO NO ARQUIVO	
	
	//Verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOPRODUTO,"a")) == NULL)
	{
		printf("Houve um inconveniente ao realizar o cadastro do produto. Verifique sua conexão com o Computador principal e inicie o cadastro do produto novamente.");               
    }
    else
    {
    	//Imprimi os dados no arquivo
		result = EscreveOProdutoNoArquivo(P, farq);
		//Valida se conseguiu imprimir os dados no aquivo
		if (result != EOF && result > 1)
		{
			printf("\nO produto cadastrado foi cadastrado com sucesso.\n");
		}
		else
		{
			printf("\nHouve um inconveniente na execução do cadastro do produto.\n");
		}	
	}
	fclose(farq);
	
	//LEITURA DO ARQUIVO E CAPTURA DA INFORMAÃ‡ÃƒO DA ULTIMA LINHA
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOPRODUTO,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R = LeituraDoProdutoNoArquivo(farq);
		}
				
		//imprimi os dados da ultima linha do arquivo
		printf("\n----------Dados do Produto Cadastrado----------");
		ImprimirDadosDoProduto(R);
	}
    fclose(farq);
	
	printf("\n");
	getchar();	
    getchar();
}

void ListarCadastroDeProduto(int mostraInativo){
	
	dados_produto R[100];	
	FILE *farq;
	int result;
	int i = 0, j= 0;
	
	//LIMPA A APRESENTAÃ‡ÃƒO NO CMD E INICIA O CADASRO DE PRODUTO
    system("cls");
	printf("--------------------PRODUTOS CADASTRADOS------------------");

	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOPRODUTO,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo atÃ© chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R[i] = LeituraDoProdutoNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    //imprimi os dados da ultima linha do arquivo
	printf("\nDados dos Produtos Cadastrados:");
	
	if (mostraInativo == 0)
	{	
		for (j = 0; j < i; j++)
		{	
			if (R[j].inativo == 0)
			{
				ImprimirDadosDoProduto(R[j]);	
			}			
		}
	}
	else	
	{	
		for (j = 0; j < i; j++)
		{	
			ImprimirDadosDoProduto(R[j]);				
		}
	}
	
	printf("\n");
}

void ListarCadastroDeProdutoPorCategoria(int codCategoria){
	
	dados_produto R[100];	
	FILE *farq;
	int result;
	int i = 0, j= 0;
	
	//LIMPA A APRESENTAÃ‡ÃƒO NO CMD E INICIA O CADASRO DE PRODUTO
    system("cls");
	printf("--------------------PRODUTOS CADASTRADOS------------------");

	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOPRODUTO,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo atÃ© chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R[i] = LeituraDoProdutoNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    //imprimi os dados da ultima linha do arquivo
	printf("\nDados dos Produtos Cadastrados Filtrados pela Categoria:");
	
	
	for (j = 0; j < i; j++)
	{	
		if (R[j].codCategoria == codCategoria)
		{
			ImprimirDadosDoProduto(R[j]);	
		}			
	}
	
	printf("\n");
}

void ExcluirCadastroDeProduto(){
	
	dados_produto R[100];	
	FILE *farq;
	int codProdutoExcluir;
	int result;
	int i = 0, j= 0;
	
	//LIMPA A APRESENTAÃ‡ÃƒO NO CMD E INICIA O CADASRO DE PRODUTO
    system("cls");
	printf("--------------------EXCLUSÃO DE PRODUTOS CADASTRADOS------------------");
	
	ListarCadastroDeProduto(0);
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
			R[i] = LeituraDoProdutoNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    printf("\nInforme o código do produto que deseja excluir:\n");
	scanf("%i", &codProdutoExcluir);

	for (j =0; j < i; j++)
	{
		if (R[j].cod == codProdutoExcluir)
		{
			break;	
		}
	}
	//imprimi os dados da ultima linha do arquivo
	char simOuNao;
		
	printf("\nDados do produto selecionado:\n");
    ImprimirDadosDoProduto(R[j]);
	
	printf("\nDeseja realmente excluir o produto? (S/N)\n");
	
	getchar();
	
	simOuNao = getchar();
	
	if (tolower(simOuNao) == 's')
	{
		int k = 0;
		R[j].inativo = 1;
		
		farq = fopen(NOMEARQUIVOPRODUTO,"w");
	
		while(k < i)
		{			
			EscreveOProdutoNoArquivo(R[k], farq);
			k++;
		}
		fclose(farq);
		printf("\nProduto excluido com sucesso!\n");
	}
	
	system("pause");	
}

void AlterarProduto(){
	
	dados_produto R[100];	
	FILE *farq;
	int codProdutoAlt;
	int result;
	int i = 0, j= 0, opc;
    int ProdutoLocalizado = 0;
    char simOuNao;
	

	//LIMPA A APRESENTAÃ‡ÃƒO NO CMD E INICIA O CADASRO DE PRODUTO
    system("cls");
	printf("--------------------ALTERACAO DE PRODUTOS CADASTRADOS------------------");
	
	ListarCadastroDeProduto(0);
	
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
			R[i] = LeituraDoProdutoNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    while (ProdutoLocalizado == 0) {
        printf("\nInforme o código do produto que deseja Alterar:\n");
        scanf("%i", &codProdutoAlt);
        
        //encontrar a linha do item
        for (j =0; j < i; j++)
        {	
            if (R[j].cod == codProdutoAlt)
            {		
                ProdutoLocalizado = 1;
                break;	
            }
        }

        if(ProdutoLocalizado == 0)
        {
            printf("Produto não localizado.\n");
        }
    }

	printf("\nDados do produto selecionado:\n");
    ImprimirDadosDoProduto(R[j]);	

	printf("\nDeseja realmente alterar o produto? (S/N)\n");
	getchar();
	
	simOuNao = getchar();
	
	if (tolower(simOuNao) == 's')
	{
		printf("\nPara alterar:");
		printf("\nNome  - 1");
		printf("\nValor - 2\n");
		scanf("%i", &opc);
		int k = 0;
		int novoCod;
		
		//alterando o campo escolhido pelo usuÃ¡rio
		if(opc == 1){
			
			printf("Insira o novo nome: ");
			getchar();
			fgets(R[j].nome, TAMANHONOMEPRODUTO, stdin);
			//REMOVE A QUEBRA DE LINHA DO FGETS
			R[j].nome[strcspn(R[j].nome, "\n")] = 0;
			
		}else{
			printf("Insira o novo valor: ");
			getchar();
			scanf("%f", &R[j].valor);
			
		}
		
		farq = fopen(NOMEARQUIVOPRODUTO,"w");
	
		while(k < i)
		{			
			EscreveOProdutoNoArquivo(R[k], farq);
			k++;
		}
		fclose(farq);
		printf("\nProduto alterado com sucesso!\n");
		printf("Dados do produto alterado: \n");
		ImprimirDadosDoProduto(R[j]);
        printf("\n");
        getchar();
        getchar();
	}
    else
    {
        printf("Processo de Alteração de Produto Cancelado!\n");
        getchar();
        getchar();
    } 		 
}

//método de manipulação geral de Produto
void Produto(){
	char opc;
	do{
		
		system("cls");
		printf(" ------------  GERENCIAMENTO DE PRODUTOS ------------  ");
		printf("\nDIGITE P PARA CADASTRAR UM PRODUTO. ");
		printf("\nDIGITE A PARA ALTERAR UM PRODUTO. ");
		printf("\nDIGITE E PARA EXCLUIR UM PRODUTO. ");
		printf("\nDIGITE R PARA VERIFICAR UMA LISTA DOS PRODUTOS CADASTRADOS. \n");
		printf("\nDIGITE V PARA VOLTAR À TELA INICIAL. \n");
			
		scanf("%c", &opc);
		
		if(tolower(opc) == 'p'){
	    	while(tolower(opc)=='p')
			{	
	            CadastroDeProduto();	  
	                
	            system("cls");
	            printf("Insira P para cadastrar um produto novamente ou informe qualquer informação para sair\n");
	            scanf("%c", &opc);            
        	}
		}	
		
		if(tolower(opc) == 'r'){
            while(tolower(opc)=='r')
			{	
                ListarCadastroDeProduto(0);	  
                getchar();
                getchar();
                
                system("cls");
                printf("Insira R verificar novamente a lista de produtos cadastrados ou informe qualquer informação para sair\n");//voltar ao menu inicial.\n");
                scanf("%c", &opc);
            }
		}
		
		if(tolower(opc) == 'e'){
			while(tolower(opc)=='e')
			{	
                ExcluirCadastroDeProduto();	  
                
                system("cls");
                printf("Insira E verificar novamente a lista de produtos cadastrados para exclusao \n ou informe qualquer informação para sair\n");//voltar ao menu inicial.\n");
                scanf("%c", &opc);
            }
		}
		
		if (tolower(opc)=='a'){
			while(tolower(opc)=='a')
			{			
				AlterarProduto();
				
				system("cls");
				printf("Insira A para verificar novamente a lista de produtos cadastrados para alteração \n ou informe qualquer informação para sair.\n");//voltar ao menu inicial.\n");
				scanf("%c", &opc);
			}
		}
		
	} while(tolower(opc) != 'v');
    system("cls");
}
