#ifndef __Bejeweled_TileSequence_h__
#define __Bejeweled_TileSequence_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

namespace bejeweled {

/**
 * Describes a sequence of tiles of the same color.
 * Each tile sequence has its start row, start column, orientation (horizontal or vertical)
 * and its size (number of tiles)
 */
class TileSequence
{
public:
    /// Represents the type of the chunk.
    enum Orientation {HORIZONTAL, VERTICAL};

    /// Constructor
    TileSequence(int typeId, Orientation orientation, int startRow, int startCol, int size);

    /// Copy ctor
    TileSequence(const TileSequence&);

    /// Assignment operator
    TileSequence& operator=(const TileSequence&);

    /// Destructor
    virtual ~TileSequence();

    /// gets the type id
    int getTypeId() const;

    /// gets the chunk length (number of tiles in it)
    int getSize() const;

    /// Returns the start row
    int getStartRow() const;
    
    /// Returns the start col
    int getStartCol() const;

    /// return the chunk orientation
    Orientation getOrientation() const;

private:
    /// The type of the chunk, horizontal or vertical.
    Orientation m_orientation;

    //// Type identifier for the tiles in that chunk.
    int m_typeId;

    /// Number of items in the chunk
    int m_size;

    /// Start location for the chunk
    int m_row, m_col;
}; // class TileSequence

} // namespace bejeweled

#endif // __Bejeweled_TileSequence_h__
