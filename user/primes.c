#include "kernel/types.h"
#include "user/user.h"
#define RE 0
#define WR 1 

void prime(int p[2]){
    close(p[WR]);
    int buf,temp,flag=1;
    // 首先读第一个数
    read(p[RE], &temp, 4);
    fprintf(1, "prime %d\n", temp);
    // 新管道
    int p_next[2];
    pipe(p_next);
    while(read(p[RE],&buf,4) != 0){
        if(buf%temp != 0) write(p_next[WR], &buf, 4);    
        flag = 0;
    }
    // 关闭管道
    close(p[RE]);
    // 只有一个数
    if(flag) exit(0);

    // 递归
    int pid = fork();
    if(pid == 0){
        prime(p_next);
    }else{
        close(p_next[WR]);
        close(p_next[RE]);
        wait(0);
    }
    exit(0);
}

int main(int argc, char* argv){
    if(argc != 1){
        fprintf(1,"pleas use: prime\n");
    }
    // 创建管道
    int p[2];
    pipe(p);
    fprintf(1, "prime 2\n");
    // 写入数字
    for(int i = 2; i <= 35; i++){
        if(i%2 != 0) write(p[WR], &i, 4);
    }
    int pid = fork();
    if(pid == 0){
        prime(p);
    }else{
        close(p[WR]);
        close(p[RE]);
        wait(0);
    }
    exit(0);
}