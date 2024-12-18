#include <stdio.h>
#include "tree.h"
#include "ADTDErr.h"
#define ROOT_NUMBER 50
#define MAGIC 123456

void CheckCreat1();
void CheckInsert1();
void CheckInsert2();
void CheckInsert3();
void CheckInsert4();
void CheckInsert5();

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

int main(void)
{
    /* chking the print */
    int ans;
    int i;
    int x;
    Tree* myTree;
    myTree = TreeCreate();
    for (i = 0; i < 3; i += 1)
    {
        x = rand() % 10 ;
        printf("%d ",x);
        TreeInsert(myTree, x);
    }
    printf("\n");
 
    TreePrint(myTree, IN_ORDER);
    printf("\n");
  
    TreePrint(myTree, PRE_ORDER);
    printf("\n");
    
    TreePrint(myTree, POST_ORDER);
    printf("\n");
           
    CheckCreat1();
    CheckInsert1();
    CheckInsert2();
    CheckInsert3();
    CheckInsert4();
    CheckInsert5();
        
    return 0;
}

void CheckCreat1()
{
    Tree* myTree = TreeCreate(); 
    if (myTree->m_magic == MAGIC && myTree->m_root == NULL){
        printf("Check Creat 1: pass\n");
    }else{
        printf("Check Creat 1: fail\n");
    }    
}

void CheckInsert1() /* insert first data */
{
    int ans;
    Tree* myTree = TreeCreate();
    ans = TreeInsert(myTree, 5); 
    if (myTree->m_root->m_father == NULL && myTree->m_root->m_left == NULL && myTree->m_root->m_right == NULL && myTree->m_root->m_data == 5 && ans == ERR_OK){
        printf("Check Insert 1: pass\n");
    }else{
        printf("Check Insert 1: fail\n");
    }    
}

void CheckInsert2() /* same data insert */
{
    int ans;
    Tree* myTree = TreeCreate();
    ans = TreeInsert(myTree, 5);
    ans = TreeInsert(myTree, 5); 
    if (ans == ERR_SAME_DATA_EXISTS){
        printf("Check Insert 2: pass\n");
    }else{
        printf("Check Insert 2: fail\n");
    }    
}

void CheckInsert3() /* small data insert */
{
    int ans;
    Tree* myTree = TreeCreate();
    ans = TreeInsert(myTree, 5);
    ans = TreeInsert(myTree, 4); 
    if (ans == ERR_OK && myTree->m_root->m_left->m_data == 4){
        printf("Check Insert 3: pass\n");
    }else{
        printf("Check Insert 3: fail\n");
    }    
}

void CheckInsert4() /* big data insert */
{
    int ans;
    Tree* myTree = TreeCreate();
    ans = TreeInsert(myTree, 5);
    ans = TreeInsert(myTree, 6); 
    if (ans == ERR_OK && myTree->m_root->m_right->m_data == 6){
        printf("Check Insert 4: pass\n");
    }else{
        printf("Check Insert 4: fail\n");
    }    
}

void CheckInsert5() /* null insert */
{
    int ans;
    Tree* myTree = TreeCreate();
    ans = TreeInsert(NULL, 5); 
    if (ans == ERR_NOT_INITIALIZED){
        printf("Check Insert 5: pass\n");
    }else{
        printf("Check Insert 5: fail\n");
    }    
}









