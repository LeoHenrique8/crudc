#define TAMANHONOME 30
#define TAMANHOCOD 10

typedef struct{
	char username[TAMANHONOME];
	char senha[TAMANHONOME];
	int cod;
	int inativo;
}dados_usuario;

void CadastroDeUsuario();
void ListarCadastroDeUsuario(int mostraInativo);
void GerenciarUsuarios();

int GeraCod(char AqruivoDeGeraCod[]);
void ImprimirDadosDoUsuario(dados_usuario T);
dados_usuario LeituraDoUsuarioNoArquivo(FILE *farq);
dados_usuario LeituraDoUsuarioOnlineNoArquivo();
int EscreveOUsuarioNoArquivo(dados_usuario T, FILE *farq);
dados_usuario Criptografar(dados_usuario U);
dados_usuario Descriptografar(dados_usuario U);
