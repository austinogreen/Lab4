#ifndef RESIZABLE_ARRAY_H
#define RESIZABLE_ARRAY_H

#include "Exceptions.h"

const unsigned long DEFAULT_ARRAY_CAPACITY = 10;        // capacity used in no arg constructor

template <typename T>
class ResizableArray {
private:
	unsigned long capacity = DEFAULT_ARRAY_CAPACITY;    // maximum capacity, in items
	unsigned long size = 0;                             // actual number of items currently in array
	T* data = NULL;                                     // pointer to array of any type
	void doubleCapacity();                              // method to double array capacity
	void halveCapacity();                               // method to halve array capacity
public:
	ResizableArray();                                   // constructs array with default capacity
	ResizableArray(unsigned long capacity);             // constructs array with specified capacity
	virtual ~ResizableArray();                          // frees array space as object is deleted
	void add(T item);                                   // adds item, increments size, doubles capacity as necessary
	void addAt(T item, unsigned long index);            // adds item at index, shifts following, doubles capacity as necessary
	void replaceAt(T item, unsigned long index);        // replaces item at index, otherwise unchanged
	void removeAt(unsigned long index);                 // removes item at index, shifts following back
	T get(unsigned long index) const;                   // returns (copy of) item at index
	unsigned long getSize() const;                      // returns number of items currently in array
};

// Add your implementation below this line. Do not add or modify anything above this line.
template<typename T>
void ResizableArray<T> :: doubleCapacity(void) {
	// Creats new type T array
	T* newT = new T[capacity * 2];

	// Copies contents of old array into the new one
	for (unsigned int i = 0; i < capacity; i++) {
		try {
			newT[i] = get(i);
		}
		catch (ExceptionIndexOutOfRange e) {
			// It broke :(
		}
	}

	// Updates the capacity
	capacity *= 2;

	// Delete old data
	delete[] data;

	// Updates old data array to new one
	data = newT;
}

template<typename T>
void ResizableArray<T> :: halveCapacity(void) {
	// Creates new type T array
	T* newT = new T[capacity / 2];

	// Copies contents of old array into the new one
	for (unsigned int i = 0; i < size; i++) {
		try {
			newT[i] = get(i);
		}
		catch (ExceptionIndexOutOfRange e) {
			// It broke :(
		}
	}

	// Updates the capacity
	capacity /= 2;

	// Delete old data
	delete[] data;

	// Updates old data array to new one
	data = newT;
}

template<typename T>
ResizableArray<T> :: ResizableArray() {
	// Creates new array of type T of default capacity
	data = new T[DEFAULT_ARRAY_CAPACITY];
}

template<typename T>
ResizableArray<T> :: ResizableArray(unsigned long capacity) {
	// Creates new array of type T of <capacity>
	data = new T[capacity];
}

template<typename T>
ResizableArray<T> :: ~ResizableArray() {
	// Deletes object if it exists
	if (data != NULL) {
		delete[] data;
	}
	// Sets data to point to null & size to 0
	data = NULL;
	size = 0;
}

template<typename T>
void ResizableArray<T> :: add(T item) {
	// doubles drilling array size if capacity is reached
	if (size >= capacity) {
		doubleCapacity();
	}

	// Adds item to the index & increments size
	data[size] = item;
	size++;

	return;
}

template<typename T>
void ResizableArray<T> :: addAt(T item, unsigned long index) {
	// Checks if index is valid
	if (index >= size) {
		// error
		throw ExceptionIndexOutOfRange();
	}

	// Shifts all data to the right
	for (unsigned long i = (size - 1); i >= index; i--) {
		data[i + 1] = data[i];
	}

	// adds item at index
	data[index] = item;

	size++;
	
	return;
}

template<typename T>
void ResizableArray<T> :: replaceAt(T item, unsigned long index) {
	// Checks if index is valid
	if (index >= size) {
		// error
		throw ExceptionIndexOutOfRange();
	}

	// Replaces item at index with <item>
	data[index] = item;

	return;
}

template<typename T>
inline void ResizableArray<T> :: removeAt(unsigned long index) {
	// Checks if index is valid
	if (index >= size) {
		// error
		throw ExceptionIndexOutOfRange();
	}

	// Shifts data to the left
	for (unsigned long i = index; i < (size - 1); i++) {
		data[i] = data[i + 1];
	}

	// Decreases size
	size--;

	// Halves the capacity if the size less than half the capacity
	if (size <= (capacity / 2)) {
		halveCapacity();
	}

	return;
}

template<typename T>
T ResizableArray<T> :: get(unsigned long index) const {
	// Checks if index is valid
	if (index >= size) {
		// return
		throw ExceptionIndexOutOfRange();
	}

	// Returns the item
	return data[index];
}

template<typename T>
unsigned long ResizableArray<T> :: getSize() const {
	// Returns the size
	return size;
} 
#endif