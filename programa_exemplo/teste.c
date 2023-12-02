#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct 
{
    char **coluna;
}linha_de_matriz;

void reconhecer_tabela (FILE *arquivo, int qtd_linhas, int qtd_colunas, linha_de_matriz *resultante)
{
    for(int i = 0; i < qtd_linhas; i++)
    {
        resultante[i].coluna = (char **)malloc(qtd_colunas * sizeof(char*)); //Pra cada linha, alocando espaço para < qtd_colunas > campos de strings
        for(int j = 0; j < qtd_colunas; j++) resultante[i].coluna[j] = (char *)malloc(21 * sizeof(char)); //pra cada campo (coluna), alocando espaço para 21 caracteres
    }

    for(int i = 0; i < qtd_linhas; i++)
    {
        for(int j = 0; j < qtd_colunas; j++)
        {
            fscanf(arquivo,"%20[^|]",resultante[i].coluna[j]); //Lendo os dados string de cada campo (delimitados por |)
            fscanf(arquivo,"|"); 
        }
    }
}

int main()
{
//>>>>>EXEMPLO DE FUNCIONALIDADE<<<<<//
    char nome_tabela[51];
    printf("Nome da tabela: ");
    fgets(nome_tabela, 51, stdin);
    nome_tabela[strcspn(nome_tabela, "\n")] = 0;
    strcat(nome_tabela,".txt");

    FILE *tabela = fopen(nome_tabela,"r");
    if (tabela == NULL)
    {
        printf("Nenhuma tabela encontrada.\n");
        return 0;
    }

    int qtd_linhas, qtd_colunas;
    fscanf(tabela,"%d %d\n", &qtd_linhas, &qtd_colunas); //Scan da quantidade de linhas e colunas (primeira informação do arquivo)

    linha_de_matriz nova_matriz[qtd_linhas]; //Declarando uma matriz com a quantidade de linhas da tabela escolhida
    reconhecer_tabela(tabela, qtd_linhas, qtd_colunas, nova_matriz); //APLICANDO A FUNÇÃO NOVA

    printf("Nova chave primaria: "); //TESTE DE CHAVE PRIMÁRIA
    int chave;
    scanf("%d", &chave);

    for(int i = 1; i < 4; i++)
    {
        int id = atoi(nova_matriz[i].coluna[0]); //>>>> CONVERTE OS DADOS DA PRIMEIRA COLUNA EM INTEIRO
        if(id == chave){
            printf("Essa chave primaria ja existe!");
        }
    }
    free(nova_matriz); //Free quando acabar de usar a matriz

    fclose(tabela); //Fim da operação
    return 0;
}
