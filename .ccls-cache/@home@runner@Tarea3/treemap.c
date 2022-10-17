#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    PairTree* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};



int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (PairTree *)malloc(sizeof(PairTree));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
  TreeMap * newMap = (TreeMap *)malloc(sizeof(TreeMap));

  newMap->root = NULL;
  newMap->current = NULL;
  newMap->lower_than = lower_than;
  
  return (newMap);
}




void insertTreeMap(TreeMap * tree, void* key, void * value){
  if(searchTreeMap(tree, key) == NULL)
  {
    if(tree->root == NULL)
    {
      TreeNode *nodo = createTreeNode(key, value);
      
      tree->root = nodo;
      tree->current = nodo;
      nodo->parent = NULL;
    }
    else
    {
      TreeNode *nActual = tree->root;
      while(nActual != NULL)
      {         
        tree->current = nActual;
        if(tree->lower_than(nActual->pair->key, key) == 0)
        {
          nActual = nActual->left;
        }
        else
        {
          nActual = nActual->right;
        }
      }
      TreeNode *nodo = createTreeNode(key, value);
      nodo->parent = tree->current;
      if(tree->lower_than(tree->current->pair->key, key) == 0)
      {
        tree->current->left = nodo;
      }
      else
      {
        tree->current->right = nodo;
      }
      
      tree->current = nodo; 
    }
  }
}



TreeNode * minimum(TreeNode * x)
{
  while(x->left != NULL)
  {
    x = x->left;
  }
  return (x);
}



void removeNode(TreeMap * tree, TreeNode* node)
{
  if((node->left == NULL) && (node->right == NULL))
  {
    if(node->parent->left == node)
    {
      node->parent->left = NULL;
    }
    else
    {
      node->parent->right = NULL;
    }
  }
  else
  {
    if((node->left == NULL) || (node->right == NULL))
    {
      if(node->parent < node)
      {
        if(node->left == NULL)
        {
          node->parent->right = node->right;
          node->right->parent = node->parent;
        }
        else
        {
          node->parent->right = node->left;
          node->left->parent = node->parent;
        }
      }
      else
      {
        if(node->left == NULL)
        {
          node->parent->left = node->right;
          node->right->parent = node->parent;
        }
        else
        {
          node->parent->left = node->left;
          node->left->parent = node->parent;
        }
      }
    }
    else
    {
      TreeNode* aux = node->right;
      
      TreeNode* nodoMinimum = minimum(aux);
      
      node->pair = nodoMinimum->pair;

      nodoMinimum->parent->left = nodoMinimum->right;
      
      free(nodoMinimum);
    }
  }
}




void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
  
    TreeNode* node = tree->current;
    removeNode(tree, node);
}




PairTree * searchTreeMap(TreeMap * tree, void* key) 
{
  TreeNode *nodoActual = tree->root;
  
  if(tree->root == NULL)
  {
    return(NULL);
  }
  else
  {
    while(nodoActual != NULL)
    {
      if(is_equal(tree, nodoActual->pair->key, key) == 1)
      {
        tree->current = nodoActual;
        return (nodoActual->pair);
      }
      if(tree->lower_than(nodoActual->pair->key, key) == 0)
      {
        nodoActual = nodoActual->left;
      }
      else
      {
        nodoActual = nodoActual->right;
      }
    }
  }
  return NULL;
}



PairTree * upperBound(TreeMap * tree, void* key) 
{
  TreeNode *nodoAUX = tree->root;
  PairTree *parUB = searchTreeMap(tree, key);
  
  if(parUB != NULL)
  {
    return(parUB);
  }
  else
  {
    if(tree->root != NULL)
    {
      while(nodoAUX != NULL)
      {         
        tree->current = nodoAUX;
        if(tree->lower_than(nodoAUX->pair->key, key) == 0)
        {
          nodoAUX = nodoAUX->left;
        }
        else
        {
          nodoAUX = nodoAUX->right;
        }
      }
      if(tree->lower_than(tree->current->pair->key, key) == 0)
      {
        return(tree->current->pair);
      }
      else
      {
        if(tree->lower_than(tree->current->parent->pair->key, key) == 0)
        {
          return(tree->current->parent->pair);
        }
        return(NULL);
      }
    }
  }
  return (NULL);
}



PairTree * firstTreeMap(TreeMap * tree) 
{
  TreeNode *nodo = tree->root;
  while(nodo->left != NULL)
  {
    nodo = nodo->left;
  }
  return (nodo->pair);
}



PairTree * nextTreeMap(TreeMap * tree) 
{
  TreeNode *nodoActual = tree->current;
  TreeNode *aux = tree->root;
  char clave[30];
  strcpy(clave, nodoActual->pair->key);

  if(nodoActual->right != NULL)
  {
    nodoActual = nodoActual->right;
  
    while(nodoActual->left != NULL)
    {
      nodoActual = nodoActual->left;
    }
    
    tree->current = nodoActual;
    return(nodoActual->pair);
  }
  else
  {
    if(nodoActual == nodoActual->parent->left)
    {
      tree->current = nodoActual->parent;
      return(nodoActual->parent->pair);
    }
    else
    {
      while(aux->right == NULL)
      {
        aux = aux->right;
      }
      if(aux == nodoActual)
      {
        return NULL;
      }

      do
      {
        if(nodoActual->parent->left == nodoActual)
        {
          if(tree->lower_than(nodoActual->pair->key , clave) == 1)
          {
            tree->current = nodoActual->parent;
            return(nodoActual->parent->pair);
          }
        }
        nodoActual = nodoActual->parent;
        
      }while(nodoActual != tree->root);
    }
  }
  return(NULL);
}