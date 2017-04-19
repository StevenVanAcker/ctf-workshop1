#include <stdio.h>

void echo() {
    char buf[100];
    fgets(buf, sizeof(buf), stdin);
    printf(buf);
    exit(0);
}

int main(int argc, char **argv) {
    echo();
    return 0;
}
