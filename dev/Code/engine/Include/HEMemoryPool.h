#pragma once

//-------------------------------------------------------------------------------------------
//	MemoryPool.h : Adopted from GCC4. Use for small, rapid memory allocations
//	for lightning speed! Override the new and delete operators for
//	objects that are created and destroyed very often to use this.
//
//  m_ppRawMemoryArray is a pointer to an array of pointers managed by
//	this object. Each of these pointers is called a 'block' and is another array
//	of data called 'chunks'.
//
//	Think of this object as pre-assigned memory. When Alloc() is called, this object
//	actually lets go of the block and returns it to the caller, simulating a memory
//	allocation. When Free() is called, the memory returns to this pool.
//
//	NOTE: The way this is written, this object initializes with only one block of chunks.
//  This should be re-written to be an input for the user.
//-------------------------------------------------------------------------------------------

#include <iostream>
#include <string>

namespace HE
{
	class MemoryPool
	{
		unsigned char ** m_ppRawMemoryArray;	// an array of memory blocks, each split up into chunks.
		unsigned char * m_pHead;				// the front of the memory chunk linked list.
		unsigned int m_chunkSize, m_numChunks;	// the size of each chunk and number of chunks per array.
		unsigned int m_memArraySize;			// the number of elements in the memory array.
		bool m_toAllowResize;					// true if we resize the memory pool when it fills.

		// tracking variables we only care about for debugging
#ifdef _DEBUG
		std::string m_debugName;
		unsigned long m_allocPeak, m_numAllocs;
#endif

	public:
		// construction
		MemoryPool(void);
		~MemoryPool(void);
		bool Init(unsigned int chunkSize, unsigned int numChunks);
		void Destroy(void);

		// allocation functions
		void * Alloc(void);
		void Free(void * pMem);
		unsigned int GetChunkSize(void) const { return m_chunkSize; }

		// settings
		void setAllowResize(bool toAllowResize) { m_toAllowResize = toAllowResize; }

		// debug functions
#ifdef _DEBUG
		void SetDebugName(const char * debugName) { m_debugName = debugName; }
		std::string GetDebugName(void) const { return m_debugName; }
#else
		void SetDebugName(const char * debugName) {}
		std::string GetDebugName(void) const { return "<No Name>"; }
#endif

	private:
		// resets internal vars
		void Reset(void);

		// internal memory allocation helpers
		bool GrowMemoryArray(void);
		unsigned char * AllocateNewMemoryBlock(void);

		// internal linked list management
		unsigned char * GetNext(unsigned char * pBlock);
		void SetNext(unsigned char * pBlockToChange, unsigned char * pNewNext);

		// don't allow copy constructor
		MemoryPool(const MemoryPool & memPool) {};
	};
}