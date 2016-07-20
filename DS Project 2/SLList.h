#pragma once
template <typename Type> class SLLIter;

template <typename Type> 
class SLList
{
private:
	friend class SLLIter<Type>;

	struct Node
	{
		Type mData;
		Node * mNext = nullptr;
	};
	Node * mhead = nullptr;
	unsigned int Size = 0;
public:	



	/////////////////////////////////////////////////////////////////////////////
		// Function : Constructor
		// Notes : constructs an empty list
		/////////////////////////////////////////////////////////////////////////////
	SLList()
	{
	
	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : Destructor
		// Notes : Destroys the list
		/////////////////////////////////////////////////////////////////////////////
	~SLList()
	{
		delete mhead;
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : Assignment Operator
		/////////////////////////////////////////////////////////////////////////////
	SLList<Type>& operator=(const SLList<Type>& that)
	{
		//if(mhead)
		
		if (this != &that)
		{		
			clear();

			if(that.mhead != nullptr)
			reverseList(that.mhead);
		
		}

		return *this;
	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : Copy Constructor
		/////////////////////////////////////////////////////////////////////////////
	SLList(const SLList<Type>& that)
	{
		mhead = nullptr;
		*this = that;
		Size = that.size();
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : addHead
		// Parameters :	v - the item to add to the list
		/////////////////////////////////////////////////////////////////////////////
	void addHead(const Type& v)
	{
		Node * temp = new Node();
		temp->mData = v;

		if (mhead == nullptr)
		{
			mhead = temp;
			mhead->mNext = nullptr;
			
		}
		else
		{
			temp->mNext = mhead;
			mhead = temp;
		}

		Size++;
	}

	void removeHead()
	{
		if (mhead)
		{
				Node * temp = mhead;
				mhead = mhead->mNext;
				delete temp;
			
			
			Size--;
		}
	}
	
		/////////////////////////////////////////////////////////////////////////////
		// Function : clear
		// Notes : clears the list, freeing any dynamic memory
		/////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		if(nullptr != mhead)
		while (mhead)
		{
			Node * temp = mhead;
			mhead = mhead->mNext;
			delete temp;

		}
		Size = 0;
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : insert
		// Parameters :	index - an iterator to the location to insert at
		//				v - the item to insert
		// Notes : do nothing on a bad iterator
		/////////////////////////////////////////////////////////////////////////////
	void insert(SLLIter<Type>& index, const Type& v)
	{
		if (index.curr)
		{
			Node * temp = new Node;
			temp->mData = v;
			if (mhead->mData == index.curr->mData)
			{
				mhead = temp;
				temp->mNext = index.curr;
				index.curr = temp;
			}
			else
			{
				temp->mNext = index.curr;
				index.curr = temp;
				index.prev->mNext = index.curr;
			}
			
			
			Size++;

		}

	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : remove
		// Parameters :	index - an iterator to the location to remove from
		// Notes : do nothing on a bad iterator
		/////////////////////////////////////////////////////////////////////////////
	void remove(SLLIter<Type>& index)
	{
		Node * temp = index.curr;
		if (index.curr)
		{
		
			if (&mhead->mData == &index.curr->mData)
			{
				index.curr = index.curr->mNext;
				mhead = index.curr;
				Size--;
			}
			else
			{
				index.curr = index.curr->mNext;
				index.prev->mNext = index.curr;
				Size--;
			}
			
			
			delete temp;
			temp = nullptr;
		
		}
		if(temp)
		delete temp;
		
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : size
		// Return : the number of items stored in the linked list.
		/////////////////////////////////////////////////////////////////////////////
		inline unsigned int size() const
		{
			return Size;
		}

		void reverseList(Node* temp)
		{
			if(temp)
			if (temp->mNext != nullptr)
			{
				reverseList(temp->mNext);
			}
				addHead(temp->mData);
		}
		
};
template <typename Type>
class SLLIter
{
public:
	friend class SLList<Type>;

	typename SLList<Type>::Node * curr;
	typename SLList<Type>::Node * prev;
	//typename SLList<Type>::Node * nxt;
	SLList<Type>* stalkThisList = nullptr;

	~SLLIter()
	{
		curr = prev = nullptr;
		stalkThisList = nullptr;

	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Parameters :	listToIterate - the list to iterate
	/////////////////////////////////////////////////////////////////////////////
	SLLIter(SLList<Type>& listToIterate)
	{
		stalkThisList = &listToIterate;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : begin
	// Notes : moves the iterator to the head of the list
	/////////////////////////////////////////////////////////////////////////////
	void begin()
	{

		curr = stalkThisList->mhead;
		prev = nullptr;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : end
	// Notes : returns true if we are at the end of the list, false otherwise
	/////////////////////////////////////////////////////////////////////////////
	bool end() const
	{
		if(curr == nullptr)
		return true;
		else
		{
			return false;
		}
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : operator++
	// Notes : move the iterator forward one node
	/////////////////////////////////////////////////////////////////////////////
	SLLIter<Type>& operator++()
	{
		if (curr != nullptr)
		{
			prev = curr;
			curr = curr->mNext;
			
			prev->mNext = curr;
		}
		
		return *this;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : current
	// Notes : returns the item at the current iterator location
	/////////////////////////////////////////////////////////////////////////////
	Type& current() const
	{
		return curr->mData;
	}


	


};
