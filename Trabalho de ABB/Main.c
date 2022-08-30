#include <stdio.h>
#include <stdlib.h>

int count = 0;

typedef struct sNode{
    int dado;
    struct sNode* esq, *dir
} Node;

Node* newNode(int dado){
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->dado = dado;
    temp->esq = temp->dir = NULL;
    count++;
    return temp;
};

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil (Node * root, int space){
    // Base case
    if (root == NULL)
    return;
    // Increase distance between levels
    space += count;
    // Process right child first
    print2DUtil (root->dir, space);
    // Print current node after space
    // count
    printf ("\n");
    for (int i = count; i < space; i++)
    printf (" ");
    printf ("%d\n", root->dado);
    // Process left child
    print2DUtil (root->esq, space);
} 
 
// Wrapper over print2DUtil()
void print2D (Node * root) {
    // Pass initial space count as 0
    print2DUtil (root, 0);
}

Node* inserir(Node* node, int dado){
    if(node == NULL) return newNode(dado);
    if(dado <= node->dado){
        node->esq = inserir(node->esq, dado);
    }else if(dado > node->dado){
        node->dir = inserir(node->dir, dado);
    }
    return node;
}


int main() {

    Node* root = NULL;

    root = inserir(root, 5);
    
    inserir (root, 12);
    inserir (root, 2);
    inserir (root, 7);
    inserir (root, 3);
    inserir (root, 1);
    inserir (root, 10);
    inserir (root, 8);
    inserir (root, 9);
    inserir (root, 4);
    inserir (root, 6);
    inserir (root, 11);

    //função de imprimir
    print2D(root);

  return 0;
}
