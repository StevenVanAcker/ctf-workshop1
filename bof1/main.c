#include <stdio.h>

int main(int argc, char **argv) {
    unsigned long target = 0;
    char buf[16];

    gets(buf);

    if(target == 0x0defaced) {
	printf("Congratulations!\n");
	system("/bin/sh");
    } else {
	printf("0x0defaced != %p\n", target);
    }
    return 0;
}
