#include<stdio.h>
#include<stdlib.h>

int fileIndex;

struct file{
    int content;
    struct file *fnp;
};


typedef struct file file;
file *head = NULL;

file* create_file(){
    file* temp = (file*)malloc(sizeof(file));
    temp->content = ++fileIndex;
    temp->fnp = NULL;
    return temp;
}

void print_map(file* head){
    while(head->fnp){
        printf("%d -> ",head->content);
        head = head->fnp;
    }
    printf("%d\n",head->content);
}

int main(){
    file* temp = head = create_file();
    for(int i=0; i<5 ;i++){
        temp->fnp = create_file();
        temp = temp->fnp;
    }
    print_map(head);
    return temp->content;
}
