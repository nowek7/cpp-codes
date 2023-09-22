#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BLOCK_SIZE 1024
#define COMMAND "ls"

#define READ_FD 0
#define WRITE_FD 1

void handlingChildProcess(pid_t pid, int fd[2])
{
  close(fd[READ_FD]);

  // Redirect stdout to write descriptor.
  dup2(fd[WRITE_FD], STDOUT_FILENO);

  close(fd[WRITE_FD]);

  execl("/bin/" COMMAND, COMMAND, "-al", NULL);
}

void handlingParentProcess(pid_t pid, int fd[2])
{
  printf("PARENT PROCESS!\n\n");

  close(fd[WRITE_FD]);

  int status;
  while (wait(&status) != pid) {
    ;
  }

  char buffer[BLOCK_SIZE];
  read(fd[READ_FD], buffer, sizeof(buffer));
  printf("%s\n", buffer);

  close(fd[WRITE_FD]);
}

int main()
{
  int fd[2];
  pid_t pid;

  if (pipe(fd) < 0) {
    printf("Failed to create pipe!\n");
    return -1;
  }

  pid = fork();
  if (pid < 0) {
    printf("Failed to create child process!\n");
    return -1;
  } else if (pid == 0) {
    handlingChildProcess(pid, fd);
  } else {
    handlingParentProcess(pid, fd);
  }

  return 0;
}
