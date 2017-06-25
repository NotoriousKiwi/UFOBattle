#include <iostream>


#pragma once
template<class T>
class DynamicArray
{
private:

	int cap;				// <--- Used to define the initial size of the array.
	int numberOfElements;	// <--- Used to define where we want to initialize from in the array. 
	T * arr;				// <--- Templated array pointer.

public:

	// DynamicArray default constructor.
	DynamicArray()
	{
		cap = 5;
		numberOfElements = 0;
		arr = new T[cap];

		initialize(numberOfElements);
	}

	// DynamicArray default destructor.
	~DynamicArray()
	{
		delete[] arr;
	}

	// Returns the size of the current array.
	int size() const
	{
		return numberOfElements;
	}						

	// Clears the way in the array.
	void initialize(int from)
	{
		for (int i = from; i < cap; ++i)
		{
			T* arr = nullptr;
		}
	}		

	// Expands the array. (Used when more items are being added to the array when it is already at its limits.)
	void expand()
	{
		cap *= 2;

		T * tempArr = new T[cap];

		for (int i = 0; i < numberOfElements; ++i)
		{
			tempArr[i] = arr[i];
		}

		delete[] arr;

		arr = tempArr;

		initialize(numberOfElements);
	}

	// Adds a selected item to the array. Templated so that any information can be passed in.
	void add(const T &obj)
	{
		if (numberOfElements >= cap)
		{
			expand();
		}

		arr[numberOfElements++] = obj;

		if(numberOfElements == cap)
		{
			std::cout << "Array is full, expanding..." << std::endl;
		}
	}

	// Gets the item at the given index.
	T& get(int index)
	{
		if (index < 0 || index > numberOfElements)
			throw("Bad index.");

		return arr[index];
	}

protected:
};

