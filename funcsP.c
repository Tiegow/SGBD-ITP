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
    printf("Quantidade de colunas invalida!\nDigite uma quantidade valida de colunas ou digite 0 para cancelar a operacao: ");
    if(reconhecer_numero_inteiro(&qtd_colunas) == 0) return; /// Testa se é um número inteiro

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
  
  char linha[151];
  if(fgets(linha, 150, lista) == NULL)
  {
    printf("\nNehuma tabela encontrada.\n");
    fclose(lista);
    remove("tabelas.txt");
  }else
  {
    printf("\n=== Tabelas criadas ===\n");
    printf("%s", linha);
    while (fgets(linha, 150, lista) != NULL)
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
    printf("Quantidade de linhas invalida!\nDigite uma quantidade valida de linhas ou digite 0 para cancelar a operacao: ");
    if(reconhecer_numero_inteiro(&qtd_linhas) == 0) return; /// Testa se é um número inteiro

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
  
  //PEGANDO OS NOMES DAS COLUNAS//

  linha_de_matriz tabela_matriz[qtd_linhas_anteriores];
  char nomes_colunas[qtd_colunas][21];
  reconhecer_tabela(arquivo_tabela1,qtd_linhas_anteriores + 1,qtd_colunas,tabela_matriz);
  
  for(int c = 0; c < qtd_colunas; c++)
  {
    strcpy(nomes_colunas[c], tabela_matriz[0].coluna[c]);
  }

  free(tabela_matriz);

  ////////////////////////////////
  
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
        printf("Coluna %s (chave primaria): ", nomes_colunas[0]);
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
        printf("Coluna %s: ", nomes_colunas[i]);
        fgets(info_coluna, 29, stdin);
        info_coluna[strcspn(info_coluna, "\n")] = 0;
        fprintf(arquivo_tabela2, "%s|", info_coluna);
      } 
    }
  }
  fclose(arquivo_tabela2);

  atualizando_qtd_de_linhas_colunas(nome_tabela, qtd_linhas, qtd_linhas_anteriores, qtd_colunas);
}

void listar_dados_tabela(char nome_tabela[])
{
  printf("\e[1;1H\e[2J");
  nome_tabela[strcspn(nome_tabela, "\n")] = 0;
  printf(">>> %s <<<\n", nome_tabela);
  strcat(nome_tabela,".txt");

  FILE *tabela = fopen(nome_tabela,"r");
  if (tabela == NULL)
  {
    printf("\nTabela nao encontrada.\n");
    return;
  }

  int qtd_linhas, qtd_colunas;
  fscanf(tabela,"%d %d\n", &qtd_linhas, &qtd_colunas);
  qtd_linhas++;

  linha_de_matriz nova_matriz[qtd_linhas]; //Declarando uma matriz com a quantidade de linhas da tabela escolhida
  reconhecer_tabela(tabela, qtd_linhas, qtd_colunas, nova_matriz); 

  for(int i = 0; i < qtd_linhas; i++)
  {
    for(int j = 0; j < qtd_colunas; j++)
    {
      printf("%s|", nova_matriz[i].coluna[j]);
    }
  }
  printf("\n");

  free(nova_matriz); //Free quando acabar de usar a matriz
  fclose(tabela); //Fim da operação
}

