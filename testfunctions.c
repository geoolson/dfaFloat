
//test function for the reader and free function
void test_reader(){
    sampleflts * file = read_floats("sample.txt"); 
    if(file){
        printf("There are %i rows\n", file->rows);
        for(int i = 0; i < file->rows; ++i){
            printf("%s \n", file->floats[i]);
        }
        free_file(file);
    }
    else
        printf("failed to load\n");
}
