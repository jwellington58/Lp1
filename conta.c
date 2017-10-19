//Arquivo com funções e estruturas de "conta"
typedef struct{
  int id_conta, numero_conta,variacao, id_cliente;
  double saldo;
}Conta;

struct No_Conta{
  Conta valor;
	struct No_Conta *prox;
};

//Função de inserir na Lista No_Conta
void inserir_No_Conta(struct No_Conta *lista, Conta e){
  struct No_Conta *novoNo = malloc(sizeof(struct No_Conta));
  novoNo->valor = e;
  novoNo->prox = lista->prox;
  lista->prox = novoNo;
}
//Função que retorna a quantidade de contas do cliente
int quantidade_De_Contas_Por_Cliente(struct No_Conta *lista, int id_cliente){
    struct No_Conta *aux = lista->prox;
    int qtd_Contas = 0;
    while (aux != NULL){
      if(id_cliente==aux->valor.id_cliente){
        qtd_Contas++;
      }
      aux = aux->prox;
    }
    return qtd_Contas;
}
//Função que determina o saldo das contas
void saldo_conta_Por_Transacao(struct No_Conta *lista, struct No_Transacao *lista_Transacao){
    lista->valor.saldo = 0;
    struct No_Transacao *aux = lista_Transacao->prox;
    //Percorre toda a lista de transações e verifica se id da conta é igual a conta origem ou destino daí atribui o valor ou decrementa
    while (aux != NULL) {

      if(lista->valor.id_conta==aux->valor.id_conta_destino){
        lista->valor.saldo += aux->valor.valor;
      }
      else if(lista->valor.id_conta==aux->valor.id_conta_origem){
        lista->valor.saldo -= aux->valor.valor;

      }
      aux = aux->prox;
    }
}
//Função que percorre todos os nos da lista de contas e chama a função para atribuir o saldo a esta conta
void saldo_conta(struct No_Conta *lista, struct No_Transacao *lista_Transacao){
  struct No_Conta *aux = lista->prox;

  while(aux!=NULL){
    //(conta.c)
    saldo_conta_Por_Transacao(aux,lista_Transacao);
    aux = aux->prox;
  }

}

 //Função que lista as contas do cliente
void saldoPrint(struct No_Conta *lista_Conta, struct No_Cliente *lista_Cliente){
  struct No_Conta *aux = lista_Conta->prox;

  while(aux!=NULL){

    if(aux->valor.id_cliente == lista_Cliente->valor.id_cliente){
      printf("|Numero da conta: %d||Variacao: %d||Saldo: %.2lf|\n",aux->valor.numero_conta,aux->valor.variacao ,aux->valor.saldo );
    }
    aux = aux->prox;
  }
  printf("||Saldo Total: %.2lf||\n", lista_Cliente->valor.saldo_total_cliente);
}
//função que diz o saldo total do cliente se a conta pertencer ao cliente o valor da conta é atribuido
//ao saldo total do cliente que representado por uma variavel do struct Cliente
void saldo_total(struct No_Conta *lista_Conta, struct No_Cliente *lista_Cliente){

  struct No_Conta *aux_conta = lista_Conta->prox;
  double saldo_total = 0;
  while (aux_conta!=NULL){
    if(lista_Cliente->valor.id_cliente==aux_conta->valor.id_cliente){
      saldo_total += aux_conta->valor.saldo;
    }
    aux_conta = aux_conta->prox;
    }
    lista_Cliente->valor.saldo_total_cliente = saldo_total;
}



//Função que recebe o numero de uma conta e retorna o id da conta
void num_Para_Id(struct No_Conta *lista_Conta, int num, int *id){
  struct No_Conta *aux_Conta  = lista_Conta->prox;
  while (aux_Conta != NULL){
    if(aux_Conta->valor.numero_conta == num){
      *id = aux_Conta->valor.id_conta;
      id++;
    }
    aux_Conta = aux_Conta->prox;
    /* code */
  }


}


//Função que busca a conta com variação 000 de acordo com o cliente passado e chama a função para exibir a fatura de cartao de credito dessa conta
void buscar_Conta(Cliente cliente, struct No_Conta *lista_Conta, struct No_Transacao_Cartao *lista_Transacao_Cartao, int mes, int ano, FILE *fileW, double *total){

    struct No_Conta *aux_Conta = lista_Conta->prox;
    int cont = 0;
    fprintf(fileW,"Fatura do mes: %d/%d\n Cliente: %s\n",mes, ano, cliente.nome);
    while (aux_Conta!=NULL){
        if(cliente.id_cliente == aux_Conta->valor.id_cliente && (aux_Conta->valor.variacao == 0)){
        //Função que escreve em um arquivo a fatura de um determinado mes de um cliente (transacao_cartao.c)
        exibir_Transacoes_Cartao_Credito(aux_Conta->valor, lista_Transacao_Cartao, mes, ano, fileW, total);
        cont = 1;

      }
      aux_Conta = aux_Conta->prox;
    }
    if(cont == 0){
      printf("Conta nao encontrada\n");
    }
}

//função que verifica se a conta pertence ao cliente (funicionalidade 4 e 5)
void validacao(struct No_Conta *lista_Conta, int id_cliente, int conta, int *validador){
  struct No_Conta *aux_Conta = lista_Conta->prox;

  while(aux_Conta !=NULL){
    if(aux_Conta->valor.numero_conta == conta && aux_Conta->valor.id_cliente == id_cliente){
      *validador = 1;
    }
    aux_Conta = aux_Conta->prox;
  }

}
