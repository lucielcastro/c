#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
  int valor, altura;
  struct no *direita, *esquerda;
} No;

No *criar(int numero)
{
  No *NovoNo = (No *)malloc(sizeof(No));

  NovoNo->valor = numero;
  NovoNo->esquerda = NULL;
  NovoNo->direita = NULL;
  NovoNo->altura = 0;
  return NovoNo;
}

// Calculando a altura do maior No da arvore
int maiorAltura(int num1, int num2)
{
  return (num1 > num2) ? num1 : num2;
}

// Calculando a altura do No da arvore
int alturaNo(No *No)
{
  if (No == NULL)
    return -1;
  else
    return No->altura;
}

// Balanceando a arvore
int fatorBalanceamento(No *No)
{
  if (No)
    return (alturaNo(No->esquerda) - alturaNo(No->direita));
  else
    return 0;
}

// Rotacao simples a esquerda
No *rotacaoEsquerda(No *raiz)
{
  No *pai, *filho;

  pai = raiz->direita;
  filho = pai->esquerda;

  pai->esquerda = raiz;
  raiz->direita = filho;

  raiz->altura = maiorAltura(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
  pai->altura = maiorAltura(alturaNo(pai->esquerda), alturaNo(pai->direita)) + 1;

  return pai;
}

// Rotacao simples a direita
No *rotacaoDireita(No *raiz)
{
  No *pai, *filho;

  pai = raiz->esquerda;
  filho = pai->direita;

  pai->direita = raiz;
  raiz->esquerda = filho;

  raiz->altura = maiorAltura(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
  pai->altura = maiorAltura(alturaNo(pai->esquerda), alturaNo(pai->direita)) + 1;

  return pai;
}

// Rotacao a direita e a esquerda
No *rotacaoDireitaEsquerda(No *raiz)
{
  raiz->direita = rotacaoDireita(raiz->direita);
  return rotacaoEsquerda(raiz);
}

// Rotacao a esquerda e a direita
No *rotacaoEsquerdaDireita(No *raiz)
{
  raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
  return rotacaoDireita(raiz);
}

// Balanceamento da arvore
No *balanceamento(No *raiz)
{
  int aux = fatorBalanceamento(raiz);

  if (aux < -1 && fatorBalanceamento(raiz->direita) <= 0)
    raiz = rotacaoEsquerda(raiz);
  else if (aux > 1 && fatorBalanceamento(raiz->esquerda) >= 0)
    raiz = rotacaoDireita(raiz);
  else if (aux > 1 && fatorBalanceamento(raiz->esquerda) < 0)
    raiz = rotacaoEsquerdaDireita(raiz);
  else if (aux < -1 && fatorBalanceamento(raiz->direita) > 0)
    raiz = rotacaoDireitaEsquerda(raiz);

  return raiz;
}

// Adicionando valores na arvore
No *adicionar(No *raiz, int numero)
{
  if (numero < raiz->valor)
  {
    if (raiz->esquerda == NULL)
      raiz->esquerda = criar(numero);
    else
      adicionar(raiz->esquerda, numero);
  }
  else
  {
    if (raiz->direita == NULL)
      raiz->direita = criar(numero);
    else
      adicionar(raiz->direita, numero);
  }

  raiz->altura = maiorAltura(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
  raiz = balanceamento(raiz);

  return raiz;
}

No *removerNo(No *raiz, int numero)
{
  if (raiz == NULL)
  {
    printf("Valor nao encontrado\n");
    return NULL;
  }
  else
  {
    if (raiz->valor == numero)
    {
      if (raiz->esquerda == NULL && raiz->direita == NULL)
      {
        free(raiz);
        printf("Folha removida: %d\n", numero);
        return NULL;
      }
      else
      {
        if (raiz->esquerda != NULL && raiz->direita != NULL)
        {
          No *aux = raiz->esquerda;

          while (aux->direita != NULL)
            aux = aux->direita;
          raiz->valor = aux->valor;
          aux->valor = numero;

          printf("Valor trocado: %d\n", numero);

          raiz->esquerda = removerNo(raiz->esquerda, numero);
          return raiz;
        }
        else
        {
          No *aux;
          if (raiz->esquerda != NULL)
            aux = raiz->esquerda;
          else
            aux = raiz->direita;
          free(raiz);
          printf("Elemento com 1 filho removido: %d\n", numero);
          return aux;
        }
      }
    }
    else
    {
      if (numero < raiz->valor)
        raiz->esquerda = removerNo(raiz->esquerda, numero);
      else
        raiz->direita = removerNo(raiz->direita, numero);
    }
    raiz->altura = maiorAltura(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    raiz = balanceamento(raiz);
    return raiz;
  }
}

void imprimir(No *raiz, int nivel)
{
  int i;
  if (raiz)
  {
    imprimir(raiz->direita, nivel + 1);
    printf("\n");

    for (i = 0; i < nivel; i++)
      printf("\t");

    printf("%d ", raiz->valor);
    imprimir(raiz->esquerda, nivel + 1);
  }
}

int main()
{
  No *raiz = NULL;

  raiz = criar(50);
  adicionar(raiz, 60);
  adicionar(raiz, 80);
  adicionar(raiz, 99);
  adicionar(raiz, 30);
  adicionar(raiz, 40);

  imprimir(raiz, 0);

  removerNo(raiz, 99);
  imprimir(raiz, 0);

  return 0;
}