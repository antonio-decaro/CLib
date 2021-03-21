typedef struct c_node* Node;

typedef struct c_list* List;

/**
 * @brief Creates a Double Linked List. 
 * @return an empty list.
 */
List newList();

/**
 * @brief Creates a list starting from an array.
 * 
 * @param array the array of data.
 * @param size the size of the array.
 * @return a list containing the same elements of the array.
 */
List newFromArray(void** array, int size);

/**
 * @brief Insert items inside the double linked list.
 * 
 * @param list the list.
 * @param el a pointer to the element to insert.
 * @param pos the position in which insert the new element.
 */
void insertListItem(List list, void* el, int pos);

/**
 * @brief Appends to the end of the list an element.
 * 
 * @param list the list.
 * @param el the element to append at the end of the list.
 */
void appendListItem(List list, void* el);

/**
 * @brief Removes an element fromt the list.
 * 
 * @param list the list.
 * @param pos the position of the element.
 */
void removeListItem(List list, int pos);

/**
 * @brief Get the List Item object on a given position.
 * 
 * @param list the list.
 * @param pos the position of the element.
 * @return the element on that position.
 */
void* getListItem(List list, int pos);

/**
 * @brief Removes the first element of the list and returns it.
 * 
 * @param list the list.
 * @return the first element.
 */
void* popListItem(List list);

/**
 * @brief Inserts an element to the beginning of the list.
 * 
 * @param list the list.
 * @param el the element.
 */
void pushListItem(List list, void* el);

/**
 * @brief Returns the size of the list.
 * 
 * @param list the list.
 * @return the list size.
 */
int listSize(List list);

/**
 * @brief Removes all the items in the list.
 * 
 * @param list the list.
 */
void clearList(List list);

/**
 * @brief Convert the list into an array.
 * 
 * @param list the list.
 * @return a pointer to the allocated array.
 */
void** listIntoArray(List list);

/**
 * @brief Get the List Iterator object that can be used to move on the list efficiently.
 * 
 * @param list the list.
 * @return the iterator pointing to the first element of the list.
 */
Node getListIterator(List list);

/**
 * @brief Get the List Iterator object that can be used to move on the list efficiently.
 * 
 * @param list the list.
 * @return the iterator pointing to the last element of the list.
 */
Node getLastListIterator(List list);

/**
 * @brief Get the Next Iterator object starting from the current iterator.
 * 
 * @param list the list.
 * @param iterator the current iterator.
 * @return the next iterator.
 */
Node getNextIterator(List list, Node iterator);

/**
 * @brief Get the Previously Iterator object starting from the current iterator.
 * 
 * @param list the list.
 * @param iterator the current iterator.
 * @return the prev iterator.
 */
Node getPrevIterator(List list, Node iterator);

/**
 * @brief Get the element associated to the current iterator.
 * 
 * @param iterator the current iterator.
 * @return a pointer to the element containing that data.
 */
void* getItemIterator(Node iterator);

/**
 * @brief Inserts an element at position of the current iterator.
 * 
 * @param iterator the current iterator.
 * @param list the list.
 * @param el the element to insert.
 */
void insertItemIterator(Node iterator, List list, void* el);

/**
 * @brief Removes the element associated to the current iterator from the list.
 * 
 * @param iterator the current iterator.
 * @param list the list.
 */
void removeItemIterator(Node iterator, List list);

/**
 * @brief Moves the iterator of a certain amount of hopes.
 * 
 * @param iterator the current iterator.
 * @param list the list.
 * @param count the number of hopes. if (count < 0) then the iterator will moves backword, if (count > 0) it will moves forward.
 */
Node moveIterator(Node iterator, List list, int count);


/**
 * @brief Checks if the current iterator is on a valid position.
 * 
 * @param iterator the current iterator.
 * @return 1 if the iterator is valid, 0 otherwise. 
 */
int isValidIterator(Node iterator);