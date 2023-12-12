#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "funcs.h"

int main(void)
{
  int operacao = 42;

  printf("=== SGBD ITP ===");
  while(operacao != 0)
  {
    printf("\nOperacoes:\n");
    printf("| Criar tabela (1)\n");
    printf("| Listar tabelas (2)\n");
    printf("| Criar nova linha em uma tabela (3)\n");
    printf("| Listar todos os dados de uma tabela (4)\n");
    printf("| Pesquisar valores em coluna (5)\n");
    printf("| Apagar uma linha (6)\n");
    printf("| Excluir uma tabela (7)\n");
    printf("| Encerrar (0)\n");
    printf("\nOperacao: ");

    if(reconhecer_numero_inteiro(&operacao) == 0) operacao = 42; /// Testa se é um número inteiro

    switch (operacao)
    {
    case 0:
      printf("\e[1;1H\e[2J"); //Move o cursor para a linha 1, coluna 1 e limpa a interface
      printf("Encerrado.");
      break;
    case 1:
      criar_tabela();
      break;
    case 2:
      listar_tabelas();
      break;
    case 3:
      criar_nova_linha();
      break;
    case 4:
      listar_tabelas();
      printf("Mostrar dados da tabela: ");
      char nome_tabela[55];
      fgets(nome_tabela, 51, stdin);
      listar_dados_tabela(nome_tabela);
      break;
    case 5:
      pesquisar();
      break;
    case 6:
      deletar_linha_tabela();
      break;
    case 7:
      deletar_tabela();
      break;
    case 42:
      break;
    default:
      printf("\nOperacao invalida.\n");
      break;
    }
  }

  return 0;
}

//Para rodar o código basta compilar tudo no terminal < gcc main.c funcsP.c funcsS.c -o final -g -W > e excutar o novo executável criado após isso < ./final >