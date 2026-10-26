#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

/* Create a node */
struct Node* createNode(int value) {
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/* Insert a node */
struct Node* insert(struct Node *root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        printf("Duplicate value not allowed!\n");

    return root;
}

/* Search for a value */
struct Node* search(struct Node *root, int value) {
    if (root == NULL || root->data == value)
        return root;

    if (value < root->data)
        return search(root->left, value);

    return search(root->right, value);
}

/* Find the minimum node */
struct Node* findMin(struct Node *root) {
    while (root != NULL && root->left != NULL)
        root = root->left;

    return root;
}

/* Delete a node */
struct Node* deleteNode(struct Node *root, int value) {
    if (root == NULL)
        return NULL;

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

/* Inorder traversal */
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

/* Preorder traversal */
void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

/* Postorder traversal */
void postorder(struct Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

/* Display tree sideways */
void display(struct Node *root, int space) {
    if (root == NULL)
        return;

    space += 5;

    display(root->right, space);

    printf("\n");

    for (int i = 5; i < space; i++)
        printf(" ");

    printf("%d\n", root->data);

    display(root->left, space);
}

/* Find tree height */
int height(struct Node *root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + (leftHeight > rightHeight
                ? leftHeight : rightHeight);
}

/* Free all nodes */
void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void) {
    struct Node *root = NULL;
    struct Node *temp;
    int choice, value, count, i;

    while (1) {
        printf("\n===== BST OPERATIONS =====\n");
        printf("1. Create BST\n");
        printf("2. Insert\n");
        printf("3. Delete\n");
        printf("4. Search\n");
        printf("5. Update\n");
        printf("6. Access Min and Max\n");
        printf("7. Display Tree\n");
        printf("8. Inorder Traversal\n");
        printf("9. Preorder Traversal\n");
        printf("10. Postorder Traversal\n");
        printf("11. Tree Height\n");
        printf("12. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                freeTree(root);
                root = NULL;

                printf("How many values? ");

                if (scanf("%d", &count) != 1 ||
                    count < 0 || count > 1000) {
                    printf("Invalid count!\n");
                    freeTree(root);
                    return 1;
                }

                for (i = 0; i < count; i++) {
                    printf("Enter value: ");

                    if (scanf("%d", &value) != 1) {
                        printf("Invalid input!\n");
                        freeTree(root);
                        return 1;
                    }

                    root = insert(root, value);
                }
                break;

            case 2:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1)
                    goto invalid_input;

                if (search(root, value) != NULL)
                    printf("Duplicate value!\n");
                else {
                    root = insert(root, value);
                    printf("Inserted successfully!\n");
                }
                break;

            case 3:
                printf("Enter value to delete: ");
                if (scanf("%d", &value) != 1)
                    goto invalid_input;

                if (search(root, value) == NULL)
                    printf("Value not found!\n");
                else {
                    root = deleteNode(root, value);
                    printf("Deleted successfully!\n");
                }
                break;

            case 4:
                printf("Enter value to search: ");
                if (scanf("%d", &value) != 1)
                    goto invalid_input;

                temp = search(root, value);

                if (temp != NULL)
                    printf("Value found: %d\n", temp->data);
                else
                    printf("Value not found!\n");
                break;

            case 5:
                printf("Enter existing value: ");
                if (scanf("%d", &value) != 1)
                    goto invalid_input;

                if (search(root, value) == NULL) {
                    printf("Value not found!\n");
                    break;
                }

                root = deleteNode(root, value);

                printf("Enter new value: ");
                if (scanf("%d", &value) != 1)
                    goto invalid_input;

                if (search(root, value) != NULL)
                    printf("New value already exists!\n");
                else {
                    root = insert(root, value);
                    printf("Updated successfully!\n");
                }
                break;

            case 6:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                    break;
                }

                temp = findMin(root);
                printf("Minimum: %d\n", temp->data);

                temp = root;
                while (temp->right != NULL)
                    temp = temp->right;

                printf("Maximum: %d\n", temp->data);
                break;

            case 7:
                if (root == NULL)
                    printf("Tree is empty!\n");
                else
                    display(root, 0);
                break;

            case 8:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 9:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 10:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;

            case 11:
                printf("Tree height: %d\n", height(root));
                break;

            case 12:
                freeTree(root);
                printf("Program ended!\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    freeTree(root);
    return 1;

invalid_input:
    printf("Invalid input! Exiting.\n");
    freeTree(root);
    return 1;
}
