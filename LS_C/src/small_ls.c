/*************************************************************************
    > File Name: small\ ls.c
    > Author: Zhekai Jin
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

void do_ls(char[]);

int main(int argc, char *av[])
{
    if(argc==1){
    do_ls(".");
    }else{
        while(--argc){
            printf("%s:\n",*++av);
            do_ls(*av);
        }
    }
    return 0;
}

void do_ls(char dirname[])
{
    DIR *dir_ptr;
    struct dirent *direntp;

    if((dir_ptr=opendir(dirname))==NULL){
        fprintf(stderr,"ls1:cannot open %s\n",dirname);
        fprintf(stdout,"Usage:./ls gives ls command under cwd");
        fprintf(stdout,"Usage:./ls arg1 arg2 gives ls command under agr1 arg2");
    }else{
        while((direntp=readdir(dir_ptr))!=NULL)
            printf("%s\n",direntp->d_name);
        closedir(dir_ptr);
    }
}
