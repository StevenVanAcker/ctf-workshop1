#include <stdio.h>

int main(int argc, char **argv) {
    char password[16] = "hello";
    char buf[16];

    gets(buf);

    if(!strcmp(buf, password) && strlen(password) > 0) {
	printf("Congratulations!\n");
	system("/bin/sh");
    } else {
	printf("Password does not match: %s\n", buf);
    }
    return 0;
}
