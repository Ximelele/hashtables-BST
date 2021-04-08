#include "variables.h"

typedef struct datah {
    char name[VELA];
    int birthday;
} DATAH;

typedef struct hash {
    DATAH *datah;
    struct hash *next;
} HASH;

int arr_size = 50000;
int stored = 0;

void insert_h(HASH **pHash, DATAH *data);

HASH **init(HASH **pHash, int size) {
    pHash = (HASH **) malloc(size * sizeof(HASH));
    for (int i = 0; i < size; ++i) {
        pHash[i] = (HASH *) malloc(sizeof(HASH));
        pHash[i]->next = NULL;
        pHash[i]->datah = NULL;
    }
    return pHash;
}

int hashF(DATAH *datah) {
    int hash = datah->birthday;
    for (int i = 1; i <= strlen(datah->name); ++i) {
        hash += datah->name[i - 1] * i;
    }
    hash += (int) strlen(datah->name);
    return hash % arr_size;
}

HASH **resize_table(HASH **pHash, HASH **new_table) {
    int old_size = arr_size;
    arr_size *= 2;
    //old data to new, rehash
    for (int i = 0; i < old_size; ++i) {
        HASH *curr = pHash[i];
        while (curr->next != NULL) {
            insert_h(new_table, curr->datah);
            curr = curr->next;
        }
    }
    return new_table;
}

void insert_h(HASH **pHash, DATAH *data) {

    int index = hashF(data);

    if (pHash[index]->datah == NULL) {
        pHash[index]->datah = data;
        pHash[index]->next = NULL;
    } else {
        HASH *curr = pHash[index];
        while (curr->next != NULL)
            curr = curr->next;

        HASH *kek = (HASH *) malloc(sizeof(HASH));
        kek->next = NULL;
        kek->datah = data;
        curr->next = kek;

    }
}

int searchH(HASH **pHash, DATAH *datah) {
    int index = hashF(datah);
    if (pHash[index]==NULL)
        return 0;
    do{
        if (pHash[index]->datah!=NULL&&!strcmp(datah->name, pHash[index]->datah->name))
            return 1;

        pHash[index] = pHash[index]->next;

    }while (pHash[index]!= NULL);
}



