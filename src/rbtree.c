#include "rbtree.h"

#include <malloc.h>

/* functions */

node_t *rotate(rbtree *t, const key_t key, node_t *pivot);

/* */

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
  // if head is empty, make it
  rbtree *temp_t = t;
  if (t->root == NULL)
  {
    // temp_t->root = (rbtree *)calloc(sizeof(rbtree), 1);
    temp_t->root = (node_t *)calloc(sizeof(node_t), 1);
  }

  node_t *h, *p, *gp, *ggp;
  // ggp = gp = p = (node_t *)t->root; // 그냥 t->root로 해야하나?
  // t->root->left = h;
  // h = t->root->left;
  h = (node_t *)t->root->left;

  node_t *new = (node_t *)malloc(sizeof(node_t));
  new->parent = new->left = new->right = NULL;
  new->key = key;
  new->color = RBTREE_RED;
  // t->root->left = new;
  h = new;

  return new;
  /*
  rbtree *temp_t = t;
  if (t->root == NULL)
  {
    temp_t->root = (rbtree *)calloc(sizeof(rbtree), 1);
  }

  node_t *new = (node_t *)malloc(sizeof(node_t));
  new->parent = new->left = new->right = NULL;
  new->key = key;
  new->color = RBTREE_RED;

  t->root->left = new;

  return new;
  */
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

/* functions */

node_t *rotate(rbtree *t, const key_t key, node_t *pivot)
{
  node_t *child, *gchild;
  if ((key > pivot->key || key == pivot->key) && pivot != t->root)
    child = (node_t *)pivot->right;
  else
    child = (node_t *)pivot->left;
}