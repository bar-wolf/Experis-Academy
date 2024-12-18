#include <stdio.h>
#include "tree.h"
#define YES 1
#define NO 0
#define ERR_NOT_INCILAIZD -1

struct Tree
{
    Node*   m_root;
    int     m_magic;
};

struct Node
{
    int     m_data;
    Node*   m_left;
    Node*   m_right;
    Node*   m_father;
};

int IsFullTree (Tree* _tree);
int IsFull (Node* _node, int _ans);

int main (void)
{
    int i;
    int x;
    Tree* myTreeA = TreeCreate(); 
    Tree* myTreeB = TreeCreate();

    TreeInsert(myTreeA, 10);
    TreeInsert(myTreeA, 20);
    TreeInsert(myTreeA, 15);
  

    
    TreeInsert(myTreeB, 10);
    TreeInsert(myTreeB, 100);
    TreeInsert(myTreeB, 11);
    TreeInsert(myTreeB, 3);
    
    printf ("tree the same...%d\n", ArrSimilerTree(myTreeA, myTreeB));
    
    
    /*for (i = 0; i < 3; i += 1)
    {
        x = rand() % 10 ;
        printf("%d ",x);
        TreeInsert(myTree, x);
    }
    printf("\n"); */   
        
    return 0;
}

/************ arr similer tree? ****************/

int ArrSimilerTree(Tree* _treeA, Tree* _treeB)
{
    if (_treeA == NULL || _treeB == NULL)
    {
        return ERR_NOT_INCILAIZD;
    }
    return ArrSimiler(_treeA->m_root, _treeB->m_root); 
}
 /* TODO */
int ArrSimiler(Node* _nodeA, Node* _nodeB)
{
    if (_nodeA == NULL && _nodeB == NULL)
    {
        return YES;
    }
    
    if ( (_nodeA->m_right != NULL && _nodeB->m_right != NULL) || (_nodeA->m_left != NULL && _nodeB->m_left != NULL) )
    {
        return ( ArrSimiler(_nodeA->m_right, _nodeB->m_right) && ArrSimiler(_nodeA->m_left, _nodeB->m_left) );   
    }

    else if ( (_nodeA->m_right == NULL && _nodeB->m_right == NULL) || (_nodeA->m_left == NULL && _nodeB->m_left == NULL) )
    {
        return YES;
    }

    else
    {
        return NO;
    }    
}


/************ is full tree? ****************/

int IsFullTree (Tree* _tree)
{
    if (_tree == NULL)
    {
        return ERR_NOT_INCILAIZD; 
    }  
    return IsFull(_tree->m_root, YES);
}

int IsFull (Node* _node, int _ans)
{

    if (_node == NULL)
    {
        return YES;
    }
    
    if ( (_node->m_left != NULL && _node->m_right == NULL) || (_node->m_left == NULL && _node->m_right != NULL) )
    {
        return NO;
    }
    
    if (_ans == NO)
    {
        return NO;
    }
    
    _ans = IsFull(_node->m_left, YES);
    
    if (_ans == NO)
    {
        return NO;
    }
    
    _ans = IsFull(_node->m_right, YES);
    
    return _ans;
}












