#include "rbtree.h"
#include <malloc.h>
#include <stdbool.h> // import false

/* global */
node_t *head;

/* functions */
node_t *rotate(rbtree *t, const key_t key, node_t *pivot);
void deleteAll(node_t *p);
void *head_node_to_t_root(rbtree *t);

/* romove func*/
bool isLeafNode(const node_t *p);
bool is2Node(const node_t *p);
bool delLeafNode(rbtree *t, key_t, node_t *delp, node_t *del);
bool redAsParent(rbtree *t, node_t *delgp, node_t *delp, node_t *sib);
key_t swapKey(node_t *del);
bool borrowKey(rbtree *t, node_t *delgp, node_t *delp, node_t *del, node_t *sib);
void bindNode(node_t *delp);
void removeSubtree(node_t *pNode);
/* */

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(sizeof(rbtree), 1);
  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  deleteAll(head);
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  if (t->root == NULL)
  {
    t->root = (node_t *)calloc(sizeof(node_t), 1);
    t->root->key = key;
    t->root->color = RBTREE_BLACK;
    t->root->left = t->root->right = NULL;

    // node_t *head_node;
    head = malloc(sizeof(node_t));
    head->left = t->root;
    head->color = RBTREE_BLACK;
    head->right = head->parent = NULL;

    return t->root;
  }

  node_t *curr, *p, *gp, *ggp;
  ggp = gp = p = (node_t *)head;
  curr = (node_t *)head->left;

  while (curr)
  {
    if (key == curr->key)
    {
      head_node_to_t_root(t);
      return NULL; // return false 말고 다른거 리턴해줘야하나? 중복방지
    }

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
      head->left->color = RBTREE_BLACK; // 여기 화살표 왜 빨강색이야 무섭게 ㄷㄷ
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

  curr = (node_t *)malloc(sizeof(node_t));
  curr->left = curr->right = NULL;
  curr->key = key;
  curr->color = RBTREE_RED;

  if (key > p->key && p != head)
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
  head->left->color = RBTREE_BLACK;

  head_node_to_t_root(t);
  return curr;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  node_t *search_point;
  // curr = (node_t *)t->root->left;
  search_point = (node_t *)head->left;

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
  node_t *min_pointer;
  min_pointer = head->left;

  while (min_pointer && min_pointer->left)
  {
    /* code */
    min_pointer = min_pointer->left;
  }

  return min_pointer;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  node_t *max_pointer;
  max_pointer = head->left;

  while (max_pointer && max_pointer->right)
  {
    /* code */
    max_pointer = max_pointer->right;
  }

  return max_pointer;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  node_t *delgp, *delp, *del, *sib;
  key_t value = p->key;
  delgp = delp = head;
  del = head->left;
  sib = 0; // sib = NULL??
  while (isLeafNode(del) == false)
  {
    if (del->color == RBTREE_BLACK)
    {
      if (redAsParent(t, delgp, delp, sib) == true)
      {
        // delgp 와 sib의 위치가 변했다. 새로 수정
        delgp = sib;
        if (del->key > delp->key || del->key == delp->key)
          sib = delp->left;
        else
          sib = delp->right;
      }
    }
    if (del != head->left && is2Node(del) == true)
    {
      // root 가 아니고 2노드이면 부풀려줘야함
      if (borrowKey(t, delgp, delp, del, sib) == false)
        bindNode(delp);
    }

    if (value == del->key)
      value = swapKey(del);

    delgp = delp;
    delp = del;
    if (value > del->key || value == del->key)
    {
      // swapkey로 인해 같은 값이 나올 수 있음.
      // In-order successor를 사용하기 때문에 오른쪽으로
      sib = del->left;
      del = del->right;
    }
    else
    {
      sib = del->right;
      del = del->left;
    }
  }
  // while 문 종료
  if (del->color == RBTREE_BLACK)
  { // del 이 black 이면 rotation
    if (redAsParent(t, delgp, delp, sib))
    {
      // delgp 와 sib의 위치가 변했다. 새로 수정
      delgp = sib;
      if (del->key > delp->key || del->key == delp->key)
        sib = delp->left;
      else
        sib = delp->right;
    }
  }
  if (del != head->left && is2Node(del))
  {
    if (!borrowKey(t, delgp, delp, del, sib))
      bindNode(delp);
  }

  if (delLeafNode(t, value, delp, del))
  {
    head_node_to_t_root(t);
    return true;
  }
  else
  {
    head_node_to_t_root(t);
    return false;
  }
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
  if ((key > pivot->key || key == pivot->key) && pivot != head)
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
    gchild->right = (node_t *)child;
  }
  if ((key > pivot->key || key == pivot->key) && pivot != head)
    pivot->right = gchild;
  else
    pivot->left = gchild;

  return gchild;
}

