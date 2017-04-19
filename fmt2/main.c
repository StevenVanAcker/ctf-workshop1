#include <stdio.h>

#ifndef CANARY
#define CANARY 31337
#endif

int main(int argc, char **argv) {
    unsigned long target = 0;
    unsigned int canary = CANARY;
    char buf[100];

    while(1) {
	printf("Target is at %p, value %p\nEnter your string to echo:\n", &target, target);
	gets(buf);

	if(canary != CANARY) {
	    printf("Someone messed with the canary!!!\n");
	    _exit(0);
	}

	printf(buf, &target);

	if(target == 0x0defaced) {
	    printf("Congratulations!\n");
	    system("/bin/sh");
	} else {
	    printf("0x0defaced != %p\n", target);
	}
    }
    return 0;
}
