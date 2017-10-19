//Arquivo com as funçoes e as estruturas que guardam os dados das "Operações"
typedef struct{
  int id_operacao;
  char nome[100];

}Operacao;

struct No_Operacao{
  Operacao valor;
	struct No_Operacao *prox;
};

 //Função de inserir na Lista No_Operacao
void inserir_No_Operacao(struct No_Operacao *lista, Operacao e){
  struct No_Operacao *novoNo = malloc(sizeof(struct No_Operacao));
  novoNo->valor = e;
  novoNo->prox = lista->prox;
  lista->prox = novoNo;
}
