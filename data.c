//Arquivo que contem as funções que contenham datas
struct tm *MesAtual()
{
  struct tm *atual; //estrutura para armazenar data e hora atual.
  time_t segundos;
  time(&segundos); //obtém o tempo em segundos desde 1900.
  atual = localtime(&segundos); //converte a hora de segundos para struct tm.
  atual->tm_mon += 1;  // Atuliza o mês, pois começa a contar do mês 0 a 11.
  atual->tm_year += 1900;    // Atualização do ano, pois a data é gerada desde de 1900.
  return atual;
}
 //Converte uma data dd/MM/aaaa para dias, para que assim a ordenação possa ser feita
 int converte_Para_Dia(struct tm data){
  return ((data.tm_year * 365) + (data.tm_mon*30) + (data.tm_mday));

}

//Converte uma determinada data MM/aaaa toda para meses
int converte_Para_Mes(int mes, int ano){
  return (ano*12 + mes);
}
