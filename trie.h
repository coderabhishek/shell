#ifndef  trie
#define trie 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node
{
struct node *nxt[26];
struct node *prev;
int word;
int sz;
char cc;
};

typedef struct node node;

node * create_node();
void add(node *root,char *pt);
void show(node *root);
void DFS(node *root);
int search(node *root,char *pt);
node* init_trie();
#endif