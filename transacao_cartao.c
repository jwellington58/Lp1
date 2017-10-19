//Arquivo com as funçoes e as estruturas que guardam os dados das "Transaçoes de Cartão de crédito"
typedef struct{
  char  descricao[50];
  struct tm data_compra;
  int id_conta, qtde_parcelas;
  double valor;
}Transacao_Cartao;

struct No_Transacao_Cartao{
  Transacao_Cartao valor;
	struct No_Transacao_Cartao *prox;
};

 //Função de inserir na Lista No_Transacao_Cartao
void inserir_No_Trasacao_Cartao(struct No_Transacao_Cartao *lista, Transacao_Cartao e){
  struct No_Transacao_Cartao *novoNo = malloc(sizeof(struct No_Transacao_Cartao));
  novoNo->valor = e;
  novoNo->prox = lista->prox;
  lista->prox = novoNo;
}

//Função que ordena as transações de cartão de crédito por data
void ordena_trasacoes_cartao_credito(struct No_Transacao_Cartao *lista_Transacao_Cartao){
    printf("ordenando transacao cartao...\n");
    struct No_Transacao_Cartao *No_fim = NULL;
    while (lista_Transacao_Cartao->prox != No_fim) {
      struct No_Transacao_Cartao *ant_aux = lista_Transacao_Cartao;
      struct No_Transacao_Cartao *aux = lista_Transacao_Cartao->prox;
      while (aux->prox != No_fim) {
        //Verifica se os dias da data do aux é maior do que os dias da data do aux->prox (data.c)
        if(converte_Para_Dia(aux->valor.data_compra) > converte_Para_Dia(aux->prox->valor.data_compra)){
          struct No_Transacao_Cartao *auxTroca = aux;
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


//Função que cria a fatura do cartao de credito de acordo com o cliente, conta mes e ano
void exibir_Transacoes_Cartao_Credito(Conta conta, struct No_Transacao_Cartao *lista_Transacao_Cartao, int mes, int ano, FILE *fileW, double *total){
    struct No_Transacao_Cartao *aux_trasacao_cartao = lista_Transacao_Cartao->prox;

    //Variavel que recebe uma data toda convetida em meses (data.c)
    int tudo_em_meses_atual = converte_Para_Mes(mes, ano);
    int tudo_em_meses, parcela, cont=0;


    while (aux_trasacao_cartao != NULL){
      //Variavel que recebe uma data toda convetida em meses (data.c)
      tudo_em_meses = converte_Para_Mes(aux_trasacao_cartao->valor.data_compra.tm_mon, aux_trasacao_cartao->valor.data_compra.tm_year);
      if((aux_trasacao_cartao->valor.id_conta == conta.id_conta) && ((tudo_em_meses_atual - tudo_em_meses) <= aux_trasacao_cartao->valor.qtde_parcelas)){
        parcela = tudo_em_meses_atual - tudo_em_meses;
        if(parcela > 0){
          fprintf(fileW,"||Data: %d/%d/%d||Descricao: %s||Valor: %.2lf||Parcela %d/%d||\n", aux_trasacao_cartao->valor.data_compra.tm_mday, aux_trasacao_cartao->valor.data_compra.tm_mon, aux_trasacao_cartao->valor.data_compra.tm_year, aux_trasacao_cartao->valor.descricao, aux_trasacao_cartao->valor.valor, parcela, aux_trasacao_cartao->valor.qtde_parcelas);
          //Ponteiro que recebe o total da fatura do cliente
          *total += aux_trasacao_cartao->valor.valor / aux_trasacao_cartao->valor.qtde_parcelas;
          cont++;
        }

      }

      aux_trasacao_cartao = aux_trasacao_cartao->prox;
      /* code */
    }

    if(cont != 0){
      printf("Fatura gerada com sucesso\n");
    }
    else{
      printf("Fatura gerada sem nenhuma conta\n");
      fprintf(fileW, "Voce nao tem contas esse mes\n");
    }



}
