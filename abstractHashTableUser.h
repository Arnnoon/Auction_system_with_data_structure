/* 
 *   abstractHashTableUser.h
 *
 *   Header file for a hash table that uses strings as keys
 *   and stores pointers to arbitrary structures as values
 *
 *   Created by Sally Goldin on 5 March 2012 for CPE 113
 *   Modified with permission by [Phoramint Taweeros] on [05/apr/2021].
 *
 *   Edit: change all name each Function that include word User to make clear
 *   meaning must use in user structure only and anouther structure and code 
 *   have not change. Change only name of function.
 */
 
 /*  Based on code by Sally Goldin from [abstractHashTable.h]
    Used with permission.
*/

#ifndef ABSTRACTHASHTABLEUSER_H
#define ABSTRACTHASHTABLEUSER_H

/* Return the number of slots in the hash table.
 */
int hashTableUserSize();

/* Return the number of items currently stored in the hash table.
 */
int hashTableItemUserCount();


/* Initialize the hash table.
 * Arguments
 *    size                - How many slots in the table
 *                          Must be 1 or greater. We assume the caller
 *                          has checked this.
 *    hashFunction        - Function that takes a string and returns an int
 *                          which will be the index into the table.
 * Returns 1 if successful, 0 if some error occurred.
 */
int hashTableUserInit(int size, unsigned int (*hashFunction)(char* key));


/* Free the hash table.
 */
void hashTableUserFree();


/* Insert a value into the hash table.
 * Arguments 
 *    key                 - character string key
 *    data                - data to store in the table
 *    pCollision          - set to true if there was a collision storing
 *                          the data, else false 
 * Returns true (1) unless hash table has not been initialized or
 * we can't allocate memory, in which case returns false (0)
 */
int hashTableUserInsert(char* key, void* data,int* pCollision);


/* Remove a value from the hash table.
 * Arguments 
 *    key                 - character string key
 * Returns the data removed, or NULL if it is not found or table not init'd .
 */
void* hashTableUserRemove(char* key);


/* Look up a value in the hash table.
 * Arguments 
 *    key                 - character string key
 * Returns the data associated with the key, or NULL if 
 * data associated with the key is not found.
 */
void* hashTableUserLookup(char* key);


#endif
