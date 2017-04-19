#include <stdio.h>

int main(int argc, char **argv) {
    unsigned int num = 0;
    char buf[16];
    int i;

    /* initialize */
    srand(time(NULL));
    num = random();

    for(i = 0; i < 5; i++) {
	printf("Guess the number\n");
	fgets(buf, sizeof(buf), stdin);

	printf("Your guess is: ");
	printf(buf, num);
	printf("\n");

	if(num == atoi(buf)) {
	    printf("Congratulations!\n");
	    system("/bin/sh");
	} else {
	    printf("You guessed wrong\n");
	}
    }

    return 0;
}
