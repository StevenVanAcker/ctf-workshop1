#include <stdio.h>

void callme() {
    printf("Congratulations!\n");
    system("/bin/sh");
}

void echo() {
    char buf[100];
    fgets(buf, sizeof(buf), stdin);
    printf(buf);
}

int main(int argc, char **argv) {
    echo();
    return 0;
}
