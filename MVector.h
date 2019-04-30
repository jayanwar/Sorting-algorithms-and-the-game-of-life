#ifndef MVECTOR_H
#define MVECTOR_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iterator>

// TODO fix find function in CoordinateArray

// Abstract Base Class for Sorting
class SortableContainer
{
public:
	// pure virtual comparison function
	virtual bool cmp(int i, int j) const = 0;
	// pure virtual size function
	virtual int size() const = 0;
	// pure virtual "swap 2 elements in vector" function
	virtual void swap(int i, int j) = 0;
};

// Represents a mathematical vector
class MVector : public SortableContainer
{
public:
	/* constructors */
	MVector() : v(0)
	{}

	// initialise empty vector of size n 
	explicit MVector(int n) : v(n)
	{}

	// initialise vector of size n with values x
	MVector(int n, double x) : v(n, x)
	{}


	/* SortableContainer functions */

	// returns true if v[i] < v[j], false otherwise
	virtual bool cmp(int i, int j) const
	{
		if (v[i] < v[j]) return true;
		else return false;
	}

	// returns no. of elements in vector
	virtual int size() const { return v.size(); }

	// swaps the places of the ith and jth elements
	virtual void swap(int i, int j)
	{
		int vtemp = v[i];
		v[i] = v[j]; v[j] = vtemp;
	}
	
	/* initialise random vector */

	// for an n-vector, give each place a random value in the range [xmin,xmax]
	void initialise_random(double xmin, double xmax)
	{
		size_t s = v.size();
		for (size_t i = 0; i < s; i++)
		{
			v[i] = xmin + (xmax - xmin)*rand() / static_cast<double>(RAND_MAX);
		}
	}

	/* overloaded operator functions */
	// access element (lvalue)
	double &operator[](int index)
	{
		/*if (index < 0 || index >= v.size()) // checking for errors
		{
			std::cout << index << " is not in the range of [0," <<
				v.size() - 1 << "]" << std::endl;
			exit(1);
		}
		else */
		return v[index];
	}

	// access element (rvalue)
	double operator[](int index) const
	{
		/*if (index < 0 || index >= v.size()) // checking for errors
		{
			std::cout << index << " is not in the range of [0," <<
				v.size() - 1 << "]" << std::endl;
			exit(1);
		}
		else */ 
		return v[index];
	}

	// print n-vector in the format v0,v1,....,vn,
	friend std::ostream& operator<<(std::ostream& os, const MVector& v);

private:
	std::vector<double> v;
};

// Represents an ordered pair of integers
struct IntegerCoordinate
{
	// constructors
	IntegerCoordinate() { unsigned X = 0, Y = 0; }
	IntegerCoordinate(unsigned X_, unsigned Y_) { X = X_, Y = Y_; }
	unsigned X, Y;

	// overloaded operators

	// return true if 2 IntegerCoordinates are equal
	bool operator==(IntegerCoordinate xy)
	{
		if (X == xy.X && Y == xy.Y) return true;
		else return false;
	}

	//  return true if LHS IntegerCoordinate is less than RHS
	bool operator<(IntegerCoordinate xy)
	{
		if (X < xy.X) return true;
		else if (X == xy.X && Y < xy.Y) return true;
		else return false;
	}
};

// Represents a vector of ordered pairs of integers
class CoordinateArray : public SortableContainer
{
public:
	// constructors
	
	// initialise empty vector of IntegerCoordinate
	CoordinateArray() : v(0)
	{}

	// initialise vector of size n with each index (1,1)
	explicit CoordinateArray(int n) : v(n, IntegerCoordinate(1, 1))
	{}

	// lexicographic ordering for a vector of IntegerCoordinate
	virtual bool cmp(int i, int j) const
	{
		if (v[i].X < v[j].X) return true;
		else if (v[i].X == v[j].X && v[i].Y < v[j].Y) return true;
		else return false;
	}

	// return no. of IntegerCoordinate in vector
	virtual int size() const
	{
		return v.size();
	}

	// swap two IntegerCoordinate in vector
	virtual void swap(int i, int j)
	{
		IntegerCoordinate vtemp = v[i];
		v[i] = v[j], v[j] = vtemp;
	}

	// append IntegerCoordinate to end of vector
	void push_back(IntegerCoordinate xy)
	{
		v.push_back(xy);
	}

	// binary search for an IntegerCoordinate in vector
	bool find(IntegerCoordinate xy)
	{
		int L = 0, R = v.size() - 1; // start and end indices
		while (L <= R)
		{
			int M = L + (R - L) / 2; // midpoint index
			if (v[M] == xy) return true; // if midpoint index is xy return true
			else if (xy < v[M]) R = M - 1; // if xy < midpoint search bottom half
			else L = M + 1; // if xy > midpoint search top half
		}
		return false; // return false if xy not found
	}
	
	// removes repeat elements from a sorted vector of IntegerCoordinate
	void unique()
	{
		for (int i = 0; i < v.size() - 1; i++)
		{
			while (v[i] == v[i + 1])
				v.erase(v.begin() + (i+1)); // remove all values equal to v[i]
		}
	}

	// each X coord a random integer in [X_min,X_max], Y coord in [Y_min,Y_max]
	void InitialiseRandom(unsigned X_min, unsigned X_max, unsigned Y_min, 
		unsigned Y_max)
	{
		size_t s = v.size();
		for (int i = 0; i < s; i++)
		{
			v[i].X = rand() % (X_max - X_min) + X_min;
			v[i].Y = rand() % (Y_max - Y_min) + Y_min;
		}
	}

