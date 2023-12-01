#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void criar_tabela(void)
{
//// NOMEANDO TABELA ////
  char nome_tabela[55];
  printf("\e[1;1H\e[2J"); //Move o cursor para a linha 1, coluna 1 e limpa a interface

  printf("==== CRIAR TABELA ====\n");
  printf("Nome da tabela: ");

  fgets(nome_tabela, 51, stdin);
  nome_tabela[strcspn(nome_tabela, "\n")] = 0; //Eliminando '\n' no fim da string

//// CRIANDO OS CAMPOS(COLUNAS) DA TABELA ////
  int qtd_colunas;
  printf("--> Adicinando colunas\nQuantidade de colunas: ");
  scanf("%d", &qtd_colunas);
  getchar(); //Lidando com o '\n' no fim de scanf

  while(qtd_colunas <= 0)
  {
    printf("Quantidade de colunas invalida!\nDigite uma quantidade valida de colunas ou digite 0 para cancelar a operacao: ");
    scanf("%d", &qtd_colunas);

    if(qtd_colunas == 0)
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
    printf("Erro ao abrir arquivo.\n");
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
    printf("Erro ao abrir arquivo.\n");
    return;
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
  printf("\e[1;1H\e[2J"); 
  printf("Tabela criada.\n");

  fclose(arquivo_tabela);
//// FIM ////
}

void listar_tabelas(void)
{
  printf("\e[1;1H\e[2J");
  FILE *lista = fopen("tabelas.txt","r");
  if (lista == NULL)
  {
    printf("Nenhuma tabela encontrada.\n");
    return;
  }
  
  char linha[51];
  if(fgets(linha, 51, lista) == NULL)
  {
    printf("Nehuma tabela encontrada.\n");
    fclose(lista);
    remove("tabelas.txt");
  }else
  {
    printf("=== Tabelas criadas ===\n");
    printf("%s", linha);
    while (fgets(linha, 51, lista) != NULL)
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
  int quant_linhas;

  printf("\e[1;1H\e[2J");
  printf("<<<< ADCIONANDO LINHA >>>>\n");
  printf("Nome da tabela: ");
  
  fgets(nome_tabela, 51, stdin);
  nome_tabela[strcspn(nome_tabela, "\n")] = 0;
  strcat(nome_tabela, ".txt");

  printf("Digite a quantidade de linhas adcionais: ");
  scanf("%i", &quant_linhas);

  /// VERIFICANDO SE TABELA EXISTE ///
  FILE *arquivo_tabela1;
  arquivo_tabela1 = fopen(nome_tabela, "r");
  if(arquivo_tabela1 == NULL)
  {
    printf("Arquivo inexistente ou Erro ao abrir arquivo.");
    return;
  }

  /// COLETANDO QUANTIDADE DE COLUNAS ///
  int quant_colunas;
  fscanf(arquivo_tabela1, "0 %i\n", &quant_colunas);
  fclose(arquivo_tabela1);

  /// ADCIONANDO INFORMAÇÕES EM UMA NOVA LINHA ///
  FILE *arquivo_tabela2;
  arquivo_tabela2 = fopen(nome_tabela, "a");
  if(arquivo_tabela2 == NULL)
  {
    printf("Erro ao abrir arquivo.");
  }

  char info_coluna[50];
  int chave_primaria;
  
  while (quant_linhas > 0)
  {
    fprintf(arquivo_tabela2, "\n");

    for(int i = 0; i < quant_colunas; i++)
    {
      if(i == 0) 
      {
        printf("Chave primaria (coluna 1): ");
        scanf("%i", &chave_primaria); 
        getchar();
        fprintf(arquivo_tabela2, "%i ", chave_primaria);
      }
      else
      {
        printf("Coluna %i: ", i+1);
        fgets(info_coluna, 29, stdin);
        info_coluna[strcspn(info_coluna, "\n")] = 0;
        fprintf(arquivo_tabela2, "%s ", info_coluna);
      } 
    }

    quant_linhas--;
  }

  fclose(arquivo_tabela2);

  //FALTA ADCIONAR O ERRO QUANDO O USUÁRIO TENTA ADCIONAR UMA CHAVE PRIMÁRIA JÁ EXISTENTE EM UMA TABELA
}

void deletar_tabela(void)
{
  printf("\e[1;1H\e[2J");
  FILE *arqivo_entrada = fopen("tabelas.txt","r"); //Abrindo arquivo da lista de tabelas
  if (arqivo_entrada == NULL)
  {
    printf("Nenhuma tabela encontrada.\n");
    return;
  }
  FILE *arquivo_saida = fopen("outlist.txt","w"); //Criando novo arquivo modificado (sem a tabela a ser deletada)
  if (arquivo_saida == NULL)
  {
    printf("Erro ao abrir arquivo.\n");
    return;
  }

  listar_tabelas();
  char nome_apagar[51];
  printf("=== DELETANDO TABELA ===\n");
  printf("Nome da tabela: ");

  fgets(nome_apagar, 51, stdin);

//// APAGANDO DA LISTA DE TABELAS ////
  char linha[51];
  int existe_tabela = 0;
  while (fgets(linha, 51, arqivo_entrada) != NULL)
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
//// FIM ////
}