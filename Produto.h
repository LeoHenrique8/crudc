#define TAMANHONOMEPRODUTO 100
#define TAMANHONOMECATEGORIA 30

typedef struct {
    int cod;
	char nome[TAMANHONOMEPRODUTO];
    float valor;
    int codCategoria;
    char nomeCategoriaDoProduto[TAMANHONOMECATEGORIA];
    int inativo;
}dados_produto;

//CRUD do Cadastro de Produto
void CadastroDeProduto();
void ListarCadastroDeProduto();
void ExcluirCadastroDeProduto();
void AlterarProduto();

int GeraCod(char AqruivoDeGeraCod[]);
void ImprimirDadosDoProduto(dados_produto T);
dados_produto LeituraDoProdutoNoArquivo(FILE *farq);
int EscreveOProdutoNoArquivo(dados_produto T, FILE *farq);

