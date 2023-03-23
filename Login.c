#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "Login.h"
#include "Usuario.h"

void imprimeUsuarioLogado(char usuario[]){
}

int Logar(char username[], char senha[]){
			
	int opc;
	
	char ArquivoDeCadUser[] = "CadastrosDeUsuario.txt";
	dados_usuario P[100];
	dados_usuario R[100];	
	FILE *farq;
	int result;
	int j, i=0;
	int valida;
	int cont;	
	
	//verificando se o usuário não apertou enter sem digitar nada
	if(strlen(username)<1 || strlen(senha)<1){
		valida=0;
		return valida;
	}
		
	//veroficando se o usuário é administrador
	if(strcmp(username, "user")==0 && strcmp(senha, "admin")==0){
		valida = 2;		
	}else{		
		//Le e verifica se conseguiu abrir o arquivo corretamente
		if((farq = fopen(ArquivoDeCadUser,"r")) == NULL)
		{
			printf("Houve um inconveniente ao visualizar os dados do cliente cadastrado. Verifique sua conexÃ£o com o Computador principal.");               
	    }
    	else
    	{
    		result = 0;
			//ve o aquivo até chegar na ultima linha e guarda o valor da ultima linha
			while(result == feof(farq))
			{
				fscanf(farq,"%i;%30[^;];%30[^;];%i\n", &R[i].cod, R[i].username, R[i].senha, &R[i].inativo);
				R[i] = Descriptografar(R[i]);
				i++;
			}
		}
    	fclose(farq);
    
    	//Encontrando o nome e senha na tabela
		valida = 0;
		for(j = 0; j <= i; j++){	
			if(strcmp(username, R[j].username)==0 && strcmp(senha, R[j].senha )==0){
				valida = 1;	
				EscreveOUsuarioOnlineNoArquivo(R[j].cod, R[j].username);		
				break;
			}			
		}		
	}
	
	printf("\n");
		
	return valida;
}


