#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

#include "funcs.h"

/// Arquivo de funções secundárias

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
            fscanf(arquivo,"%29[^|]",resultante[i].coluna[j]); //Lendo os dados string de cada campo (delimitados por |)
            fscanf(arquivo,"|"); 
        }
    }
    //A função vai "retornar" a matriz resultante com os dados preenchidos
}

int chave_primaria_existe (int chave_primaria, int qtd_linhas, int qtd_colunas, char nome_tabela[55])
{
    FILE *tabela = fopen(nome_tabela,"r");
    if (tabela == NULL)
    {
        printf("\nERRO, Nenhuma tabela encontrada.\n");
        return 1;
    }

    linha_de_matriz matriz_tabela[qtd_linhas]; 
    reconhecer_tabela(tabela, qtd_linhas, qtd_colunas, matriz_tabela); 
    
    for(int i = 1; i < qtd_linhas; i++)
    {
        int id = atoi(matriz_tabela[i].coluna[0]); 
        if(id == chave_primaria)
        {
            printf("\nERRO, essa linha nao sera inserida, chave primaria ja existe!\n");
            free(matriz_tabela); 
            fclose(tabela);
            return 1;
        }
    }
    free(matriz_tabela); 
    fclose(tabela);

    return 0;
}

void atualizando_qtd_de_linhas_colunas(char nome_tabela[55], int qtd_linhas, int qtd_linhas_anteriores, int qtd_colunas)
{
  FILE *arquivo_tabela00;
  arquivo_tabela00 = fopen(nome_tabela, "r+");
  if(arquivo_tabela00 == NULL)
  {
    printf("\nErro ao abrir arquivo.\n");
  }
  
  fprintf(arquivo_tabela00, "%i %i\n", qtd_linhas + qtd_linhas_anteriores, qtd_colunas);
  fclose(arquivo_tabela00);
}

int reconhecer_numero_inteiro(int* numero) 
{
    int limpador;

    if (scanf("%i", numero) != 1) 
    {
        while ((limpador = getchar()) != '\n' && limpador != EOF);
        printf("\r\nERRO, numero invalido, digite um numero inteiro!\n");
        return 0;
    }

    // Verifica se há mais caracteres no buffer após a leitura do número inteiro
    while ((limpador = getchar()) != '\n' && limpador != EOF)
    {
        if (!isspace(limpador)) // Verifica se não é um espaço em branco
        { 
            while ((limpador = getchar()) != '\n' && limpador != EOF);
            printf("\r\nERRO, numero invalido, digite um numero inteiro!\n");
            return 0;
        }
    }

    return 1;
}

int reconhecer_numero_double(double* numero) 
{
    int limpador;

    if (scanf("%lf", numero) != 1) 
    {
        while ((limpador = getchar()) != '\n' && limpador != EOF);
        return 0;
    }

    // Verifica se há mais caracteres no buffer após a leitura do número inteiro
    while ((limpador = getchar()) != '\n' && limpador != EOF)
    {
        if (!isspace(limpador)) // Verifica se não é um espaço em branco
        { 
            while ((limpador = getchar()) != '\n' && limpador != EOF);
            return 0;
        }
    }

    return 1;
}

void string_para_maisculo(char* nome)
{
    int i = 0;
    while (nome[i]) 
    {
        nome[i] = toupper(nome[i]);
        i++;
    }
}

