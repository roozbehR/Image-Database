/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


/**
 *  A helper function that allocates a new tree node.
 *
 *  @param value The entry's value. It represents either an attribute or a filename.
 *  @return A pointer to the newly allocated node.
 *  (for now it returns NULL, so the compiler does not complain)
 */
struct TreeNode *allocate_node(const char *value) {
	
	struct TreeNode *new_node = NULL;
	new_node = malloc(sizeof(struct TreeNode));
	new_node->value = malloc(sizeof(BUFFER_SIZE));
	strcpy(new_node->value, value);
	new_node->child = NULL;
	new_node->sibling = NULL;
	return new_node;

}
/**
 * This function sees if it can find a colour match in the data base
 * 
 * @param tree A pointer to the root of the tree
 * @param value of the colour of the node we want to insert
 * 
 */
struct TreeNode *colour_match(struct TreeNode *root, char *colour){

	struct TreeNode *p = root;
	//value NULL indicates this colour does not exist in the database
	if (p->child == NULL)
	{	
		//printf("No colour exist yet\n");
		return NULL;
	}

	p = p->child;
	if (strcmp(p->value, colour) == 0)
	{
		//printf("Found the colour at the beggining\n");
		return p;
	}
	while (p->sibling != NULL)
	{
		if (strcmp(p->value, colour) == 0)
		{
			//printf("Found the colour some where in the list\n");
			return p;
		}
		p = p->sibling;
	}
	if (p->sibling == NULL && strcmp(p->value, colour) == 0)
	{
		//printf("Found the colour at the end of the list\n");
		return p;
	}

	return NULL;
}
/**
 * This function sees if it can find a shape match in the data base
 * 
 * @param tree A pointer to the root of the tree
 * @param value of the shape of the node we want to insert
 * 
 */
struct TreeNode *shape_match(struct TreeNode *root, char *shape){
	
	struct TreeNode *p = root;
	if (p == NULL)
	{
		return NULL;
	}
	p = p->child;
	if (strcmp(p->value, shape) == 0)
	{
		//printf("found shape at the beggining of the list\n");
		return p;
	}
	while (p->sibling != NULL)
	{
		if (strcmp(p->value, shape) == 0)
		{
			//printf("found shape some where in the list\n");
			return p;
		}
		p = p->sibling;
	}
	if (p->sibling == NULL && strcmp(p->value, shape) == 0)
	{
		//printf("Found the shape at the end of the list\n");
		return p;
	}
	//printf("No shape match found\n");
	return NULL;
} 
/**
 * This function sees if it can find a shape match in the data base
 * 
 * @param tree A pointer to the root of the tree
 * @param value of the shape of the node we want to insert
 * 
 */
struct TreeNode *texture_match(struct TreeNode *root, char *texture){
	
