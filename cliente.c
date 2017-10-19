 //Arquivo com as funçoes e as estruturas que guardam os dados dos "Clientes"
typedef struct{
  int id_cliente;
  char nome[50];
  char cpf[20];
  char telefone[50];
  char municipio[50];
  char estado[50];
  double saldo_total_cliente;
}Cliente;

struct No_Cliente{
  Cliente valor;
	struct No_Cliente *prox;
  //double saldo_total;
};

//Função de inserir na Lista No_Cliente
void inserir_No_Cliente(struct No_Cliente *lista, Cliente e){
  struct No_Cliente *novoNo = malloc(sizeof(struct No_Cliente));
  novoNo->valor = e;
  novoNo->prox = lista->prox;
  lista->prox = novoNo;
}
//Função que busca todos clientes relacionados ao estado passado pelo cliente//
void buscarPorEstado(struct No_Cliente *lista, char estado[50], struct No_Conta *lista_Conta){
  struct No_Cliente *aux = lista->prox;
  int qtd = 0;
  //Percorre a lista até o final
  while(aux != NULL){
    //Se o estado passado pelo cliente for igual ao estado do cliente o programa entra no if
    if(!strcmp(aux->valor.estado,estado)){
      printf("|Cliente: %s||ID: %d||Cpf: %s||telefone: %s||Municipio: %s||Total de contas: %d||\n\n", aux->valor.nome, aux->valor.id_cliente, aux->valor.cpf, aux->valor.telefone, aux->valor.municipio, quantidade_De_Contas_Por_Cliente(lista_Conta, aux->valor.id_cliente));
      qtd++;
    }
    aux = aux->prox;
  }
  //Se qtd é igual a zero é pq não existem clientes nesse Estado
  if(qtd==0){
    printf("Nao existem clientes nesse Estado\n");
  }
}

//Função que retorna o cliente de acordo com o numero do cpf
void buscaPorCpf(struct No_Cliente *lista_Cliente, char cpf[20], struct No_Conta *lista_Conta){
  struct No_Cliente *aux = lista_Cliente->prox;
  double total = 0;
  int qtd = 0;
  while(aux!=NULL){
    if(!strcmp(aux->valor.cpf,cpf)){
      printf("|Cliente: %s||ID: %d||Cpf: %s||telefone: %s||Municipio: %s|\n", aux->valor.nome, aux->valor.id_cliente, aux->valor.cpf, aux->valor.telefone, aux->valor.municipio);
      printf("|--------------------Listagem das Contas--------------------|\n" );
      saldoPrint(lista_Conta, aux);

      qtd++;
    }
    aux = aux->prox;
  }
  if(qtd==0){
    printf("CPF nao encontrado\n");
  }

}

//Função que calcula o saldo total para todos os clientes
void calcula_saldo(struct No_Cliente *lista_Cliente, struct No_Conta *lista_Conta){
  struct No_Cliente *aux = lista_Cliente->prox;
  while (aux!=NULL){
    //(conta.c)
    saldo_total(lista_Conta,aux);
    aux = aux->prox;
  }
}

//Função que ordena a lista de clientes pelo saldo total
void ordenar_Por_Saldo(struct No_Cliente *lista_Cliente){
  printf("ordenando cliente...\n");
  struct No_Cliente *No_fim = NULL;
  while (lista_Cliente->prox != No_fim) {
    struct No_Cliente *ant_aux = lista_Cliente;
    struct No_Cliente *aux = lista_Cliente->prox;
    while (aux->prox != No_fim) {
      if(aux->valor.saldo_total_cliente < aux->prox->valor.saldo_total_cliente){
        struct No_Cliente *auxTroca = aux;
        aux = aux->prox;
        auxTroca->prox = auxTroca->prox->prox;
        ant_aux->prox = aux;
        aux->prox = auxTroca;
        ant_aux = aux;
        aux = auxTroca;
      }
      else{
      ant_aux = aux;
      aux = aux->prox;
    }
  }
    No_fim = aux;  /* code */
  }

}

//Função que exibe o saldo de todos os clientes em ordem decrecente
void exibir_Todos_Clientes(struct No_Cliente *lista_Cliente){
  struct No_Cliente *aux_Cliente = lista_Cliente->prox;

  while (aux_Cliente!=NULL) {

    printf("||Nome: %s||Cpf: %s||Saldo total %.2lf||\n", aux_Cliente->valor.nome, aux_Cliente->valor.cpf, aux_Cliente->valor.saldo_total_cliente);
    aux_Cliente = aux_Cliente->prox;
  }
}


//Função que procura o cliente passado pelo filtro e chama a função para achar a conta com variação 000
void buscar_Cliente(struct No_Cliente *lista_Cliente, struct No_Conta *lista_Conta, struct No_Transacao_Cartao *lista_Transacao_Cartao, char cpf[20], int mes, int ano, FILE *fileW, double *total){

  struct No_Cliente *aux_Cliente = lista_Cliente->prox;
  int cont = 0;
  while (aux_Cliente!=NULL){
    if(!strcmp(aux_Cliente->valor.cpf,cpf)){
      //(conta.c) Depois que o cliente é achado a lista de contas é percorrida para que posam ser achadas as contas do cliente
      buscar_Conta(aux_Cliente->valor, lista_Conta, lista_Transacao_Cartao, mes, ano, fileW,  total);
      cont = 1;
      break;
    }
    aux_Cliente = aux_Cliente->prox;
  }
  if(cont==0){
    printf("Cliente nao encontrado\n");
  }
}

//Função que faz a validação da conta pelo cpf do cliente
void valida_Conta(struct No_Cliente *lista_Cliente, struct No_Conta *lista_Conta, char cpf[20], int conta, int *validador){
  struct No_Cliente *aux_Cliente = lista_Cliente->prox;

  while (aux_Cliente != NULL){
    if(!strcmp(aux_Cliente->valor.cpf, cpf)){
      //(conta.c)
      validacao(lista_Conta, aux_Cliente->valor.id_cliente, conta, validador);
    }
    aux_Cliente = aux_Cliente->prox;
  }
}
