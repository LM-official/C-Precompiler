#include "functions.h"

int main(int argc, char* args[]){
    Stats* sts = initialize_stats();
    Mods* mds = initialize_mod(argc, args);

    if(!mds->input) return 1; // no input file (mandatory parameter)

    errno = 0;

    char *text = file_include(sts, mds->input, mds->verbose);
    file_compacter(&text);
    print_output(mds->output, text);

    if(mds->verbose) print_statistics(sts, text); // otherwise it prints empty statistics

    /* free resources */
    free(text);
    free(mds);

    for(int i = 0; i != sts->num_files; i++){
        File* f = sts->files[i];
        for(int j = 0; j != f->num_var; j++){
            Var* v = f->vars[j];
            free(v->name);  // free the variable name
        }
        free(f->name);      // free the file name
        free(f->vars);      // free the variables pointer
    }
    free(sts->files);       // free the files pointer
    free(sts);

    /* gcc -Wall -o cpre src/main.c src/funzioni.c
    ./cpre --in=test1.c -v > o.txt */
    return 0;
}