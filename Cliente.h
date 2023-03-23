#define TAMANHONOMECLIENTE 30
#define TAMANHOCOD 3
#define TAMANHOTEL 20

typedef struct{
	char nome[TAMANHONOMECLIENTE];
	int cod;
	char tel[TAMANHOTEL];
	char cpf[16];
	int inativo;
}dados_cliente;

//CRUD do Cadastro de Produto
void CadastroDeCliente();
void ListarCadastroDeCliente();
void ExcluirCadastroDeCliente();
void AlterarCliente();

void ImprimirDadosDoCliente(dados_cliente T);
dados_cliente LeituraDoClienteNoArquivo(FILE *farq);
int EscreveOClienteNoArquivo(dados_cliente T, FILE *farq);
void ImprimirDadosDoCliente();

