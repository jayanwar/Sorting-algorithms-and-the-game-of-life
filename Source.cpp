#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "MVector.h"
#include "timing.h"

// takes a vector v and sorts it according to the bubble sort algortihm 
void bubble(SortableContainer &v)
{
	for (int i = 0; i < v.size() - 1; i++)
	{
		bool sorted = true;
		for (int j = 0; j < v.size() - 1 - i; j++)
			/* assuming last i indices have been sorted, swap v_j, v_j+1 if
			v_j+1 < v_j */
			if (v.cmp(j + 1, j)) 
				v.swap(j, j + 1);
				sorted = false;
		if (sorted) break;
	}
}

/* takes a vector v and takes 2 indices start and end, calculates the midpoint
index mid, and sorts the values so median of the three values is at the start */
void MedOfThree(SortableContainer &v, int start, int end)
{
	int mid = start + (end - start) / 2;
	if (v.cmp(end, start)) v.swap(end, start);
	if (v.cmp(mid, start)) v.swap(mid, start);
	if (v.cmp(end, mid)) v.swap(end, mid);
	v.swap(start, mid);
}

/* takes a vector v and 2 indices start and end, and places the pivot chosen by 
MedOfThree in the correct position between start and end, and all elements in 
subsequence greater than it above pivot and all elements less than below pivot*/
int CorrectPivotPlacement(SortableContainer &v, int start, int end)
{
	MedOfThree(v, start, end); // choose pivot and place at start
	int p_goes_here = start + 1; // index of pivot
	for (int i = start + 1; i <= end; i++)
	{
		// if v[i] < pivot, increase index of pivot by 1
		if (v.cmp(i, start))
		{
			v.swap(p_goes_here, i);
			p_goes_here++;
		}
	}
	p_goes_here--;
	v.swap(start, p_goes_here); // place pivot in correct position
	return p_goes_here; // return index of pivot
}

/* takes a vector and sorts it between indices start and end according to the
quicksort method*/
void quick_recursive(SortableContainer &v, int start, int end)
{
	if (start == end) { ; } // do nothing if vector is empty or 1 dim.
	else
	{
		int pivot_index = CorrectPivotPlacement(v, start, end);
		// do quicksort on either side of pivot if possible
		if (pivot_index != start) quick_recursive(v, start, pivot_index - 1);
		if (pivot_index != end) quick_recursive(v, pivot_index + 1, end);
	}
}

// wrapper for quick_recursive
void quick(SortableContainer &v) { quick_recursive(v, 0, v.size() - 1); }

/*takes a SortableContainer v, it's end index end and some index i, and performs
a heap sort on the 3 indices i, 2*i+1 and 2*i+2, and calls heap_from_root again
if the largest node wasn't in the correct place*/
void heap_from_root(SortableContainer &v, int i, int end)
{
	// initialise indices of the parent node and it's 2 child nodes
	int parent = i, child1 = 2 * i + 1, child2 = 2 * i + 2;
	// find the largest value among the parent and children if possible
	if (child1 < end && v.cmp(parent, child1)) { parent = child1; }
	if (child2 < end && v.cmp(parent, child2)) { parent = child2; }
	/* if the largest value wasn't in the correct place, place it at the correct
	index i and peform heap sort where the largest value was */
	if (parent != i)
	{
		v.swap(parent, i);
		heap_from_root(v, parent, end);
	}
}

// takes a SortableContainer v and sorts it according to the Heapsort method
void heap(SortableContainer &v)
{
	int end = v.size()-1;
	// build a maximal heap (i.e. biggest possible binary tree)
	for (int i = end / 2; i >= 0; i--)
	{
		heap_from_root(v, i, end);
	}
	/* largest value is at the root of heap, so place it at the ith index and call 
	heap_from_root */
	for (int i = end; i >= 0; i--)
	{
		v.swap(0, i);
		heap_from_root(v, 0, i);
	}
}

