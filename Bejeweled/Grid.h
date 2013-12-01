#ifndef __Bejeweled_Grid_h__
#define __Bejeweled_Grid_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <vector>

namespace bejeweled {

/**
 * Mimics A 2d grid representation of a 1d vector for efficiency.
 * Usage example :
 *  Grid<int> x(5,3);
 *  Grid[5][3] = 7;
 */
template<class ValueType>
class Grid {
public:
    /// Initialize the grid with the given rows and columns, and fill with the specified default value.
    Grid(int rows, int cols, const ValueType& initialValue = ValueType());

    /// Empty ctor - initializes an empty grid.
    Grid();

    /// Copy ctor and assignment operator - copy another grid (using the vector deep-copying)
    Grid(const Grid& other);
    Grid& operator=(const Grid& other);

    /// Dimension getters
    int getNumRows() const;
    int getNumCols() const;
    bool isEmpty() const;
    void clear();
    void resize(int rows, int cols, const ValueType& initialValue=ValueType());

    /// Access operators - return a pointer to the start of the given row.
    /// Calling the returned value again would give the item in the desired column
    ValueType* operator[](int row);
    const ValueType* operator[](int row) const;

    /// Swap method for copy-and-swap in the assignment operator. (found by ADL)
    friend void swap(Grid& a, Grid&b);

private:
    int m_numRows, m_numCols;

    /// A 1d array that holds the data
    std::vector<ValueType> m_array;
}; // class Grid

} // namespace bejeweled

// Template functions implementations
#include "Grid.inl"

#endif // __Bejeweled_Grid_h__
