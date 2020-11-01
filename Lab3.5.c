#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void primeNum(){
	printf("Enter a number to check if the number is primary : ");
}

void parentPro(){
        printf("Parent Process\n");

}

void childPro(){
        printf("Child Process\n");

}

int main(void) {
    void sigint_handler(int sig);

    int num;
    int prime;
    int pipefds[2];
    int buff;
    pipe(pipefds);
    int pid = fork();

    if(signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("Signal");
        exit(1);
    }

    if(pid == 0) {
	childPro();
        close(pipefds[0]);
        primeNum();
        scanf("%d", &num);
        write(pipefds[1], &num, sizeof(num));
    }
    else if(pid > 0) {
	wait(NULL);
        parentPro();
        close(pipefds[1]);
        read(pipefds[0], &buff, sizeof(buff));
	prime = buff / 2;

	for (int i = 2; i <= prime; i++) {
		if ( prime % 2 != 0) {
		printf("Is a Prime Number \n");
		}
		if ( prime % 2 == 0) {
		printf("Is not a Prime Number \n");
		}
		return EXIT_SUCCESS;
	}
}

    else {
        perror("Error");
	return EXIT_SUCCESS;
    }

}

void sigint_handler(int sig) {
    printf("Don't end this program!\n");
}
