#include "kernel/types.h"
#include "user/user.h"
#define r_end 0
#define w_end 1 
int main(int argc, char* argv){
    int p_to_c[2];
    int c_to_p[2];
    pipe(p_to_c);
    pipe(c_to_p);
    char buf = 's';
    int pid = fork();
    if(pid == 0){
        close(c_to_p[r_end]);
        close(p_to_c[w_end]);
        
        if(read(p_to_c[r_end],&buf,1) != 1){
            fprintf(1,"child read error");
            exit(1);
        }else{
            fprintf(1, "%d: received ping\n", getpid());        
        }  
        if(write(c_to_p[w_end], &buf,1) != 1){
            fprintf(1, "child write error");
            exit(1);
        }
        close(p_to_c[r_end]);
        close(c_to_p[w_end]);
        exit(0);
    }else{
        close(p_to_c[r_end]);
        close(c_to_p[w_end]);
        
        if(write(p_to_c[w_end],&buf,1) != 1){
            fprintf(1," parent write error");
            exit(1);
        }
        
        if(read(c_to_p[r_end], &buf,1) != 1){
            fprintf(1, " parent read error");
            exit(1);
        }else{
            fprintf(1, "%d: received pong\n", getpid());        
        }
        close(p_to_c[w_end]);
        close(c_to_p[r_end]);
        exit(0);
    }
}