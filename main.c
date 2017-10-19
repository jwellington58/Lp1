//Arquivo principal do projeto
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.c"
#include "transacao.c"
#include "cliente.c"
#include "conta.c"
#include "transacao_cartao.c"
#include "operacao.c"
#include "manipulacao.c"


int main(){
  //variavel do tipo FILE usada para a manipulação de arquivos. Mais especificamente leitura
  FILE *file = fopen("arquivo.txt", "r");
  //variavel para escrita da fatura no arquivo txt
  FILE *fileW;

  int n, num_conta,m,a;
  //Ponteito que apontara para o endereço de memoria de um vetor que armazenará os ids de todas as variações de uma conta da funcionalidade 5 e 4
  int *id;
  //Variavel que armazenará o valor 1 caso a conta passada na 4 e 5 pertença ao cpf passado e 0 se não pertencer
  int validador;
  double total;
  //vetor que armazenará os ids de todas as variações de uma conta da funcionalidade 5 e 4
  int vetor[3],z;
  for(z=0;z<3;z++){
    vetor[z] = -1;
  }
  char cpf[20];
  char estado[3];
  //Declaração da Lista de Transação (transacao.c)
  struct No_Transacao *lista_Transacao = malloc(sizeof(struct No_Transacao));
	lista_Transacao->prox = NULL;
  //Declaração a Lista de Cliente (cliente.c)
  struct No_Cliente *lista_Cliente = malloc(sizeof(struct No_Cliente));
	lista_Cliente->prox = NULL;
  //Declaração da Lista de Operações (operecao.c)
  struct No_Operacao *lista_Operacao = malloc(sizeof(struct No_Operacao));
	lista_Operacao->prox = NULL;
  //Declaração da lista de contas (conta.c)
  struct No_Conta *lista_Conta = malloc(sizeof(struct No_Conta));
	lista_Conta->prox = NULL;
  //Declaração da Lista de Transações com cartão de credito (transacao_cartao.c)
  struct No_Transacao_Cartao *lista_Transacao_Cartao = malloc(sizeof(struct No_Transacao_Cartao));
	lista_Transacao_Cartao->prox = NULL;
  //Chamada da função que ler as trnasações do arquivo (manipulacao.c)
  lerTransacao(file, lista_Transacao);
  //Chamada da função que ler as contas do arquivo (manipulacao.c)
  lerConta(file, lista_Conta);
  //Chamada da funçao que ler os clientes do arquivo (manipulacao.c)
  lerCliente(file,lista_Cliente);
  //Chamada da função que ler as operações presentes no arquivo (manipulacao.c)
  lerOperacao(file, lista_Operacao);
  //Chamada da função que ler as transacoes_cartao_credito presentes no arquivo (manipulacao.c)
  lerTransacaoCartao(file, lista_Transacao_Cartao);
  //Funçao que calcula o saldo das contas ((conta.c))
  saldo_conta(lista_Conta,lista_Transacao);
  //Função que calcula o saldo total do cliente (cliente.c)
  calcula_saldo(lista_Cliente,lista_Conta);
  //chamada da função que ordena as transações por data (transacao.c)
  ordena_trasacoes(lista_Transacao);
  //Chamada da função que ordena as transaçoes de cartao de credito (transacao_cartao.c)
  ordena_trasacoes_cartao_credito(lista_Transacao_Cartao);
  //Função que ordena a lista de clientes pelo saldo (cliente.c)
  ordenar_Por_Saldo(lista_Cliente);
  //Menu principal do projeto
  do{
    printf(" ________________________________________________________\n");
    printf("|Digite 1 para perquisar cliente por estado              |\n");
    printf("|Digite 2 para perquisar saldo de um cliente             |\n");
    printf("|Digite 3 para listar saldo de todos clientes            |\n");
    printf("|Digite 4 para perquisar o extrato no mes atual          |\n");
    printf("|Digite 5 para listar as transacoes de um mes especifico!|\n");
    printf("|Digite 6 para gerar fatura                              | \n");
    printf("|Digite 0 para sair!                                     |\n");
    printf("|________________________________________________________|\n");
    scanf("%d", &n);

    if(n==1){
      printf("Digite o estado no qual voce deseja buscar clientes em letra MAIUSCULA\n");
      scanf("%s", estado);
      //Chamada da função que faz a busca de clientes por Estado (cliente.c)
      buscarPorEstado(lista_Cliente, estado,lista_Conta);
    }
    else if(n==2){
      printf("Digite o cpf do cliente que você deseja buscar \n");
      scanf("%s", cpf);
      //Função que busca cliente por CPF (cliente.c)
      buscaPorCpf(lista_Cliente,cpf,lista_Conta);
    }
    else if(n==3){
      //Funçao que exibi todos os clientes (cliente.c)
      exibir_Todos_Clientes(lista_Cliente);
    }
    else if(n==4){
      //Chamada da função que retorna um ponteiro de struct tm com a data atual (data.c)
      struct tm *atual = MesAtual();
      printf("%d/%d\n", atual->tm_mon, atual->tm_year);
      printf("Digite o CPF do cliente\n");
      scanf("%s", cpf);
      printf("Digite a conta que voce deseja listar:\n");
      scanf("%d", &num_conta);
      //(cliente.c) função que verifica se a conta informada pertence ao cliente passado,
      //se pertencer um ponteiro que aponta para o valor de validador receberá 1 se não continuara em 0
      validador = 0;
      valida_Conta(lista_Cliente, lista_Conta, cpf, num_conta, &validador);
      if(validador ==1){
        //Função que retorna o id de uma conta atraves do numero da conta
        //Todas as variações dessa conta são armazenadas em um vetor atraves de um ponteiro que aponta para o primeiro indice do vetor
        id = &vetor[0];
        //(conta.c)
        num_Para_Id(lista_Conta, num_conta, id);
        printf("Saldo do mes anterior:\n");
        if(atual->tm_mon > 1){
            //Função que exibi o saldo da conta de acordo com o ano, mes e id passado (transacao.c)
            saldo_Por_Data(lista_Transacao, vetor, atual->tm_year, atual->tm_mon - 1);
        }
        else if(atual->tm_mon == 1){
            //Função que exibi o saldo da conta de acordo com o ano, mes e id passado (transacao.c)
            saldo_Por_Data(lista_Transacao, vetor, atual->tm_year - 1, 12);
        }
        printf("Saldo do mes atual:\n");
        //Função que exibi o saldo da conta de acordo com o ano, mes e id passado (transacao.c)
        saldo_Por_Data(lista_Transacao, vetor, atual->tm_year, atual->tm_mon);
        printf("Listagem das transações do mes atual:\n");
        exibir_Transacoes(lista_Transacao, vetor, atual->tm_mon, atual->tm_year);//(transacao.c)
      }
      else{
        printf("Essa conta nao pertence a esse cliente\n");
      }
    }else if(n==5){


      printf("Digite o CPF do cliente\n");
      scanf("%s", cpf);
      printf("Digite a conta que voce deseja listar:\n");
      scanf("%d", &num_conta);
      printf("Digite uma data no formato MM/aaaa\n");
      scanf("%d/%d", &m,&a);

      validador = 0;
      //(cliente.c) função que verifica se a conta informada pertence ao cliente passado,
      //se pertencer um ponteiro que aponta para o valor de validador receberá 1 se não continuara em 0
      valida_Conta(lista_Cliente, lista_Conta, cpf, num_conta, &validador);
      if(validador ==1){
        //Função que retorna o id de uma conta atraves do numero da conta //(conta.c)
        //Todas as variações dessa conta são armazenadas em um vetor atraves de um ponteiro que aponta para o primeiro indice do vetor
        id = &vetor[0];                                                                    //id =1
        num_Para_Id(lista_Conta, num_conta, id);
        printf("Saldo do mes anterior:\n");
        if(m > 1){
            //Função que exibi o saldo da conta de acordo com o ano, mes e id passado (transacao.c)
            saldo_Por_Data(lista_Transacao, vetor, a, m - 1);
        }
        else if(m == 1){
            //Função que exibi o saldo da conta de acordo com o ano, mes e id passado (transacao.c)
            saldo_Por_Data(lista_Transacao, vetor, a - 1, 12);
          }
        printf("Saldo do mes atual:\n");
        //Função que exibi o saldo da conta de acordo com o ano, mes e id passado (transacao.c)
        saldo_Por_Data(lista_Transacao, vetor, a, m);
        printf("Listagem das transações do mes atual:\n");
        exibir_Transacoes(lista_Transacao, vetor, m, a);//(transacao.c)
      }
      else{
        printf("Essa conta nao pertence a esse cliente\n");
      }
    }
    else if(n==6){
      printf("Digite os CPF do cliente\n");
      scanf("%s",cpf);
      printf("Digite a data no formato MM/aaaa\n");
      scanf("%d/%d", &m, &a);
      fileW = fopen("fatura.txt", "w");

      //Variavel que vai ser apontada por um ponteiro que receberá o valor total da fatura;
      total = 0;
      //(cliente.c)
      buscar_Cliente(lista_Cliente, lista_Conta, lista_Transacao_Cartao, cpf, m, a, fileW, &total);
      fprintf(fileW,"||Total: %.2lf|| Minimo: %.2lf||\n",  total, total * 0.1);
      fclose(fileW);
    }


  }while (n!=0);

}
