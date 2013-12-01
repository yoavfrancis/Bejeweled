#include "TileSequence.h"

namespace bejeweled {

TileSequence::TileSequence(int typeId, TileSequence::Orientation orientation, int startRow, int startCol, int size) 
 : m_orientation(orientation), m_typeId(typeId), m_size(size), m_row(startRow), m_col(startCol)
{ }

TileSequence::TileSequence(const TileSequence& other) {
    this->operator=(other);
}

TileSequence& TileSequence::operator=(const TileSequence& other) {
    if(this != &other) {
        m_orientation = other.m_orientation;
        m_col = other.m_col;
        m_row = other.m_row;
        m_size = other.m_size;
        m_typeId = other.m_typeId;
    }
    return *this;
}
TileSequence::~TileSequence() 
{ }

int TileSequence::getTypeId() const {
    return m_typeId;
}

TileSequence::Orientation TileSequence::getOrientation() const {
    return m_orientation;
}

int TileSequence::getSize() const {
    return m_size;
}

int TileSequence::getStartRow() const {
    return m_row;
}

int TileSequence::getStartCol() const {
    return m_col;
}

} // namespace bejeweled
