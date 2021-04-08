#include "variables.h"
///https://steemit.com/programming/@drifter1/programming-c-hashtables-with-linear-probing
typedef struct datast {
    char name[VELA];
    int birthday;
} DATAST;
typedef struct HashT{
    DATAST *data;
}HASHT;

int table_size=200000;
int hash(DATAST *datast){
    int sum=0;
    for (int i=0;i<strlen(datast->name);i++){
        sum+=datast->name[i]+(datast->name[i]*i+1);
    }
    return sum%table_size;
}
HASHT initl(HASHT hasht[]){
    for (int i = 0; i < table_size; ++i) {
        hasht[i].data = NULL;
    }

}
void linear_insert(HASHT hasht[],int hashin,DATAST *datast){

    if(hasht[hashin].data==NULL&&hashin<table_size){
        hasht[hashin].data=datast;
        return;
    }
    hashin=(hashin+100)%table_size;
    linear_insert(hasht,hashin,datast);
}

int linear_search(HASHT hasht[],DATAST *datast){
    int i=hash(datast);
    do{
        if(!strcmp(hasht[i].data->name,datast->name))
            return i;
        i=(i+100)%table_size;
    } while (i!=table_size);
    return -1;


}

