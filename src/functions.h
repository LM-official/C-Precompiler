#pragma once
/* #ifndef FUNCTIONS_H
#define FUNCTIONS_H
...
#endif */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

// ::::::::::::::::::::::::::::::::::::::: STATISTICS ::::::::::::::::::::::::::::::::::::::::::::::

// info about a file's variable
typedef struct{
    char* name;     // identifier
    int first_err;  // index of the first error occurrence
    int row;        // row where it was found
} Var;

// info about the variable list
typedef struct{
    Var *vars;      // pointer to the block of variables
    int len;        // length of the list
} List_var;

// file info
typedef struct{
    char* name;     // file name
    unsigned size;  // file size in bytes
    int num_row;    // number of rows
    int num_com;    // number of comments
    Var** vars;     // pointer to the variable pointers
    int num_var;    // number of variables
} File;

// statistics info
typedef struct{
    File** files;   // pointer to the file pointers with their info
    int num_files;  // number of files
} Stats;

// modules info
typedef struct{
    char* input;    // input file name
    char* output;   // output file name
    int verbose;    // flag to compute the statistics
} Mods;

/**
 * @brief Initializes the statistics struct.
 * @return The statistics struct.
 */
Stats* initialize_stats();

/**
 * @brief Initializes the executable's modules struct.
 * @param argc The number of the executable's arguments.
 * @param args The executable's arguments.
 * @return The pointer to the modules struct.
 */
Mods* initialize_mod(int argc, char* args[]);

/**
 * @brief Initializes the struct for a file.
 * @return The pointer to the file struct.
 */
File* initialize_file();

/**
 * @brief Adds the variable to the file.
 * @param f The file to add the variable to.
 * @param v The variable to add.
 */
void add_var(File* f, Var* v);

/**
 * @brief Adds the file to the statistics.
 * @param sts The statistics.
 * @param f The file to add to the statistics.
 */
void add_file(Stats* sts, File* f);

/**
 * @brief Prints the text to the destination if present, otherwise prints the text to stdout.
 * @param dest The destination file.
 * @param res The text to print.
 */
void print_output(const char* dest, const char* res);

/**
 * @brief Prints the statistics.
 * @param sts The statistics to print.
 * @param res The output text.
 */
void print_statistics(Stats* sts, const char* res);


// ::::::::::::::::::::::::::::::::::::::: ERRORS :::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @brief Prints the possible error and stops execution.
 */
void errors();

/**
 * @brief Prints the possible error during a file operation and stops execution.
 * @param f The input file.
 */
void file_errors(FILE* f);


// ::::::::::::::::::::::::::::::::::::::: UTILITIES :::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @brief Counts the number of digits of the input value.
 * @param n The input value.
 * @return The number of digits of the input value.
 */
unsigned num_digits(int n);

/**
 * @brief Compares the two input strings.
 * @param str1 The first string.
 * @param str2 The second string.
 * @return 1 if the input strings are equal, 0 otherwise.
 */
int is_equal(const char *str1, const char *str2);

/**
 * @brief Compares the two input strings.
 * @param str1 The first string.
 * @param str2 The second string.
 * @param n The number of characters to compare.
 * @return 1 if the first n characters of the input strings are equal, 0 otherwise.
 */
int is_n_equal(const char* str1, const char* str2, int n);

/**
 * @brief Removes in place the leading and trailing whitespace characters of the input string.
 * @param string The input string.
 */
void strstrip(char **string);

/**
 * @brief Removes the empty lines from the input text.
 * @param text The input text.
 */
void file_compacter(char **text);


// ::::::::::::::::::::::::::::::::::::::: BASIC FILE ::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @brief Opens the file at the input path in read mode.
 * @param path The path of the file to open.
 * @return The pointer to the opened file.
 */
FILE *file_open_read(const char *path);

/**
 * @brief Returns the number of bytes of the file.
 * @param f The input file.
 * @return The number of bytes of the file.
 */
unsigned file_size(FILE *f);

/**
 * @brief Reads the text of the input file.
 * @param f The input file.
 * @return The text of the input file.
 */
char *file_text(FILE *f);

/**
 * @brief Opens the file at the input path in write mode.
 * @param path The path of the file to open.
 * @return The pointer to the opened file.
 */
FILE *file_open_write(const char*path);

/**
 * @brief Writes the input text into the input file.
 * If the file already contained text it is overwritten.
 * @param f The destination file.
 * @param text The text to insert into the file.
 */
void file_write(FILE *f, const char *text);

/**
 * @brief Closes the input file.
 * @param f The file to close.
 */
void file_close(FILE *f);


// ::::::::::::::::::::::::::::::::::::::: ADVANCED FILE ::::::::::::::::::::::::::::::::::::::::::::
/**
 * @brief Removes the comments according to the C standard from the input text.
 * @param text The input text.
 * @param verbose Indicates whether or not to update the statistics.
 * @return The number of commented lines.
 */
unsigned file_del_comments(char **text, int verbose);

/**
 * @brief Detects whether the file to include has already been included before.
 * @param name file name.
 * @return 1 if the file was already included, 0 otherwise.
 */
int is_already_included(Stats *sts, const char *name);

/**
 * @brief Resolves the "file.h" includes.
 * @param sts The statistics.
 * @param path The path of the file to include.
 * @param verbose Indicates whether or not to update the statistics.
 */
char *file_include(Stats *sts, const char* path, int verbose);


// ::::::::::::::::::::::::::::::::::::::: VARIABLE CHECKING ::::::::::::::::::::::::::::::::::::::::
/**
 * @brief Takes the first instruction of the text starting from the input index and updates it.
 * @param text The input text.
 * @param index The input index.
 * @return The first instruction of the text starting from the input index.
 */
char* get_instruction(const char* text, int* index);
/**
 * @brief Takes the first lowercase word of the text starting from the input index and updates it.
 * @param text Input text.
 * @param index The input index.
 * @return The first lowercase word of the text starting from the input index.
 */
char* get_word(const char* text, int* index, int* row);
/**
 * @brief Takes the index of the last type of the input instruction.
 * @param text The input instruction.
 * @return The index of the last type of the input instruction.
 */

int is_cast(const char* instr, int i, int len);

int index_type(const char* instr, int* row);
/**
 * @brief Creates the list of variables of the input instruction.
 * @param filename The file name of the instruction.
 * @param instr The instruction to take the variables from.
 * @return The list of variables of the input instruction.
 */
List_var* get_variables(const char* instr, int* row);
/**
 * @brief Detects whether the input word is a C keyword.
 * @param word Input word.
 * @return 1 if the input word is a C keyword, 0 otherwise.
 */
int is_keyword(const char* word);
/**
 * @brief Checks the input identifier.
 * @param filename The file name of the variable.
 * @param var The variable to check.
 */
int check_variable(const char *name);
/**
 * @brief Analyzes the text of the input file and updates the statistics.
 * @param filename Input file name.
 * @param file_text The input text.
 * @return The number of rows of the file.
 */
int check_file(File* f, const char* file_text);