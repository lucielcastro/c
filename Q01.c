#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int num;
  struct node* dir;
  struct node* esq;
}Node;
Node* criaArvore(){
  return NULL;
}

int arvoreVazia(Node* raiz){ 
  return raiz == NULL;
}
void inserirArvore(Node** raiz, int num){
  if(*raiz == NULL){ // Raiz vazia
    *raiz = (Node*)malloc(sizeof(Node)); 
    (*raiz)->esq = NULL; 
    (*raiz)->dir = NULL; 
    (*raiz)->num = num; 
  }else{
    if(num < (*raiz)->num){ // verificar se é menor que o no principal
      inserirArvore(&(*raiz)->esq, num); //insere a esquerda
    }
    if(num > (*raiz)->num){ //verifica se e maior
      inserirArvore(&(*raiz)->dir, num); //insere a direita
    }
  }
}
void imprimirArvore(Node* raiz){ 
  printf("|"); 
  if(!arvoreVazia(raiz)) {
    
    printf(" <%d> ", raiz->num); 
    imprimirArvore(raiz->esq);
    imprimirArvore(raiz->dir);
  }
  printf("|"); 
}    

int busca(Node* raiz, int num) {

  
  if(arvoreVazia(raiz)) { 
    return 0;
  }
  
  return raiz->num==num || busca(raiz->esq, num) || busca(raiz->dir, num);
}
void remover(Node** pRaiz, int numero){
   
    if(*pRaiz == NULL){  
       printf("\numero nao existe na arvore!\n");
       return;
    }
    
    if(numero < (*pRaiz)->num){
    	remover(&(*pRaiz)->esq, numero);
	}
    else{
        if(numero > (*pRaiz)->num){
        	remover(&(*pRaiz)->dir, numero);
		}
        else{   
            Node *pAux = *pRaiz;
            if (((*pRaiz)->esq == NULL) && ((*pRaiz)->dir == NULL)){ //No nao tem fihos
                free(pAux);
                (*pRaiz) = NULL; 
            }else{    
                if ((*pRaiz)->esq == NULL){ // so tem o filho da direita
                    (*pRaiz) = (*pRaiz)->dir;
                    pAux->dir = NULL;
                    free(pAux);
				    pAux = NULL;
                }else{           
                    if((*pRaiz)->dir == NULL){ //so tem filho da esquerda
                        (*pRaiz) = (*pRaiz)->esq;
                        pAux->esq = NULL;
                        free(pAux); 
					    pAux = NULL;
                    }else{   
                        pAux = (*pRaiz)->esq;  
                        pAux->esq = (*pRaiz)->esq;    
                        pAux->dir = (*pRaiz)->dir;
                        (*pRaiz)->esq = (*pRaiz)->dir = NULL;
                        free((*pRaiz));  
				        *pRaiz = pAux;  
				        pAux = NULL;   
                    }
                }
            }
        }
    }
}
int qtdNo(Node *raiz){
  if(raiz == NULL){
    return 0;
  }
  else{
    return 1+qtdNo(raiz->esq)+qtdNo(raiz->dir);
  }

}
int qtdNaoFolhas(Node *raiz){
  if(raiz == NULL){
    return 0;
  }
  else if ((raiz->esq)!=NULL && (raiz->dir) != NULL){
    return 1+(qtdNaoFolhas(raiz->esq)+qtdNaoFolhas(raiz->dir));
  }
}
int qtdFolhas(Node *raiz){
  if(raiz == NULL){
    return 0;
  }
  else if (raiz->dir==NULL && raiz->esq == NULL){
    return 1;
  }
  else{
    return qtdFolhas(raiz->esq)+qtdFolhas(raiz->dir);
  }
}
int alturaArv(Node *raiz){
  if(raiz == NULL){
    return -1;
  }
  else{
    int esquerda = alturaArv(raiz->esq);
    int direita = alturaArv(raiz->dir);
    if(esquerda>direita){
      return esquerda + 1;
    }
    else{
      return direita + 1;
    }
  }
}
int maiorNum(Node *raiz){
	if(raiz->dir != NULL){
		maiorNum(raiz->dir);
	}else if(raiz->dir == NULL){
		return raiz->num;
	}
}
int buscaImpar(Node* raiz, int num) {
  
  if(arvoreVazia(raiz)) { 
    return 0;
  }
  else if(raiz->num%2 != 0){
  return raiz->num==num || busca(raiz->esq, num) || busca(raiz->dir, num);
  }
}

int main() {
   Node *arvore = criaArvore();
  
   int valor;
   
   while( 1 ){ 
    int op;
    
 printf("\n\n");
 printf("|             ARVORE                   |\n");
 printf("|      1 - Inserir                     |\n");
 printf("|      2 - Arvore Vazia?               |\n");
 printf("|      3 - Mostrar elementos           |\n");
 printf("|      4 - Buscar valor                |\n");
 printf("|      5 - Remover valor               |\n");
 printf("|      6 - Quantidade de No            |\n");
 printf("|      7 - Quantidade de Folhas        |\n");
 printf("|      8 - Quantidade de Nos Nao Folhas|\n");
 printf("|      9 - Altura Arvore               |\n");
 printf("|      10 - Maior NUmero               |\n");
 printf("|      11 - Buscar impar               |\n");
 printf("|          0 - Sair                    |\n");
 
    printf("\nopcao?: ");
    scanf("%d", &op);

    switch (op){
      
      case 1: 
           printf( "\nInforme valor: " );
           scanf( "%d", &valor );
        inserirArvore(&arvore, valor);
      break;

      case 2: 
        if(arvoreVazia(arvore))
              {
                printf("\n\nArvore vazia!!\n");
              } else {
                printf("\n\nArvore NAO vazia!!\n");
              }
      break;

      case 3:
        imprimirArvore(arvore);
      break;
      
      case 4:
        printf( "\nInforme valor a buscar: " );
        scanf( "%d", &valor);
        if(busca(arvore, valor)){
               printf("\nO numero %d pertence a arvore!\n", valor);
             } else {
               printf("\nO numero %d NAO pertence a arvore!\n", valor);
             }
      break;
      
      case 5:
        printf( "\nInforme valor para remover: " );
        scanf( "%d", &valor);
        remover(&arvore, valor);
       break;
       case 6:
        printf("Qtd de nos: %d",qtdNo(arvore));
       break;
       case 7:
        printf("Qtd de folhas: %d",qtdFolhas(arvore));
       break;
        case 8:
        printf("Qtd de Nos nao folhas: %d",qtdNaoFolhas(arvore));
       break;
        case 9:
        printf("Altura arvore: %d",alturaArv(arvore));
       break;
       case 10:
        printf("Maior num: %d",maiorNum(arvore));
       break;
           case 11:
        printf( "\nInforme valor a buscar: " );
        scanf( "%d", &valor);
        if(buscaImpar(arvore, valor)){
               printf("\nO numero %d pertence a arvore!\n", valor);
             } else {
               printf("\nO numero %d NAO pertence a arvore!\n", valor);
             }
      case 0:
        free(arvore);
        exit(0);
      default: 
	  printf( "\nOPCAO INVALIDA!\n" );
    }
  }    
 
}