void pesquisar(void)
{
  printf("\e[1;1H\e[2J");
  listar_tabelas();

  char nome_tabela_alvo[55];
  printf("=== PESQUISANDO VALOR ===\n");
  printf("Nome da tabela: ");
  fgets(nome_tabela_alvo, 51, stdin);
  nome_tabela_alvo[strcspn(nome_tabela_alvo, "\n")] = 0;
  strcat(nome_tabela_alvo,".txt");

  FILE *tabela_pesquisa = fopen(nome_tabela_alvo,"r"); //Abrindo arquivo da tabela alvo
  if (tabela_pesquisa == NULL)
  {
    printf("\nTabela nao encontrada.\n");
    return;
  }

  // Fornecendo as colunas //
  int qtd_linhas, qtd_colunas;
  fscanf(tabela_pesquisa,"%d %d\n", &qtd_linhas, &qtd_colunas);
  qtd_linhas++;

  linha_de_matriz tabela_matriz[qtd_linhas];
  reconhecer_tabela(tabela_pesquisa, qtd_linhas, qtd_colunas, tabela_matriz);

  printf("Selecione uma das colunas para pesquisar:\n\n");
  for(int j = 0; j < qtd_colunas; j++)
  {
    printf("%s|", tabela_matriz[0].coluna[j]);
  }
  printf("\n");
  ///////////////////////////

  // Identificando a coluna desejada //
  char nome_coluna_alvo[21];
  int posicao_coluna_alvo;

  printf("\nColuna: ");
  fgets(nome_coluna_alvo,20,stdin);
  nome_coluna_alvo[strcspn(nome_coluna_alvo, "\n")] = 0;
  int encontrou = 0;

  for(int j = 0; j < qtd_colunas; j++)
  {
    if(strcmp(nome_coluna_alvo,tabela_matriz[0].coluna[j]) == 0)
    {
      posicao_coluna_alvo = j;
      encontrou = 1;
    }else if(j == qtd_colunas && encontrou == 0)
    {
      printf("Coluna nao encontrada ou inexistente\n");
      return;
    }
  }
  /////////////////////////////////////

  // (Tentando) Identificar a "natureza" da coluna //
  int tipo_numero;
  double teste;
  char *endptr;

  int qtd_numeros = qtd_linhas-1;
  double coluna_de_numeros[qtd_numeros];

  teste = strtod(tabela_matriz[1].coluna[posicao_coluna_alvo], &endptr); //Testa se a string pode ser um numero (double)

  if(teste == 0)
  {
    tipo_numero = 0;
  } 
  else
  {
    int j = 0;
    for(int i = 1; i < qtd_linhas; i++)
    {
      teste = strtod(tabela_matriz[i].coluna[posicao_coluna_alvo], &endptr);
      coluna_de_numeros[j] = teste;
      j++;
    }
    tipo_numero = 1;
  }
  ///////////////////////////////////////////////////

  int opcao;
  printf(">>> Opcoes de pesquisa:\n");
  printf("1 - valores maiores que o valor informado\n");
  printf("2 - valores maiores ou iguais ao valor informado\n");
  printf("3 - valores iguais ao valor informado\n");
  printf("4 - valores menores que o valor informado\n");
  printf("5 - valores menores ou iguais ao valor informado\n");
  printf("6 - valores proximos ao informado (nomes)\n");
  printf("\nValor para pesquisar: ");

  if(tipo_numero) //TRABALHANDO COM NUMEROS
  {
    double valor_numero_pesquisa;
    scanf("%lf", &valor_numero_pesquisa);
    printf("Opcao de pesquisa: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
      printf("\n>>> Valores em %s maiores que %.2lf:\n", nome_coluna_alvo, valor_numero_pesquisa);
      for(int i = 0; i<qtd_numeros; i++)
      {
        if(coluna_de_numeros[i] > valor_numero_pesquisa)
        {
          printf("%s;\n", tabela_matriz[i+1].coluna[posicao_coluna_alvo]);
        }
      }
      break;
    
    case 2:
    printf("\n>>> Valores em %s maiores ou iguais a %.2lf:\n", nome_coluna_alvo, valor_numero_pesquisa);
    for(int i = 0; i<qtd_numeros; i++)
    {
      if(coluna_de_numeros[i] >= valor_numero_pesquisa)
      {
        printf("%s;\n", tabela_matriz[i+1].coluna[posicao_coluna_alvo]);
      }
    }
    break;

    case 3:
    printf("\n>>> Valores em %s iguais a %.2lf:\n", nome_coluna_alvo, valor_numero_pesquisa);
    for(int i = 0; i<qtd_numeros; i++)
    {
      if(coluna_de_numeros[i] == valor_numero_pesquisa)
      {
        printf("%s;\n", tabela_matriz[i+1].coluna[posicao_coluna_alvo]);
      }
    }
    break;

    case 4:
    printf("\n>>> Valores em %s menores que %.2lf:\n", nome_coluna_alvo, valor_numero_pesquisa);
    for(int i = 0; i<qtd_numeros; i++)
    {
      if(coluna_de_numeros[i] < valor_numero_pesquisa)
      {
        printf("%s;\n", tabela_matriz[i+1].coluna[posicao_coluna_alvo]);
      }
    }
    break;

    case 5:
    printf("\n>>> Valores em %s menores ou iguais a %.2lf:\n", nome_coluna_alvo, valor_numero_pesquisa);
    for(int i = 0; i<qtd_numeros; i++)
    {
      if(coluna_de_numeros[i] <= valor_numero_pesquisa)
      {
        printf("%s;\n", tabela_matriz[i+1].coluna[posicao_coluna_alvo]);
      }
    }
    break;
    
    default:
      printf("Opcao invalida.\n");
      break;
    }
  } 
  else //TRABALHANDO COM STRINGS
  {
    char valor_palavra_pesquisa[30];
    fgets(valor_palavra_pesquisa,29,stdin);
    valor_palavra_pesquisa[strcspn(valor_palavra_pesquisa, "\n")] = 0;
    printf("Opcao de pesquisa: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
      printf("\n>>> Valores em %s maiores que %s:\n", nome_coluna_alvo, valor_palavra_pesquisa);
      for(int i = 1; i < qtd_linhas; i++)
      {
        if(strcmp(tabela_matriz[i].coluna[posicao_coluna_alvo],valor_palavra_pesquisa) > 0)
        {
          printf("%s;\n", tabela_matriz[i].coluna[posicao_coluna_alvo]);
        }
      }
      break;
    
    case 2:
    printf("\n>>> Valores em %s maiores ou iguais a %s:\n", nome_coluna_alvo, valor_palavra_pesquisa);
    for(int i = 1; i < qtd_linhas; i++)
    {
      if(strcmp(tabela_matriz[i].coluna[posicao_coluna_alvo],valor_palavra_pesquisa) >= 0)
      {
        printf("%s;\n", tabela_matriz[i].coluna[posicao_coluna_alvo]);
      }
    }
    break;

    case 3:
    printf("\n>>> Valores em %s iguais a %s:\n", nome_coluna_alvo, valor_palavra_pesquisa);
    for(int i = 1; i < qtd_linhas; i++)
    {
      if(strcmp(tabela_matriz[i].coluna[posicao_coluna_alvo],valor_palavra_pesquisa) == 0)
      {
        printf("%s;\n", tabela_matriz[i].coluna[posicao_coluna_alvo]);
      }
    }
    break;

    case 4:
    printf("\n>>> Valores em %s menores que %s:\n", nome_coluna_alvo, valor_palavra_pesquisa);
    for(int i = 1; i < qtd_linhas; i++)
    {
      if(strcmp(tabela_matriz[i].coluna[posicao_coluna_alvo],valor_palavra_pesquisa) < 0)
      {
        printf("%s;\n", tabela_matriz[i].coluna[posicao_coluna_alvo]);
      }
    }
    break;

    case 5:
    printf("\n>>> Valores em %s menores ou iguais a %s:\n", nome_coluna_alvo, valor_palavra_pesquisa);
    for(int i = 1; i < qtd_linhas; i++)
    {
      if(strcmp(tabela_matriz[i].coluna[posicao_coluna_alvo],valor_palavra_pesquisa) <= 0)
      {
        printf("%s;\n", tabela_matriz[i].coluna[posicao_coluna_alvo]);
      }
    }
    break;

    case 6:
    printf("\n>>> Valores em %s proximos a %s:\n", nome_coluna_alvo, valor_palavra_pesquisa);
    int proximidade = strlen(valor_palavra_pesquisa)/2; //Compara ate a metade da string

    for(int i = 1; i < qtd_linhas; i++)
    {
      if(strncmp(tabela_matriz[i].coluna[posicao_coluna_alvo],valor_palavra_pesquisa,proximidade) == 0)
      {
        printf("%s;\n", tabela_matriz[i].coluna[posicao_coluna_alvo]);
      }
    }
    break;
    
    default:
      printf("Opcao invalida.\n");
      break;
    }
  }

  free(tabela_matriz);
  fclose(tabela_pesquisa);
}

