#include <fstream>
#include <iostream>
#include<string>
#include <string.h>

#include "SLList.h"
#include <ctime>
#include <conio.h>
using namespace std;

template <typename Type>
class HTable
{
private:
	unsigned int myBuckets = 0;
	unsigned int(*funcPointer) (const Type &num);
	SLList<Type> * myItems = nullptr;
	unsigned int  Size = 0;
public:
#pragma once
	

	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor 
	// Parameters : numOfBuckets - the number of buckets
	//              hFunction - pointer to the hash function for this table
	// Notes : constructs an empty hash table
	/////////////////////////////////////////////////////////////////////////////
	HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v))
	{
		myBuckets = numOfBuckets;
		funcPointer = hFunction;
		myItems = new SLList<Type>[numOfBuckets];


	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : Destructor
		// Notes : destroys a hash table
		/////////////////////////////////////////////////////////////////////////////
	~HTable()
	{
		myItems->clear();
		//delete[] myItems;
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : Assignment Operator
		/////////////////////////////////////////////////////////////////////////////
	HTable<Type>& operator=(const HTable<Type>& that)
	{
		if (&that != this)
		{

			delete[] myItems;
			myItems = new SLList<Type>[that.myBuckets];
			funcPointer = that.funcPointer;
			for (unsigned int i = 0; i < Size; i++)
			{
				myItems[i] = that.myItems[i];
			}
		}
		return *this;
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : Copy Constructor
		/////////////////////////////////////////////////////////////////////////////
	HTable(const HTable<Type>& that)
	{
		myItems = new SLList<Type>[that.myBuckets];
		funcPointer = that.funcPointer;
		for (unsigned int i = 0; i < Size; i++)
		{
			myItems[i] = that.myItems[i];
		}
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : insert
		// Parameters : v - the item to insert into the hash table
		/////////////////////////////////////////////////////////////////////////////
	void insert(const Type& v)
	{
		int insertHere = (*funcPointer)(v);
		(myItems[insertHere]).addHead(v);
	
		Size++;
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : findAndRemove
		// Parameters : v - the item to remove(if it is found)
		/////////////////////////////////////////////////////////////////////////////
	bool findAndRemove(const Type& v)
	{
		int check = find(v);
		if (check == -1)
		{
			return false;
		}
		else
		{
			
			SLLIter<Type> * iter = new  SLLIter<Type>((myItems[check]));
			iter->begin();
			for (int i = 0; i < (myItems[check]).size(); i++)
			{
				if (v == iter->current())
				{
					(myItems[check]).remove(*iter);
					check = find(v);
					if (check == -1)
					{
						delete iter;
						return true;
					}
				}
				iter->operator++();

			}

			
		}
	
	
	}


		/////////////////////////////////////////////////////////////////////////////
		// Function : clear
		// Notes : clears the hash table
		/////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		delete[] myItems;
		//myItems->clear();
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : find
		// Parameters : v - the item to look for
		// Return : the bucket we found the item in or -1 if we didn’t find the item.
		/////////////////////////////////////////////////////////////////////////////
	int find(const Type& v) const
	{
		int checkItem = (*funcPointer)(v);

		SLLIter<Type> * iter = new  SLLIter<Type>((myItems[checkItem]));
		iter->begin();
		for (int i = 0; i < (myItems[checkItem]).size(); i++)
		{
			if (v == iter->current())
			{
				delete iter;
				return checkItem;
			}
			iter->operator++();

		}
	
		delete iter;
			return -1;
		
	}



	void loadDict(string FN)
	{
		ifstream fin;

		fin.open(FN);
		if (fin.is_open())
		{
			
			string word;
			while (!fin.eof())
			{
				
				getline(fin, word);
				if (word.length() > 2 && word.length() < 7 && word.find("'") == word.npos)
					insert(word);
			}

		

			fin.close();
		}


	}

	void GetRandWord()
	{
		int brNum = 0;
		int iNum = 0;
		srand(time(NULL));
		brNum = rand() % myBuckets;
		string temp;
		SLLIter<Type> * iter = new SLLIter<Type>((myItems[brNum]));
		iNum = rand() % (myItems[brNum]).size();
		iter->begin();
		for (int i = 0; i < iNum; i++)
		{
			++iter;
		}
	
		temp = iter->current();
		while (temp.length() != 6)
		{
			delete iter;
			brNum = rand() % myBuckets;
			iter = new SLLIter<Type>((myItems[brNum]));
			iNum = rand() % (myItems[brNum]).size();
			iter->begin();
			for (int i = 0; i < iNum; i++)
			{
				++iter;
			}
			temp = iter->current();
			
		}
		cout << temp;
		//delete temp;
		
	}

	void display()
	{
		int yo2 = 0;
		SLLIter<Type> * iter = new  SLLIter<Type>(*myItems);
		iter->begin();
		for (int i = 0; i < myBuckets; i++)
		{
			int yo = myItems[i].size();
			//cout << iter->current() << endl;
			if (yo == 0)
				yo2++;
				//cout << "Bucket " << i << " has " << yo << " items in it" << endl ;
			iter->operator++();
		}
		cout << yo2;
		delete iter;
	}

	void HTable<Type>::printSomeStuff(const char* filePath = "hashdata.txt")
	{
		// we're gonna need to open a file for all this data
		ofstream outFile(filePath);

		// let's make sure the file got opened
		if (outFile.is_open())
		{
			// number of empty buckets, total count of elements, index of emptiest bucket, index of fullest bucket
			unsigned int empty = 0;
			unsigned int totalCount = 0;
			unsigned int loIndex = 0;
			unsigned int hiIndex = 0;

			// loop through all the buckets
			for (unsigned int i = 0; i < myBuckets; ++i)
			{
				// add the number of elements in each bucket to the total count
				totalCount += myItems[i].size();
				// print the index of this bucket and its size to the file
				outFile << i << " : " << myItems[i].size() << '\n';

				// if this list is empty, increment the empty count
				if (myItems[i].size() == 0)
					++empty;

				// if this list has less elements than the lowest one recorded so far, store this as the new lowest
				if (myItems[i].size() < myItems[loIndex].size())
					loIndex = i;
				// else, if this list has more elements than the highest one recorded so far, store this as the new highest
				else if (myItems[i].size() > myItems[hiIndex].size())
					hiIndex = i;
			}

			// print the total count of items and number of buckets to the file
			outFile << '\n' << totalCount << " Total items stored in " << myBuckets << " buckets\n";
			// print the number of empty buckets
			outFile << '\n' << empty << " Buckets are empty\n\n";
			// get the number of elements in the emptiest bucket
			unsigned int Low = myItems[loIndex].size();
			// get the range fullest-emptiest+1
			unsigned int range = myItems[hiIndex].size() - Low + 1;
			// print this info to the file
			outFile << "each bucket contains between " << Low << " and " << Low + range - 1 << " items.\n\n";

			// make a new array to count how many buckets contain each number of items between the emptiest and fullest
			// and initialize each cell to 0
			unsigned int* arr = new unsigned int[range];
			for (unsigned int j = 0; j < range; ++j)
				arr[j] = 0;

			// now we go through and count how many buckets contain each number of items...
			// 3 buckets have 15 items
			// 5 buckets have 16 items
			// etc.
			for (unsigned int k = 0; k < myBuckets; ++k)
				++arr[myItems[k].size() - Low];

			// now print this data to the file
			for (unsigned int p = 0; p < range; ++p)
				outFile << arr[p] << " buckets have " << p + Low << " items\n";

			// delete the array we made a minute ago, we are done with it
			delete[] arr;
		}
	}

};
