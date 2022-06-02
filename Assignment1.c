/* From the Unix Manual:
int nftw(const char *dirpath,
int (*fn) (const char *fpath, const struct stat *sb, int typeflag), int nopenfd);
nftw() walks through the directory tree that is located under the directory dirpath, and calls fn() once for each entry in the tree. By default, directories are handled before the files and subdirectories they contain (preorder traversal). fn() is a function provided by the programmer.

Read the manual and other online resources about nftw() and symbolic links (A symbolic UNIX link is a special file that points to another file/folder in the file system), then write a C program, call it countCycles, to count the number of symbolic links that form cycles. Your program should search in a directory hierarchy and prints the total number of the cycles found.

Synopsis: countCycles [target-directory]
When target-directory is missing, the current working directory will be used.

In particular, you should use the system call nftw() to walk across a directory tree. This system call will do all the recursive walk for you and, each time it visits a file or a directory, it will call your own function (a function that you pass as a parameter to nftw()).
  
  
Program : 
*/
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <libgen.h>
#include <errno.h>

#define BUF_LEN PATH_MAX

static int countCycles(const char *fpath, const struct stat *sb,int typeflag,struct FTW *ftwbuf){
     // getting symbolic path link
    if(typeflag == FTW_SL){   
        char actualPath [PATH_MAX + 1];
        int loopLength = ftwbuf->level;
        int countCycles = 0;
        
        char *data = realpath(fpath,actualPath);

        char *originalFilePath = strdup(fpath);

        char *parentPath  = dirname(originalFilePath);

        while((loopLength) !=0){
            if(strcmp(parentPath, actualPath) == 0){  
                printf("Parent path : %s \t, Actual path : %s \n",parentPath, actualPath);  
                countCycles++;
            }   
            loopLength--;
            parentPath = dirname(parentPath); 
        }
        if(countCycles>0){
            printf("Count cycles : %d ",countCycles);
        }
    }
    return 0;
}

int main(int argc, char *argv[]){
    int flags = 0;
  
    if (nftw((argc < 2) ? "." : argv[1], countCycles, 20, FTW_PHYS) == -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }
   exit(EXIT_SUCCESS);
}
