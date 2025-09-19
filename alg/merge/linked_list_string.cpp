#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USE_CHAR_POINTER 1
#define MAX_CHARS 64

typedef struct SinglyLinkedNode {
    #if USE_CHAR_POINTER
        char *data;
    #else
        char data[MAX_CHARS];
    #endif
    struct SinglyLinkedNode *next;
} SinglyLinkedNode;

typedef struct DoublyLinkedNode {
    #if USE_CHAR_POINTER
        char *data;
    #else
        char data[MAX_CHARS];
    #endif
    struct DoublyLinkedNode *prev;
    struct DoublyLinkedNode *next;
} DoublyLinkedNode;

typedef struct CircularBuffer {
    #if USE_CHAR_POINTER
        char **items;
    #else
        char (*items)[MAX_CHARS];
    #endif
    int capacity;
    int count;
    int head;
} CircularBuffer;

char* safe_strdup(const char* s) {
    if (s == NULL) return NULL;
    char* d = (char*)malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void insertSingly(SinglyLinkedNode **head_ref, const char* new_data, int position) {
    SinglyLinkedNode* new_node = (SinglyLinkedNode*)malloc(sizeof(SinglyLinkedNode));
    if (!new_node) {
        printf("Erro: Falha ao alocar memoria para o no.\n");
        return;
    }

    #if USE_CHAR_POINTER
        new_node->data = safe_strdup(new_data);
    #else
        strncpy(new_node->data, new_data, MAX_CHARS - 1);
        new_node->data[MAX_CHARS - 1] = '\0';
    #endif

    if (position == 0) {
        new_node->next = *head_ref;
        *head_ref = new_node;
        return;
    }

    SinglyLinkedNode* current = *head_ref;
    int i;
    for (i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Posicao invalida. Inserindo no final.\n");
        SinglyLinkedNode* last = *head_ref;
        if (last) {
            while(last->next) last = last->next;
            last->next = new_node;
            new_node->next = NULL;
        } else {
            *head_ref = new_node;
            new_node->next = NULL;
        }
    } else {
        new_node->next = current->next;
        current->next = new_node;
    }
}

void deleteSingly(SinglyLinkedNode **head_ref, int position) {
    if (*head_ref == NULL) {
        printf("Lista vazia, nada para deletar.\n");
        return;
    }

    SinglyLinkedNode* temp = *head_ref;

    if (position == 0) {
        *head_ref = temp->next;
        #if USE_CHAR_POINTER
            free(temp->data);
        #endif
        free(temp);
        return;
    }

    int i;
    for (i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Posicao invalida.\n");
        return;
    }

    SinglyLinkedNode* node_to_delete = temp->next;
    temp->next = node_to_delete->next;

    #if USE_CHAR_POINTER
        free(node_to_delete->data);
    #endif
    free(node_to_delete);
}

void printSingly(SinglyLinkedNode* node) {
    printf("Lista Encadeada: [ ");
    int i = 0;
    while (node != NULL) {
        printf("(%d: \"%s\") -> ", i++, node->data);
        node = node->next;
    }
    printf("NULL ]\n");
}

void freeSingly(SinglyLinkedNode** head_ref) {
    SinglyLinkedNode* current = *head_ref;
    SinglyLinkedNode* next;
    while (current != NULL) {
        next = current->next;
        #if USE_CHAR_POINTER
            free(current->data);
        #endif
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

void insertDoubly(DoublyLinkedNode **head_ref, const char* new_data, int position) {
    DoublyLinkedNode* new_node = (DoublyLinkedNode*)malloc(sizeof(DoublyLinkedNode));
    if (!new_node) {
        printf("Erro: Falha ao alocar memoria para o no.\n");
        return;
    }
    
    #if USE_CHAR_POINTER
        new_node->data = safe_strdup(new_data);
    #else
        strncpy(new_node->data, new_data, MAX_CHARS - 1);
        new_node->data[MAX_CHARS - 1] = '\0';
    #endif
    new_node->prev = NULL;
    new_node->next = NULL;

    if (position == 0) {
        new_node->next = *head_ref;
        if (*head_ref != NULL) {
            (*head_ref)->prev = new_node;
        }
        *head_ref = new_node;
        return;
    }

    DoublyLinkedNode* current = *head_ref;
    int i;
    for (i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Posicao invalida. Inserindo no final.\n");
        DoublyLinkedNode* last = *head_ref;
        if(last) {
            while(last->next) last = last->next;
            last->next = new_node;
            new_node->prev = last;
        } else {
            *head_ref = new_node;
        }
    } else {
        new_node->next = current->next;
        if (current->next != NULL) {
            current->next->prev = new_node;
        }
        current->next = new_node;
        new_node->prev = current;
    }
}

void deleteDoubly(DoublyLinkedNode **head_ref, int position) {
    if (*head_ref == NULL) {
        printf("Lista vazia, nada para deletar.\n");
        return;
    }

    DoublyLinkedNode* node_to_delete = *head_ref;
    if (position == 0) {
        *head_ref = node_to_delete->next;
        if (*head_ref != NULL) {
            (*head_ref)->prev = NULL;
        }
        #if USE_CHAR_POINTER
            free(node_to_delete->data);
        #endif
        free(node_to_delete);
        return;
    }

    int i;
    for (i = 0; node_to_delete != NULL && i < position; i++) {
        node_to_delete = node_to_delete->next;
    }

    if (node_to_delete == NULL) {
        printf("Posicao invalida.\n");
        return;
    }

    if (node_to_delete->next != NULL) {
        node_to_delete->next->prev = node_to_delete->prev;
    }
    if (node_to_delete->prev != NULL) {
        node_to_delete->prev->next = node_to_delete->next;
    }
    
    #if USE_CHAR_POINTER
        free(node_to_delete->data);
    #endif
    free(node_to_delete);
}

void printDoubly(DoublyLinkedNode* node) {
    printf("Lista Duplamente Encadeada: [ NULL <=> ");
    int i = 0;
    while (node != NULL) {
        printf("(%d: \"%s\") <=> ", i++, node->data);
        node = node->next;
    }
    printf("NULL ]\n");
}

void freeDoubly(DoublyLinkedNode** head_ref) {
    DoublyLinkedNode* current = *head_ref;
    DoublyLinkedNode* next;
    while (current != NULL) {
        next = current->next;
        #if USE_CHAR_POINTER
            free(current->data);
        #endif
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

CircularBuffer* createCircularBuffer(int capacity) {
    CircularBuffer* cb = (CircularBuffer*)malloc(sizeof(CircularBuffer));
    if (!cb) return NULL;

    #if USE_CHAR_POINTER
        cb->items = (char**)malloc(sizeof(char*) * capacity);
    #else
        cb->items = malloc(sizeof(char[MAX_CHARS]) * capacity);
    #endif
    
    if (!cb->items) {
        free(cb);
        return NULL;
    }

    cb->capacity = capacity;
    cb->count = 0;
    cb->head = 0;
    return cb;
}

void freeCircularBuffer(CircularBuffer* cb) {
    if (!cb) return;
    #if USE_CHAR_POINTER
        for (int i = 0; i < cb->count; i++) {
            int index = (cb->head + i) % cb->capacity;
            free(cb->items[index]);
        }
    #endif
    free(cb->items);
    free(cb);
}

void insertCircular(CircularBuffer* cb, const char* item, int position) {
    if (cb->count == cb->capacity) {
        printf("Buffer cheio. Nao e possivel inserir.\n");
        return;
    }
    if (position < 0 || position > cb->count) {
        printf("Posicao invalida. Inserindo no final.\n");
        position = cb->count;
    }

    int tail = (cb->head + cb->count) % cb->capacity;

    for (int i = cb->count; i > position; i--) {
        int to_idx = (cb->head + i) % cb->capacity;
        int from_idx = (cb->head + i - 1) % cb->capacity;
        cb->items[to_idx] = cb->items[from_idx];
    }

    int insert_idx = (cb->head + position) % cb->capacity;
    #if USE_CHAR_POINTER
        cb->items[insert_idx] = safe_strdup(item);
    #else
        strncpy(cb->items[insert_idx], item, MAX_CHARS - 1);
        cb->items[insert_idx][MAX_CHARS - 1] = '\0';
    #endif
    
    cb->count++;
}

void deleteCircular(CircularBuffer* cb, int position) {
    if (cb->count == 0) {
        printf("Buffer vazio.\n");
        return;
    }
    if (position < 0 || position >= cb->count) {
        printf("Posicao invalida.\n");
        return;
    }

    int delete_idx = (cb->head + position) % cb->capacity;
    
    #if USE_CHAR_POINTER
        free(cb->items[delete_idx]);
    #endif

    for (int i = position; i < cb->count - 1; i++) {
        int to_idx = (cb->head + i) % cb->capacity;
        int from_idx = (cb->head + i + 1) % cb->capacity;
        cb->items[to_idx] = cb->items[from_idx];
    }

    cb->count--;
}

void printCircular(const CircularBuffer* cb) {
    printf("Buffer Circular (Capacidade: %d, Ocupado: %d): [ ", cb->capacity, cb->count);
    for (int i = 0; i < cb->count; i++) {
        int index = (cb->head + i) % cb->capacity;
        printf("(%d: \"%s\") ", i, cb->items[index]);
    }
    printf("]\n");
}

void menuSingly() {
    SinglyLinkedNode* head = NULL;
    char choice;
    char buffer[MAX_CHARS];
    int pos;

    while (1) {
        printSingly(head);
        printf("Singly-Linked >> (i)nserir, (d)eletar, (v)oltar: ");
        scanf(" %c", &choice);
        clear_input_buffer();

        if (choice == 'v') break;

        switch (choice) {
            case 'i':
                printf("  String para inserir: ");
                fgets(buffer, MAX_CHARS, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                printf("  Posicao para inserir: ");
                scanf("%d", &pos);
                clear_input_buffer();
                insertSingly(&head, buffer, pos);
                break;
            case 'd':
                printf("  Posicao para deletar: ");
                scanf("%d", &pos);
                clear_input_buffer();
                deleteSingly(&head, pos);
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }
    freeSingly(&head);
}

void menuDoubly() {
    DoublyLinkedNode* head = NULL;
    char choice;
    char buffer[MAX_CHARS];
    int pos;

    while (1) {
        printDoubly(head);
        printf("Doubly-Linked >> (i)nserir, (d)eletar, (v)oltar: ");
        scanf(" %c", &choice);
        clear_input_buffer();

        if (choice == 'v') break;

        switch (choice) {
            case 'i':
                printf("  String para inserir: ");
                fgets(buffer, MAX_CHARS, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                printf("  Posicao para inserir: ");
                scanf("%d", &pos);
                clear_input_buffer();
                insertDoubly(&head, buffer, pos);
                break;
            case 'd':
                printf("  Posicao para deletar: ");
                scanf("%d", &pos);
                clear_input_buffer();
                deleteDoubly(&head, pos);
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }
    freeDoubly(&head);
}

void menuCircular() {
    CircularBuffer* cb = createCircularBuffer(10);
    if (!cb) {
        printf("Falha ao criar buffer circular!\n");
        return;
    }
    char choice;
    char buffer[MAX_CHARS];
    int pos;

    while (1) {
        printCircular(cb);
        printf("Circular Buffer >> (i)nserir, (d)eletar, (v)oltar: ");
        scanf(" %c", &choice);
        clear_input_buffer();

        if (choice == 'v') break;

        switch (choice) {
            case 'i':
                printf("  String para inserir: ");
                fgets(buffer, MAX_CHARS, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                printf("  Posicao para inserir: ");
                scanf("%d", &pos);
                clear_input_buffer();
                insertCircular(cb, buffer, pos);
                break;
            case 'd':
                printf("  Posicao para deletar: ");
                scanf("%d", &pos);
                clear_input_buffer();
                deleteCircular(cb, pos);
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }
    freeCircularBuffer(cb);
}


int main() {
    int choice;
    printf("Usando representacao de string: %s\n", USE_CHAR_POINTER ? "char* (ponteiro)" : "char[] (array)");
    
    while (1) {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("Digite o tipo de implementacao de lista:\n");
        printf("(1) Encadeada\n");
        printf("(2) Duplamente encadeada\n");
        printf("(3) Buffer circular\n");
        printf("(4) Sair\n");
        printf("Escolha: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Entrada invalida. Por favor, insira um numero.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                menuSingly();
                break;
            case 2:
                menuDoubly();
                break;
            case 3:
                menuCircular();
                break;
            case 4:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
