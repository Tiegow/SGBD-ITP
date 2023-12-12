# SGBD-ITP
Implementação de um Sistema de Gerenciamento de Banco de Dados. Explorarando os conceitos abordados na disciplina ITP, do curso de TI UFRN.
# Sobre o Projeto
O projeto consiste em implementar um Sistema de Gerenciamento de Banco de Dados (SGBD) simplificado baseado no modelo relacional. Não é o objetivo desse projeto criar um SGBD para ser utilizado em produção por sistemas de informação, mas “apenas” explorar os conceitos abordados na disciplina ITP. O SGBD ITP (nome dado ao SGBD simplificado) deverá ser capaz de realizar uma série de operações.
# Funcionamento e Operações
Com o SGBD, o usuário pode criar e manipular tabelas, a fim de armazenar e gerenciar dados. O arquivo **final.exe** é responsável por executar o programa. As tabelas são armazenadas em arquivos de texto, que são salvos na pasta em que se encontra o arquivo executável.

Crie uma pasta para guardar o arquivo final.exe junto das tabelas. É possível que as tabelas não sejam reconhecidas caso estejam em um diretório diferente de final.exe.

- ## Sobre o código
  O código é modularizado em três partes: main.c, funcsP.c e funcsS.c. A função **main** é resoponsável apenas por receber do usuário as operações que ele deseja realizar e fazer as chamadas das suas respectivas funções. Para cada operação existe uma função em **funcsP** (funções principais). Algumas funções principais precisam de outras funções secundárias para funcionarem, que separamos em **funcsS**.
- ## Sobre as tabelas
  Cada tabela criada é um arquivo de texto, escrito em um formato específico que facilita a leitura dos dados pelo programa. Não altere os arquivos de texto manualmente, ou pode encontrar problemas na hora de executar as operações do SGBD.

  Para facilitar a manipulação de tabelas, foi criado uma struct simples, chamada **linha_de_matriz**. A struct representa uma única linha de uma matriz, onde cada coluna guarda uma string (ou seja, um vetor de strings). A struct permite criar matrizes de strings (matriz tridimensional) de forma mais amigável, que servem para coletar temporariamente todos os dados de uma tabela e executar operações de forma mais fácil do que manipular diretamente o arquivo de texto da tabela. No arquivo de cabeçalho funcs.h é possivel ver todas as assinaturas de funções e struct scriadas.

  Uma vez criada uma matriz tridimensional, a função secundária **reconhecer_tabela** pode ser usada para preencher a matriz com os dados salvos em texto no arquivo da tabela. A função tem como argumentos o ponteiro para o arquivo da tabela, a quantidade de linhas da tabela, a quantidade de colunas e a matriz a ser preenchida:
  ```
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
      //A função vai "retornar" a matriz resultante com os dados preenchidos
  }
  ```
Executando o programa você deve se deparar com a interface inicial do SGBD ITP, que apresenta as sete operações principais disponíveis durante a execução. Na interface principal, o usuário deve inserir o número correspondente a operação que quer executar (1 a 7, e 0 para encerrar)
- ## Criar Tabela
  O programa pedirá que o usuário nomeie a nova tabela, em seguida, solicitará a quantidade de colunas que a tabela deve ter. A partir desse ponto, se o usuário forneceu as informações necessárias corretamente, o arquivo de texto "tabelas.txt" é criado (ou alterado, caso já exista). Esse arquivo apenas lista as tabelas já criadas.

  Adicionando tabela na lista de tabelas:
  
  ```
  FILE *lista_tabelas;
  lista_tabelas = fopen("tabelas.txt","a"); //Abrindo arquivo da lista de tabelas para escrita
  
  if(lista_tabelas == NULL)
  {
    printf("\nErro ao abrir arquivo.\n");
    return;
  }

  fprintf(lista_tabelas, "%s\n", nome_tabela); //Registrando o nome da nova tabela
  fclose(lista_tabelas);
  ```
  Em seguida, é criado o arquivo de texto que vai receber as informações da tabela. O programa pedirá do usuário os nomes da coluna de chave primária e de cada uma das outras colunas criadas. No fim do processo, a tabela está feita e pronta para ser manipulada.

  Salvando as informações da tabela:
  
  ```
  fprintf(arquivo_tabela, "0 %d\n", qtd_colunas); //Salvando no arquivo a quantidade de linhas e colunas da tabela
  
  char nome_nova_coluna[21];
  for(int i = 0; i < qtd_colunas; i++) //Recebendo os nomes de cada coluna
  {
    fgets(nome_nova_coluna, 21, stdin);
  
    nome_nova_coluna[strcspn(nome_nova_coluna, "\n")] = 0; //Eliminando '\n' no fim da string
    fprintf(arquivo_tabela, "%s|", nome_nova_coluna); //Escrevendo a coluna no arquivo da tabela
  }
  ```
  A nova tabela estará representada em texto, registradas a quantidade de linhas, a quantidade de colunas e os nomes das colunas, parecido com o seguinte:
  ```
  0 3
  ID|Nome|Idade|
  ```
- ## Listar tabelas
  Essa função usa o arquivo tabelas.txt para apresentar na interface as tabelas disponíveis. Caso não exista nenhuma tabela, isso também é informado.
  
  Esse processo acontece dessa forma:
  ```
  /// Lendo a lista de tabelas ///
  
    if(fgets(linha, 150, lista) == NULL) //Se não houver nada na primeira linha, informa que não existem tabelas
    {
      printf("\nNehuma tabela encontrada.\n");
      fclose(lista);
      remove("tabelas.txt");
    }else
    {
      printf("\n=== Tabelas criadas ===\n");
      printf("%s", linha);
      while (fgets(linha, 150, lista) != NULL) //Apresenta todas as linhas com os nomes das tabelas
      {
        printf("%s", linha);
      }
    }
  ```
