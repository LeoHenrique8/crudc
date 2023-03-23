#define DESCRICAOVENDA 30
#define TAMANHONOMEVENDEDOR 30
#define TAMANHONOMECLIENTE 30
#define TAMANHONOMECATEGORIA 30
#define TAMANHONOME 100

typedef struct {
    int codVenda;
    char descricao[DESCRICAOVENDA];
    int codCliente;
    char nomeCliente[TAMANHONOMECLIENTE];
    float valorVenda;
    int codVendedor;
    char nomeVendedor[TAMANHONOMEVENDEDOR];
    int inativo;
}dados_venda;

typedef struct {
    int codVenda;
    int codProduto;
	char nomeProduto[TAMANHONOME];
    int codCategoria;
	char nomeCategoriaDoProduto[TAMANHONOMECATEGORIA];
    int quantidadeVenda;
	float valorUnitario;
	float valorTotal;    
}dados_itemVenda;

//CRUD do Cadastro de Produto
void CadastroDeVenda();
void ListarVendas();
void ExcluirVendas();

void ImprimirDadosDaVenda(dados_venda T);
dados_venda LeituraDaVendaNoArquivo(FILE *farq);
int EscreveAVendaNoArquivo(dados_venda T, FILE *farq);

