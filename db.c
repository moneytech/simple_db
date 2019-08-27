#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;


InputBuffer* new_input_buffer()  {
  InputBuffer* input_bffer = malloc(sizeof(InputBuffer));
  input_bffer->buffer = NULL;
  input_bffer->buffer_length = 0;
  input_bffer->input_length = 0;

  return input_bffer;
}

void print_prompt()  {
  printf("db > ");
}

void read_input(InputBuffer* input_buffer)  {
  ssize_t bytes_read = getline(&input_buffer->buffer, &input_buffer->buffer_length, stdin);  //bytes_read包括了最后的\n字符

  if (bytes_read <= 0)  {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer)  {
  free(input_buffer->buffer);
  free(input_buffer);
}

int main(int argc, char* argv[])  
{
  InputBuffer* input_buffer = new_input_buffer();
  while(true)  {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, ".exit") == 0)  {
      printf("bye-bye!\n");
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    }
    else  {
      printf("Unrecognize command %s .\n", input_buffer->buffer);
    }
  }

  return 0;
}