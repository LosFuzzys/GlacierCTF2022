#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>


char * storage[0x10];
int sizes[0x10];



void setup(){
    setvbuf(stdin,NULL,_IONBF,0);
    setvbuf(stdout,NULL,_IONBF,0);
    setvbuf(stderr,NULL,_IONBF,0);
    alarm(5);
}

int read_input(char * arr, int size){
    printf("> ");
    return read(0,arr,size);
}


void menu(){
    puts("[1] Add");
    puts("[2] Change");
    puts("[3] Delete");
    puts("[4] Exit");
    printf("> ");
}

void change(){
    unsigned int index,size;
    puts("Index?");
    printf("> ");
    scanf("%u",&index);
    getc(stdin);
    if (index > 0x10){
        puts("Invalid index!");
        return;
    }
    if (storage[index] != NULL){
        puts("Contents:");
        read_input(storage[index],sizes[index]);
    }
    puts("Success!");

}


void add(){
    unsigned int index,size;
    puts("Index?");
    printf("> ");
    scanf("%u",&index);
    getc(stdin);
    puts("size?");
    printf("> ");
    scanf("%u",&size);
    getc(stdin);

    if (size > 0x408){
        puts("Invalid size");
        return;
    }

    if (index > 0x10){
        puts("Invalid index!");
        return;
    }
    char * new = (char *) malloc(size);
    puts("Content: ");
    read_input(new,size);
    storage[index] = new;
    sizes[index] = size;
    puts("Success!");



}

void print_logo(FILE * fd){
    while(!feof(fd)) {
        putchar(fgetc(fd));
    }
    fseek(fd,0,0);
}

void delete(){
    unsigned int index,size;
    puts("Index?");
    printf("> ");
    scanf("%u",&index);
    getc(stdin);

    if (index > 0x10 || storage[index] == NULL){
        puts("Invalid index!");
        return;
    }

    free(storage[index]);
    storage[index] = NULL;
    sizes[index] = 0;

}

int print_intro(){

    puts("Wellcome to just another menu challenge!");
    puts("You have done plenty of these in the past");
    puts("so how hard could it really be");
}


int main(){
    setup();
    char name[] = "./logo.txt";
    FILE * fd = fopen(name,"r");
    // print_intro();
    while (1){
        print_logo(fd);
        menu();
        int choice;
        scanf("%u",&choice);
        getc(stdin);
        switch (choice)
        {
            case 1:
                add();
                break;
            case 2:
                change();
                break;
            case 3:
                delete();
                break;
            case 4:
                exit(1337);
                break;

            default:
                exit(42);
        }
    }
    return 0;
}
