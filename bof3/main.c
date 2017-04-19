#include <stdio.h>

void callme() {
    printf("Congratulations!\n");
    system("/bin/sh");
}

void docopy() {
    char buf[16];
    gets(buf);
}

int main(int argc, char **argv) {
    docopy();
    return 0;
}
