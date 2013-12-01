#include <ctime>
#include <algorithm>
#include "BoardModel.h"
#include "TileSequence.h"
#include "Grid.h"

namespace bejeweled {

BoardModel::BoardModel(int numRows, int numCols, int numTileTypes)
: m_numRows(numRows), m_numCols(numCols), m_numTileTypes(numTileTypes), m_grid(numRows, numCols, EMPTY_TILE)
{
    std::srand(std::time(0));
    fillBoard();
}

BoardModel::~BoardModel() {
    // Grid will be automatically cleaned
}

void BoardModel::fillBoard() {
    bool boardReady = false;

   // Fill board with random tiles.
    for(int i=0; i<m_numRows; ++i) {
        for(int j=0; j<m_numCols; ++j) {
            m_grid[i][j] = std::rand() % m_numTileTypes;
        }
    }

    // While there was any match in the board, fix the causing tile with a new random tile and check again
    while(!boardReady) {
        boardReady = true;
        // Note that we must NOT iterate until m_numRows-2, as this will cause us to miss tiles
        // the isBeginningOfSequence method checks if the row is in boundary.
        for(int i=0; i<m_numRows; ++i) { 
            for(int j=0; j<m_numCols; ++j) {
               if(isBeginningOfSequence(i, j)) {
                    boardReady = false;
                    m_grid[i][j] = std::rand() % m_numTileTypes;
               }
            }
        }
    }
}

bool BoardModel::hasSequencesProximity(int row, int col) const {
    using std::max;
    using std::min;

    // Check if one of the tiles to the left/above the current tile is a beginning of a sequence (and perhaps involving
    // the current tile)
    for(int i=max(row-1, 0); i<min(row+2, m_numRows); ++i) {
        for (int j=max(col-1, 0); j<min(col+2, m_numCols); ++j) {
            if (isBeginningOfSequence(i, j) || isEndOfSequence(i, j)) {
                return true;
            }
        }
    }

    return false;
}

bool BoardModel::gravitateBoardStep() {
    bool found = false;
    for(int j=0; j<m_numCols; ++j) {
        /// Gravitate up until the first row.
        for(int i=m_numRows-1; i>0; --i) {
            if(m_grid[i][j] == EMPTY_TILE) {
                // Found empty tile - move all tiles above it back.
                for(int k=i; k>0; --k) {
                    if(m_grid[k-1][j] != EMPTY_TILE) {
                        // Moved back a non-empty tile - board is not "gravitatized"
                        found = true;
                    }
                    m_grid[k][j] = m_grid[k-1][j];
                    m_grid[k-1][j] = EMPTY_TILE;
                }
                break;
            }
        }
    }
    return found;
}

bool BoardModel::dropNewTilesRow() {
    bool dropped = false;
    for(int j=0; j<m_numCols; ++j) {
        if(m_grid[0][j] == EMPTY_TILE) {
            dropped = true;
            m_grid[0][j] = std::rand() % m_numTileTypes;
        }
    }
    return dropped;
}

bool BoardModel::swapTiles(int row1, int col1, int row2, int col2) {
    if((col1 == col2 && (row1 == row2-1 || row1 == row2+1)) ||
        (row1 == row2 && (col1 == col2-1 || col1 == col2+1)))
    {
        if(m_grid[row1][col1] == EMPTY_TILE || m_grid[row2][col2] == EMPTY_TILE ||
           m_grid[row1][col1] ==  m_grid[row2][col2]) {
            return false; // if either tile is empty or they have same color - no need to swap
        }
        int tmp = m_grid[row1][col1];
        m_grid[row1][col1] = m_grid[row2][col2];
        m_grid[row2][col2] = tmp;
        return true;
    } 
    return false; // tiles are not adjacent.
}


int BoardModel::getNumRows() const {
    return m_numRows;
}

int BoardModel::getNumColumns() const {
    return m_numCols;
}

int BoardModel::getTileId(int row, int col) const {
    return m_grid[row][col];
}

bool BoardModel::hasMoreMoves() {
    bool hasMove = false;
    // Horizontal moves - pass on every column and switch each tile with the one to its right.
    for(int j=0; j<m_numCols-1; ++j) {
        for(int i=0; i<m_numRows; ++i) {
            if(hasMove) {
                return true;
            }

            if(swapTiles(i, j, i, j+1)) {
                if(hasSequencesProximity(i, j)) {
                    hasMove=true;
                }
                // Swap occurred - swap back to preserve board state.
                swapTiles(i, j, i, j+1);
            }
        }
    }

    // Vertical moves - pass on every row and switch each tile with the one to below it.
    for(int i=0; i<m_numRows-1; ++i) {
        for(int j=0; j<m_numCols; ++j) {
            if(hasMove) {
                return true;
            }

            if(swapTiles(i, j, i+1, j)) {
                if(hasSequencesProximity(i, j)) {
                    hasMove=true;
                }
                // Swap occurred - swap back to preserve board state.
                swapTiles(i, j, i+1, j);
            }
        }
    }
    return hasMove;
}

bool BoardModel::markAllSequencesOnBoard() {
    if (!findAllSequences()) {
        return false;
    }

    for (std::vector<TileSequence>::const_iterator it = m_matchingSequences.begin();
        it != m_matchingSequences.end();
        ++it)
    {
        markSequenceOnBoard(*it);
    }
    return true;
}


bool BoardModel::findAllSequences() {
    m_matchingSequences.clear();

    // Find all the horizontal matches and create the matching sequence objects.
    int curMatchLen = 1;
    int curCellId = EMPTY_TILE;
    int curIndexStart = -1;

    // Look for horizontal matches - check each tile with the one after it.
    for (int i = 0; i < m_numRows; ++i) {
        curMatchLen = 1;
        for (int j = 0; j < m_numCols - 1; ++j) {
            if (m_grid[i][j] == EMPTY_TILE) {
                curMatchLen = 1;
                continue;
            }

            // Found a sequence of same tiles in a row of length 2 at least.
            if (m_grid[i][j] == m_grid[i][j + 1]) {
                curMatchLen++;
            }
            else {
                // match sequence broken - check if previous sequence was more than 3
                if (curMatchLen >= 3) {
                    m_matchingSequences.push_back(
                        TileSequence(m_grid[i][j],
                        TileSequence::HORIZONTAL,
                        i,
                        j - (curMatchLen - 1), // Start column position for the sequence
                        curMatchLen));
                }
                curMatchLen = 1;
            }
        }

        // Found a match up until the last item in current row.
        if (curMatchLen >= 3) {
            m_matchingSequences.push_back(
                TileSequence(m_grid[i][m_numCols - 1],
                TileSequence::HORIZONTAL,
                i,
                m_numCols - curMatchLen, // Start column position for the sequence
                curMatchLen));
        }
    }

    // Look for vertical matches -  check each tile with the one after it.
    curMatchLen = 1;
    for (int j = 0; j < m_numCols; ++j) {
        curMatchLen = 1;
        for (int i = 0; i < m_numRows - 1; ++i) {
            if (m_grid[i][j] == EMPTY_TILE) {
                curMatchLen = 1;
                continue;
            }

            // Found a sequence of same tiles in a row of length 2 at least.
            if (m_grid[i][j] == m_grid[i + 1][j]) {
                curMatchLen++;
            }
            else {
                // match sequence broken - check if previous sequence was more than 3
                if (curMatchLen >= 3) {
                    m_matchingSequences.push_back(
                        TileSequence(m_grid[i][j],
                        TileSequence::VERTICAL,
                        i - (curMatchLen - 1), // Start row position for the sequence
                        j,
                        curMatchLen));
                }
                curMatchLen = 1;
            }
        }

        // Found a match up until the last item in current row.
        if (curMatchLen >= 3) {
            m_matchingSequences.push_back(
                TileSequence(m_grid[m_numRows - 1][j],
                TileSequence::VERTICAL,
                m_numRows - curMatchLen, // Start row position for the sequence
                j,
                curMatchLen));
        }
    }

    return !m_matchingSequences.empty();
}

void BoardModel::markSequenceOnBoard(const TileSequence& sequence) {
    if (sequence.getOrientation() == TileSequence::HORIZONTAL) {
        for (int j = sequence.getStartCol();
            j < sequence.getStartCol() + sequence.getSize();
            ++j)
        {
            m_grid[sequence.getStartRow()][j] = EMPTY_TILE;
        }
    }
    else if (sequence.getOrientation() == TileSequence::VERTICAL) {
        for (int i = sequence.getStartRow();
            i < sequence.getStartRow() + sequence.getSize();
            ++i)
        {
            m_grid[i][sequence.getStartCol()] = EMPTY_TILE;
        }
    }
}

bool BoardModel::isBeginningOfSequence(int i, int j) const {
    return ((j>=0 && j<m_numCols-2 && m_grid[i][j] == m_grid[i][j+1] && m_grid[i][j] == m_grid[i][j+2]) ||
            (i>=0 && i<m_numRows-2 && m_grid[i][j] == m_grid[i+1][j] && m_grid[i][j] == m_grid[i+2][j]));
}


bool BoardModel::isEndOfSequence(int i,int j) const {
    return ((j<m_numCols && j>=2 && m_grid[i][j-1] == m_grid[i][j] && m_grid[i][j-2] == m_grid[i][j]) ||
            (i<m_numRows && i>=2 && m_grid[i-1][j] == m_grid[i][j] && m_grid[i-2][j] == m_grid[i][j]));
}


// UNUSED METHODS (for testing in a "non-stepwise" fashion)
#if 0

bool BoardModel::hasSequences() const {
    for (int i = 0; i < m_numRows; ++i) {
        for (int j = 0; j < m_numCols; ++j) {
            if (isBeginningOfSequence(i, j)) {
                return true;
            }
        }
    }
    return false;
}


void BoardModel::stabilizeBoard() {
    while (markAllSequencesOnBoard()) {
        gravitateBoard();
        dropNewTiles();
    }
}

bool BoardModel::makeMove(int row1, int col1, int row2, int col2) {
    if (!swapTiles(row1, col1, row2, col2)) {
        return false; //tiles are not adjacent.
    }
    else {
        if (hasSequences()) {
            stabilizeBoard();
            return true;
        }
        return false; // Move yielded no sequences
    }
}

void BoardModel::gravitateBoard() {
    // Pass on all columns, removing empty tiles and moving others forward.
    for (int j = 0; j < m_numCols; ++j) {
        for (int i = 1; i<m_numRows; ++i) {
            if (m_grid[i][j] == EMPTY_TILE) {
                // Found empty tile - move all tiles above it back.
                for (int k = i; k>0; --k) {
                    m_grid[k][j] = m_grid[k - 1][j];
                    m_grid[k - 1][j] = EMPTY_TILE;
                }
            }
        }
    }
}

void BoardModel::dropNewTiles() {
    // Drop new random tiles in every column, left to right, bottom to top.
    for (int j = 0; j < m_numCols; ++j) {
        for (int i = m_numRows - 1; i >= 0; --i) {
            if (m_grid[i][j] == EMPTY_TILE) {
                m_grid[i][j] = std::rand() % m_numTileTypes;
            }
        }
    }
}
#endif

} //namespace bejeweled
