#ifndef BRANCHBOUND_H
#define BRANCHBOUND_H
#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "GridMap.h"

//class node
struct heapNode
{
	float lowerCost;      //��ǰ�ڵ��������У�������·����ȡ�õ��ܺķѵ�����
	float currentCost;    //�Ӹ�����ǰ�ڵ�ĵ�ǰ���еĺķ�
	float restMinCost;    //�ӵ�ǰ�ڵ㵽���һ���ڵ㣬ÿ���ڵ����С���ߵĺķ�֮��
	int s;              //�Ӹ��ڵ㵽��ǰ�ڵ��·��Ϊ[0:s]
	int *currentTour;   //�Ӹ��ڵ㵽��ǰ�ڵ��·��(����)

						//��������ʱ������ת��
	operator float() { return lowerCost; }

	//���ش��ں������������С���ѱȽ�
	bool operator>(const heapNode &right)
	{
		return lowerCost > right.lowerCost;
	}
};

//class minHeap
template<class T>
class minHeap
{
public:
	minHeap(int initialCapacity = 10);
	~minHeap() { delete[] heap; }
	bool empty() const { return heapSize == 0; }
	int size() const
	{
		return heapSize;
	}
	const T& top()
	{// return min element
		if (heapSize == 0)
			exit(1);
		return heap[1];
	}
	void pop();
	void push(const T&);
	//void initialize(T *, int);
	void deactivateArray()
	{
		heap = NULL; arrayLength = heapSize = 0;
	}
	//void output(std::ostream& out) const;
private:
	int heapSize;       // number of elements in queue
	int arrayLength;    // queue capacity + 1
	T *heap;            // element array
};


template<class T>
minHeap<T>::minHeap(int initialCapacity)
{// Constructor.
	if (initialCapacity < 1)
	{
		std::cout << "Initial capacity = " << initialCapacity << " Must be > 0";
		exit(1);
	}
	arrayLength = initialCapacity + 1;
	heap = new T[arrayLength];
	heapSize = 0;
}


template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0)
	{
		std::cout << "new length must be >= 0" << std::endl;
		exit(1);
	}

	T* temp = new T[newLength];              // new array
	int number = std::min(oldLength, newLength);  // number to copy
	std::copy(a, a + number, temp);
	delete[] a;                             // deallocate old memory
	a = temp;
}

template<class T>
void minHeap<T>::push(const T& theElement)
{// Add theElement to heap.

 // increase array length if necessary
	if (heapSize == arrayLength - 1)
	{// double array length
		changeLength1D(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	// find place for theElement
	// currentNode starts at new leaf and moves up tree
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] > theElement)
	{
		// cannot put theElement in heap[currentNode]
		heap[currentNode] = heap[currentNode / 2]; // move element down
		currentNode /= 2;                          // move to parent
	}

	heap[currentNode] = theElement;
}

template<class T>
void minHeap<T>::pop()
{// Remove max element.
 // if heap is empty return null
	if (heapSize == 0)   // heap empty
	{
		std::cout << "heap is empty!" << std::endl;
		exit(1);
	}

	// Delete min element
	heap[1].~T();

	// Remove last element and reheapify
	T lastElement = heap[heapSize--];

	// find place for lastElement starting at root
	int currentNode = 1,
		child = 2;     // child of currentNode
	while (child <= heapSize)
	{
		// heap[child] should be smaller child of currentNode
		if (child < heapSize && heap[child] > heap[child + 1])
			child++;

		// can we put lastElement in heap[currentNode]?
		if (lastElement <= heap[child])
			break;   // yes

					 // no
		heap[currentNode] = heap[child]; // move child up
		currentNode = child;             // move down a level
		child *= 2;
	}
	heap[currentNode] = lastElement;
}



//class branch and bound algorithm
class BranchBound {

public:

	BranchBound(const int & iNodeNum);
	~BranchBound();

	//two dimension distance
	float TwoDDistance(const pcl::PointXYZ & oPointOne,
		               const pcl::PointXYZ & oPointTwo);

	//initial the objective value between each node pairs
	void SimpleInitial(const pcl::PointCloud<pcl::PointXYZ> & vNodeCloud);

	//get obejective value between each node pairs
	void ObjectiveMatrix(const std::vector<std::vector<float>> & vObjectMatrix);

	//using branch and bound to solve op (Orienteering problem) 
	float SolveOP(std::vector<int> & vResTour);

private:

	//ȫ�ֱ���
	int iNodeNum;
	//vEffective[1:n][1:n] ��ʾ����֮������кķѣ�������·����ķѵ���-1
	std::vector<std::vector<float>> vEffective; 

};




#endif // !minHeap.h