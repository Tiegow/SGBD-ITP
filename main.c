#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "funcs.h"

int main(void)
{
  int operacao = 1;

  while(operacao != 0)
  {
    printf("Operacoes:\n");
    printf("| Criar tabela (1)\n");
    printf("| Listar tabelas (2)\n");
    printf("| Encerrar (0)\n");
    printf("\nOperacao: ");

    scanf("%d", &operacao);
    getchar(); //Lidando com o '\n' no fim de scanf

    switch (operacao)
    {
    case 0:
      printf("Encerrando");
      break;
    case 1:
      criar_tabela();
      break;
    case 2:
      listar_tabelas();
      break;
    default:
      printf("Operacao invalida.");
      break;
    }
  }

  return 0;
}

//Para rodar o código basta compilar tudo no terminal < gcc main.c funcs.c -o final -g -W > e excutar o novo executável criado após isso < ./final >