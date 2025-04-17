#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
 
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1
 
int main(void)
{
  // char write_msg[BUFFER_SIZE] = "Greetings";
  char parent_msg[BUFFER_SIZE] = "Greetings";
  // char read_msg[BUFFER_SIZE];
  char child_msg[BUFFER_SIZE] = "Hello back!";
  char read_buf[BUFFER_SIZE];

  // int fd[2];

  int parent_to_child[2]; 
  int child_to_parent[2]; 
  
  pid_t pid;

   if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
     fprintf(stderr,"Pipe failed");
     return 1;
   }
 
   /* fork a child process */
   pid = fork();
 
   if (pid < 0) { /* error occurred */
     fprintf(stderr, "Fork Failed");
     return 1;
   }
 
   if (pid > 0) { /* parent process */
     close(parent_to_child[READ_END]);
     close(child_to_parent[WRITE_END]);
     // printf("PARENT: Writing message\n");

     printf("PARENT: Sending message: %s\n", parent_msg);
     // write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
     write(parent_to_child[WRITE_END], parent_msg, strlen(parent_msg)+1);
     // printf("PARENT: Wrote message, exiting\n");
 
     /* close the write end of the pipe */
     // close(fd[WRITE_END]);
     close(parent_to_child[WRITE_END]);

     read(child_to_parent[READ_END], read_buf, BUFFER_SIZE);
     printf("PARENT: Received: %s\n", read_buf);
     close(child_to_parent[READ_END]);

     wait(NULL); 
     
   }
   else { /* child process */
     // close(fd[WRITE_END]);
     close(parent_to_child[WRITE_END]);
     close(child_to_parent[READ_END]);
     // printf("CHILD: Reading message\n");
 
     // read(fd[READ_END], read_msg, BUFFER_SIZE);
     read(parent_to_child[READ_END], read_buf, BUFFER_SIZE); 
     printf("CHILD: Received: %s\n", read_buf);
 
     /* close the read end of the pipe */
     close(parent_to_child[READ_END]);

     printf("CHILD: Sending message: %s\n", child_msg);
     write(child_to_parent[WRITE_END], child_msg, strlen(child_msg)+1);
     close(child_to_parent[WRITE_END]);
   }
   return 0;
}