bool isLeafNode(const node_t *p)
{
  if (p == 0) // null ? 0 ??
    return false;
  if ((p->left == 0 || (p->left && p->left->color == RBTREE_RED && !p->left->left && !p->left->right)) &&
      (p->right == 0 || (p->right && p->right->color == RBTREE_RED && !p->right->left && !p->right->right)))
    return true;
  else
    return false;
}

bool is2Node(const node_t *p)
{
  if (p == 0)
    return false;
  if (p->color == RBTREE_RED)
    return false;
  if ((p->left == 0 && p->right == 0) || (p->left && p->right && p->left->color != RBTREE_RED && p->right->color != RBTREE_RED))
    return true;
  else
    return false;
}
bool redAsParent(rbtree *t, node_t *delgp, node_t *delp, node_t *sib)
{
  if (sib == 0 || sib->color != RBTREE_RED)
    return false;
  rotate(t, sib->key, delgp);
  sib->color = RBTREE_BLACK;
  delp->color = RBTREE_RED;
  return true;
}

bool borrowKey(rbtree *t, node_t *delgp, node_t *delp, node_t *del, node_t *sib)
{
  node_t *sibrc;
  if (is2Node(sib))
    return false;
  if (del->key > sib->key)
  {
    if (sib->left && sib->left->color == RBTREE_RED)
      sibrc = sib->left;
    else // 이거 다른 조건 이나 색깔 생각 안하고 그냥 오른쪽이라고 찍어도 되는건가ㅏ
      sibrc = sib->right;
  }
  else
  {
    if (sib->right && sib->right->color == RBTREE_RED)
      sibrc = sib->right;
    else // 이거 다른 조건 이나 색깔 생각 안하고 그냥 왼쪽이라고 찍어도 되는건가ㅏ
      sibrc = sib->left;
  }

  if ((delp->key > sib->key) != (sib->key > sibrc->key))
  {
    // double rotation
    rotate(t, sibrc->key, delp);
    rotate(t, sibrc->key, delgp);
    sib->color = RBTREE_BLACK;
    sibrc->color = RBTREE_RED;
  }
  else
  {
    // single rotation
    rotate(t, sib->key, delgp);
    sib->color = RBTREE_RED;
    sibrc->color = RBTREE_BLACK;
  }
  del->color = RBTREE_RED;
  delp->color = RBTREE_BLACK;

  if (head->left->color == RBTREE_RED)
    head->left->color = RBTREE_BLACK;
  return true;
}

void bindNode(node_t *delp)
{
  delp->color = RBTREE_BLACK;
  delp->left->color = RBTREE_RED;
  delp->right->color = RBTREE_RED;
}

key_t swapKey(node_t *del)
{
  node_t *cdd;
  cdd = del->right;
  while (cdd->left)
    cdd = cdd->left;
  del->key = cdd->key;
  return cdd->key;
}

bool delLeafNode(rbtree *t, key_t key, node_t *delp, node_t *del)
{
  if (key == del->key && !del->left && !del->right)
  {
    // (no child)
    free(del);
    if ((key > delp->key || key == delp->key) && delp != head)
      delp->right = NULL;
    else
      delp->left = NULL;
    return true;
  }
  else if (key == del->key) // del = black, tow children = red
  {
    node_t *ret;
    if (del->left)
    {
      del->left->right = del->right;
      ret = del->left;
      ret->color = RBTREE_BLACK;
      free(del);
    }
    else if (del->right)
    {
      del->right->left = del->left; // del->left가 있으면 바로 위의 가정법이 실행되는거아니려나..?
      ret = del->right;
      ret->color = RBTREE_BLACK;
      free(del);
    }
    if ((ret->key > delp->key || ret->key == delp->key) && delp != head)
      delp->right = ret;
    else
      delp->left = ret;
    return true;
  }
  else if (del->left && key == del->left->key)
  {
    free(del->left);
    del->left = NULL;
    return true;
  }
  else if (del->right && key == del->right->key)
  {
    free(del->right);
    del->right = NULL;
    return true;
  }
  else
  {
    return false;
  }
}

void deleteAll(node_t *p)
{
  if (p != NULL)
  {
    deleteAll(p->left);
    deleteAll(p->right);
    free(p);
  }
}

void *head_node_to_t_root(rbtree *t)
{
  t->root = head->left;
}