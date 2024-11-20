#include <stdio.h>
#include <stdlib.h> /*malloc, calloc, size_t */
#include "vector.h"
#include "sort.h"
#include "ADTDErr.h"

/* genral helping functions */
void Swap(Vector* _vec, size_t _i, size_t _j);
size_t VecNumOfItems(Vector* _vec);
int GetFromVec(Vector* _vec, size_t _i);
void PrintArr(size_t* _arr, size_t _size);
void PrintIntArr(int* _arr, size_t _size);

/* quick helping functions */
void Quick(Vector* _vec, size_t _smallI, size_t _bigI);
int Partition(Vector* _vec, int _left, int _right);

/* selection helping functions */
size_t FindMinNumIndex(Vector* _vec, size_t _startIndex);
void SheftRightFromTo(Vector* _vec, size_t _from, size_t _to);

/* insertion and shell helping functions */
void InsertionByGap(Vector* _vec, size_t _gap);
void Insertion(Vector* _vec);

/* counting helping functions */
void Counting(Vector* _vec, size_t* _countArr, size_t _size);
void CumulativeSums(size_t* _countArr, size_t _size);
void Placing(Vector* _vec, int* _arr, size_t* _countArr, size_t _size);
void TransferToVector(Vector* _vec, int* _arr, size_t _size);

/* radix helping functions */
int FindMax (Vector* _vec, size_t _size);
int FindegMaxDigits(Vector* _vec);
void CuntingByDigit(Vector* _vec, int _digit, int* _helpArr);
void CountingD(Vector* _vec, size_t* _countArr, size_t _size, int _digit);
void PlacingD(Vector* _vec, int* _arr, size_t* _countArr, size_t _size, int _digit);


