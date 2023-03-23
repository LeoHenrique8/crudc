#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include "CategoriaProduto.h"

#define TAMANHONOMECATEGORIA 30
#define NOMEARQUIVOCATEGORIA "CategoriaDeProduto.txt"

void ImprimirDadosDaCategoriaDoProduto(dados_categoria T){
	
	int i;
	//Verifica o tamanho da string, pora ajustar na exibiçao, nomes embaixo de nomes e valores embaixo de valores/
	if(strlen(T.nome)<TAMANHONOMECATEGORIA)
	{
    	//Como o tamanho máximo TAMANHONOME, ele calcula o tamanho da string, e subtrai de TAMANHONOME para ver quanto espaço falta/				
		int diflen = TAMANHONOMECATEGORIA - strlen(T.nome);
    	//ele soma os espaços necessários na string do nome para alinhar com o valor/				
		for(i=0; i<diflen;i++){
			strcpy(T.nome, strcat(T.nome, "."));
		}
	}
	printf("\nCodigo: %i | Nome : %s ", T.cod, T.nome);		
}

dados_categoria LeituraDaCategoriaNoArquivo(FILE *farq){
	
	dados_categoria T;
	fscanf(farq,"%i;%30[^;];%i\n",  &T.cod, T.nome, &T.inativo);
	return T;
}

int EscreveACategoriaNoArquivo(dados_categoria T, FILE *farq){
	
	int escreveuComSucesso;	
	
	escreveuComSucesso = fprintf(farq,"%i;%s;%i\n", T.cod, T.nome, T.inativo);
	
	return escreveuComSucesso;
}

void CadastroDeCategoriaDeProduto(){
	
	dados_categoria P;
	dados_categoria R;	
	FILE *farq;
	int result;
	int j;
	
	//LIMPA A APRESENTAÇÃO NO CMD E INICIA O CADASTRO DE PRODUTO
    //PEDE AS INFORMAÇOES NECESSÁRIAS PARA O CADASTRO DE PRODUTO
	system("cls");
	printf("--------------------CADASTRO DE CATEGORIA PRODUTO------------------");
	
	printf("\nDigite o nome da categoria: ");
	getchar();
	fgets(P.nome, TAMANHONOMECATEGORIA, stdin);
	ToUpperString(P.nome);
	
	//REMOVE A QUEBRA DE LINHA DO FGETS
	P.nome[strcspn(P.nome, "\n")] = 0;
	P.inativo = 0;
	P.cod = GeraCod("CodCategoria.txt");

	//INICIA A GRAVAÃ‡ÃƒO DOS DADOS DO PRODUTO NO ARQUIVO	
	
	//Verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCATEGORIA,"a")) == NULL)
	{
		printf("Houve um inconveniente ao realizar o cadastro da categoria do produto. Verifique sua conexão com o Computador principal e inicie o cadastro da categoria do produto novamente.");               
    }
    else
    {
    	//Imprimi os dados no arquivo
		result = EscreveACategoriaNoArquivo(P, farq);
		//Valida se conseguiu imprimir os dados no aquivo
		if (result != EOF && result > 1)
		{
			printf("\nA categoria foi cadastrada com sucesso.\n");
		}
		else
		{
			printf("\nHouve um inconveniente na execução do cadastro da categoria do produto.\n");
		}	
	}
	fclose(farq);
	
	//LEITURA DO ARQUIVO E CAPTURA DA INFORMAÃ‡ÃƒO DA ULTIMA LINHA
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCATEGORIA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados da categoria de produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo até chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R = LeituraDaCategoriaNoArquivo(farq);
		}
				
		//imprimi os dados da ultima linha do arquivo
		printf("\n----------Dados da Categoria Cadastrada----------");
		ImprimirDadosDaCategoriaDoProduto(R);
	}
    fclose(farq);
	
	printf("\n");
}

