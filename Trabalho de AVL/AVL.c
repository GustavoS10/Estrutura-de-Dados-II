#include <stdio.h>
#include <stdlib.h>
int count = 0;
struct Node {
  int dado, altura;
  struct Node *esq;
  struct Node *dir;
};

int max(int a, int b) { return (a > b) ? a : b; }
// função de pegar a altura da arvore
int altura(struct Node *nodo) {
  if (nodo == NULL)
    return 0;
  return 1 + max(altura(nodo->esq), altura(nodo->dir));
}
struct Node *newNode(int dado) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->dado = dado;
  node->esq = NULL;
  node->dir = NULL;
  node->altura = 0; // novo nodo iniciado com altura 0
  return (node);
}

// Função que roda a arvore para a direita
struct Node *rightRotate(struct Node *rotacao) {
  struct Node *novaPosicao = rotacao->esq;
  struct Node *T2 = novaPosicao->dir;
  // passo que executa a rotação da arvore
  novaPosicao->dir = rotacao;
  rotacao->esq = T2;
  // passo que atualiza a altura
  rotacao->altura = altura(rotacao);
  novaPosicao->altura = altura(novaPosicao);
  // retorna o novo rotacionado
  return novaPosicao;
}

struct Node *leftRotate(struct Node *rotacao) {
  struct Node *recebeRotacao = rotacao->dir;
  struct Node *T2 = recebeRotacao->esq;
  // Perform rotation
  recebeRotacao->esq = rotacao;
  rotacao->dir = T2;
  // Update heights
  rotacao->altura = altura(rotacao);
  recebeRotacao->altura = altura(recebeRotacao);
  // Return new root
  return recebeRotacao;
}

// Get Balance factor of node N
int getBalance(struct Node *N) {
  if (N == NULL)
    return 0;
  return altura(N->esq) - altura(N->dir);
}

struct Node *insert(struct Node *node, int dado) {
  if (node == NULL)
    return (newNode(dado));

  if (dado < node->dado)
    node->esq = insert(node->esq, dado);
  else if (dado > node->dado)
    node->dir = insert(node->dir, dado);
  else // Equal keys are not allowed in BST
    return node;
  /* 2. Atualiza a altura da arvore */
  node->altura = altura(node);
  /* 3. Pega o balanço da arvore para fazer as rotações caso tenha necessidade
   */
  int balance = getBalance(node);
  // 4. 4 casos de rotação
  // LL
  if (balance > 1 && dado < node->esq->dado)
    return rightRotate(node);
  // RR
  if (balance < -1 && dado > node->dir->dado)
    return leftRotate(node);
  // LR
  if (balance > 1 && dado > node->esq->dado) {
    node->esq = leftRotate(node->esq);
    return rightRotate(node);
  }
  // RL
  if (balance < -1 && dado < node->dir->dado) {
    node->dir = rightRotate(node->dir);
    return leftRotate(node);
  }
  /* retorna o ponteiro que nao foi alterado por alguma "Falha" */
  return node;
}

struct Node *minValueNode(struct Node *node) {
  struct Node *current = node;
  /* loop para encontrar o ultimo elemento mais a esquerda */
  while (current->esq != NULL)
    current = current->esq;
  return current;
}
/* Função recursiva para deletar o node com a chave  de uma subarvore e retorna a arvore modificada apos o delet */
struct Node *deleteNode(struct Node *root, int key) {
  // 1- se a arvore for null retorna ele pois nao tem 
  if (root == NULL)
    return root;
  /*Se a chave que será deletada é menro do que o root acontece a chamda recursiva passando que o elemento esta na subarvore da esquerda*/
  if (key < root->dado)
    root->esq = deleteNode(root->esq, key);
  // If the key to be deleted is greater than the
  // root's key, then it lies in right subtree
  /*Se a chave que será deletada é menro do que o root acontece a chamda recursiva passando que o elemento esta na subarvore da direta*/
  else if (key > root->dado)
    root->dir = deleteNode(root->dir, key);
    /*Se a chave for a mesma simplesmente sera deletado :)*/
  else {
    // Com um filho ou sem filho
    if ((root->esq == NULL) || (root->dir == NULL)) {
      struct Node *temp = root->esq ? root->esq : root->dir;
      // Sem filhos
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else           // One child case
        *root = *temp; // Copy the contents of
                       // the non-empty child
      free(temp);
    } else {
      // node with two children: Get the inorder
      // successor (smallest in the right subtree)
      struct Node *temp = minValueNode(root->dir);
      // Copy the inorder successor's data to this node
      root->dado = temp->dado;
      // Delete the inorder successor
      root->dir = deleteNode(root->dir, temp->dado);
    }
  }
  // If the tree had only one node then return
  if (root == NULL)
    return root;
  // 2- Atualiza a altura da arvore após o delete
  root->altura = 1 + max(altura(root->esq), altura(root->dir));
  /*3- Pega o balanço do nodo (para chegar se está balanceada ou nao)*/
  int balance = getBalance(root);
  // Se o nodo nao estiver balaçado tem 4 casos
  // Left Left simplesmente faz o balanço da subarvore para a esquerda
  if (balance > 1 && getBalance(root->esq) >= 0)
    return rightRotate(root);
  // Left Right simplesmente faz o balanço da subarvore para a esquerda e dps para direita
  if (balance > 1 && getBalance(root->esq) < 0) {
    root->esq = leftRotate(root->esq);
    return rightRotate(root);
  }
  // Right Right simplesmente faz o balanço da subarvore para a dir
  if (balance < -1 && getBalance(root->esq) <= 0)
    return leftRotate(root);
  // Right Left simplesmente faz o balanço da subarvore para a direita e dps para esquerda
  if (balance < -1 && getBalance(root->dir) > 0) {
    root->dir = rightRotate(root->dir);
    return leftRotate(root);
  }
  return root;
}
void preOrder(struct Node *root) {
  if (root != NULL) {
    printf("  %d - %i  ", root->dado, root->altura);
    preOrder(root->esq);
    preOrder(root->dir);
  }
}
void Order(struct Node *node) {
  if (node != NULL) {
    Order(node->esq);
    printf("%i  ", node->dado);
    Order(node->dir);
  }
}
void posOrder(struct Node *node) {
  if (node != NULL) {
    posOrder(node->esq);
    posOrder(node->dir);
    printf("%i  ", node->dado);
  }
}

int main() {
  struct Node *root = NULL;

  /* Constructing tree given in the above figure */
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 25);
  printf("\nDeletando node 25\n");
  root = deleteNode(root, 25);
  /*
      30
      / \
     20 40
    / \	 \
   10 25 50
  */
  printf("Preorder traversal of the constructed AVL"
         " tree is \n");
  preOrder(root);

  printf("\n\n\n");

  return 0;
}
