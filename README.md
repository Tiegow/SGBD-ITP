# SGBD-ITP
Implementação de um Sistema de Gerenciamento de Banco de Dados. Explorarando os conceitos abordados na disciplina ITP, do curso de TI UFRN.
# Sobre o Projeto
O projeto consiste em implementar um Sistema de Gerenciamento de Banco de Dados (SGBD) simplificado baseado no modelo relacional. Não é o objetivo desse projeto criar um SGBD para ser utilizado em produção por sistemas de informação, mas “apenas” explorar os conceitos abordados na disciplina ITP. O SGBD ITP (nome dado ao SGBD simplificado) deverá ser capaz de realizar uma série de operações.
# Funcionamento e Operações
Com o SGBD, o usuário pode criar e manipular tabelas, a fim de armazenar e gerenciar dados. O arquivo **final.exe** é responsável por executar o programa. As tabelas são armazenadas em arquivos de texto, que são salvos na pasta em que se encontra o arquivo executável.

Crie uma pasta para guardar o arquivo final.exe junto das tabelas. É possível que as tabelas não sejam reconhecidas caso estejam em um diretório diferente de final.exe.

- ## Sobre o código
  O código é modularizado em três partes: main.c, funcsP.c e funcsS.c. A função **main** é resoponsável apenas por receber do usuário as operações que ele deseja realizar e fazer as chamadas das suas respectivas funções. Para cada operação existe uma função em **funcsP** (funções principais). Algumas funções principais precisam de outras funções secundárias para funcionarem, que separamos em **funcsS**.

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
