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
#include <zip.h>
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
    char *my_password;
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

    password_file=fopen("./password_list.txt","r");
    if(password_file == NULL) {
        perror("Error in opening password list file.");
        exit(1);
    }

    while(fscanf(password_file, "%s\n",my_password)!=EOF) {
        //lettura linea per linea del nostro dizionario, ogni lettura và salvata nella variabile pass che poi và usata nel seguente codice:

        int iRetPassword = zip_set_default_password(za, my_password);
        //printf("password: %i", iRetPassword);

        for (i = 0; i < zip_get_num_entries(za, 0); i++) {
            if (zip_stat_index(za, i, 0, &sb) == 0) {
                printf("==================\n");
                len = strlen(sb.name);
                printf("Name: [%s], ", sb.name);
                printf("Size: [%lu], ", sb.size);
                printf("mtime: [%u]\n", (unsigned int) sb.mtime);
                if (sb.name[len - 1] == '/') {
                    safe_create_dir(sb.name);
                } else {
                    zf = zip_fopen_index(za, i, 0);
                    if (!zf) {
                        fprintf(stderr, "zip_fopen_index error\n");
                        //invece di questo errore, qua dovremmo mettere che nessuna password è stata trovata
                        exit(100);
                    }

                    fd = open(sb.name, O_RDWR | O_TRUNC | O_CREAT, 0644);
                    if (fd < 0) {
                        fprintf(stderr, "open file error\n");
                        exit(101);
                    }

                    sum = 0;
                    while (sum != sb.size) {
                        len = zip_fread(zf, buf, 100);
                        if (len < 0) {
                            fprintf(stderr, "zip_fread error\n");
                            exit(102);
                        }
                        write(fd, buf, len);
                        sum += len;
                    }
                    close(fd);
                    zip_fclose(zf);
                }
            } else {
                printf("File[%s] Line[%d]\n", __FILE__, __LINE__);
                //output desiderato da paulo
            }
        }
    }
    if (zip_close(za) == -1) {
        fprintf(stderr, "%s: can't close zip archive `%s'\n", prg, archive);
        return 1;
    }
    return 0;
}