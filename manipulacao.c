 //Arquivo onde ocorre a manipulação de arquivo

//Função que ler as Transações presentes no arquivo
void lerTransacao(FILE *file, struct No_Transacao *lista){
  printf("Lendo transacao...\n");
  Transacao t;
  char linha[10001];
  //Ler o arquivo até achar "*transacões"
  do{
    if(feof(file)){
      file = fopen("arquivo.txt", "r");
    }
    fscanf(file, "%s\n", linha);
  }while (strcmp(linha, "*transacoes*"));
  // Lê todas as transaçoes adiciona em um struct do tipo Transacao e depois adiciona a lista
  while (fscanf(file, "%d/%d/%d, %d, %d, %d, %lf;\n",&t.data.tm_mday,&t.data.tm_mon,&t.data.tm_year, &t.id_operacao, &t.id_conta_origem, &t.id_conta_destino, &t.valor) == 7) {
    //Insere na lista de transacões
    inserir_No_Trasacao(lista, t);
    //printf("%d/%d/%d----%d----%d----%d----%lf\n", t.data.tm_mday,t.data.tm_mon,t.data.tm_year, t.id_operacao, t.id_conta_origem,t.id_conta_destino,t.valor);

  }
}
//Função que ler os clientes presentes no arquivo
void lerCliente(FILE *file, struct No_Cliente *lista){
  printf("Lendo Cliente...\n");
  Cliente c;
  char linha[10001];
  //Ler o arquivo até achar "*cliente*"
  do{
    if(feof(file)){
      file = fopen("arquivo.txt", "r");
    }
    fscanf(file, "%s\n", linha);
  }while (strcmp(linha, "*cliente*"));
  // Lê todas os clientes adiciona em um struct do tipo Cliente e depois adiciona a lista
  while (fscanf(file, "%d, %[^,], %[^,], %[^,], %[^,], %[^;];\n",&c.id_cliente, c.nome, c.cpf, c.telefone, c.municipio, c.estado) == 6) {
    //Insere na lista de clientes
    inserir_No_Cliente(lista, c);
    //printf("%d----%s----%s----%s----%s----%s\n", c.id_cliente, c.nome, c.cpf,c.telefone,c.municipio, c.estado);

  }
}
//Função que ler as contas presentes no arquivo
void lerConta(FILE *file, struct No_Conta *lista){
  printf("Lendo conta...\n");
  Conta co;
  char linha[10001];
  //Ler o arquivo até achar "*conta" "
  do{
    if(feof(file)){
      file = fopen("arquivo.txt", "r");
    }
    fscanf(file, "%s\n", linha);
  }while (strcmp(linha, "*conta*"));
  // Lê todas as contas adiciona em um struct do tipo Conta e depois adiciona a lista
  while (fscanf(file, "%d, %d, %d, %d;\n",&co.id_conta, &co.numero_conta, &co.variacao,  &co.id_cliente) == 4) {
    //Insere na lista de contas
    inserir_No_Conta (lista, co);
    //printf("%d----%d----%d----%d\n", co.id_conta, co.numero_conta, co.variacao, co.id_cliente);

  }
}
//Função que ler as operações presentes no arquivo
void lerOperacao(FILE *file, struct No_Operacao *lista){
  printf("Lendo op...\n");
  Operacao op;
  char linha[10001];
  //Ler o arquivo até achar "*operacao*" "
  do{
    if(feof(file)){
      file = fopen("arquivo.txt", "r");
    }
    fscanf(file, "%s\n", linha);
  }while (strcmp(linha, "*operacao*"));
  // Lê todas as operações adiciona em um struct do tipo Operacao e depois adiciona a lista
  while (fscanf(file, "%d, %[^;];\n",&op.id_operacao, op.nome) == 2) {
    //Insere na lista de operações
    inserir_No_Operacao (lista, op);
    //printf("%d----%s\n", op.id_operacao, op.nome);

  }
}
//Função que ler as transações de cartao de credito presentes no arquivo
void lerTransacaoCartao(FILE *file, struct No_Transacao_Cartao *lista){
  printf("Lendo transacao cartao...\n");
  Transacao_Cartao tc;
  char linha[10001];
  //Ler o arquivo até achar "*transacoes_cartao_credito*" "
  do{
    if(feof(file)){
      file = fopen("arquivo.txt", "r");
    }
    fscanf(file, "%s\n", linha);
  }while (strcmp(linha, "*transacoes_cartao_credito*"));
  // Lê todas as Transacoes com cartão de credito  adiciona em um struct do tipo Transacao_Cartao e depois adiciona a lista
  while (fscanf(file, "%d/%d/%d, %d, %[^,], %d, %lf;\n",&tc.data_compra.tm_mday, &tc.data_compra.tm_mon,&tc.data_compra.tm_year, &tc.id_conta, tc.descricao, &tc.qtde_parcelas, &tc.valor) == 7) {
    //Insere na lista de transacoes_cartao_credito
    inserir_No_Trasacao_Cartao (lista, tc);
    //printf("%d/%d/%d-----%d-------%s------%d--------%lf;\n",tc.data_compra.tm_mday,tc.data_compra.tm_mon,tc.data_compra.tm_year, tc.id_conta, tc.descricao, tc.qtde_parcelas, tc.valor);

  }
}
