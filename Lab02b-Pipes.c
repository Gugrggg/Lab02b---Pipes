#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    int value = 5;
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == 0) { /* child process */
        close(pipefd[0]); 
        printf("Entrei no filho!\n");
        value += 15;
        printf("CHILD: value = %d\n", value); /* LINE A */
        write(pipefd[1], &value, sizeof(value));
        close(pipefd[1]);

        exit(EXIT_SUCCESS);
    } else if (pid > 0) { /* parent process */
        wait(NULL);
        close(pipefd[1]);
        read(pipefd[0], &value, sizeof(value));
        printf("PARENT: value = %d\n", value); /* LINE A */
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}
