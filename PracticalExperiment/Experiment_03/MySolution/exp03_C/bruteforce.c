//Developed By Matteo Di Fabio 264339 and Luca Genovese 264364
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <stdbool.h>
#include <zip.h>

#define N 256

const char *prg;
 
static void safe_create_dir(const char *dir)
{
    if (mkdir(dir, 0755) < 0) {
        if (errno != EEXIST) {
            perror(dir);
            exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    const char *archive;
    struct zip *za;
    struct zip_file *zf;
    struct zip_stat sb;
    char buf[100];
    int err;
    int i, len;
    int fd;
    long long sum;
    prg = argv[0];
    FILE *password_file;
    char my_password[N];
    bool found = false;
    if(argc < 5) {
        perror("Please provide the minimum parameter number:  bruteforce -l path-to-dictionary-file -f path-to-zip-file\n");
        exit(1);
    }

    if(strcmp(argv[1],"-l")!=0){
        perror("Please provide the parameter as following:  bruteforce -l path-to-dictionary-file -f path-to-zip-file\n");
        exit(1);
    }
    if(strcmp(argv[3],"-f")!=0){
        perror("Please provide the parameter as following:  bruteforce -l path-to-dictionary-file -f path-to-zip-file\n");
        exit(1);
    }
        archive = argv[4];

    if ((za = zip_open(archive, 0, &err)) == NULL) {
        zip_error_to_str(buf, sizeof(buf), err, errno);
        fprintf(stderr, "%s: can't open zip archive `%s': %s\n", prg,
            archive, buf);
        return 1;
    }

    password_file=fopen(argv[2],"r");
    if(password_file == NULL) {
        perror("Error in opening password list file.");
        exit(1);
    }

    while(!found && fscanf(password_file, "%s\n",my_password)!=EOF) {
        for (i = 0; i < zip_get_num_entries(za, 0); i++) {
            if (zip_stat_index(za, i, 0, &sb) == 0) {
                len = strlen(sb.name);
                if (sb.name[len - 1] != '/') {
                    zf = zip_fopen_index_encrypted(za, i, 0, my_password);
                    if (zf && sb.encryption_method!=ZIP_EM_NONE) {
                        zip_fclose(zf);
                        found = true;
                    }
                }
            } 
        }
    }
    
    if(found){
        printf("The password is %s\n",my_password);
    } else {
        printf("Password not found in the file %s\n",argv[2]);
    }

    fclose(password_file);

    if (zip_close(za) == -1) {
        fprintf(stderr, "%s: can't close zip archive `%s'\n", prg, archive);
        return 1;
    }
    return 0;
}