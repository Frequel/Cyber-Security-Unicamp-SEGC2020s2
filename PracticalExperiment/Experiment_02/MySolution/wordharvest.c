//Developed By Matteo Di Fabio 264339 and Luca Genovese 264364
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <dirent.h>
#include <stdbool.h>
#define N 256

char** extensions;
FILE *fp;

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void listdir(const char *name)
{
    DIR *dir;
    struct dirent *entry;
    int i;
    char* compare;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            listdir(path);
        } else if(entry->d_type == DT_REG){
            const char *ext = strrchr(entry->d_name,'.');
            for(i = 0; *(extensions + i); ++i)
            {
                compare = concat(".",extensions[i]);
                if(!strcmp(ext, compare))
                    fprintf (fp,"%s/%s\n", name, entry->d_name);
            }
        }
    }
    closedir(dir);
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

//letter with accent are considered special character
void check_word(char *my_keyword){
    FILE *keyword_file= {0};
    char *tmp_keyword[N];
    bool find=false;
    keyword_file=fopen("./out_keyword.txt","r+");

    if(keyword_file == NULL) {
        perror("Error in file opening check_word.");
        exit(1);
    }

    while(fscanf(keyword_file, "%s\n",tmp_keyword)!=EOF){

        if(strcmp(my_keyword,tmp_keyword)==0){
            find=true;
            return;
        }
    }
    if(!find){
        fprintf(keyword_file,"%s\n",my_keyword);
    }
    fclose(keyword_file);
}

void open_file(char *filename) {
    FILE *my_file;
    char word[N] = {0};
    char c;
    int i = 0;
    bool valid=true;

    printf("================================================\n");
    printf("Opening file: %s\n", filename);
    my_file = fopen(filename, "r");
    if (my_file == NULL) {
        perror("Error in file opening open_file.");
        exit(1);
    }
    printf("File opened\n");
    i = 0;
    (c = fgetc(my_file));
    do{
        word[i++] = (char) c;       
        if(c==EOF){
            valid=false;
        }
        if (!((c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123) )) {
            word[i-1] = '\0';        
            if(strlen(word)>0) {   //avoid to  search empty string in case of multiple space or special character
                check_word(word);
            }
            i=0;
        }
        c = fgetc(my_file);
    }while(valid);
    fclose(my_file);
}

int main(int argc, char **argv) {
    char* src_add;
    char* dst_add; 
    int n,i;
    char my_path[N]={0};
    FILE *pathfile;
    
    // check numbers of parameters
    if(argc < 5) {
        perror("Please provide the minimum parameter number\n");
        exit(1);
    }

    if(argc==5){
        if(strcmp(argv[1],"-d")!=0){
            perror("Please provide the -d as first parameter\n");
            exit(1);
        }
        if(strcmp(argv[3],"-o")!=0){
            perror("Please provide the -o as second parameter\n");
            exit(1);
        }
        src_add = argv[2];
        dst_add = argv[4];        
        extensions = (char **) malloc(2 * sizeof(char*));
        extensions[0] = (char *) malloc(4 * sizeof(char));
        extensions[1] = (char *) malloc(5 * sizeof(char));
        extensions[0]="txt";
        extensions[1]="text";
    }
    else if(argc==7){

        if(strcmp(argv[1],"-e")!=0){
            perror("Please provide the -e as first parameter\n");
            exit(1);
        }
        if(strcmp(argv[3],"-d")!=0){
            perror("Please provide the -d as second parameter\n");
            exit(1);
        }
        if(strcmp(argv[5],"-o")!=0){
            perror("Please provide the -o as third parameter\n");
            exit(1);
        }

        src_add = argv[4];
        dst_add = argv[6];

        extensions = str_split(argv[2], ':');

    }

    printf("source file: %s\ndestination address: %s\n", src_add,dst_add);

    if (extensions)
    {
        for (i = 0; *(extensions + i); i++)
            printf("extension %d =[%s]\n", i, *(extensions + i));

        printf("\n");
    }
	
    fp = fopen("./filesDaLeggere.txt", "w");
    
    if(fp == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    
    listdir(src_add);

    free(extensions);
    
    fclose(fp);

    pathfile=fopen("./filesDaLeggere.txt","r");
    if(pathfile == NULL) {
        perror("Error in file opening main.");
        exit(1);
    }
    while (fgets(my_path, sizeof(my_path), pathfile)!=NULL) {
        my_path[strlen(my_path)-1]='\0';
        open_file(my_path);    
    }

    printf("All the files are read\n");
    fclose(pathfile);

    return 0;

}
