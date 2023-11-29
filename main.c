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

//PAYSANDUUUU

  FILE *arquivo_tabela;
  arquivo_tabela = fopen(nome_tabela,"w");
  if(arquivo_tabela == NULL)
  {
    printf("Erro ao abrir arquivo.");
    return;
  }

  char nome_chave_primaria[21];
  printf("Nome de chave primaria: ");
  fgets(nome_chave_primaria, 21, stdin);

  fputs(nome_chave_primaria, arquivo_tabela);
  fclose(arquivo_tabela);

  FILE *lista_tabelas;
  lista_tabelas = fopen("tabelas.txt","a");
  if(arquivo_tabela == NULL)
  {
    printf("Erro ao abrir arquivo.");
    return;
  }

  fprintf(lista_tabelas, "%s\n", nome_tabela);
  fclose(lista_tabelas);
}

int main(void)
{
  int operacao;

  printf("Operacoes:\n");
  printf("| Criar tabela (1)\n");
  printf("\nOperacao: ");

  scanf("%d", &operacao);
  getchar(); //Lidando com o '\n' no fim de scanf

  switch (operacao)
  {
  case 1:
    criar_tabela();
    break;
  
  default:
    printf("Operacao invalida.");
    break;
  }

  return 0;
}
