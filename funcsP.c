#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "funcs.h"

/// Arquivo de funções principais

void criar_tabela(void)
{
//// NOMEANDO TABELA  ////
  char nome_tabela[55];
  printf("\e[1;1H\e[2J"); //Move o cursor para a linha 1, coluna 1 e limpa a interface

  printf("==== CRIAR TABELA ====\n");
  printf("Nome da tabela: ");

  fgets(nome_tabela, 51, stdin);
  nome_tabela[strcspn(nome_tabela, "\n")] = 0; //Eliminando '\n' no fim da string

//// CRIANDO OS CAMPOS(COLUNAS) DA TABELA ////
  int qtd_colunas;
  printf("--> Adicinando colunas\nQuantidade de colunas: ");
  if(reconhecer_numero_inteiro(&qtd_colunas) == 0) return; /// Testa se é um número inteiro

  while(qtd_colunas <= 0)
  {
    printf("Quantidade de colunas invalida!\nDigite uma quantidade valida de colunas ou digite 0 para cancelar a operacao:");
    scanf("%d", &qtd_colunas);

    if(qtd_colunas <= 0)
    {
      printf("\e[1;1H\e[2J"); 
      return; //CANCELANDO OPERAÇÃO//
    }
  }
//// LISTANDO NOVA TABELA CRIADA ////
  FILE *lista_tabelas;
  lista_tabelas = fopen("tabelas.txt","a");
  if(lista_tabelas == NULL)
  {
    printf("\nErro ao abrir arquivo.\n");
    return;
  }

  fprintf(lista_tabelas, "%s\n", nome_tabela);
  fclose(lista_tabelas);

//// CRIANDO ARQUIVO PARA TABELA ////
  strcat(nome_tabela,".txt"); //Adicionando extensão '.txt' para nomear um arquivo com o nome da tabela
  FILE *arquivo_tabela;
  arquivo_tabela = fopen(nome_tabela,"w");
  if(arquivo_tabela == NULL)
  {
    printf("\nErro ao abrir arquivo.\n");
    return;
  }

  fprintf(arquivo_tabela, "0 %d\n", qtd_colunas); //Salvando no arquivo a quantidade de linhas e colunas da tabela
  char nome_nova_coluna[21];
  for(int i = 0; i < qtd_colunas; i++)
    {
      i == 0 ? printf("Nome - Chave primaria (coluna 1): ") : printf("Nome - Coluna %d: ", i+1);
      fgets(nome_nova_coluna, 21, stdin);
      nome_nova_coluna[strcspn(nome_nova_coluna, "\n")] = 0; //Eliminando '\n' no fim da string
      fprintf(arquivo_tabela, "%s|", nome_nova_coluna);
    }
  printf("\e[1;1H\e[2J"); 
  printf("Tabela criada.\n");

  fclose(arquivo_tabela);
//// FIM - CRIAR TABELA ////
}

void listar_tabelas(void)
{
  printf("\e[1;1H\e[2J");
  FILE *lista = fopen("tabelas.txt","r");
  if (lista == NULL)
  {
    printf("\nNenhuma tabela encontrada.\n");
    return;
  }
  
  char linha[200];
  if(fgets(linha, 200, lista) == NULL)
  {
    printf("\nNehuma tabela encontrada.\n");
    fclose(lista);
    remove("tabelas.txt");
  }else
  {
    printf("=== Tabelas criadas ===\n");
    printf("%s", linha);
    while (fgets(linha, 200, lista) != NULL)
    {
      printf("%s", linha);
    }
    printf("=======================\n");
  }
  fclose(lista);
}