int main()
{	

	std::srand(std::time(NULL));
	/*
	std::ofstream bubbletime;
	bubbletime.open("bubbletime.csv");
	bubbletime << "size,avg time (MVector),avg time (CoordinateArray)\n";
	for (int n = 1; n <= 1000; n++) /* calculate average time for vectors of size
	up to 1000 
	{
		double avgtime_v = 0.0, avgtime_c = 0.0;
		for (int i = 1; i <= 10; i++) // calculate time for 10 vectors of size n
		{
			MVector v(n*10);
			v.initialise_random(0.0, 10000.0); // random MVector of size n
			double StartTime = Timer(); // start timer
			bubble(v); // sort
			double EndTime = Timer(); // end timer
			avgtime_v += (EndTime - StartTime); // add time taken to avgtime
		}
		avgtime_v /= 10.0; // divide avgtime by 10, thus getting the average time
		for (int i = 1; i <= 10; i++) // calculate time for 10 vectors of size n
		{
			CoordinateArray c(n*10);
			c.InitialiseRandom(0, 1000, 0, 1000); // random CoordinateArray size n
			double StartTime = Timer(); //start timer
			bubble(c); // sort	
			double EndTime = Timer(); //end timer
			avgtime_c += (EndTime - StartTime); // add time taken to avgtime
		}
		avgtime_c /= 10.0; // divide avgtime by 10, thus getting the average time
		// write the size of vector and time taken to sort to a csv file
		bubbletime << n*10 << "," << avgtime_v << "," << avgtime_c << "\n";
	}
	bubbletime.close();
	*/
	/*
	std::ofstream quicktime;
	quicktime.open("quicktime.csv");
	quicktime << "size,avg time (MVector),avg time (CoordinateArray)\n";
	for (int n = 1; n <= 1000; n++)
	{
		double avgtime_v = 0.0, avgtime_c = 0.0;
		for (int i = 1; i <= 10; i++)
		{
			MVector v(n*1000);
			v.initialise_random(0.0, 10000.0);
			double StartTime = Timer();
			quick(v);
			double EndTime = Timer();
			avgtime_v += (EndTime - StartTime);
		}
		avgtime_v /= 10.0;
		for (int i = 1; i <= 10; i++)
		{
			CoordinateArray c(n*1000);
			c.InitialiseRandom(0, 1000, 0, 1000);
			double StartTime = Timer();
			quick(c);
			double EndTime = Timer();
			avgtime_c += (EndTime - StartTime);
		}
		avgtime_c /= 10.0;
		quicktime << n*1000 << "," << avgtime_v << "," << avgtime_c << "\n";
	}
	quicktime.close();
	
	
	std::ofstream heaptime;
	heaptime.open("heaptime.csv");
	heaptime << "size,avg time (MVector),avg time (CoordinateArray)\n";
	for (int n = 1; n <= 1000; n++)
	{
		double avgtime_v = 0.0, avgtime_c = 0.0;
		for (int i = 1; i <= 10; i++)
		{
			MVector v(n*1000);
			v.initialise_random(0.0, 10000.0);
			double StartTime = Timer();
			heap(v);
			double EndTime = Timer();
			avgtime_v += (EndTime - StartTime);
		}
		avgtime_v /= 10.0;
		for (int i = 1; i <= 10; i++)
		{
			CoordinateArray c(n*1000);
			c.InitialiseRandom(0, 1000, 0, 1000);
			double StartTime = Timer();
			heap(c);
			double EndTime = Timer();
			avgtime_c += (EndTime - StartTime);
		}
		avgtime_c /= 10.0;
		heaptime << n*1000 << "," << avgtime_v << "," << avgtime_c << "\n";
	}
	heaptime.close();
	*/
	

	/*
	Life Game1(4);

	IntegerCoordinate a1(1, 1);
	IntegerCoordinate b1(1, 2);
	IntegerCoordinate c1(2, 1);
	IntegerCoordinate d1(2, 2);

	
	Game1.LiveCells[0] = a1;
	Game1.LiveCells[1] = b1;
	Game1.LiveCells[2] = c1;
	Game1.LiveCells[3] = d1;

	while (Game1.gen <= 5206)
	{
		quick(Game1.LiveCells);
		std::cout << Game1.LiveCells << "\n";
		CoordinateArray PossLiveCells = Game1.DeadCells();
		quick(PossLiveCells);
		PossLiveCells.unique();
		Game1.born(PossLiveCells);
		Game1.die();
		Game1.tick();
	}
	
	
	Life Game2(3);
	
	IntegerCoordinate a2(5, 4);
	IntegerCoordinate b2(5, 5);
	IntegerCoordinate c2(5, 6);

	Game2.LiveCells[0] = a2;
	Game2.LiveCells[1] = b2;
	Game2.LiveCells[2] = c2;

	while (Game2.gen <= 5)
	{
		quick(Game2.LiveCells);
		std::cout << Game2.LiveCells << "\n";
		CoordinateArray PossLiveCells = Game2.DeadCells();
		quick(PossLiveCells);
		PossLiveCells.unique();
		Game2.born(PossLiveCells);
		Game2.die();
		Game2.tick();
	}
	*/
	Life Game3(7);

	IntegerCoordinate a3(10001, 10001);
	IntegerCoordinate b3(10002, 10001);
	IntegerCoordinate c3(10002, 10003);
	IntegerCoordinate d3(10004, 10002);
	IntegerCoordinate e3(10005, 10001);
	IntegerCoordinate f3(10006, 10001);
	IntegerCoordinate g3(10007, 10001);

	Game3.LiveCells[0] = a3;
	Game3.LiveCells[1] = b3;
	Game3.LiveCells[2] = c3;
	Game3.LiveCells[3] = d3;
	Game3.LiveCells[4] = e3;
	Game3.LiveCells[5] = f3;
	Game3.LiveCells[6] = g3;
	
	while (Game3.gen <= 5210)
	{
		quick(Game3.LiveCells);
		std::cout << " (~BBC) Gen = " << Game3.gen << ",     #LiveCells = "
			<< Game3.LiveCells.size() << "\n";
		CoordinateArray PossLiveCells = Game3.DeadCells();
		quick(PossLiveCells);
		PossLiveCells.unique();
		Game3.born(PossLiveCells);
		Game3.die();
		Game3.tick();
	}
	quick(Game3.LiveCells);
	std::cout << " (~BBC) Gen = " << Game3.gen << ",     #LiveCells = "
		<< Game3.LiveCells.size() << "\n" << Game3.LiveCells << "\n";
	return 0;
}
	

/*
	std::ofstream acorn;
	acorn.open("acorn.csv");
	for (int i = 0; i < Game3.LiveCells.size(); i++)
	{
		acorn << Game3.LiveCells[i].X << "," << Game3.LiveCells[i].Y << "\n";
	}
	acorn.close();
*/