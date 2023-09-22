#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP_READ_CHAR 'q'
#define READ_BLOCK_SIZE 1024

void help()
{
  printf("Incorrect number of arguments!\n");
  printf("Correct execution of program: \t ./main file1 file2\n");
}

int getSizeFile(FILE* file)
{
  if (file == NULL) {
    return 0;
  }

  fseek(file, 0, SEEK_END);
  const int size = ftell(file);
  fseek(file, 0, SEEK_SET);

  return size;
}

int backup(const char* srcPath, const char* destPath)
{
  FILE* srcFile = fopen(srcPath, "r");
  FILE* destFile = fopen(destPath, "w");
  if (!srcFile || !destFile) {
    printf("(%s:%d) Was something gone wrong!", __FILE__, __LINE__);
    return 0;
  }

  fseek(srcFile, 0, SEEK_END);
  const int size = ftell(srcFile);
  fseek(srcFile, 0, SEEK_SET);

  char* buffer = malloc(size + 1);

  // Read from src file and write to dest file.
  fread(buffer, 1, size, srcFile);
  fwrite(buffer, size, 1, destFile);

  free(buffer);

  // Close files.
  fclose(srcFile);
  fclose(destFile);

  // Return success
  return 1;
}

int main(int argc, char** argv)
{
  // Check arguments.
  if (argc != 3) {
    printf("Incorrect number of arguments!\n");
    printf("Correct execution of program: \t ./main file1 file2\n");
    return -1;
  }

  const char* srcPath = argv[1];
  const char* destPath = argv[2];

  FILE* srcFile = fopen(srcPath, "w");
  if (!srcFile) {
    printf("Was something gone wrong! Failed to open file!\n");
    return -1;
  }

  char inputText[READ_BLOCK_SIZE];

  int stop = 0;
  while (!stop) {
    printf("Your text: ");
    fgets(inputText, sizeof(inputText), stdin);

    const int inputTextLength = strlen(inputText);
    stop = (inputTextLength == 2) && (inputText[0] = 'q');
    if (!stop) {
      fwrite(inputText, strlen(inputText), 1, srcFile);
    }
  }

  // Close source file.
  fclose(srcFile);

  int success = backup(srcPath, destPath);
  if (!success) {
    printf("Error during rewriting!\n");
  }

  return 0;
}