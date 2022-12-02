#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char * notes[0x10];

unsigned int sizes[0x10];

void setup(){
    setvbuf(stdin,NULL,_IONBF,0);
    setvbuf(stdout,NULL,_IONBF,0);
    setvbuf(stderr,NULL,_IONBF,0);
    alarm(30);
}

void menu(){
    puts("[1] Add");
    puts("[2] Delete");
    puts("[3] Write");
    puts("[4] View");
    puts("[5] Exit");
    printf("> ");
}


void view(){
    unsigned int i;
    puts("idx: ");
    scanf("%u", &i);
    getc(stdin);

    if (i > 0xf)
        exit(1);

    printf("data: %s", notes[i]);
}



void add(){
    char buf[0x100];
    unsigned int i,s;
    puts("idx: ");
    scanf("%u", &i);
    getc(stdin);

    if (i > 0xf)
        exit(1);

    puts("size: ");
    read(0,buf,0x100);
    s = (unsigned int) atoi(buf);
    if (s>0x1000)
        exit(0);

    char* new = malloc(s);

    if (new >0){
        notes[i] = new;
        sizes[i] = s;
    }
}


void delete(){
    unsigned int i;
    puts("idx: ");
    scanf("%u", &i);
    getc(stdin);

    if (i > 0xf)
        exit(1);

    free(notes[i]);


}


void _write(){
    unsigned int i;
    puts("idx: ");
    scanf("%u", &i);
    getc(stdin);

    if (i > 0xf)
        exit(1);
    puts("contents: ");
    read(0,notes[i],sizes[i]);
}

int main(){
    setup();
    while (1){
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
                delete();
                break;
            case 3:
                _write();
                break;
            case 4:
                view();
                break;
            case 5:
                exit(0);
                break;
            default:
                exit(42);
        }
    }
    return 0;
}
