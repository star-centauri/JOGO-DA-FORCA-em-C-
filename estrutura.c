#include<stdio.h>
#include<stdlib.h>

FILE* abrirArq(char nome[], char modo[]);
FILE* fecharArq(FILE *arq);

int main(void) {

  FILE *temp;
  temp=abrirArq("teste.txt", "r");
  temp=fecharArq(temp);
  return 0;
}

FILE* abrirArq(char nome[], char modo[]) {
  FILE *arq;
  arq=fopen(nome, modo);
  if(!arq) {
    printf("Não vou possivel abrir o arquivo %s", nome);
  }

  return arq;
}


FILE* fecharArq(FILE *arq){
  if(!arq){
    printf("\nErro ao fechar o arquivo\n");
  }
  fclose(arq);

  return arq;
}
