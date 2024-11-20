#ifndef __LIST_H__
#define __LIST_H__

typedef struct Person Person; 
struct Person
{
    int     m_id;         /* Primary Key */
    char    m_name[128];
    int     m_age;
    Person* m_next;
};


/*  insert head 
description: insert a person to the begining of the list
             not: the insert head do not keep order (see ListInsertByKey function)    
input: 1. pointer of the head of the list
       2. pointer of the person to insert 
output: pointer of the head of the list
error:  do not insert if _p = NULL            */
Person* ListInsertHead(Person* _head ,Person* _p);


/*  remove head 
description: remove a person to the begining of the list
input: 1. pointer of the head of the list
       2. pointer to get beck the pointer of removed person 
output: pointer of the head of the list
error:                                        */ 
Person* ListRemoveHead(Person* _head, Person** _item);


/*  insert by key 
description: insert a person in order of id.
             not: 1. canot insert a person with same id as one of the persons in the list
                  2. insert the person befor the first aver person with higher id
input: 1. pointer of the head of the list
       2. _key (id number of the person)
       3. pointer of the person to insert  
output: pointer of the head of the list
error:  do not insert if _p = NULL          */
Person* ListInsertByKey(Person* _head, int _key, Person* _p);


/*  insert by key recursia
description: insert a person in order of id usinig recursia (same functional as ListInsertByKey function)
             not: 1. canot insert a person with same id as one of the persons in the list
                  2. insert the person befor the first aver person with higher id
input: 1. pointer of the head of the list
       2. _key (id number of the person)
       3. pointer of the person to insert  
output: pointer of the head of the list
error:  do not insert if _p = NULL          */
Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p);


/*  remove by key
description: remove a person with spesific id
input: 1. pointer of the head of the list
       2. _key (id number of the person to remov)
       3. pointer to get beck the pointer of removed person 
output: pointer of the head of the list
error:                                      */
Person* ListRemoveByKey(Person* _head, int _key, Person* *_p);


/*  remove by key recursia
description: remove a person with spesific id recursia (same functional as ListRemoveByKey function)
input: 1. pointer of the head of the list
       2. _key (id number of the person to remov)
       3. pointer to get beck the pointer of removed person 
output: pointer of the head of the list
error:                                      */
Person* ListRemoveByKeyRec(Person* _head, int _key, Person**_p);


/*  print
description: print the list
input:  pointer of the head of the list 
output: void
error:                                      */
void PrintList(Person* _head);


#endif   /* __LIST_H__ */