	// access element (lvalue)
	IntegerCoordinate &operator[](int index)
	{
		/*if (index < 0 || index >= v.size()) // checking for errors
		{
			std::cout << index << " is not in the range of [0," <<
				v.size() - 1 << "]" << std::endl;
			exit(1);
		}
		else*/
		return v[index];
	}

	// access element (rvalue)
	IntegerCoordinate operator[](int index) const
	{
		/*if (index < 0 || index >= v.size()) // checking for errors
		{
			std::cout << index << " is not in the range of [0," <<
				v.size() - 1 << "]" << std::endl;
			exit(1);
		}
		else*/
		return v[index];
	}

	// print n-vector in the format v0,v1,....,vn,
	friend std::ostream& operator<<(std::ostream& os, const CoordinateArray& v);

private:
	std::vector<IntegerCoordinate> v;
};

// Represents a vector of live cells for the game of Life
class Life : public CoordinateArray
{
public:
	// Storage of the coordinates of the live cells
	CoordinateArray LiveCells;
	// generation of the game
	int gen;

	// Constructor
	Life(int n)
	{
		CoordinateArray LC(n);
		LiveCells = LC;
		CoordinateArray LiveCellsNext;
		int gen = 0;
	}

	// returns CoordinateArray of the 8 neighbours of an IntegerCoordinate
	CoordinateArray neighbours(CoordinateArray Cells, int i)
	{
		CoordinateArray v;
		// if out of index range return empty vector
		if (i < 0 || i >= Cells.size()) return v;
		else
		{
			CoordinateArray v(8);
			IntegerCoordinate BL(Cells[i].X - 1, Cells[i].Y - 1); 
			IntegerCoordinate CL(Cells[i].X - 1, Cells[i].Y);
			IntegerCoordinate TL(Cells[i].X - 1, Cells[i].Y + 1);
			IntegerCoordinate BC(Cells[i].X, Cells[i].Y - 1);
			IntegerCoordinate TC(Cells[i].X, Cells[i].Y + 1);
			IntegerCoordinate BR(Cells[i].X + 1, Cells[i].Y - 1);
			IntegerCoordinate CR(Cells[i].X + 1, Cells[i].Y);
			IntegerCoordinate TR(Cells[i].X + 1, Cells[i].Y + 1);
			v[0] = BL; v[1] = CL; v[2] = TL; v[3] = BC;
			v[4] = TC; v[5] = BR; v[6] = CR; v[7] = TR;
			return v;
		}
	}

	// Returns the dead cells that may be alive at next generation (with repeats)
	CoordinateArray DeadCells()
	{
		CoordinateArray dc;
		for (int i = 0; i < LiveCells.size(); i++)
		{
			/* for each live cells neighbours, if it is a dead cell, append it to
			the CoordinateArray dc */
			CoordinateArray nbrs = neighbours(LiveCells, i);
			for (int j = 0; j < nbrs.size(); j++)
			{
				if (!LiveCells.find(nbrs[j])) dc.push_back(nbrs[j]);
			}
		}
		return dc;
	}

	// find the dead cells that become alive and add to LiveCellsNext
	void born(CoordinateArray PossLiveCells)
	{
		for (int i = 0; i < PossLiveCells.size(); i++)
		{
			int count = 0; // count for live neighbours
			CoordinateArray nbrs = neighbours(PossLiveCells, i);
			// if live neighbour found for a dead cell, add 1 to count
			for (int j = 0; j < 8; j++)
			{
				if (LiveCells.find(nbrs[j])) count++;
			}
			/* if PossLiveCells[i] has 3 live neighbours, append PossLiveCells[i]
			to LiveCellsNext */
			if (count == 3) LiveCellsNext.push_back(PossLiveCells[i]);
		}
	}
	
	// Find the live cells that stay alive and add to LiveCellsNext
	void die()
	{
		int n = LiveCells.size();
		for (int i = 0; i < n; i++)
		{
			int count = 0; // count for live neighbours
			CoordinateArray nbrs = neighbours(LiveCells, i);
			// if a live neighbour is found for LiveCells[i], add 1 to count
			for (int j = 0; j < 8; j++)
			{
				if (LiveCells.find(nbrs[j])) count++;
			}
			/* if 2 or 3 live neighbours were found, append LiveCells[i] to 
			LiveCellsNext */
			if (count == 2 || count == 3) LiveCellsNext.push_back(LiveCells[i]);
		}
	}


	/* advance time one unit, replace LiveCells with LiveCellsNext and empty 
	LiveCellsNext */
	void tick() 
	{
		LiveCells = LiveCellsNext;
		CoordinateArray v;
		LiveCellsNext = v;
		gen += 1; 
	}

private :
	// Storage of live cells for next generation
	CoordinateArray LiveCellsNext;
};

// print MVector in the format v0,v1,....,vn,
std::ostream& operator<<(std::ostream& os, const MVector& v)
{
	for (int i = 0; i < v.size(); i++) { os << v[i] << ","; }
	return os;
}

// print IntegerArray in the format (v0.X,v0.Y),(v1.X,v1.Y),...,(vn.X,vn.Y),
std::ostream& operator<<(std::ostream& os, const CoordinateArray& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		os << "(" << v[i].X << "," << v[i].Y << "),";
	}
	return os;
}

#endif