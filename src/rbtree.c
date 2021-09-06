#include "rbtree.h"

#include <malloc.h>

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(sizeof(rbtree), 1);
  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(const rbtree *t, const key_t key)
{
  rbtree *virtual_t = t;
  if (t->root == NULL)
  {
    virtual_t->root = (node_t *)calloc(sizeof(node_t), 1);
  }

  node_t *curr, *p, *gp, *ggp;
  ggp = gp = p = (node_t *)t->root;
  curr = (node_t *)t->root->left;

  // while

  node_t *temp = (node_t *)malloc(sizeof(node_t));
  temp->left = temp->right = NULL;
  temp->key = key;
  temp->color = RBTREE_RED;

  if (key > p->key && p != t->root)
    p->right = temp;
  else
    p->left = temp;

  return temp;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

int rbtree_erase(const rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}