void ListarCategoriaDeProduto(int mostraInativo){
	
	dados_categoria R[100];	
	FILE *farq;
	int result;
	int i = 0, j= 0;
	
	//LIMPA A APRESENTAÇÃO NO CMD E INICIA O CADASRO DE CATEGORIA
	printf("--------------------CATEGORIAS DE PRODUTO CADASTRADAS------------------");

	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCATEGORIA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados da categoria do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo atÃ© chegar na ultima linha e guarda o valor da ultima linha
		while(result == feof(farq))
		{
			R[i] = LeituraDaCategoriaNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    //imprimi os dados da ultima linha do arquivo
	printf("\nDados das categorias cadastradas:");
	
	if (mostraInativo == 0)
	{	
		for (j = 0; j < i; j++)
		{	
			if (R[j].inativo == 0)
			{
				ImprimirDadosDaCategoriaDoProduto(R[j]);	
			}			
		}
	}
	else	
	{	
		for (j = 0; j < i; j++)
		{	
			ImprimirDadosDaCategoriaDoProduto(R[j]);				
		}
	}
	
	printf("\n");
}

void ExcluirCategoriaDeProduto(){
	
	dados_categoria R[100];	
	FILE *farq;
	int codProdutoExcluir;
	int result;
	int i = 0, j= 0;
	
	//LIMPA A APRESENTAÃ‡ÃƒO NO CMD E INICIA O CADASRO DE PRODUTO
    system("cls");
	printf("--------------------EXCLUSÃO DE CATEGORIA DE PRODUTO ------------------");
	
	ListarCategoriaDeProduto(0);
	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCATEGORIA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados da categoria do produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo atÃ© chegar na ultima linha
		while(result == feof(farq))
		{			
			R[i] = LeituraDaCategoriaNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    printf("\nInforme o código da categoria do produto que deseja excluir:\n");
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
		
	printf("\nDados da categoria do produto selecionado:\n");
    ImprimirDadosDaCategoriaDoProduto(R[j]);
	
	printf("\nDeseja realmente excluir a categoria do produto? (S/N)\n");
	
	getchar();
	
	simOuNao = getchar();
	
	if (tolower(simOuNao) == 's')
	{
		int k = 0;
		R[j].inativo = 1;
		
		farq = fopen(NOMEARQUIVOCATEGORIA,"w");
	
		while(k < i)
		{			
			EscreveACategoriaNoArquivo(R[k], farq);
			k++;
		}
		fclose(farq);
		printf("\nCategoria excluida com sucesso!\n");
	}
	
	system("pause");	
}

void AlterarCategoriaProduto(){
	
	dados_categoria R[100];	
	FILE *farq;
	int codProdutoAlt;
	int result;
	int i = 0, j= 0, opc;
    int ProdutoLocalizado = 0;
    char simOuNao;
	
	//LIMPA A APRESENTAÃ‡ÃƒO NO CMD E INICIA O CADASRO DE PRODUTO
    system("cls");
	printf("--------------------ALTERACAO DE PRODUTOS CADASTRADOS------------------");
	
	ListarCategoriaDeProduto(0);
	
	//LEITURA DO ARQUIVO E CAPTURA OS DADOS DE TODAS AS LINHAS
	
	//Le e verifica se conseguiu abrir o arquivo corretamente
	if((farq = fopen(NOMEARQUIVOCATEGORIA,"r")) == NULL)
	{
		printf("Houve um inconveniente ao visualizar os dados da categoria de produto cadastrado. Verifique sua conexão com o Computador principal.");               
    }
    else
    {
    	result = 0;
		//ve o aquivo atÃ© chegar na ultima linha
		while(result == feof(farq))
		{			
			R[i] = LeituraDaCategoriaNoArquivo(farq);
			i++;
		}
	}
    fclose(farq);
    
    while (ProdutoLocalizado == 0) {
        printf("\nInforme o código da categoria de produto que deseja Alterar:\n");
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

	printf("\nDados da categoria de produto selecionado:\n");
    ImprimirDadosDaCategoriaDoProduto(R[j]);	

	printf("\nDeseja realmente alterar a categoria de produto? (S/N)\n");
	getchar();
	
	simOuNao = getchar();
	
	if (tolower(simOuNao) == 's')
	{
		printf("\nPara alterar:");
		printf("\nNome  - 1");
		
		scanf("%i", &opc);
		int k = 0;
		int novoCod;
		
		//alterando o campo escolhido pelo usuÃ¡rio
		if(opc == 1){
			
			printf("Insira o novo nome: ");
			getchar();
			fgets(R[j].nome, TAMANHONOMECATEGORIA, stdin);
			//REMOVE A QUEBRA DE LINHA DO FGETS
			R[j].nome[strcspn(R[j].nome, "\n")] = 0;
			
		}
		
		farq = fopen(NOMEARQUIVOCATEGORIA,"w");
	
		while(k < i)
		{			
			EscreveACategoriaNoArquivo(R[k], farq);
			k++;
		}
		fclose(farq);
		printf("\nCategoria de Produto alterado com sucesso!\n");
		printf("Dados da categoria de produto alterada: \n");
		ImprimirDadosDaCategoriaDoProduto(R[j]);
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

//método de manipulação geral de Categoria de Produto
void Categoria(){
	system("cls");
	char opc;
	do{
		
		system("cls");
		printf(" ------------  GERENCIAMENTO DE CATEGORIA DE PRODUTOS ------------  ");
		printf("\nDIGITE P PARA CADASTRAR UMA CATEGORIA DE PRODUTO. ");
		printf("\nDIGITE A PARA ALTERAR UMA CATEGORIA DE PRODUTO. ");
		printf("\nDIGITE E PARA EXCLUIR UMA CATEGORIA DE PRODUTO. ");
		printf("\nDIGITE R PARA VERIFICAR UMA LISTA DAS CATEGORIAS DE PRODUTO CADASTRADAS. \n");
		printf("\nDIGITE V PARA VOLTAR À TELA INICIAL. \n");
			
		scanf("%c", &opc);
		
		if(tolower(opc) == 'p'){
	    	while(tolower(opc)=='p')
			{	
	            CadastroDeCategoriaDeProduto();	  
	            getchar();
				    
	            system("cls");
	            printf("Insira P para cadastrar uma categoria de produto novamente ou informe qualquer informação para sair\n");
	            scanf("%c", &opc);            
        	}
		}	
		
		if(tolower(opc) == 'r'){
            while(tolower(opc)=='r')
			{	
                system("cls");
				ListarCategoriaDeProduto(0);	  
                getchar();
                getchar();
                
                system("cls");
                printf("Insira R verificar novamente a lista de categorias de produto cadastradas ou informe qualquer informação para sair\n");//voltar ao menu inicial.\n");
                scanf("%c", &opc);
            }
		}
		
		if(tolower(opc) == 'e'){
			while(tolower(opc)=='e')
			{	
                ExcluirCategoriaDeProduto();	  
                
                system("cls");
                printf("Insira E verificar novamente a lista de categorias de produto cadastradas para exclusao \n ou informe qualquer informação para sair\n");//voltar ao menu inicial.\n");
                scanf("%c", &opc);
            }
		}
		
		if (tolower(opc)=='a'){
			while(tolower(opc)=='a')
			{			
				AlterarCategoriaProduto();
				
				system("cls");
				printf("Insira A para verificar novamente a lista de categorias de produto cadastradas para alteração \n ou informe qualquer informação para sair.\n");//voltar ao menu inicial.\n");
				scanf("%c", &opc);
			}
		}
		
	} while(tolower(opc) != 'v');
    system("cls");
}
