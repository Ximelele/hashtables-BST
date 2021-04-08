#include "variables.h"

void avl_search_test(NODE *rootAVL) {
    DATA *data = NULL;
    clock_t startavl = clock();
    for (int i = 0; i < 10; ++i) {
        fr = TEST_FILE;
        for (int j = 0; j < 99996; ++j) {
            data = (DATA *) malloc(sizeof(DATA));
            if (j) getc(fr);
            fscanf(fr, "%[^,],%d", data->name, &data->birthday);
           search_avl(rootAVL,data);
        }
    }
    clock_t endavl = clock();
    double avl_insert_T = (double) (endavl - startavl) / (double) CLOCKS_PER_SEC;
    printf("Search time AVL: %.3lfs\n\n", avl_insert_T);
}

void avl_insert_test() {
    NODE *rootAVL;
    clock_t startavl = clock();
    for (int i = 0; i < 10; ++i) {
        rootAVL = NULL;
        DATA *data = NULL;
        fr = TEST_FILE;

        //preOrder(root);
        for (int j = 0; j < 99996; ++j) {

            data = (DATA *) malloc(sizeof(DATA));
            if (j) getc(fr);
            fscanf(fr, "%[^,],%d", data->name, &data->birthday);
            rootAVL = insert_avl(rootAVL, data);
        }
    }
    clock_t endavl = clock();
    double avl_insert_T = (double) (endavl - startavl) / (double) CLOCKS_PER_SEC;
    printf("Insert time AVL: %.3lfs\n", avl_insert_T);
    avl_search_test(rootAVL);
}


void rbtree_search_test(NODERB *root) {
    DATARB *datarb = NULL;
    clock_t startrb = clock();
    for (int i = 0; i < 10; ++i) {
        fr = TEST_FILE;
        for (int j = 0; j < 99996; ++j) {
            datarb = (DATARB *) malloc(sizeof(DATARB));
            if (j) getc(fr);
            fscanf(fr, "%[^,],%d", datarb->name, &datarb->birthday);
            searchRB(root,datarb);
        }
    }
    clock_t endrb = clock();
    double rb_insert_T = (double) (endrb - startrb) / (double) CLOCKS_PER_SEC;
    printf("Search time R-B tree: %.3lfs\n\n", rb_insert_T);
}

void rbtree_insert_test() {
    NODERB *root;
    clock_t startrb = clock();
    for (int i = 0; i < 10; ++i) {
        fr = TEST_FILE;
        root = NULL;
        DATARB *datarb = NULL;

        for (int i = 0; i < 99996; ++i) {
            datarb = (DATARB *) malloc(sizeof(DATARB));
            if (i) getc(fr);
            fscanf(fr, "%[^,],%d", datarb->name, &datarb->birthday);
            root = insert(root, datarb);
            root->color = 0;
        }
    }
    clock_t endrb = clock();
    double rb_insert_T = (double) (endrb - startrb) / (double) CLOCKS_PER_SEC;
    printf("Insert time R-B tree: %.3lfs\n", rb_insert_T);
    rbtree_search_test(root);
}


void chainging_search_test(HASH **test) {
    DATAH *datah = NULL;
    clock_t hashS = clock();
    for (int i = 0; i < 10; ++i) {
        fr = TEST_FILE;
        for (int j = 0; j < 99996; ++j) {
            datah = (DATAH *) malloc(sizeof(DATAH));
            if (j) getc(fr);
            fscanf(fr, "%[^,],%d", datah->name, &datah->birthday);
            searchH(test,datah);
        }
    }
    clock_t hashE = clock();
    double hashtable = (double) (hashE - hashS) / (double) CLOCKS_PER_SEC;
    printf("Separate chaining search: %.3lfs\n\n", hashtable);
}

void chainging_insert_test() {
    HASH **test;
    clock_t hashS = clock();
    for (int i = 0; i < 10; ++i) {
        arr_size = 50000;
        stored = 0;
        fr = TEST_FILE;
        test = NULL;
        test = init(test, arr_size);
        DATAH *datah = NULL;

        for (int j = 0; j < 99996; ++j) {
            datah = (DATAH *) malloc(sizeof(DATAH));
            if (j) getc(fr);
            fscanf(fr, "%[^,],%d", datah->name, &datah->birthday);
            insert_h(test, datah);
            stored++;
            double resize = (double) ((1.0 * stored) / arr_size);
            if (resize > DEFAULT_LOAD_FACTOR) {
                printf("Resizing ");
                HASH **new_table = NULL;
                new_table = init(new_table, arr_size * 2);
                test = resize_table(test, new_table);
            }
        }
    }
    clock_t hashE = clock();
    double hashtable = (double) (hashE - hashS) / (double) CLOCKS_PER_SEC;

    printf("\nSeparate chaining insert: %.3lfs\n", hashtable);
    chainging_search_test(test);
}


void linear_probing_search(HASHT hasht[]) {

    clock_t hashS = clock();
    for (int i = 0; i < 10; ++i) {
        fr = TEST_FILE;
        for (int j = 0; j < 99996; ++j) {
            DATAST *datast= (DATAST *) malloc(sizeof(DATAST));
            if (j) getc(fr);
            fscanf(fr, "%[^,],%d", datast->name, &datast->birthday);
            linear_search(hasht,datast);
        }
    }
    clock_t hashE = clock();
    double hashtable = (double) (hashE - hashS) / (double) CLOCKS_PER_SEC;
    printf("Linear probing search: %.3lfs\n", hashtable);

}

void linear_probing_insert() {
    clock_t hashS = clock();
    HASHT hasht[table_size];
    for (int i = 0; i < 10; ++i) {
        fr = TEST_FILE;
        DATAST *datast = NULL;
        initl(hasht);
        for (int j = 0; j < 99996; ++j) {
            datast = (DATAST *) malloc(sizeof(DATAST));
            if (j) getc(fr);
            fscanf(fr, "%[^,],%d", datast->name, &datast->birthday);
            linear_insert(hasht, hash(datast), datast);
        }
    }
    clock_t hashE = clock();
    double linear_prob = (double) (hashE - hashS) / (double) CLOCKS_PER_SEC;
    printf("Linear probing insert: %.3lfs\n", linear_prob);
    linear_probing_search(hasht);
}



