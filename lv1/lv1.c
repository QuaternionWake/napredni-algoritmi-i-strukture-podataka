#include<stdio.h>
#include<stdlib.h>

struct AVLNode_
{
    int x;
    int height;
    struct AVLNode_ *left;
    struct AVLNode_ *right;
};
typedef struct AVLNode_ AVLNode; 

int height(AVLNode *node) {
    int lh, rh;
    if (node == NULL)
        return 0;
    lh = height(node->left);
    rh = height(node->right);
    if (lh>rh) return 1+lh;
    return 1+rh;
}
 
AVLNode* newNode(int X)
{
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->x   = X;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return node;
}
 
AVLNode *RRotate(AVLNode *C) {
    printf(" Right");
    
    AVLNode *B = C->left;
    AVLNode *V3 = B->right;
    
    B->right = C;
    C->left = V3;
 
    C->height = height(C);
    B->height = height(B);
 
    return B;
}
 
AVLNode *LRotate(AVLNode *C) {
    printf(" Left");
    
    AVLNode *B = C->right;
    AVLNode *V3 = B->left;
 
    B->left = C;
    C->right = V3;
 
    C->height = height(C);
    B->height = height(B);
 
    return B;
}
 
int BalanceFactor(AVLNode *node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}
 
AVLNode* InsertAVL(AVLNode* node, int X)
{
    if (node == NULL)
        return newNode(X);
 
    if (X < node->x)
        node->left  = InsertAVL(node->left, X);
    else if (X > node->x)
        node->right = InsertAVL(node->right, X);
    else return node;
 
    node->height = height(node);
    int bf = BalanceFactor(node);
    //printf("\nNode %d height %d bf %d\n", node->x, node->height, bf );
 
    // LL rotation
    if (bf > 1 && X < node->left->x)
        return RRotate(node);
 
    // RR rotation
    if (bf < -1 && X > node->right->x)
        return LRotate(node);
 
    // LR rotate (double rotation)
    if (bf > 1 && X > node->left->x) {
        node->left =  LRotate(node->left);
        return RRotate(node);
    }
    
    // RL rotate (double rotation)
    if (bf < -1 && X < node->right->x) {
        node->right = RRotate(node->right);
        return LRotate(node);
    }

    return node;
}


AVLNode *SmallestNode( AVLNode *node ) {
    AVLNode *t = node;
    while ( t->left != NULL ) t = t->left;
    return t;
}
 
AVLNode* DeleteAVL(AVLNode* node, int X)
{
    if (node == NULL) return node;
    if ( X < node->x )
        node->left = DeleteAVL(node->left, X);
    else if( X > node->x )
        node->right = DeleteAVL(node->right, X);
    else {
        if( (node->left == NULL) || (node->right == NULL) ) {
            AVLNode *temp = node->left ? node->left : node->right;
            if (temp == NULL) {
                temp = node;
                node = NULL;
            }
            else *node = *temp;
            free( temp );
        }
        else {
            AVLNode* temp = SmallestNode(node->right);
            node->x = temp->x;
            node->right = DeleteAVL(node->right, temp->x);
        }
    }
    if (node==NULL) return node;
    node->height = height(node);
    int bf = BalanceFactor(node);
    if (bf > 1 && BalanceFactor(node->left) >= 0)
        return RRotate(node);
    if (bf > 1 && BalanceFactor(node->left) < 0) {
        node->left =  LRotate(node->left);
        return RRotate(node);
    }
    if (bf < -1 && BalanceFactor(node->right) <= 0)
        return LRotate(node);
    if (bf < -1 && BalanceFactor(node->right) > 0) {
        node->right = RRotate(node->right);
        return LRotate(node);
    }
    return node;
}


 
void PreorderAVL(AVLNode *node) {
    if (node==NULL) return;
    printf("%d(H%d) ", node->x, node->height);
    PreorderAVL(node->left);
    PreorderAVL(node->right);
}

void InorderAVL(AVLNode *node) {
    if (node==NULL) return;
    InorderAVL(node->left);
    printf("%d(H%d) ", node->x, node->height);
    InorderAVL(node->right);
}

void PostorderAVL(AVLNode *node) {
    if (node==NULL) return;
    PostorderAVL(node->left);
    PostorderAVL(node->right);
    printf("%d(H%d) ", node->x, node->height);
}
 

int main() {
    AVLNode *root = NULL;
    int i, newnode;
    int V[] = { 25, 13, 18, 9, 22, 21, 26, 21, 4, 20, 1, 15 };
 
    for (i=0; i<13; i++) {
        newnode = V[i];
        printf("Inserting %2d.. rotations:", newnode);
        root = InsertAVL(root, newnode);
        printf("\n");
    }
    puts("");
    printf("Preorder : "); PreorderAVL(root); puts("");
    printf("Inorder  : "); InorderAVL(root); puts("");
    printf("Postorder: "); PostorderAVL(root); puts("");
    
    
 /*   int DelV[] = {35,36,9,6,3,14,12,37,21,15,23};
    for (i=0; i<11; i++) {
        printf("Deleting %d.. rotations: ",  DelV[i]);
        root = DeleteAVL(root, DelV[i]);
        puts("");
        printf("Preorder : "); PreorderAVL(root); puts("");
        printf("Inorder  : "); InorderAVL(root); puts("");
        printf("Postorder: "); PostorderAVL(root); puts("");
    }*/
    return 0;
}
