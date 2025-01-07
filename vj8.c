#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define MALLOC_ERROR -1

struct treeNode;
typedef struct treeNode* TreePosition;
typedef struct treeNode {
    int data;
    TreePosition left;
    TreePosition right;
} TreeNode;

struct queueNode;
typedef struct queueNode* QueuePosition;
typedef struct queueNode {
    TreePosition treeNode;
    QueuePosition next;
} QueueNode;

QueuePosition rear = NULL;

TreePosition insert(int x, TreePosition root);
TreePosition search(int x, TreePosition root);
int printPreorder(TreePosition root, int level);
int printInorder(TreePosition root, int level);
int printPostorder(TreePosition root, int level);
QueuePosition enqueue(TreePosition levelItem);
TreePosition dequeue();
int printLevelorder(TreePosition root);
TreePosition findMin(TreePosition root);
TreePosition deleteElement(TreePosition root, int x);
int deleteTree(TreePosition root);

int main() {
    TreePosition root = NULL;
    int choice;

    root = insert(4, root);
    root = insert(9, root);
    root = insert(2, root);
    root = insert(10, root);
    root = insert(6, root);
    root = insert(3, root);
    root = insert(1, root);
    root = insert(5, root);
    root = insert(7, root);

    search(6, root);
    search(11, root);

    printf("Odaberite vrstu ispisa (1-Preorder, 2-Inorder, 3-Postorder, 4-Levelorder): ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("Preorder ispis:\n");
        printPreorder(root, 0);
        break;
    case 2:
        printf("Inorder ispis:\n");
        printInorder(root, 0);
        break;
    case 3:
        printf("Postorder ispis:\n");
        printPostorder(root, 0);
        break;
    case 4:
        printf("Levelorder ispis:\n");
        printLevelorder(root);
        break;
    default:
        printf("Neispravan unos.\n");
        break;
    }

    root = deleteElement(root, 7);
 

    deleteTree(root);

    return EXIT_SUCCESS;
}

TreePosition insert(int x, TreePosition root) {
    if (root == NULL) {
        root = (TreePosition)malloc(sizeof(TreeNode));
        if (root == NULL) return NULL;
        root->data = x;
        root->left = NULL;
        root->right = NULL;
    }
    else if (x < root->data) {
        root->left = insert(x, root->left);
    }
    else if (x > root->data) {
        root->right = insert(x, root->right);
    }
    return root;
}

TreePosition search(int x, TreePosition root) {
    if (root == NULL) return NULL;
    if (x < root->data) return search(x, root->left);
    if (x > root->data) return search(x, root->right);
    return root;
}

int printPreorder(TreePosition root, int level) {
    int i;
    for (i = 0; i < level; i++) printf("   ");
    printf("%d\n", root->data);
    if (root->left != NULL) printPreorder(root->left, level + 1);
    if (root->right != NULL) printPreorder(root->right, level + 1);
    return 0;
}

int printInorder(TreePosition root, int level) {
    int i;
    if (root->left != NULL) printInorder(root->left, level + 1);
    for (i = 0; i < level; i++) printf("   ");
    printf("%d\n", root->data);
    if (root->right != NULL) printInorder(root->right, level + 1);
    return 0;
}

int printPostorder(TreePosition root, int level) {
    int i;
    if (root->left != NULL) printPostorder(root->left, level + 1);
    if (root->right != NULL) printPostorder(root->right, level + 1);
    for (i = 0; i < level; i++) printf("   ");
    printf("%d\n", root->data);
    return 0;
}

QueuePosition enqueue(TreePosition treeNode) {
    QueuePosition queueNode = (QueuePosition)malloc(sizeof(QueueNode));
    if (queueNode == NULL) return NULL;
    queueNode->treeNode = treeNode;
    if (rear == NULL) {
        queueNode->next = queueNode;
        return queueNode;
    }
    queueNode->next = rear->next;
    rear->next = queueNode;
    rear = queueNode;
    return queueNode;
}

TreePosition dequeue() {
    if (rear == NULL) return NULL;
    TreePosition levelItem;
    if (rear == rear->next) {
        levelItem = rear->treeNode;
        free(rear);
        rear = NULL;
    }
    else {
        QueuePosition front = rear->next;
        levelItem = front->treeNode;
        rear->next = front->next;
        free(front);
    }
    return levelItem;
}

int printLevelorder(TreePosition root) {
    rear = enqueue(root);
    if (rear == NULL) return MALLOC_ERROR;
    while (rear != NULL) {
        TreePosition treeNode = dequeue();
        printf("%d ", treeNode->data);
        if (treeNode->left != NULL) rear = enqueue(treeNode->left);
        if (treeNode->right != NULL) rear = enqueue(treeNode->right);
    }
    printf("\n");
    return 0;
}

TreePosition findMin(TreePosition root) {
    if (root->left == NULL) return root;
    return findMin(root->left);
}

TreePosition deleteElement(TreePosition root, int x) {
    if (root == NULL) return NULL;
    if (x < root->data) {
        root->left = deleteElement(root->left, x);
    }
    else if (x > root->data) {
        root->right = deleteElement(root->right, x);
    }
    else if (root->left != NULL && root->right != NULL) {
        TreePosition minInRight = findMin(root->right);
        root->data = minInRight->data;
        root->right = deleteElement(root->right, root->data);
    }
    else {
        TreePosition temp = root;
        if (root->left == NULL) root = root->right;
        else root = root->left;
        free(temp);
    }
    return root;
}

int deleteTree(TreePosition root) {
    if (root == NULL) return EXIT_SUCCESS;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
    return EXIT_SUCCESS;
}
