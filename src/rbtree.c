#include "rbtree.h"
#include <malloc.h>
#include <stdbool.h> // import false

/* functions */
node_t *rotate(const rbtree *t, const key_t key, node_t *pivot);

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

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  if (t->root == NULL)
  {
    t->root = (node_t *)calloc(sizeof(node_t), 1);
    t->root->color = RBTREE_BLACK;
  }

  node_t *curr, *p, *gp, *ggp;
  ggp = gp = p = (node_t *)t->root;
  curr = (node_t *)t->root->left;

  while (curr)
  {
    if (key == curr->key)
      return NULL; // return false 말고 다른거 리턴해줘야하나? 중복방지

    // 자식 노드 둘 다 있고 빨강이면 color promotion
    if (curr->left && curr->right && curr->left->color == RBTREE_RED && curr->right->color == RBTREE_RED)
    {
      curr->color = RBTREE_RED;
      curr->left->color = curr->right->color = RBTREE_BLACK;

      // 부모가 빨강이면 rotation
      if (p->color == RBTREE_RED)
      {
        gp->color = RBTREE_RED;
        if ((key > gp->key) != (key > p->key))
          p = rotate(t, key, gp);
        curr = rotate(t, key, ggp);
        curr->color = RBTREE_RED;
      }

      // 뿌리는 항상 검정
      t->root->left->color = RBTREE_BLACK; // 여기 화살표 왜 빨강색이야 무섭게 ㄷㄷ
    }
    // 한 칸씩 내려가기
    ggp = gp;
    gp = p;
    p = curr;
    if (key > curr->key)
      curr = curr->right;
    else
      curr = curr->left;
  }

  // while
  curr = (node_t *)malloc(sizeof(node_t));
  curr->left = curr->right = NULL;
  curr->key = key;
  curr->color = RBTREE_RED;

  if (key > p->key && p != t->root)
    p->right = curr;
  else
    p->left = curr;

  // 부모가 빨강이면 회전!

  if (p->color == RBTREE_RED)
  {
    gp->color = RBTREE_RED;
    if ((key > gp->key) != (key > p->key))
      p = rotate(t, key, gp);
    curr = rotate(t, key, ggp);
    curr->color = RBTREE_RED;
  }

  // root는 항상 검정으로
  t->root->left->color = RBTREE_RED;

  return curr;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  node_t *search_point;
  // curr = (node_t *)t->root->left;
  search_point = (node_t *)t->root->left;

  while (search_point)
  {
    /* code */
    if (key == search_point->key)
      return search_point;

    if (search_point->key > key)
      search_point = search_point->right;
    else
      search_point = search_point->left;
  }
  // TODO: implement find
  return NULL;
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

int rbtree_erase(rbtree *t, node_t *p)
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
node_t *rotate(const rbtree *t, const key_t key, node_t *pivot)
{
  node_t *child, *gchild;
  if ((key > pivot->key || key == pivot->key) && pivot != t->root)
    child = (node_t *)pivot->right;
  else
    child = (node_t *)pivot->left;

  if (key > child->key || key == child->key) //Rotate Left
  {
    gchild = (node_t *)child->right;
    child->right = gchild->left;
    gchild->left = (node_t *)child;
  }
  else
  {
    gchild = (node_t *)child->left;
    child->left = gchild->right;
    gchild->right = child->left;
  }
  if ((key > pivot->key || key == pivot->key) && pivot != t->root)
    pivot->right = gchild;
  else
    pivot->left = gchild;

  return gchild;
}