/* 
 *   abstractSortBinary.h
 *
 *   Header file for a binary tree's functions 
 *
*/

#ifndef ABSTRACTSORTBINARY_H
#define ABSTRACTSORTBINARY_H

/*insert node to binary Tree by doing recursive
 *Arguments
 *	current								- current node that we are at of Bianry tree
 *	newNode								- New node to insert in Binary tree
 */
void insertBinaryNode(void* current, void* newNode);

/*allocated memory for new node and call insert function to insert node to binary tree
 *Arguments
 *	newNodeData						- data of new node in form PRODUCT_T
*/
void createBinaryNode(void* newNodeData);

/*Print the data of each node in binary tree by using in order
 *Arguments
 *	current								- current node that we are at of Bianry tree
 */
void printAllBinary(void* currentNode);

/*Free all memory allocated of binary tree used
 *Arguments
 *	current								- current node that we are at of Bianry tree
 */
void freeBinaryTree(void* currentNode);

#endif