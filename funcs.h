/// TIPOS ///
typedef struct linha_de_matriz
{
    char **coluna;
}linha_de_matriz;

/// ASSINATURAS PRINCIPAIS ///
void criar_tabela(void);
void listar_tabelas(void);
void criar_nova_linha(void);
void listar_dados_tabela(void);
void deletar_tabela(void);

/// ASSINATURAS SECUNDÁRIAS ///
void reconhecer_tabela (FILE *arquivo, int qtd_linhas, int qtd_colunas, linha_de_matriz *resultante);
int chave_primaria_existe (int chave_primaria, int qtd_linhas, int qtd_colunas, char nome_tabela[55]);
void atualizando_qtd_de_linhas_colunas(char nome_tabela[55], int qtd_linhas, int qtd_linhas_anteriores, int qtd_colunas);