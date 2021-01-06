#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET 26 
#define TEXT 1024   //the maximum number of character for the line reading from the input

struct node{  //tree's node struct
	int count;    
	char letter;
	struct node* children[ALPHABET];
};

void print(struct node* root, char *word, int len);  //print in lexigraphic order
void printR(struct node* root, char *word, int len); //print in reveres lexigraphic order
void set_leaf(struct node* root);  //sets all the childrens of a leaf to NULL

int main(int argc, char *argv[]){

	char *line = (char *) malloc(TEXT); //line from input
	int len;
	
	fgets(line, TEXT, stdin);
	
	len = strlen(line);                    //free wasted memory
	line = (char *) realloc(line, len+1);
	if(len == 0 || len == 1){              //check for input
		printf("error in input\n");
		free(line);
		return 1;
	}
	
	struct node *root = (struct node*) malloc(sizeof(struct node)); //tree's root and node
	struct node *n = root;
	set_leaf(n);
	n->count = 0;  

	int i;
	for(i = 0; i < len; i++){    //read every character in line and insert to the tree
		char chr = line[i];
		short index = (short) chr;   
		if(index >= 97 && index <= 122){  //check if input is a valid letter
			index -= 97;              //convert letter to index in array
			if(n->children[index] != NULL){   //check if child exist 
				n = (n->children[index]); 
			}   
			else{  //make new child node
				n->children[index] = (struct node*) malloc(sizeof(struct node));
				n = (n->children[index]);
				set_leaf(n);
				n->letter = chr;
				n->count = 0;
			}
		}
		else if(chr == ' ' || chr == '\r' || chr == '\n'){ //finished a letter update word count
			n->count++;
			n = root;
		}
	}
	root->count = 0; //root deafault word count
	
	char word[len];  //the word that will be printed
	word[0] = '\0';
	if(argc == 2 && *argv[1] == 'r'){  //check for argument r
		printR(root, word, len);
	}
	else{
		print(root, word, len);
	}
	
	free(line);
	return 0;
}

//print in a post order so longer words would be printed first 
void printR(struct node *root, char *word, int len){

	if(root == NULL){
		return;
	}
	
	struct node* n; //child node
	char temp[len]; //copy of the word
	
	int i;
	for(i = ALPHABET-1; i >= 0; i--){ //search from z to a
		strcpy(temp, word);
		if(root->children[i] != NULL){ //check for children until reached a leaf
			strcat(temp, &(root->children[i]->letter)); //update the word to fit the root path
			n = root->children[i];
			printR(n, temp, len);
		}
	}
	strcpy(temp, word); 
	
	if(root->count != 0){ 
		printf("%s %d\n", temp, root->count);
	}
	free(root);
}

//print pre order so shorter words would be printed first
void print(struct node* root, char *word, int len){
	if(root == NULL){
		return;
	}
	
	struct node* n; //child node
	char temp[len]; //copy of the word
	
	if(root->count != 0){
			printf("%s %d\n", word, root->count);
		}
	
	int i;
	for(i = 0; i < ALPHABET; i++){ //search from a to z
		strcpy(temp, word);	
		if(root->children[i] != NULL){   //check for children until reached a leaf
			strcat(temp, &(root->children[i]->letter)); //update the word to fit the root path
			n = root->children[i];
			print(n, temp, len);
		}
	}
	
	free(root);	
}

void set_leaf(struct node* root){
	int i;
	for(i = 0; i < ALPHABET; i++){
		root->children[i] = NULL;
	}	
}




