- ## Criar linhas na tabela
  Com uma tabela já criada é possível adicionar linhas por meio dessa operação. O programa solicitará o nome da tabela a ser manipulada e a quantidade de linhas que o usuário pretende adicionar. As novas linhas logo serão adicionadas uma por uma.

  Para cada linha, o usuário deverá digitar os dados que deseja armazenar em cada coluna, começando sempre pela coluna de chave primária e seguindo para as próximas colunas. A chave primária deve ser **obrigatoriamente** um inteiro não negativo e **não pode se repetir**.

  As novas linhas são salvas no arquivo de texto referente a tabela da seguinte forma:
  ```
  2 3
  ID|Nome|Idade|
  1|Gustavo|57|
  2|Tiego|88|
  ```
- ## Listar os dados da tabela
  A função **listar_dados_tabela** recebe como argumento o nome da tabela que o usuário deseja visualizar os dados. Essa operação faz uso da matriz tridimensional de caracteres, desenvolvida para a função secundária mencionada anteriormente (reconhecer_tabela), para mostrar na interface todos os dados das linhas e colunas da tabela.
  ```
  int qtd_linhas, qtd_colunas;
  fscanf(tabela,"%d %d\n", &qtd_linhas, &qtd_colunas); //Atribuindo a quantidade de linhas e colunas da tabela
  qtd_linhas++;

  linha_de_matriz nova_matriz[qtd_linhas]; //Declarando uma matriz com a quantidade de linhas da tabela escolhida
  reconhecer_tabela(tabela, qtd_linhas, qtd_colunas, nova_matriz); 

  for(int i = 0; i < qtd_linhas; i++)
  {
    for(int j = 0; j < qtd_colunas; j++)
    {
      printf("%s|", nova_matriz[i].coluna[j]); //Apresenta o dado em string de cada coluna
    }
  }
  ```
- ## Pesquisar valores na tabela
  A pesquisa de valores em uma tabela é feita por coluna, ou seja, só é possível pesquisar por valores de uma mesma coluna na tabela. Como a maioria das outras funções, essa vai solicitar a tabela alvo. Logo em seguida, o usuario verá na interface as colunas da tabela e deverá digitar o nome da coluna para fazer a pesquisa de valores. Não é possível realizar pesquisas em tabelas vazias (sem linhas).

  A função **reconhecer_tabela** vai se encarregar de passar os dados para uma matriz, que vai ser usada para pesquisar os valores.

  Selecionadas a tabela e a coluna, a interface apresentará várias opções de pesquisa. O programa usa uma estrutura de switch para permitir que o usuário pesquise por:
  - 1 - Valores maiores que o valor informado
  - 2 - Valores maiores ou iguais ao valor informado
  - 3 - Valores iguais ao valor informado
  - 4 - Valores menores que o valor informado
  - 5 - Valores menores ou iguais ao valor informado
  - 6 - Valores próximos ao valor informado (strings)
    
  No caso 6, foi determinado que uma string é próxima da outra quando a primeira metade delas são iguais:
  
  ```
  case 6:
  printf("\n>>> Valores em %s proximos a %s:\n", nome_coluna_alvo, valor_palavra_pesquisa);
  int proximidade = strlen(valor_palavra_pesquisa)/2; //A proximidade é a metade do tamanho da string

  for(int i = 1; i < qtd_linhas; i++)
  {
    if(strncmp(tabela_matriz[i].coluna[posicao_coluna_alvo],valor_palavra_pesquisa,proximidade) == 0) //Compara strings até a metade
    {
      printf("%s;\n", tabela_matriz[i].coluna[posicao_coluna_alvo]); //Mostra na interface o valor pesquisado
    }
  }
  break;
  ```
  - **Observação:** Na matriz que guarda os dados da tabela, todos os valores são strings. Portanto, foi desenvolvido um método para reconhecer caso determinada coluna se trata de uma coluna de numeros (double) ou uma coluna de palavras (string). Para isso, o programa usa a função strtod(), da biblioteca "stdlib" para verificar se uma string pode ser convertida para número.

    O primeiro elemento da coluna vai ser testado. Se for um número, aquela coluna será considerada uma coluna de números. A função cria um vetor de numeros double para representar a coluna e fazer as pesquisas com base em numeros:
  ```
  // Tentando Identificar a "natureza" da coluna //
  int tipo_numero;
  double teste; //Numero retornado na strtod
  char *endptr;

  int qtd_numeros = qtd_linhas-1;
  double coluna_de_numeros[qtd_numeros]; //Vetor de numeros double

  teste = strtod(tabela_matriz[1].coluna[posicao_coluna_alvo], &endptr); //Testa se a string pode ser um numero (double)

  if(teste == 0)
  {
    tipo_numero = 0; //A coluna não é de numeros
  } 
  else
  {
    int j = 0;
    for(int i = 1; i < qtd_linhas; i++) //Atribuindo os numeros da coluna ao vetor de numeros
    {
      teste = strtod(tabela_matriz[i].coluna[posicao_coluna_alvo], &endptr);
      coluna_de_numeros[j] = teste;
      j++;
    }
    tipo_numero = 1;
  }
  ```
  Com isso, o programa sabe se deve fazer pesquisas de numeros, usando operadores relacionais numericos (<, >, ==, etc.) ou usando comparação de strings (strcmp).
