
 //Arquivo com as funçoes e as estruturas que guardam os dados das "Transaçoes"
typedef struct{
  struct tm data;
  //char data[15];
  int id_operacao, id_conta_origem, id_conta_destino;
  double valor;

}Transacao;

struct No_Transacao{
  Transacao valor;
	struct No_Transacao *prox;
};
//Função de inserir na Lista No_Transacao
void inserir_No_Trasacao(struct No_Transacao *lista, Transacao e){

  struct No_Transacao *novoNo = malloc(sizeof(struct No_Transacao));
  novoNo->valor = e;
  novoNo->prox = lista->prox;
  lista->prox = novoNo;

}

//Função que ordena transações por ano,mês e dia
void ordena_trasacoes(struct No_Transacao *lista_Transacao){
    printf("ordenando transacao...\n");
    struct No_Transacao *No_fim = NULL;
    while (lista_Transacao->prox != No_fim) {
      struct No_Transacao *ant_aux = lista_Transacao;
      struct No_Transacao *aux = lista_Transacao->prox;
      while (aux->prox != No_fim) {
        //Verifica se os dias da data do aux é maior do que os dias da data do aux->prox
        if(converte_Para_Dia(aux->valor.data) > converte_Para_Dia(aux->prox->valor.data)){
          struct No_Transacao *auxTroca = aux;
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
//Função que retorna o saldo da conta de um cliente de acordo com uma data MM/aaaa
void saldo_Por_Data(struct No_Transacao *lista_Transacao, int id_conta[], int ano, int mes){
  struct No_Transacao *aux_trasacao = lista_Transacao->prox;
  double saldo = 0;
  int tudo_em_meses;
  //Recebe a data mes e ano toda em meses (data.c)
  int tudo_em_meses_atual = converte_Para_Mes(mes, ano);
  while (aux_trasacao!=NULL) {
    //Recebe a data mes e ano toda em meses (data.c)
    tudo_em_meses = converte_Para_Mes(aux_trasacao->valor.data.tm_mon,aux_trasacao->valor.data.tm_year);
    //Se a data da transacao for menor igual que a data passada como parametro
    //Ou conta_origem ou conta_destino igual a uma das variações da conta
    //entra no if
    if( tudo_em_meses <=  tudo_em_meses_atual &&(aux_trasacao->valor.id_conta_origem == id_conta[0] || aux_trasacao->valor.id_conta_destino == id_conta[0] || aux_trasacao->valor.id_conta_origem == id_conta[1] || aux_trasacao->valor.id_conta_destino == id_conta[1] || aux_trasacao->valor.id_conta_origem == id_conta[2] || aux_trasacao->valor.id_conta_destino == id_conta[2])){
        if(aux_trasacao->valor.id_conta_origem == id_conta[0] || aux_trasacao->valor.id_conta_origem == id_conta[1] || aux_trasacao->valor.id_conta_origem == id_conta[2]){
          saldo = saldo - aux_trasacao->valor.valor;

        }
        if(aux_trasacao->valor.id_conta_destino == id_conta[0] || aux_trasacao->valor.id_conta_destino == id_conta[1] || aux_trasacao->valor.id_conta_destino == id_conta[2]){

          saldo = saldo + aux_trasacao->valor.valor;
          }
    }
    aux_trasacao = aux_trasacao->prox;
  }
  printf("||Saldo: %.2lf||\n", saldo);
}
//Função que exibi toda.s as transações de uma determinada conta
void exibir_Transacoes(struct No_Transacao *lista_Transacao, int id_conta[], int mes, int ano){
  struct No_Transacao *aux_trasacao = lista_Transacao->prox;
  int cont = 0;
  while(aux_trasacao != NULL){
    //Se a data da transacao for igual  a data passada como parametro
    //Ou conta_origem ou conta_destino igual a uma das variações da conta
    //entra no if
    if(aux_trasacao->valor.data.tm_year == ano && aux_trasacao->valor.data.tm_mon == mes &&(aux_trasacao->valor.id_conta_origem == id_conta[0] || aux_trasacao->valor.id_conta_destino == id_conta[0] || aux_trasacao->valor.id_conta_origem == id_conta[1] || aux_trasacao->valor.id_conta_destino == id_conta[1] || aux_trasacao->valor.id_conta_origem == id_conta[2] || aux_trasacao->valor.id_conta_destino == id_conta[2])){
      if(aux_trasacao->valor.id_conta_origem == id_conta[0] || aux_trasacao->valor.id_conta_origem == id_conta[1] || aux_trasacao->valor.id_conta_origem == id_conta[2]){
        printf("||Data: %d/%d/%d||Valor: %.2lf\n",aux_trasacao->valor.data.tm_mday, aux_trasacao->valor.data.tm_mon, aux_trasacao->valor.data.tm_year, aux_trasacao->valor.valor * -1);
        cont++;
      }
      if(aux_trasacao->valor.id_conta_destino == id_conta[0] ||  aux_trasacao->valor.id_conta_destino == id_conta[1] || aux_trasacao->valor.id_conta_destino == id_conta[2]){
        printf("||Data: %d/%d/%d||Valor: %.2lf||\n", aux_trasacao->valor.data.tm_mday, aux_trasacao->valor.data.tm_mon, aux_trasacao->valor.data.tm_year,aux_trasacao->valor.valor);
        cont++;
      }
    }
    aux_trasacao = aux_trasacao->prox;
  }
  if(cont==0){
    printf("Nao foram realizadas transacoes nesse mes\n");
  }
}
