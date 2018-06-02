#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define BUFFER 10000

//used to store a ragged array of strings to test if they're floats
typedef struct test_floats{
    int rows;
    char ** floats;
}sampleflts;

sampleflts * read_floats(char *filename);//parses a textfile and returns a pointer to a test_floats struct
void free_file(sampleflts * floats);//deallocates memory used for the test_floats struct

int main(int argc, char ** argv){
    //my state table, it has 10 states. Each state is made up of 128 elements in the array to represent the ascii table
    //78 is the decimal value for 'N' and just signifies to Not accept
    int _table[1280]=
    {
        78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,0,78,78,78,78,78,78,78,78,78,78,2,78,2,3,78,1,1,1,1,1,1,1,1,1,1,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,

        78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,4,78,1,1,1,1,1,1,1,1,1,1,78,78,78,78,78,78,78,78,78,78,78,6,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,6,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,

        78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,3,78,1,1,1,1,1,1,1,1,1,1,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,

        78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,1,1,1,1,1,1,1,1,1,1,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,

        78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,7,7,7,7,7,7,7,7,7,7,78,78,78,78,78,78,78,78,78,78,78,6,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,6,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,

        78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,

        78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,8,78,8,78,78,9,9,9,9,9,9,9,9,9,9,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,

        78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,7,7,7,7,7,7,7,7,7,7,78,78,78,78,78,78,78,78,78,78,78,6,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,6,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,

        78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,9,9,9,9,9,9,9,9,9,9,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,

        78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,9,9,9,9,9,9,9,9,9,9,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78
    };
    int * table = _table;
    if(argc > 1)
    {
        sampleflts * samples = read_floats(argv[1]);
        if(samples){
            for(int n = 0; n < samples->rows; ++n){
                char * num = samples->floats[n];
                int state = 0;
                printf("\n%s\n", num);
                //this loop iterates through the string and updates the state
                for( int i = 0; state != 'N' && num[i] != '\0'; ++i ){
                    state = table[ (state*128 + (int)num[i]) ];
                    printf("    Next state: %i\n", state);
                }
                //these are the accept states
                if(state == 5 || state == 7 || state == 9 || state == 1 || state == 4){
                    printf("Accept\n");
                }
                else{
                    printf("NAN\n");
                }
            }
            free_file(samples);
        }
    }
    else{
        printf("Please enter the name of the file to test for floats\n");
        printf("Usage: %s [filename]\n", argv[0]);
        printf("Example: %s floats.txt\n", argv[0]);

    }
    return 0;
}


sampleflts * read_floats(char *filename){
    sampleflts * nums = NULL;
    char buffer[BUFFER];
    char ** floats;//the ragged array that will be return in the struct
    int charCount = 0, c = 0, rows = 0;
    FILE * fp;
    if(!(fp = fopen(filename, "r")))
    {
        printf("failed to open\n");
        return NULL;
    }
    c = getc(fp);
    //counts how many rows are in the text file
    while(c != EOF ){
        if(c == '\n')
            ++rows;
        c= getc(fp);
    }
    rewind(fp);//moves the file pointer back to the start
    c = 0;// re-initialize c to zero
    floats = malloc(sizeof(char*) * rows);//make an array the size of the number of lines in the text file
    for(int i = 0; i < rows && c != EOF; ++i){
        //iterate through all rows of the ragged array
        c = getc(fp);
        charCount = 0;
        while( c != '\n' && (charCount < BUFFER) && c != EOF){
            //fills a buffer with characters from a single line in the file
            buffer[charCount] = c;
            c = getc(fp);
            ++charCount;
        }
        buffer[charCount] = '\0';//inserts a null terminator at the end of the string
        floats[i] = malloc(sizeof(char)*(charCount+1));//set the row to the size of the string in the buffer
        strcpy(floats[i], buffer);//copies the string from the buffer into the ragged array
    }
    nums = malloc(sizeof(sampleflts));
    nums->floats = floats;
    nums->rows = rows;
    fclose(fp);
    return nums;
}

//deallocates memory from a pointer to the testfloats struct
void free_file(sampleflts * floats){
    if(floats){
        for(int i = 0; i < floats->rows; ++i){
            free(floats->floats[i]);
        }
        free(floats->floats);
        free(floats);
    } 
}
