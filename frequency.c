#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET 26 
#define WORD 30

struct node{  //tree's node struct
	int count;    
	char letter;
	struct node* children[ALPHABET];
};

void print(struct node* root, char *word);  //print in lexigraphic order
void printR(struct node* root, char *word); //print in reveres lexigraphic order
void set_leaf(struct node* root);  //sets all the childrens of a leaf to NULL

int main(int argc, char *argv[]){

	struct node *root = (struct node*) malloc(sizeof(struct node)); //tree's root and node
	struct node *n = root;
	set_leaf(n);
	n->count = 0;  
	
	char chr[2];
	while(fgets(chr,2,stdin) != NULL){    //read every character in stdin and insert to the tree
		short index = (short) chr[0];   
		if(index >= 97 && index <= 122){  //check if input is a valid letter
			index -= 97;              //convert letter to index in array
			if(n->children[index] != NULL){   //check if child exist 
				n = (n->children[index]); 
			}   
			else{  //make new child node
				n->children[index] = (struct node*) malloc(sizeof(struct node));
				n = (n->children[index]);
				set_leaf(n);
				n->letter = chr[0];
				n->count = 0;
			}
		}
		else if(chr[0] == ' ' || chr[0] == '\r' || chr[0] == '\n'){ //finished a letter update word count
			n->count++;
			n = root;
		}
	}
	root->count = 0; //root deafault word count
	
	char word[WORD];  //the word that will be printed
	word[0] = '\0';
	if(argc == 2 && *argv[1] == 'r'){  //check for argument r
		printR(root, word);
	}
	else{
		print(root, word);
	}
	
	return 0;
}

//print in a post order so longer words would be printed first 
void printR(struct node *root, char *word){

	if(root == NULL){
		return;
	}
	
	struct node* n; //child node
	char temp[WORD]; //copy of the word
	
	int i;
	for(i = ALPHABET-1; i >= 0; i--){ //search from z to a
		strcpy(temp, word);
		if(root->children[i] != NULL){ //check for children until reached a leaf
			strcat(temp, &(root->children[i]->letter)); //update the word to fit the root path
			n = root->children[i];
			printR(n, temp);
		}
	}
	strcpy(temp, word); 
	
	if(root->count != 0){ 
		printf("%s %d\n", temp, root->count);
	}
	free(root);
}

//print pre order so shorter words would be printed first
void print(struct node* root, char *word){
	if(root == NULL){
		return;
	}
	
	struct node* n; //child node
	char temp[WORD]; //copy of the word
	
	if(root->count != 0){
			printf("%s %d\n", word, root->count);
		}
	
	int i;
	for(i = 0; i < ALPHABET; i++){ //search from a to z
		strcpy(temp, word);	
		if(root->children[i] != NULL){   //check for children until reached a leaf
			strcat(temp, &(root->children[i]->letter)); //update the word to fit the root path
			n = root->children[i];
			print(n, temp);
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




























