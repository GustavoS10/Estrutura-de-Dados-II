#include <stdio.h>
#include <stdlib.h>

int count = 0;

typedef struct sNode {
  int dado;
  struct sNode *esq, *dir;
} Node;

//prototipação
void preOrder(Node*);
void Order(Node*);
void posOrder(Node*);
Node* newNode(int);
void print2DUtil(Node*, int);
Node* inserir(Node*, int);
Node* remover(Node*, int);

void preOrder(Node *node) {
  if (node != NULL) {
    printf("%i  ", node->dado);
    preOrder(node->esq);
    preOrder(node->dir);
  }
}
void Order(Node *node) {
  if (node != NULL) {
    Order(node->esq);
    printf("%i  ", node->dado);
    Order(node->dir);
  }
}
void posOrder(Node *node) {
  if (node != NULL) {
    posOrder(node->esq);
    posOrder(node->dir);
    printf("%i  ", node->dado);
  }
}

// int verifNum(int dd, int de) {
//   if (dd < de) {
//     return dd;
//   } else {
//     return de;
//   }
// }


// Node *procurarMaior(Node *node, int dado) {
//   int aux = 0;
//   Node* no;

//   if (dado == node->dado) {
//     // if (node->esq->dado < node->dir->dado) {
//     //   return node->dir;
//     // } else {
//     //   return NULL;
//     // }
//   }
//   if (dado <= node->dado) {
//     aux = node->dado;
//     node->esq = procurarMaior(node->esq, dado);
//   } else if (dado > node->dado) {
//     aux = node->dado;
//     node->dir = procurarMaior(node->dir, dado);
//   }
//   return node;
// }

// Instanciando novo nodo e alocando memória
Node *newNode(int dado) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->dado = dado;
  temp->esq = temp->dir = NULL;
  count++;
  return temp;
};


// Função de imprimir árvore
void print2DUtil(Node *root, int space) {
  if (root == NULL)
    return;
  space += count;
  print2DUtil(root->dir, space);
  printf("\n");
  for (int i = count; i < space; i++)
    printf(" ");
  printf("%d\n", root->dado);
  print2DUtil(root->esq, space);
}
void print2D(Node *root) { print2DUtil(root, 0); }
// END Função de imprimir árvore

// Função de inserir dados
Node *inserir(Node *node, int dado) {
  if (node == NULL)
    return newNode(dado);
  if (dado <= node->dado) {
    node->esq = inserir(node->esq, dado);
  } else if (dado > node->dado) {
    node->dir = inserir(node->dir, dado);
  }
  return node;
}

// Função de remoção
Node *remover(Node *node, int dado) {
  int aux = 0;
  Node *temp;
  if (dado == node->dado) {
    if (node->esq == NULL && node->dir == NULL) {
      aux = node->dado;
      free(node);
      return NULL;
    }
    if (node->dir == NULL) { // se o direito tiver vazio só tem o esquerdo
      aux = node->dado;
      temp = node->esq;
      free(node);
      return temp;
    } else if (node->esq == NULL) { // se o esquerdo tiver vazio só tem o dir
      aux = node->dado;
      temp = node->dir;
      free(node);
      return temp;
    } else if (node->esq != NULL && node->dir != NULL) {
      Node* p, *q;

      p = node; q = node->esq;      
      while(q->dir != NULL){
        p = q;
        q = q->dir;
      }
      // o *q é o nó anterior ao r na ordem sub arvore da esquerda, raiz e a subarvore da direita
      //p é o pai de q
      if(p != node){
        p->dir = q->esq;
        q->esq = node->esq;
      }
      q->dir = node->dir;
      free(node);
      return q;
    }
  }
  if (dado <= node->dado) {
    aux = node->dado;
    node->esq = remover(node->esq, dado);
  } else if (dado > node->dado) {
    aux = node->dado;
    node->dir = remover(node->dir, dado);
  }
  return node;
}

int main() {

  Node* root = NULL;
  root = inserir(root, 10);
  
  inserir(root, 5);
  inserir(root, 3);
  inserir(root, 15);
  inserir(root, 12);
  inserir(root, 13);
  inserir(root, 19);
  inserir(root, 20);
  inserir(root, 17);
  inserir(root, 4);
  inserir(root, 10);
  inserir(root, 9);
  inserir(root, 1);
  inserir(root, 11);
  // inserir(root, 21);
  // inserir(root, 22);
  // remover(root, 4);
  // remover(root, 1);
  // remover(root, 3);

  preOrder(root);

  printf("\n");

  // remover(root, 3);
  // remover(root, 5);
  
  //quando apgar a raiz tem que reatribuir ela 
  // root = remover(root, 10);

  printf("\n");
  preOrder(root);
  
  printf("\n");
  printf("\n");
  Order(root);
  
  printf("\n");
  printf("\n");
  posOrder(root);

  printf("\n=========================================\n");
  printf("\n");
  printf("\n");

  // remover(root, 3);
  // remover(root, 10);

  // função de imprimir
  print2D(root);
  printf("\n");
  printf("\n");
  return 0;
}