void criar_nova_linha(void)
{
  /// COLETANDO NOME DA TABELA E QUANTIDADE DE LINHAS ADCIONAIS ///
  char nome_tabela[55];
  int qtd_linhas, linhas_anteriores;

  printf("\e[1;1H\e[2J");
  listar_tabelas();
  printf("<<<< ADCIONANDO LINHA >>>>\n");
  printf("Nome da tabela: ");
  
  fgets(nome_tabela, 51, stdin);
  nome_tabela[strcspn(nome_tabela, "\n")] = 0;
  strcat(nome_tabela, ".txt");

  printf("Digite a quantidade de linhas adcionais: ");
  if(reconhecer_numero_inteiro(&qtd_linhas) == 0) return; /// Testa se é um número inteiro

  while(qtd_linhas <= 0)
  {
    printf("Quantidade de linhas invalida!\nDigite uma quantidade valida de linhas ou digite 0 para cancelar a operacao:");
    scanf("%i", &qtd_linhas);

    if(qtd_linhas <= 0)
    {
      printf("\e[1;1H\e[2J"); 
      return; //CANCELANDO OPERAÇÃO//
    }
  }

  /// VERIFICANDO SE TABELA EXISTE ///
  FILE *arquivo_tabela1;
  arquivo_tabela1 = fopen(nome_tabela, "r");
  if(arquivo_tabela1 == NULL)
  {
    printf("\nArquivo inexistente ou Erro ao abrir arquivo.\n");
    return;
  }

  /// COLETANDO QUANTIDADE DE COLUNAS E LINHAS///
  int qtd_colunas, qtd_linhas_anteriores;
  fscanf(arquivo_tabela1, "%i %i\n", &qtd_linhas_anteriores, &qtd_colunas);
  fclose(arquivo_tabela1);

  /// ADCIONANDO INFORMAÇÕES EM UMA NOVA LINHA ///
  FILE *arquivo_tabela2;
  arquivo_tabela2 = fopen(nome_tabela, "a");
  if(arquivo_tabela2 == NULL)
  {
    printf("\nErro ao abrir arquivo.\n");
  }

  char info_coluna[30];
  int chave_primaria[qtd_linhas];
  
  for(int j = 0; j < qtd_linhas; j++)
  {
    for(int i = 0; i < qtd_colunas; i++)
    {
      if(i == 0) 
      {
        printf("Chave primaria (coluna 1): ");
        if(reconhecer_numero_inteiro(&(chave_primaria[j])) == 0) /// Testa se é um número inteiro
        {
          fclose(arquivo_tabela2);
          return;
        }

        /// VERIFICA SE CHAVE PRIMÁRIA JÁ EXISTE ///
        if(chave_primaria_existe(chave_primaria[j], qtd_linhas_anteriores + 1, qtd_colunas, nome_tabela))
        {
          atualizando_qtd_de_linhas_colunas(nome_tabela, j, qtd_linhas_anteriores, qtd_colunas);
          fclose(arquivo_tabela2);
          return;
        }

        for(int k = 0; k < j; k++)
        {
          for (int m = k; m < j; m++)
          {
            if(chave_primaria[k] == chave_primaria[m+1]) 
            {
              atualizando_qtd_de_linhas_colunas(nome_tabela, j, qtd_linhas_anteriores, qtd_colunas);
              printf("\nERRO, essa linha nao sera inserida, chave primaria digitada anteriormente!\n");
              fclose(arquivo_tabela2);
              return;
            }
          }
        }
      
        fprintf(arquivo_tabela2, "\n");
        fprintf(arquivo_tabela2, "%i|", chave_primaria[j]);
      }
      else
      {
        printf("Coluna %i: ", i+1);
        fgets(info_coluna, 29, stdin);
        info_coluna[strcspn(info_coluna, "\n")] = 0;
        fprintf(arquivo_tabela2, "%s|", info_coluna);
      } 
    }
  }
  fclose(arquivo_tabela2);

  atualizando_qtd_de_linhas_colunas(nome_tabela, qtd_linhas, qtd_linhas_anteriores, qtd_colunas);
}

void listar_dados_tabela(void)
{
  listar_tabelas();
  char nome_tabela[51];
  printf("Mostrar dados da tabela: ");
  fgets(nome_tabela, 51, stdin);
  nome_tabela[strcspn(nome_tabela, "\n")] = 0;
  strcat(nome_tabela,".txt");

  FILE *tabela = fopen(nome_tabela,"r");
  if (tabela == NULL)
  {
    printf("\nNenhuma tabela encontrada.\n");
    return;
  }

  int qtd_linhas, qtd_colunas;
  fscanf(tabela,"%d %d\n", &qtd_linhas, &qtd_colunas); //Scan da quantidade de linhas e colunas (primeira informação do arquivo)
  qtd_linhas++;

  linha_de_matriz nova_matriz[qtd_linhas]; //Declarando uma matriz com a quantidade de linhas da tabela escolhida
  reconhecer_tabela(tabela, qtd_linhas, qtd_colunas, nova_matriz); //APLICANDO A FUNÇÃO NOVA

  printf("\e[1;1H\e[2J");
  for(int i = 0; i < qtd_linhas; i++)
  {
    for(int j = 0; j < qtd_colunas; j++)
    {
      printf("%s|", nova_matriz[i].coluna[j]);
    }
    printf("\n");
  }
  printf("\n");

  free(nova_matriz); //Free quando acabar de usar a matriz
  fclose(tabela); //Fim da operação
}

void deletar_tabela(void)
{
  printf("\e[1;1H\e[2J");
  FILE *arqivo_entrada = fopen("tabelas.txt","r"); //Abrindo arquivo da lista de tabelas
  if (arqivo_entrada == NULL)
  {
    printf("\nNenhuma tabela encontrada.\n");
    return;
  }
  FILE *arquivo_saida = fopen("outlist.txt","w"); //Criando novo arquivo modificado (sem a tabela a ser deletada)
  if (arquivo_saida == NULL)
  {
    printf("\nErro ao abrir arquivo.\n");
    return;
  }

  listar_tabelas();
  char nome_apagar[51];
  printf("=== DELETANDO TABELA ===\n");
  printf("Nome da tabela: ");

  fgets(nome_apagar, 51, stdin);

//// APAGANDO DA LISTA DE TABELAS ////
  char linha[200];
  int existe_tabela = 0;
  while (fgets(linha, 200, arqivo_entrada) != NULL)
  {
    if(strcmp(linha,nome_apagar) != 0)
    {
      fputs(linha, arquivo_saida); //*COLOQUE O QUE NÃO FOR A TABELA DELETADA NO NOVO ARQUIVO*
    }else
    {
      existe_tabela = 1;
    }
  }
  fclose(arqivo_entrada);
  fclose(arquivo_saida);

  remove("tabelas.txt"); //Excluindo lista original
  rename("outlist.txt", "tabelas.txt"); //Renomeando a nova lista para o nome padrão

//// APAGANDO ARQUIVO ////
  nome_apagar[strcspn(nome_apagar, "\n")] = 0; //Eliminando '\n' no fim da string
  strcat(nome_apagar,".txt"); //Adicionando extensão '.txt' para encontrar o arquivo

  remove(nome_apagar);
  printf("\e[1;1H\e[2J");
  existe_tabela == 0 ? printf("Tabela nao encontrada. Encerrando operacao.\n") : printf("Tabela removida.\n");
//// FIM - DELETAR TABELA////
}