/*********************** babel ********************/    
ADTErr BabelSort(Vector* _vec)
{
    register int i, j, fleg;
    int num1, num2;
    size_t size; 

    if (_vec == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    VectorItemsNum(_vec, &size);
    if (size == 0)
    {
        return ERR_VECTOR_EMPTY;
    }
            
    for (j = 0; j < size; j++)
    {
        fleg = 0;
        for (i = 1; i < size - j; i++)
        {
            VectorGet(_vec, i - 1, &num1);    
            VectorGet(_vec, i, &num2);
            if (num2 < num1)
            {
                VectorSet(_vec, i - 1, num2);
                VectorSet(_vec, i, num1);
                fleg = 1; 
            }
        }
        if (fleg == 0)
        {
           return ERR_OK;
        }    
    }
    
    return ERR_OK;
}


/********************* shack ********************/    
ADTErr ShackSort(Vector* _vec)
{
    register int i, j, fleg;
    int num1, num2;
    size_t size; 

    if (_vec == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }

    VectorItemsNum(_vec, &size);
    if (size == 0)
    {
        return ERR_VECTOR_EMPTY;
    }
            
    for (j = 0; j < size; j++)
    {
        fleg = 0;
        
        /** forward **/
        for (i = j + 1; i < size - j; i++)
        {
            VectorGet(_vec, i - 1, &num1);    
            VectorGet(_vec, i, &num2);
            if (num2 < num1)
            {
                VectorSet(_vec, i - 1, num2);
                VectorSet(_vec, i, num1);
                fleg = 1; 
            }
        }
        if (fleg == 0)
        {
           return ERR_OK;
        }
        
        /** backward **/        
        for (i = size - j - 1; i > j; i--)
        {
            VectorGet(_vec, i - 1, &num1);    
            VectorGet(_vec, i, &num2);
            if (num2 < num1)
            {
                VectorSet(_vec, i - 1, num2);
                VectorSet(_vec, i, num1);
                fleg = 1; 
            }
        }
        if (fleg == 0)
        {
           return ERR_OK;
        }   
    }
    
    return ERR_OK;
}


/********************* quick ********************/    
ADTErr QuickSort(Vector* _vec)
{
    size_t size;
    
    if (_vec == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
     
    VectorItemsNum(_vec, &size);
    if (size == 0)
    {
        return ERR_VECTOR_EMPTY;
    }
    
    Quick(_vec, 0, size - 1);
    
    return ERR_OK;
}
  
void Quick(Vector* _vec, size_t _smallI, size_t _bigI)
{
    size_t pivot;
    if (_smallI < _bigI)
    {
        pivot = Partition(_vec, _smallI, _bigI);
        
        Quick(_vec, _smallI, pivot - 1);
        Quick(_vec, pivot + 1, _bigI); 
    }
}

/* TODO partitions stil donot work for evry case */
int Partition(Vector* _vec, int _left, int _right)
{
	int _leftVal, _rightVal;
	int pivotVal, pivotIndex;
	pivotIndex = _left - 1;
	
	VectorGet(_vec, _left, &_leftVal);
	VectorGet(_vec, _right, &_rightVal);
	VectorGet(_vec, pivotIndex, &pivotVal);
	
	for(_left; _left <= _right; _left++)
	{
		VectorGet(_vec, _left, &_leftVal);
		if(_leftVal >= pivotVal)
		{
			for(_right; _right >= _left; _right--)
			{
				VectorGet(_vec, _right, &_rightVal);
				if(_rightVal < pivotVal)
				{
					Swap(_vec, _leftVal, _rightVal);
					VectorGet(_vec, _left, &_leftVal);
					VectorGet(_vec, _right, &_rightVal);
					break;
				}	
			}
		}
	}
	VectorGet(_vec, _right, &_rightVal);
	Swap(_vec, _leftVal, _rightVal);
	VectorGet(_vec, _right, &_rightVal);
	return _right + 1;
}


/******************** Shell **********************/
ADTErr ShellSort(Vector* _vec)
{
    size_t size;    
    
    if (_vec == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }

    VectorItemsNum(_vec, &size);
    if (size == 0)
    {
        return ERR_VECTOR_EMPTY;
    }
    InsertionByGap(_vec, size / 2);
    return ERR_OK;    
}

/* insertion by gap */
void InsertionByGap(Vector* _vec, size_t _gap)
{
    int numToInsert;
    int i, j, k; 
    size_t size = VecNumOfItems(_vec);
    if (_gap == 0)
    {
        return;
    } 
    
    for (j = 0; j < _gap; j++)
    {
        for (i = j + _gap; i < size; i += _gap)
        {
            numToInsert = GetFromVec(_vec, i);
            for (k = i - _gap; k >= 0; k -= _gap)
            {
                if (numToInsert < GetFromVec(_vec, k))
                {
                    Swap(_vec, k, k + _gap); 
                }
                else
                {
                    break;       
                }
            } 
        }
    }
    InsertionByGap(_vec, _gap / 2);        
}


/********************** Insertion ********************/
ADTErr InsertionSort(Vector* _vec)
{
    size_t size;    
    
    if (_vec == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }

    VectorItemsNum(_vec, &size);
    if (size == 0)
    {
        return ERR_VECTOR_EMPTY;
    }
    Insertion(_vec);
    return ERR_OK;
}

/* insertion (gap = 1)*/
void Insertion(Vector* _vec)
{
    int numToInsert;
    int i, j; 
    size_t size = VecNumOfItems(_vec); 
    for (i = 1; i < size; i++)
    {
        numToInsert = GetFromVec(_vec, i);
        for (j = i - 1; j >= 0; j--)
        {
            if (numToInsert < GetFromVec(_vec, j))
            {
               Swap(_vec, j, j + 1); 
            }
            else
            {
                break;       
            }
        }
    }    
}


/********************* select ********************/
ADTErr SelectionSort (Vector* _vec)
{
    int minNum;
    size_t i, minIndex; 
    size_t numOfItems = VecNumOfItems(_vec);
     
    if (_vec == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    if (numOfItems == 0)
    {
        return ERR_VECTOR_EMPTY;
    }
    
    for (i = 0; i < numOfItems - 1; i++)
    {    
        minIndex = FindMinNumIndex(_vec, i);
        minNum = GetFromVec(_vec, minIndex);
  
        SheftRightFromTo(_vec, i, minIndex);
        VectorSet(_vec, i, minNum);
    }
    return ERR_OK;
}

/* min index */
size_t FindMinNumIndex(Vector* _vec, size_t _startIndex)
{
    size_t minIndex = _startIndex; 
    int min = GetFromVec(_vec, _startIndex);
    size_t numOfItems = VecNumOfItems(_vec);
    for (; _startIndex < numOfItems; _startIndex++)
        {
            if (min > GetFromVec(_vec, _startIndex))
            {
                min = GetFromVec(_vec, _startIndex);             
                minIndex = _startIndex;
            }                     
        }
   return minIndex;     
}

/* sheft right */
void SheftRightFromTo(Vector* _vec, size_t _from, size_t _to)
{
    int temp;
    size_t i;
    for (i = _to; i > _from; i--)
    {
        temp = GetFromVec(_vec, i - 1);
        VectorSet(_vec, i, temp);    
    }
}

/* TODO add a min valu to */ 
/******************** counting **********************/
ADTErr CountingSort(Vector* _vec, int _maxValue)
{
    size_t size;    
    size_t* countArr;   
    int* helpArr;
    
    if (_vec == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }

    VectorItemsNum(_vec, &size);
    if (size == 0)
    {
        return ERR_VECTOR_EMPTY;
    } 
    
    countArr = (size_t*)calloc(_maxValue + 1, sizeof(size_t));
    helpArr = (int*)malloc(size * sizeof(int));
    if (countArr == NULL || helpArr == NULL)
    {
        return ERR_NOT_INITIALIZED; /* TODO cheang the error*/    
    }
    
    Counting(_vec, countArr, size);
    CumulativeSums(countArr, _maxValue);
    Placing(_vec, helpArr, countArr, size);
    TransferToVector(_vec, helpArr, size);
    
    free(countArr);
    free(helpArr);
    
    return ERR_OK;
}

/* Counting */
void Counting(Vector* _vec, size_t* _countArr, size_t _size)
{
    size_t i;
    int temp;
    for (i = 0; i < _size; i++)
    {
        temp = GetFromVec(_vec, i);
        _countArr[temp] += 1; 
    }
}

/* cumulative sums */
void CumulativeSums(size_t* _countArr, size_t _size)
{
    size_t i;
    for (i = 1; i <= _size; i += 1)
    {
        _countArr[i] = _countArr[i] + _countArr[i - 1];
    }
}

/* placing */
void Placing(Vector* _vec, int* _arr, size_t* _countArr, size_t _size)
{
    size_t i;
    size_t plac;
    int temp;
    for (i = _size; i > 0;)
    {
        i--;
        temp = GetFromVec(_vec, i);
        plac = _countArr[temp];
        _arr[plac -1] = temp;
         
        _countArr[temp] -= 1; 
    }
}

/* transper to the vector */
void TransferToVector(Vector* _vec, int* _arr, size_t _size)
{
    size_t i;
    for (i = 0; i < _size; i += 1)
    {
        VectorSet(_vec, i, _arr[i]);
    }
}


/******************** radix **********************/
ADTErr RadixSort(Vector* _vec)
{   
    int i;
    size_t size; 
    int maxDigits;
    int* helpArr;
    if (_vec == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }

    VectorItemsNum(_vec, &size);
    if (size == 0)
    {
        return ERR_VECTOR_EMPTY;
    }
    
    maxDigits = FindegMaxDigits(_vec); 
    
    helpArr = (int*)malloc(size * sizeof(int));
    if (helpArr == NULL)
    {
        return ERR_NOT_INITIALIZED; /* TODO cheang the error*/    
    }
    
    for (i = 1; i <= maxDigits; i += 1)
    {
        CuntingByDigit(_vec, i, helpArr); 
    }
    
    free(helpArr);    
    return ERR_OK;
}

/* Counting by digits */
void CuntingByDigit(Vector* _vec, int _digit, int* _helpArr)
{
    size_t size;    
    size_t countArr [10] = {0};   
    size = VecNumOfItems(_vec);
     
    CountingD(_vec, countArr, size, _digit);
    CumulativeSums(countArr, 9);
    PlacingD(_vec, _helpArr, countArr, size, _digit);
    TransferToVector(_vec, _helpArr, size);
}

/* Counting for radix */
void CountingD(Vector* _vec, size_t* _countArr, size_t _size, int _digit)
{
    size_t i;
    int temp;
    for (i = 0; i < _size; i++)
    {
        temp = FindNumDigit(_vec, i, _digit);
        _countArr[temp] += 1; 
    }
}

/* num of digits */
int FindNumDigit(Vector* _vec, size_t _index, int _digit)
{
    int i;
    int num = GetFromVec(_vec, _index);
    
    if (_digit == 1)
    {
        num = num % 10;
    }
    
    for (i = 1; i < _digit; i += 1)
    {
        num = num / 10;
    }
    
    num = num % 10;

    return num;
}

/* placing for radix */
void PlacingD(Vector* _vec, int* _arr, size_t* _countArr, size_t _size, int _digit)
{
    size_t i;
    size_t plac;
    int temp, tempDigit;
    for (i = _size; i > 0;)
    {
        i--;
        temp = GetFromVec(_vec, i);
        tempDigit = FindNumDigit(_vec, i, _digit);
        plac = _countArr[tempDigit];
        _arr[plac -1] = temp;
         
        _countArr[tempDigit] -= 1; 
    }
}

/* Findeg Max Digits */
int FindegMaxDigits(Vector* _vec)
{
    int i;
    int count = 1;
    size_t size = VecNumOfItems(_vec);
    int max = FindMax (_vec, size);
    if (max == 0)
    {
        return 1;
    }
    for(i = 10; ; i *= 10)
    {
        if (max % i == max)
        {
            return count;
        }
        count++;
    }
} 

/* Findeg Max Num */
int FindMax (Vector* _vec, size_t _size)
{
    int max;
    size_t i;
    max = GetFromVec(_vec, 0);
    for (i = 1; i < _size; i += 1)
    {
        if (max < GetFromVec(_vec, i))
        {
            max = GetFromVec(_vec, i);     
        }
    }
    return max;
} 


/********************* merge ********************/
ADTErr MergeSort(Vector* _vec)
{
    size_t size;    
    
    if (_vec == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }

    VectorItemsNum(_vec, &size);
    if (size == 0)
    {
        return ERR_VECTOR_EMPTY;
    }    
}


/************ genral helping functions ***********/
/* swap */
void Swap(Vector* _vec, size_t _i, size_t _j)
{
    int data_i, data_j;
    VectorGet(_vec, _i, &data_i);
    VectorGet(_vec, _j, &data_j);
    
    VectorSet(_vec, _i, data_j);
    VectorSet(_vec, _j, data_i);
}

/* get from vector */
int GetFromVec(Vector* _vec, size_t _i)
{
    int num;
    VectorGet(_vec, _i, &num);
    return num;
}

/* vector size */
size_t VecNumOfItems(Vector* _vec)
{
    size_t numOfItems;
    VectorItemsNum(_vec, &numOfItems);
    return numOfItems;
}

/* ptint arr of size_t */
void PrintArr(size_t* _arr, size_t _size)
{
    int i;
    for (i = 0; i < _size; i += 1)
    {
        printf("%ld ", _arr[i]);
    } 
    printf("\n");
}

/* ptint arr of int */
void PrintIntArr(int* _arr, size_t _size)
{
    int i;
    for (i = 0; i < _size; i += 1)
    {
        printf("%d ", _arr[i]);
    } 
    printf("\n");
}


/************* search *****************/
size_t Search1(int* _arr, size_t _size, int _num)
{
    int i;
    if (_arr == NULL)
    {
        return;
    }
    for (i = 0; i < _size; i += 1)
    {
        if (_arr[i] == _num)
        {
            return i;
        }
    }
    return -1;
}  


size_t Search2(int* _arr, size_t _size, int _num)
{
    int temp, i;
    if (_arr == NULL)
    {
        return;
    }
    
    if (_arr[_size - 1] == _num)
    {
        return _size - 1;
    }
    else
    {
        temp = _arr[_size - 1];
        _arr[_size - 1] = _num;
        for (i = 0; ;i += 1)
        {
            if (_arr[i] == _num)
            {
                break;
            }
        }
    }    
    _arr[_size - 1] = temp;
    if (i == _size - 1)
    {
        return -1;
    }
    return i;
}  




























