#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include "ADTDErr.h"
#include "tree.h"

#define MAGIC 123456

#define LEFT 100
#define RIGHT 101

#define YES 200
#define NO 201

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

/*********** helping functions *************/
int FindTheLeav(Node* _father, Node** _leav, int _data);
Node* NodeMalloc(int _data);
Node* CreateRootNode(int _data);
void PrintIn(Node* _node);
void PrintPre(Node* _node);
void PrintPost(Node* _node);
int Found(Node* _node, int _data);

/*********** create *************/

Tree* TreeCreate()
{
    Tree* myTree;
    
    myTree = (Tree*)malloc(sizeof(Tree)); 
    if (myTree == NULL)
    {
        return NULL;
    }
    
    myTree-> m_root = NULL;
    myTree-> m_magic = MAGIC;
    
    return myTree;
}        
        
/*********** destroy *************/

void TreeDestroy(Tree* _tree)
{
    if (_tree == NULL)
    {
        return;
    }
    
    if (_tree->m_magic == MAGIC)
    {
        return; /* TODO delite node by node by recursia */
    }    
}

/*********** insert *************/

ADTErr TreeInsert(Tree* _tree, int _data)
{
    int ans;
    Node* leav;
    Node* nodeInsert;
  
    if (_tree == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    if (_tree->m_root == NULL)
    {
        _tree->m_root = CreateRootNode(_data);
        if ( _tree->m_root == NULL)
        {
            return ERR_ALLOCATION_FAILED;
        }        
        return ERR_OK; 
    }
    
    ans = FindTheLeav(_tree->m_root, &leav, _data);
    if (ans == ERR_SAME_DATA_EXISTS)
    {
        return ERR_SAME_DATA_EXISTS;
    }
    
    nodeInsert = NodeMalloc(_data);
    if (nodeInsert == NULL)
    {
        return ERR_ALLOCATION_FAILED;
    }
    
    nodeInsert->m_father = leav;
    if (ans == LEFT)
    {
        leav->m_left = nodeInsert;
    }
    else
    {
        leav->m_right = nodeInsert;
    }
    
    return ERR_OK;
}

/*********** finde *************/

int TreeIsDataFound(Tree* _tree, int _data)
{
    if (_tree == NULL)
    {
        return;
    }
    return Found(_tree-> m_root, _data);
}

int Found(Node* _node, int _data)
{
    int ans;
    if (_node == NULL)
    {
        return NO;
    }
    if (_node->m_data == _data)
    {
        return YES;
    } 
    Found(_node->m_left, _data);
    return Found(_node->m_right, _data);
}

/*********** print *************/

void TreePrint(Tree* _tree, TreeTraverse _treeTraversMode)
{
    if (_tree == NULL)
    {
        return;
    }
    
    if (_treeTraversMode ==  PRE_ORDER)
    {
        PrintPre(_tree->m_root);
    }
    
    else if (_treeTraversMode == POST_ORDER)
    {
        PrintPost(_tree->m_root);
    }
    
    else
    {
        PrintIn(_tree->m_root);
    }
}

void PrintIn(Node* _node)
{
    if (_node == NULL)
    {
        return;
    }
    PrintIn(_node->m_left);
    printf("%d ", _node->m_data);
    PrintIn(_node->m_right);
}

void PrintPre(Node* _node) /* TODO not warking well*/
{
    if (_node == NULL)
    {
        return;
    }
    printf("%d ", _node->m_data);
    PrintPre(_node->m_left);
    PrintPre(_node->m_right);
}

void PrintPost(Node* _node)
{
    if (_node == NULL)
    {
        return;
    }
    PrintPost(_node->m_left);
    PrintPost(_node->m_right);
    printf("%d ", _node->m_data);
}

/***********************************/
 
Node* CreateRootNode(int _data)
{
    Node* Root;

    Root = (Node*)malloc(sizeof(Node)); 
    if (Root == NULL)
    {
        return NULL;
    }
    
    Root->m_data = _data;
    Root->m_left = NULL;
    Root->m_right = NULL;
    Root->m_father = NULL;
    return Root;
}

int FindTheLeav(Node* _father, Node** _leav, int _data)
{
    Node* tempNode;
    Node* runNode;
    
    runNode = _father;
    while (runNode != NULL)
    {
        tempNode = runNode;
        if (_data == runNode->m_data)
        {
            return ERR_SAME_DATA_EXISTS;
        }
        
        if (_data < runNode->m_data)
        {
           runNode = runNode->m_left;
        }
        else
        {
            runNode = runNode->m_right;
        }   
    }    
    
    *_leav = tempNode;
    if (_data < tempNode-> m_data)
    {
        return LEFT;
    }
    else
    {
        return RIGHT;
    }   

}

    
Node* NodeMalloc(int _data)
{
    Node* newNode;
    newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }
    else
    {
        newNode->m_data = _data;
        newNode->m_left = NULL;
        newNode->m_right = NULL;
        return newNode;
    }
}
































      


