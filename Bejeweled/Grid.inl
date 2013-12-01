#ifndef __Bejeweled_Grid_inl__
#define __Bejeweled_Grid_inl__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "Grid.h"

namespace bejeweled {

template<class ValueType>
Grid<ValueType>::Grid(int rows, int cols, const ValueType& initialValue) 
: m_numRows(rows), m_numCols(cols)
{
    resize(rows, cols, initialValue);
}

template<class ValueType>
Grid<ValueType>::Grid() 
: m_numRows(0), m_numCols(0), m_array(0)   
{ }

template<class ValueType>
Grid<ValueType>::Grid(const Grid& other)
: m_numRows(other.m_numRows), m_numCols(other.m_numCols), m_array(other.m_array) 
{ }

template<class ValueType>
Grid<ValueType>& Grid<ValueType>::operator=(const Grid& other) {
    swap(*this, other);
    return *this;
}

template<class ValueType>
int Grid<ValueType>::getNumCols() const {
    return m_numCols;
}

template<class ValueType>
int Grid<ValueType>::getNumRows() const {
    return m_numRows;
}

template<class ValueType>
bool Grid<ValueType>::isEmpty() const {
    return m_array.empty();
}

template<class ValueType>
void Grid<ValueType>::clear() {
    m_array.clear();
    m_numRows = 0;
    m_numCols = 0;
}

template<class ValueType>
void Grid<ValueType>::resize(int rows, int cols, const ValueType& initialValue) {
    m_numRows = rows;
    m_numCols = cols;
    if(m_numRows == 0) {
        m_numCols = 0;
    }
    m_array.resize(m_numRows*m_numCols, initialValue);
}

template<class ValueType>
ValueType* Grid<ValueType>::operator[](int row) {
    return &m_array[row * m_numCols];
}

template<class ValueType>
const ValueType* Grid<ValueType>::operator[](int row) const {
    return &m_array[row * m_numCols];
}

template<class ValueType>
void swap(Grid<ValueType>& a, Grid<ValueType>&b) {
    using std::swap;
    swap(a.m_m_numCols, b.m_m_numCols);
    swap(a.m_numRows, b.m_numRows);
    swap(a.m_array, b.m_array);
}

} // namespace bejeweled

#endif //__Bejeweled_Grid_inl__
