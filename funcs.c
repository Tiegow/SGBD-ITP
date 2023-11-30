#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void criar_tabela(void)
{
  char nome_tabela[51];
  printf("\e[1;1H\e[2J"); //Move o cursor para a linha 1, coluna 1 e limpa a interface

  printf("==== CRIAR TABELA ====\n");
  printf("Nome da tabela: ");

  fgets(nome_tabela, 51, stdin);
  nome_tabela[strcspn(nome_tabela, "\n")] = 0; //Eliminando '\n' no fim da string
  strcat(nome_tabela,".txt"); //Adicionando extensão '.txt' para nomear um arquivo com o nome da tabela

  FILE *arquivo_tabela;
  arquivo_tabela = fopen(nome_tabela,"w");
  if(arquivo_tabela == NULL)
  {
    printf("Erro ao abrir arquivo.");
    return;
  }

//// CRIANDO OS CAMPOS(COLUNAS) DA TABELA ////
  int qtd_colunas;
  printf("--> Adicinando colunas\nQuantidade de colunas: ");
  scanf("%d", &qtd_colunas);
  getchar(); //Lidando com o '\n' no fim de scanf

  while(qtd_colunas <= 0)
  {
    printf("Quantidade de colunas invalida!\nDigite uma quantidade valida de colunas ou digite 0 para cancelar a operacao:");
    scanf("%d", &qtd_colunas);

    if(qtd_colunas == 0)
    {
      printf("\e[1;1H\e[2J"); //Move o cursor para a linha 1, coluna 1 e limpa a interface
      fclose(arquivo_tabela);
      remove(nome_tabela); //Excluindo tabela vazia
      return; //CANCELANDO OPERAÇÃO//
    }
  }

  fprintf(arquivo_tabela, "0 %d\n", qtd_colunas); //Salvando no arquivo a quantidade de linhas e colunas da tabela
  char nome_nova_coluna[21];
  for(int i = 0; i < qtd_colunas; i++)
    {
      i == 0 ? printf("Nome - Chave primaria (coluna 1): ") : printf("Nome - Coluna %d: ", i+1);
      fgets(nome_nova_coluna, 21, stdin);
      nome_nova_coluna[strcspn(nome_nova_coluna, "\n")] = 0; //Eliminando '\n' no fim da string
      fprintf(arquivo_tabela, "%s ", nome_nova_coluna);
    }
  printf("\e[1;1H\e[2J"); //Move o cursor para a linha 1, coluna 1 e limpa a interface
  printf("Tabela criada.\n");

  fclose(arquivo_tabela);
//// FIM - CRIAÇÃO DE ARQUIVO TABELA ////

//// LISTANDO NOVA TABELA CRIADA ////
  FILE *lista_tabelas;
  lista_tabelas = fopen("tabelas.txt","a");
  if(arquivo_tabela == NULL)
  {
    printf("Erro ao abrir arquivo.");
    return;
  }

  fprintf(lista_tabelas, "%s\n", nome_tabela);
  fclose(lista_tabelas);
//// FIM ////
}
