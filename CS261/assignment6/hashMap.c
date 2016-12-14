/*********************************************************************
** Program Filename: hashmap.c
** Author: Travis Robinson
** Date: 08/06/2015
** Description: hashMap implementation for assignment 6
** Input:Value and KeyType variables
** Output: N/A, integrates with main.c
*********************************************************************/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"



/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
 /*********************************************************************
** Function: _freeMap
** Description: frees all links and the map itself
** Parameters: pointer to hashMap
** Pre-Conditions: hashMap not null
** Post-Conditions: hashMap memory freed
*********************************************************************/
void _freeMap (struct hashMap * ht)
{
	/*write this*/
	for (int index = 0; index < ht->tableSize; index++)
    {
        if (ht->table[index] != NULL)
        {
            struct hashLink* current = ht->table[index];
            while (current != NULL)
            {
                hashLink* temp = current;
                current = current->next;
                //ValueType* val = &temp->value;
                //free(val);
                char* ptrKey = temp->key;
                free(ptrKey);
                free(temp);
            }
        }
    }
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/*
Resizes the hash table to be the size newTableSize
*/
/*********************************************************************
** Function: _setTableSize
** Description: resizes hash table
** Parameters: pointer to hashMap, int for new table size
** Pre-Conditions: map is not null
** Post-Conditions: table now has number of buckets equal to new table size
*********************************************************************/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	/*write this*/

    struct hashMap* newMap = createMap(newTableSize);
    for (int index = 0; index < ht->tableSize; index++)
    {
        struct hashLink* current = ht->table[index];
        while (current != NULL)
        {
            insertMap(newMap,current->key,current->value);
            current = current->next;
        }
    }
    hashLink ** temp = ht->table;
    int tempSize = ht->tableSize;
    ht->tableSize = newMap->tableSize;
    newMap->tableSize = tempSize;
    ht->table = newMap->table;
    newMap->table = temp;

    free(newMap);

 //   *newMap = *ht;
 //   deleteMap(newMap);
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".

 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.

 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
 /*********************************************************************
** Function: insertMap
** Description: inserts a new key with value into the map, or if key is already there
** gives it the new value
** Parameters: pointer to map, key, and value
** Pre-Conditions: map not null, key not null
** Post-Conditions: new key with value is in the map, or old key has the
** new value
*********************************************************************/
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{
	/*write this*/
	if (tableLoad(ht)>=LOAD_FACTOR_THRESHOLD)
    {
        _setTableSize(ht,2*ht->tableSize);
    }
	int index;
	if (HASHING_FUNCTION == 1)
    {
        index = stringHash1(k) % ht->tableSize;
    }
    else
    {
        index = stringHash2(k) % ht->tableSize;
    }
    if (index < 0)
    {
        index = index+ht->tableSize;
    }
//////////////////////////////////////////////////////////////////////
    struct hashLink* current = ht->table[index];
	if (containsKey(ht,k) != 0)
    {
        while (current != NULL)
        {
            if (strcmp(current->key,k) == 0)
            {
                current->value = v;
                return;
            }
            current = current->next;
        }
    }
    else
    {
        struct hashLink* newHashLink = malloc(sizeof(struct hashLink));
        newHashLink->key = k;
        newHashLink->value = v;
        newHashLink->next = ht->table[index];
        ht->table[index] = newHashLink;
        ht->count = ht->count+1;
    }
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.

 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.

 if the supplied key is not in the hashtable return NULL.
 */
 /*********************************************************************
** Function: atMap
** Description: returns the value at the selected key
** Parameters: pointer to hashMap, the key
** Pre-Conditions: map is not null
*********************************************************************/
ValueType* atMap (struct hashMap * ht, KeyType k)
{
	/*write this*/
	int index;
	if (HASHING_FUNCTION == 1)
    {
        index = stringHash1(k) % ht->tableSize;
    }
    else
    {
        index = stringHash2(k) % ht->tableSize;
    }
    if (index < 0)
    {
        index = index+ht->tableSize;
    }
    struct hashLink* current = ht->table[index];

    while (current != NULL)
    {
        if (strcmp(current->key,k) == 0)
        {
            ValueType* val = &ht->table[index]->value;
            return val;
        }
        current = current->next;
    }
	return NULL;
}

/*
 a simple yes/no if the key is in the hashtable.
 0 is no, all other values are yes.
 */
 /*********************************************************************
** Function: containsKey
** Description: returns 0 if the desired key is not in the map, else
** returns an int that isn't 0
** Parameters: pointer to hashMap, the key
** Pre-Conditions: hashMap not null
*********************************************************************/
int containsKey (struct hashMap * ht, KeyType k)
{
	/*write this*/
    int index;
	if (HASHING_FUNCTION == 1)
    {
        index = stringHash1(k) % ht->tableSize;
    }
    else
    {
        index = stringHash2(k) % ht->tableSize;
    }
    if (index < 0)
    {
        index = index+ht->tableSize;
    }

    struct hashLink* current = ht->table[index];
    while (current != NULL)
    {
        if (strcmp(current->key,k) == 0)
        {
            return 1;
        }
        else
        {
            current = current->next;
        }
    }
    return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
 /*********************************************************************
** Function: removeKey
** Description: removes the link associated with the desired key
** Parameters: pointer to hashMap, key
** Pre-Conditions: hashMap not null
*********************************************************************/
void removeKey (struct hashMap * ht, KeyType k)
{
	/*write this*/
    int index;
	if (HASHING_FUNCTION == 1)
    {
        index = stringHash1(k) % ht->tableSize;
    }
    else
    {
        index = stringHash2(k) % ht->tableSize;
    }
    if (index < 0)
    {
        index = index+ht->tableSize;
    }

    struct hashLink* current = ht->table[index];

    if (current == NULL)
    {
        return;
    }
    else if (strcmp(current->key,k) == 0);
    {
        struct hashLink* temp = current;;
        ht->table[index] = NULL;
        free(temp);
        ht->count = ht->count-1;
        return;
    }
    while (current->next != NULL)
    {
        if (strcmp(current->next->key,k) == 0)
        {
            struct hashLink* temp = current->next;
            current->next = current->next->next;
            free(temp);
            ht->count = ht->count-1;
        }
    }
}

/*
 returns the number of hashLinks in the table
 */
 /*********************************************************************
** Function: size
** Description: returns number of links
** Parameters: pointer to the hashMap
** Pre-Conditions: hashMap not null
*********************************************************************/
int size (struct hashMap *ht)
{
	/*write this*/
	//return 0;
    return ht->count;
}

/*
 returns the number of buckets in the table
 */
 /*********************************************************************
** Function: capacity
** Description: returns number of buckets
** Parameters: pointer to the hashMap
** Pre-Conditions: hashMap not null
*********************************************************************/
int capacity(struct hashMap *ht)
{
	/*write this*/
	return ht->tableSize;
	//return 0;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
  /*********************************************************************
** Function: emptyBuckets
** Description: returns number of empty buckets
** Parameters: pointer to the hashMap
** Pre-Conditions: hashMap not null
*********************************************************************/
int emptyBuckets(struct hashMap *ht)
{
	/*write this*/
    int count = 0;
	for (int index = 0; index < ht->tableSize; index++)
    {
        if (ht->table[index] == NULL)
        {
            count++;
        }
    }
    return count;
	//return 0;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)

 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
  /*********************************************************************
** Function: tableLoad
** Description: returns the table load as a float
** Since it didn't say to use full buckets, I'm assuming number of buckets
** is what's desired for this function
** Parameters: pointer to the hashMap
** Pre-Conditions: hashMap not null
*********************************************************************/
float tableLoad(struct hashMap *ht)
{
	/*write this*/
	return (float)((float)ht->count/(float)ht->tableSize);
	//return 0;
}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {
			printf("\nBucket Index %d -> ", i);
		}
		while(temp != 0){
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;
		}
	}
}


