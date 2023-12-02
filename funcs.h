typedef struct linha_de_matriz
{
    char **coluna;
}linha_de_matriz;
void criar_tabela(void);
void listar_tabelas(void);
void criar_nova_linha(void);
void deletar_tabela(void);
void reconhecer_tabela (FILE *arquivo, int qtd_linhas, int qtd_colunas, linha_de_matriz *resultante);
//arquivo de assinaturas de funções