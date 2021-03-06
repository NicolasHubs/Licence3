/*
	TP1 - SYR2
	ANDRIAMILANTO Tompoariniaina
	BOUCHERIE Thomas
*/

#include <reverse.h>


/**
 * The main function to be thrown
 *
 * Parameters:
 *     - int argc  => The number of arguments
 *     - char** filename  => The name of the file (only the second element)
 *
 * Return:
 *     - int  => The result of the execution
 */
int main(int argc, char** filename) {
	return reverse_file(filename[1]);
}


/**
 * Function to display a file in reverse
 *
 * Parameters:
 *     - char* filename  => The name of the file
 *
 * Return:
 *     - int  => The result of the execution
 */
int reverse_file(char* filename) {
	// Try to open the file
	int file = open(filename, O_RDONLY);

	// If we could open it correctly
	if (file >= 0) {

		// Create the buffer
		char* buffer = malloc(BUFFER_SIZE);

		// If we were able to allocate the memory for the buffer
		if (buffer != NULL) {

			int result_read = read(file, buffer, BUFFER_SIZE);

			// Check that the file isn't empty
			if (result_read > 0) {

				// Create the list
				simple_list * ma_liste = NULL;

				// While we still can read
				do {

					// Put the line read in the list and check error
					if (add(&ma_liste, buffer) != 0)
						return -1;

					// Clear the current buffer
					bzero(buffer, BUFFER_SIZE);

					// Load another line
					result_read = read(file, buffer, BUFFER_SIZE);

				} while (result_read > 0);

				// Reverse the list
				ma_liste = reverse_list(ma_liste);

				// Then for each element of the reversed list
				simple_list * iterator = ma_liste;
				while (iterator != NULL) {

					// Display each element of the list
					reverse_buffer(iterator->content);

					// Then load the next one
					simple_list * last = iterator;
					iterator = iterator->next;

					// Free the last iterator
					free_list(last);
				}

				// Close the file
				int result_close = close(file);

				// Free the buffer
				free(buffer);

				// If close correctly
				if (result_close == 0)
					return 0;
			}
		}
	}

	// If an error occured
	return -1;
}


/**
 * Function to display a buffer in reverse
 *
 * Parameters:
 *     - char* buffer  => The buffer to use
 *
 */
void reverse_buffer(char* buffer) {
	int i;
	for (i = (BUFFER_SIZE - 1); i >= 0; i = (i - sizeof(char))) {
		printf("%c", buffer[i]);
	}
}





/* ##############################  External functions for the list ############################## */
/**
 * Add an element to the list
 *
 * Parameters:
 *     - simple_list** list  => A pointer to the list structure
 *     - char* content  => The content of the list element
 *
 * Returns:
 *     - int  => The result of the execution
 */
int add(simple_list** list, char* content) {
	// Error if the pointer of pointer is null
	if (list != NULL) {

		// Create the new element
		simple_list * new_element = malloc(sizeof(simple_list));

		if (new_element != NULL) {

			// Create the content buffer
			char* content_buffer = malloc(BUFFER_SIZE);

			// Copy the buffer passed
			memcpy(content_buffer, content, BUFFER_SIZE);

			// Add its values
			new_element->content = content_buffer;
			new_element->next = NULL;

			// If it's the first element
			if (* list == NULL)
				* list = new_element;

			// If not, link it to the last element
			else {

				// Travel to the last element
				simple_list * tail = * list;
				while (tail->next != NULL) {
					tail = tail->next;
				}

				// Then add this element to it
				tail->next = new_element;
			}

			// Ok here
			return 0;
		}
	}

	// If an error occured
	return -1;
}


/**
 * Free the memory used by a list structure
 *
 * Parameters:
 *     - simple_list* list  => A pointer to the element to free
 *
 */
void free_list(simple_list* list) {
	free(list->content);
	free(list);
}


/**
 * Reverse a list
 *
 * Parameters:
 *     - simple_list* list  => A pointer to the first element of the list to reverse
 *
 * Returns:
 *     - simple_list*  => A pointer to the new list head
 */
simple_list* reverse_list(simple_list* head) {
	// Some temporary variables
	simple_list* tmp = NULL;
	simple_list* tmp2;

	// While there are still some unreversed elements
	while (head != NULL) {
		// Get the current element and store it in a var
		tmp2 = head;
		head = head->next;

		// Switch the next of the current element with the last one
		tmp2->next = tmp;
		tmp = tmp2;
	}

	// Return the new head
	return tmp;
}
