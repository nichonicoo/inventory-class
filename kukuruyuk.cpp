#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50

typedef struct Node {
    char inserts[11];
    int count;
    struct Node *next;
} Node;

Node *hashTable[SIZE];
int insertOrder[SIZE];
int numOrdered;

// function for hashing the id
int hashId(char *inserts) {

    int totalHash = 0;
    for (int i = 0; i < 10; i++) {
        if (inserts[i] >= 'A' && inserts[i] <= 'Z') {
            totalHash += inserts[i] - 'A';
        } else if (inserts[i] >= '0' && inserts[i] <= '9') {
            totalHash += inserts[i] - '0';
        }
    }
    return totalHash % SIZE;
}

// funtion for insert to hash but inorder.
void insert(char *inserts) {

    int index = hashId(inserts);

    Node *temp = hashTable[index];
    while (temp != NULL) {
        if (strcmp(temp->inserts, inserts) == 0) {
            temp->count++;
            return;
        }
        temp = temp->next;
    }

    Node *newNode = (Node*) malloc(sizeof(Node));
    strcpy(newNode->inserts, inserts);
    newNode->count = 1;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;

    insertOrder[numOrdered++] = index;
}

// function to print 
void viewList() {

    printf("No\t|ID\t\t|Key\t|Jumlah\n");
    printf("--------------------------------------\n");

    for (int i = 0; i < numOrdered; i++) {

        int index = insertOrder[i];
        Node *temp = hashTable[index];
        int key = hashId(temp->inserts);

        while (temp != NULL) {
            printf("%d\t|%s\t|%d\t|%d\n",  i+1 , temp->inserts, key, temp->count);
            temp = temp->next;
        }
    }
}

// delete the data.
void retrieve(char *inserts) {

    int index = hashId(inserts);

    Node *prev = NULL;
    Node *curr = hashTable[index];
    while (curr != NULL) {
        if (strcmp(curr->inserts, inserts) == 0) {
            curr->count--;
            if (curr->count == 0) {
                if (prev == NULL) {
                    hashTable[index] = curr->next;
                } else {
                    prev->next = curr->next;
                }
                free(curr);
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int main() {
    
    int choice;
    char id[11];
    
    do {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Print\n");
        printf("3. Retrieve\n");
        printf("4. Exit\n");

        printf("\nPilih : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nMasukan ID (10 Karakter): ");
                scanf("%s", id);
                printf("Barang berhasil dimasukan!\n");
                insert(id);
                break;
            case 2:
                viewList();
                break;
            case 3:
                printf("\nMasukan ID (10 Karakter): ");
                scanf("%s", id);
                printf("Barang berhasil di ambil!\n");
                retrieve(id);
                break;
            case 4:
                printf("\nDadaaaa!\n");
                break;
            default:
                printf("\nGa jelas \n");
        }
    } while (choice != 4);

    return 0;
}