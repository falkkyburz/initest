#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"


// define a structure for holding the values in "Section 1".
typedef struct{
    int int_val;
    float float_val;
    const char* string_val;
} section_one;

// define a structure for holding the values in "Section 2".
typedef struct{
    int int_val;
    float float_val;
    const char* string_val;
} section_two;

// define a structure for holding all of the config.
typedef struct
{
    section_one s1;
    section_two s2;
} configuration;

static int handler(void* config, const char* section, const char* name,
                   const char* value)
{
    // config instance for filling in the values.
    configuration* pconfig = (configuration*)config;

    // define a macro for checking Sections and keys under the sections.
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

    // fill the values in config struct for Section 1.
    if(MATCH("Section 1", "string-value")){ 
        pconfig->s1.string_val = strdup(value);
    }else if(MATCH("Section 1", "int-value")){
        pconfig->s1.int_val = atoi(value);
    }else if(MATCH("Section 1", "float-value")){
        pconfig->s1.float_val = strtof(value, NULL);

    // fill the values in config struct for Section 2.
    }else if(MATCH("Section 2", "string-value")){
        pconfig->s2.string_val = strdup(value);
    }else if(MATCH("Section 2", "int-value")){
        pconfig->s2.int_val = atoi(value);
    }else if(MATCH("Section 2", "float-value")){
        pconfig->s2.float_val = strtof(value, NULL);
    }else{
        return 0;
    }

    return 1;
}

// function for pretty-printing.
void pp_config(configuration config){
    printf("\nCONFIG---\n\n");

    printf("[Section 1]\n");
    printf("string-value: %s\n", config.s1.string_val);
    printf("int-value: %d\n", config.s1.int_val);
    printf("float-value: %f\n", config.s1.float_val);

    printf("\n");

    printf("[Section 2]\n");
    printf("string-value: %s\n", config.s2.string_val);
    printf("int-value: %d\n", config.s2.int_val);
    printf("float-value: %f\n", config.s2.float_val);
}

int main(int argc, char* argv[])
{
    // config for holding values.
    configuration config;

    // parse the .ini file
    if (ini_parse("initest.ini", handler, &config) < 0) {
        printf("Can't load 'initest.ini'\n");
        return 1;
    }

    // print the config.
    pp_config(config);

    // free the memory before exiting.
    free((void*)config.s1.string_val);
    free((void*)config.s2.string_val);

    return 0;
}