#define TAMANHONOMECATEGORIA 30

typedef struct {
    char nome[TAMANHONOMECATEGORIA];
    int cod;
    int inativo;
}dados_categoria;

//CRUD do Cadastro de Produto
void CadastroDeCategoriaDoProduto();
void ListarCategoriaDeProduto();
void ExcluirCategoriaDeProduto();
void AlterarCategoriaDeProduto();

int GeraCod(char AqruivoDeGeraCod[]);
void ImprimirDadosDaCategoria(dados_categoria T);
dados_categoria LeituraDaCategoriaNoArquivo(FILE *farq);
int EscreveACategoriaNoArquivo(dados_categoria T, FILE *farq);

