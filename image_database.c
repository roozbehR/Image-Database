/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "utils.h"

int main(void) {

        // char array to hold a line of input
	char buf[BUFFER_SIZE] = {'\0'};

        // char* array to hold the pointers to tokens
	char *args[INPUT_ARG_MAX_NUM];

        // the root of the tree
        struct TreeNode root;
        root.value = "";
        root.child = NULL;
        root.sibling = NULL;

	struct TreeNode *root_ptr = &root;

        // Add your code below:
        args[0] = malloc(sizeof(BUFFER_SIZE));
        args[1] = malloc(sizeof(BUFFER_SIZE));
        args[2] = malloc(sizeof(BUFFER_SIZE));
        args[3] = malloc(sizeof(BUFFER_SIZE));
        args[4] = malloc(sizeof(BUFFER_SIZE));
        //Add to ur notes that fgets returns NULL when it gets to end of the file
    while (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
            
            int arg_num = tokenize(buf, args);
        if ((arg_num == 5) && (args[0][0] == 'i' && args[0][1] == '\0'))
        {
                tree_insert(root_ptr, args);
        }
        else if ((arg_num == 4) && (args[0][0] == 'q' && args[0][1] == '\0'))
        {
                tree_search(root_ptr, args);
        }
        else if ((arg_num == 1) && (args[0][0] == 'p' && args[0][1] == '\0'))
        {       
                tree_print(root_ptr);
        }
        else 
        {
                 fprintf(stderr, "Invalid command.\n");
        }
    }
       
        return 0;
}