	struct TreeNode *p = root;
	if (p == NULL)
	{
		return NULL;
	}
	p = p->child;
	if (strcmp(p->value, texture) == 0)
	{
		return p;
	}
	while (p->sibling != NULL)
	{
		if (strcmp(p->value, texture) == 0)
		{
			return p;
		}
		p = p->sibling;
	}
	if (p->sibling == NULL && strcmp(p->value, texture) == 0)
	{
		return p;
	}
	return NULL;
} 
/**
 * This function searches in the database and returns the coorect position that the node should be inserted
 * 
 * @param tree A pointer to the root of the tree
 @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
struct TreeNode *correct_pos(struct TreeNode *curr, char *val){
	struct TreeNode *p = NULL;
	struct TreeNode *q = curr;
	if (q->sibling == NULL)
	{
			return q;
	}
	while (q->sibling != NULL)
	{	
		if (strcmp(val, q->value) > 0)
		{
			p = q;
			q = q->sibling;
		}
		else if (strcmp(val, q->value) < 0)
		{
			return p;
		}
	}
	if (p->sibling->sibling == NULL)
	{
		if (strcmp(val, q->value) > 0)
		{
			return q;
		}
		else if (strcmp(val, q->value) < 0)
		{
			return p;
		}
	}
	return NULL;
	
}
/**
 * This function inserts in depth 1 (colour) of the database
 * 
 * @param tree A pointer to the root of the tree
 @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void firstDepthInsert(struct TreeNode *root, char **values){
	
	struct TreeNode *parent = NULL;
	parent = root;
	struct TreeNode *curr = NULL;
	curr = root;
	struct TreeNode *p = NULL;
	//Inserts first colour since there is not colour in database yet
	if (root->child == NULL)
	{
		curr->child = allocate_node(values[1]);
		curr = curr->child;
		curr->child = allocate_node(values[2]);
		curr = curr->child;
		curr->child = allocate_node(values[3]);
		curr = curr->child;
		curr->child = allocate_node(values[4]);

	}
	//Colour(s) exist in the database already
	else 
	{
		parent = curr;
		curr = curr->child;
		//Takes care of the case that you insert the node in the beggining of the list for colour
		if (strcmp(values[1], curr->value) < 0 && strcmp(root->child->value, curr->value) == 0)
		{
			p = allocate_node(values[1]);
			p->sibling = curr;
			parent->child = p;
			p->child = allocate_node(values[2]);
			p = p->child;
			p->child = allocate_node(values[3]);
			p = p->child;
			p->child = allocate_node(values[4]);
		}
		//Takes care of the case that you insert in the middle or at the end of the list
		else if (strcmp(values[1], curr->value) > 0)
		{
			curr = correct_pos(curr, values[1]);
				if (curr->sibling == NULL)
				{
					p = allocate_node(values[1]);
					curr->sibling = p;
					p->child = allocate_node(values[2]);
					p = p->child;
					p->child = allocate_node(values[3]);
					p = p->child;
					p->child = allocate_node(values[4]);
				}
				else 
				{
					p = allocate_node(values[1]);
					p->sibling = curr->sibling;
					curr->sibling = p;
					p->child = allocate_node(values[2]);
					p = p->child;
					p->child = allocate_node(values[3]);
					p = p->child;
					p->child = allocate_node(values[4]);

				}
			
			
		}
		
	}		
}
/**
 * This function inserts in depth 2 (shape) of the database
 * 
 * @param tree A pointer to the root of the tree
 @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void secondDepthInsert(struct TreeNode *root, char **values){

	struct TreeNode *parent = NULL;
	parent = root;
	struct TreeNode *curr = NULL;
	curr = root;
	struct TreeNode *p = NULL;
	parent = curr;
	curr = curr->child;
		if (strcmp(values[2], curr->value) < 0 && strcmp(root->child->value, curr->value) == 0)
		{	
			//Inserting at the beggining
			p = allocate_node(values[2]);
			p->sibling = curr;
			parent->child = p;
			p->child = allocate_node(values[3]);
			p = p->child;
			p->child = allocate_node(values[4]);
		}
		else if (strcmp(values[2], curr->value) > 0)
		{	
			//Inserting using list traversal
			curr = correct_pos(curr, values[2]);
				if (curr->sibling == NULL)
				{
					p = allocate_node(values[2]);
					curr->sibling = p;
					p->child = allocate_node(values[3]);
					p = p->child;
					p->child = allocate_node(values[4]);
				}
				else 
				{
					p = allocate_node(values[2]);
					p->sibling = curr->sibling;
					curr->sibling = p;
					p->child = allocate_node(values[3]);
					p = p->child;
					p->child = allocate_node(values[4]);
				}
			
		}	
}
/**
 * This function inserts in depth 3 (texture) of the database
 * 
 * @param tree A pointer to the root of the tree
 @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void thirdDepthInsert(struct TreeNode *root, char **values){

	struct TreeNode *parent = NULL;
	parent = root;
	struct TreeNode *curr = NULL;
	curr = root;
	struct TreeNode *p = NULL;
	parent = curr;
	curr = curr->child;
		if (strcmp(values[3], curr->value) < 0 && strcmp(root->child->value, curr->value) == 0)
		{	
			//Inserting at the beggining
			p = allocate_node(values[3]);
			p->sibling = curr;
			parent->child = p;
			p->child = allocate_node(values[4]);
		}
		else if (strcmp(values[3], curr->value) > 0)
		{	
			//Inserting using list traversal
			curr = correct_pos(curr, values[3]);
			//printf("The current_pos is pointing at %s\n", curr->value);
				if (curr->sibling == NULL)
				{
					p = allocate_node(values[3]);
					curr->sibling = p;
					p->child = allocate_node(values[4]);
				}
				else 
				{
					p = allocate_node(values[3]);
					p->sibling = curr->sibling;
					curr->sibling = p;
					p->child = allocate_node(values[4]);
				}
			
		}	
}
/**
 * This function inserts in depth 3 (texture) of the database
 * 
 * @param tree A pointer to the root of the tree
 @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void forthDepthInsert(struct TreeNode *root, char **values){

	struct TreeNode *parent = NULL;
	parent = root;
	struct TreeNode *curr = NULL;
	curr = root;
	struct TreeNode *p = NULL;
	parent = curr;
	curr = curr->child;
		if (strcmp(values[4], curr->value) < 0 && strcmp(root->child->value, curr->value) == 0)
		{	
			p = allocate_node(values[4]);
			p->sibling = curr;
			parent->child = p;
		}
		else if (strcmp(values[4], curr->value) > 0)
		{	
			curr = correct_pos(curr, values[4]);
				if (curr->sibling == NULL)
				{
					p = allocate_node(values[4]);
					curr->sibling = p;
				}
				else 
				{
					p = allocate_node(values[4]);
					p->sibling = curr->sibling;
					curr->sibling = p;
				}
			
		}	
}
/**
 *  Insert a new image to a tree
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void tree_insert(struct TreeNode *root, char **values) {

	struct TreeNode *curr = NULL;
	curr = root;
	struct TreeNode *value_colour = colour_match(curr, values[1]);
	struct TreeNode *value_shape = NULL;
	struct TreeNode *value_texture = NULL;
	if (value_colour == NULL)
	{	
		firstDepthInsert(curr, values);

	}
	else if (shape_match(value_colour, values[2]) == NULL)
	{
		secondDepthInsert(value_colour, values);
	}
	else 
	{

		value_shape = shape_match(value_colour, values[2]);
		if (texture_match(value_shape, values[3]) == NULL)
		{
			thirdDepthInsert(value_shape, values);
		}
		else 
		{
			value_texture = texture_match(value_shape, values[3]);
			forthDepthInsert(value_texture, values);
		}
	}
	
}

/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */
void tree_search(const struct TreeNode *root, char **values) {

	struct TreeNode *replica_root = (struct TreeNode *)root;
	if (replica_root->child == NULL)
	{
		printf("(NULL)\n");
		return;
	}
	struct TreeNode *colour_pos = colour_match(replica_root, values[1]);
	if (colour_pos == NULL)
	{
		printf("(NULL)\n");
		return;
	}
	struct TreeNode *shape_pos = shape_match(colour_pos, values[2]);
	if (shape_pos == NULL)
	{
		printf("(NULL)\n");
		return;
	}
	struct TreeNode *texture_pos = texture_match(shape_pos, values[3]);
	if (texture_pos == NULL)
	{
		printf("(NULL)\n");
		return;
	}
	struct TreeNode *posFirstFile = texture_pos->child; 

	while (posFirstFile->sibling != NULL)
	{
		fprintf(stdout, "%s ", posFirstFile->value);
		posFirstFile = posFirstFile->sibling;
	}
	fprintf(stdout, "%s\n", posFirstFile->value);
}

