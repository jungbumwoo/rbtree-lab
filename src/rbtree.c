#include "rbtree.h"
#include <stdlib.h>
#include <malloc.h>

// 총 개수 세는거도 만들어보자ㅏ

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(sizeof(rbtree), 1);
  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  node_t *child = t->root->left;
  delete_childtrees(child);
  free(t);
}

node_t *rbtree_insert(const rbtree *t, const key_t key)
{
  node_t *h, *p, *gp, *ggp;
  ggp = gp = p = t->root; // starts from root
  h = (node_t *)t->root->left;

  // find spot : while

  // TODO: implement insert
  struct node_t *h = malloc(sizeof(struct node_t));
  h->key = key;
  h->left = h->right = 0;
  h->color = RBTREE_RED;

  // if (key > p->key && p != t->root)
  //   p->right = h;
  // else
  //   p->left = t;

  return h; // Err:: return null ㅠㅠ
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

void delete_childtrees(node_t *ch)
{
  if (ch)
  {
    delete_childtrees(ch->left);
    delete_childtrees(ch->right);
    free(ch);
  }
}

node_t *rotate(const input_key, node_t *pivot, const rbtree *t) // 인자 &key로 줘야하나..?
{
  node_t *child, *gchild;
  if ((input_key > pivot->key || input_key == pivot->key) && pivot != t->root) // 중복 허용 안되는데 input_key == pivot->key는 왜있음?
    child = (node_t *)pivot->right;                                            // 그냥 pivot->right 하면 안됨?
}