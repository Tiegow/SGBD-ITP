#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "funcs.h"

int main(void)
{
  int operacao = 1;

  while(operacao != 0)
  {
    printf("\nOperacoes:\n");
    printf("| Criar tabela (1)\n");
    printf("| Listar tabelas (2)\n");
    printf("| Criar nova linha em uma tabela (3)\n");
    printf("| Excluir uma tabela (7)\n");
    printf("| Encerrar (0)\n");
    printf("\nOperacao: ");

    scanf("%d", &operacao);
    getchar(); //Lidando com o '\n' no fim de scanf

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
    case 7:
      deletar_tabela();
      break;
    default:
      printf("\e[1;1H\e[2J");
      printf("Operacao invalida.");
      break;
    }
  }

  return 0;
}

//Para rodar o código basta compilar tudo no terminal < gcc main.c funcs.c -o final -g -W > e excutar o novo executável criado após isso < ./final >