/**
 *  Helps to print the data int he database
 *
 *  @param tree A pointer to the root of the tree.
 */
void printDatabase(struct TreeNode *tree, char attr[4][BUFFER_SIZE], int depth){

	if (tree == NULL)
	{
		return;
	}
	if (depth == 4)
	{
		while (tree != NULL)
		{	strcpy(attr[3], tree->value);
			printf("%s %s %s %s\n", attr[0], attr[1], attr[2], attr[3]);
			tree = tree->sibling;
		}
	}
	else if (depth == 3)
	{
		strcpy(attr[2], tree->value);
		printDatabase(tree->child, attr, depth+1);
		printDatabase(tree->sibling, attr, depth);
	}
	else if (depth == 2)
	{
		strcpy(attr[1], tree->value);
		printDatabase(tree->child, attr, depth+1);
		printDatabase(tree->sibling, attr, depth);
	}
	else if (depth == 1)
	{
		strcpy(attr[0], tree->value);
		printDatabase(tree->child, attr, depth+1);
		printDatabase(tree->sibling, attr, depth);
	}
	else 
	{
		return;
	}
}
/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree) {

	int depth = 1;
	struct TreeNode *curr = (struct TreeNode *)tree;
	if (curr->child == NULL)
	{
		printf("(NULL)\n");
		return;
	}
	curr = curr->child;
	char attr[4][BUFFER_SIZE];
	printDatabase(curr, attr, depth);

}
