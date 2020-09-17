/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <string.h>

#include "utils.h"


/*
 * Tokenize the string stored in cmd based on DELIMITERS as separators.
 * Return the number of tokens, and store pointers to them in cmd_argv.
 */
int tokenize(char *cmd, char **cmd_argv) {
        // returning 0 for now, so the compiler does not complain
        char *token = NULL;
        int num_tok = 0;
        token = strtok(cmd, DELIMITERS);
        while (token != NULL){
                num_tok++;
                //check strcpy feature in your notes later
                if (num_tok <= INPUT_ARG_MAX_NUM)
                {
                        strcpy(cmd_argv[num_tok - 1], token);
                }
                token = strtok(NULL, DELIMITERS);
        }
        return num_tok;
}
