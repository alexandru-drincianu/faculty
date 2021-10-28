#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {

pid_t pid;
int fd;
int n;
char buffer[64];
int k=0;
int status;
int x=0;

    if(argc!=4) perror("Numar de argumente incorect\n");
    else {
        for(int i=1 ; i<=3;i++)
        {
            pid=fork();
            if(pid < 0)
                perror("Eroare");
            if(pid == 0)//copil
            {
                fd=(open(argv[i], O_RDONLY));
                if (fd < 0)
                    perror("Eroare la deschidere fisier");
                else {
                    n=read(fd,buffer,64);
                    while (n != 0)
                    {
                        for(int j=0; j<n;j++){
                            if(islower(buffer[j]))
                            {
                            printf("%c ",buffer[j]);
                            k++;
                            }
                        }
                    n=read(fd,buffer,64);
                    }    
                }
            exit(k);
            }
            else//parinte
            {
                waitpid(pid,&status,0);
                x = x + WEXITSTATUS(status);
            }
        }    
    }
    printf("%d",x);
return 0;
}