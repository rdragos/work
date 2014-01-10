#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAXCHAR 1000

void compute_tree(char *current_file, int lev) {
     
    int i;
    
    for (i = 0; i < lev; ++i) {
        printf("|---");
    }
    printf("%s\n", current_file);

    struct stat st; 
    stat(current_file, &st);
    
    if (S_ISDIR(st.st_mode) == 0) {
        return ;
    }
    
    
    DIR *pd = opendir(current_file); 
    struct dirent *pde;

    while((pde = readdir(pd)) != NULL) {
        if (strcmp(pde -> d_name, ".") == 0) {
            continue;
        }
        if (strcmp(pde -> d_name, "..") == 0) {
            continue;
        }
        
        char *new_dir = (char*)malloc(MAXCHAR);
        strcpy(new_dir, current_file); 
        strcat(new_dir, "/");
        strcat(new_dir, pde -> d_name);
        compute_tree(new_dir, lev + 1);
        free(new_dir);
    }
    if (pd != NULL) {
        closedir(pd);
    }
}
        
int main(int argc, char *argv[]) {
    
    char current_file[] = "/home/dragos/work/teme";
    compute_tree(current_file, 0); 
    return 0;
}
