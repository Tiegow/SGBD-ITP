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
