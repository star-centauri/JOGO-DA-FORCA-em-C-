#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Prótotipo das funções */
FILE* abrirArq(char nome[], char modo[]);
FILE* fecharArq(FILE *arq);
void adicionarDica();
void maiusculo(char dica[]);
void adicionarPalavra();

/* Função Principal */
int main(void) {

  FILE *temp;
  temp=abrirArq("dicas.txt", "a");
  temp=fecharArq(temp);
  adicionarPalavra();
  return 0;
}

/* Função para Adicionar dicas */
void adicionarDica() {
  char dica[201];
  char temp[201];
  char resp;
  bool erro = false;

  do {
    system("cls");
    printf("\nDigite uma dica de até 200 caracteres: \n");
    fflush(stdin);
    fgets(dica, 201, stdin);
    printf("\nDeseja continuar com a dica %s? <S/N>\n", dica);
    fflush(stdin);
    resp=getchar();
  }while (resp != 'S' && resp != 's');

  maiusculo(dica);
  FILE *arq;
  arq = abrirArq("dicas.txt", "r");

  while(!feof(arq)){
    fflush(stdin);
    fscanf(arq, "%s", temp);
    if(strcmp(dica, temp) == 0) {
      printf("\nEssa dica já existe!\n");
      erro = true;
      break;
    }
  }

  arq=fecharArq(arq);

  if(erro == false){
    arq=abrirArq("dicas.txt", "a");
    fseek(arq, 0, SEEK_END);
    fprintf(arq, "%s\n", dica);
    arq=fecharArq(arq);
  }

  printf("\nAperte uma tecla para voltar ao menu...\n");
  fflush(stdin);
  resp = getchar();

}

/* Função para adicionar palavra */
void adicionarPalavra() {
  char dica[201];
  char regTemp[202];
  char resp;
  bool erro= true;
  FILE *temp;

  struct {
    unsigned int idDica;
    char palavra[201];
  } registro;

  do {
    system("cls");
    printf("Digite uma palavra de até 200 caracteres: ");
    fflush(stdin);
    fgets(registro.palavra, 201, stdin);
    printf("Digite a dica: ");
    fflush(stdin);
    fgets(dica, 201, stdin);
    printf("Deseja continuar com a palavra %s ?<S/N>", registro.palavra);
    fflush(stdin);
    resp=getchar();
  } while(resp != 'S' && resp != 's');

  maiusculo(registro.palavra);
  maiusculo(dica);
  temp = abrirArq("dicas.txt", "r");
  registro.idDica = 0;

  while(!feof(temp)) {
    fgets(regTemp, sizeof(regTemp), temp);

    if(strcmp(dica, regTemp) == 0) {
      erro = false;
      break;
    }
      registro.idDica++;
  }

  fseek(temp, sizeof(dica)*registro.idDica, SEEK_SET);
  fgets(regTemp, sizeof(regTemp), temp);
  printf("\nString:%s \nID:%u\n", regTemp, registro.idDica+1);

  temp = fecharArq(temp);
}

/* Função para abrir arquivos */
FILE* abrirArq(char nome[], char modo[]) {
  FILE *arq;
  arq=fopen(nome, modo);
  if(!arq) {
    printf("Não vou possivel abrir o arquivo %s", nome);
  }

  return arq;
}

/* função para fechar arquivos */
FILE* fecharArq(FILE *arq){
  if(!arq){
    printf("\nErro ao fechar o arquivo\n");
  }
  fclose(arq);

  return arq;
}

/* Função para transforma letra minúscula em maiúscula */
void maiusculo(char dica[]){
  int i;

  for (i=0; i <= strlen(dica); i++) {
    if(dica[i] >= 97 && dica[i] <= 122) {
      dica[i] -= 32;
    }
  }
}
