int buscaImpar(Node* raiz, int num) {
  
  if(arvoreVazia(raiz)) { 
    return 0;
  }
  else if(raiz->num%2 != 0){
  return raiz->num==num || busca(raiz->esq, num) || busca(raiz->dir, num);
  }
}