void deletar_linha_tabela(void)
{
  printf("\e[1;1H\e[2J");
  listar_tabelas();

  char nome_tabela_alvo[55];
  int chave;
  printf("=== APAGANDO LINHA ===\n");
  printf("Nome da tabela: ");
  fgets(nome_tabela_alvo, 51, stdin);

  listar_dados_tabela(nome_tabela_alvo);

  FILE *tabela_entrada = fopen(nome_tabela_alvo,"r"); //Abrindo arquivo da tabela alvo
  if (tabela_entrada == NULL)
  {
    printf("\nTabela nao encontrada.\n");
    return;
  }

  printf("\nApagar da chave primaria: ");
  if(reconhecer_numero_inteiro(&chave) == 0) return; /// Testa se é um número inteiro
  
  FILE *tabela_saida;

  int qtd_linhas, qtd_colunas;
  fscanf(tabela_entrada,"%d %d\n", &qtd_linhas, &qtd_colunas);
  qtd_linhas++;

  linha_de_matriz matriz_entrada[qtd_linhas];
  reconhecer_tabela(tabela_entrada, qtd_linhas, qtd_colunas, matriz_entrada); 

  for(int i = 0; i < qtd_linhas; i++) //Verifica se a chave primaria realmente existe para remove-la
  {
    if(atoi(matriz_entrada[i].coluna[0]) == chave)
    {
      tabela_saida = fopen("novatabela.txt","w"); //Criando nova tabela (sem a linha a ser deletada)
      if (tabela_saida == NULL)
      {
        printf("\nErro ao abrir arquivo.\n");
        return;
      }
      fprintf(tabela_saida,"%d %d\n", qtd_linhas-2, qtd_colunas);
      break;
    }else
    {
      if(i == qtd_linhas-1)
      {
        printf("\nEssa linha nao existe ou nao foi encontrada.\n");
        return;
      }
    }
  }
  //fprintf(tabela_saida,"%d %d\n", qtd_linhas-2, qtd_colunas);
  for(int i = 0; i < qtd_linhas; i++)
  {
    for(int j = 0; j < qtd_colunas; j++)
    {
      if(atoi(matriz_entrada[i].coluna[0]) != chave)
      {
        fprintf(tabela_saida,"%s|", matriz_entrada[i].coluna[j]);
      }
    }
  }
  free(matriz_entrada);

  fclose(tabela_entrada);
  fclose(tabela_saida);

  remove(nome_tabela_alvo); //Excluindo tabela original
  rename("novatabela.txt",nome_tabela_alvo); //Renomeando a nova tabela para o nome original

  printf("\nLinha removida.\n");
//// FIM - DELETAR LINHA////
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
  char nome_apagar[55];
  printf("=== DELETANDO TABELA ===\n");
  printf("Nome da tabela: ");

  fgets(nome_apagar, 51, stdin);

//// APAGANDO DA LISTA DE TABELAS ////
  char linha[151];
  int existe_tabela = 0;
  while (fgets(linha, 150, arqivo_entrada) != NULL)
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
  existe_tabela == 0 ? printf("\nTabela nao encontrada. Encerrando operacao.\n") : printf("Tabela removida.\n");
//// FIM - DELETAR TABELA////
}
