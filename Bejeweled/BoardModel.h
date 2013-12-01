#ifndef __Bejeweled_BoardModel_h__
#define __Bejeweled_BoardModel_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <SDL.h>
#include <vector>
#include "Grid.h"
#include "TileSequence.h"

namespace bejeweled {

/**
 * Represents the game board as a logical unit.
 * Uses a grid of integers to represent the boar
 */
class BoardModel
{
public:
    /// Identifier for an empty tile.
    static const int EMPTY_TILE = -1;

    /*
     * Constructor
     * @param numRows    Amount of rows on the board
     * @param numCols     Amount of columns on the board
     * @param numTileTypes  How many tile types are available
     */
    BoardModel(int numRows, int numCols, int numTileTypes);

    /// Destructor
    virtual ~BoardModel();

    /// @return The height of the board
    int getNumRows() const;

    /// @return The width of the board
    int getNumColumns() const;

    /// @return the id of the tile in the given position
    int getTileId(int row, int col) const;

    /** 
     * Randomize the board with tiles - can be changed to a strategy pattern later.
     * The board created will not contain any matches (that is, it'll be "ready-to-play")
     */ 
    void fillBoard();

    /**
     * Checks if the tile in the given positions has a match in its immediate proximity.
     * That is, check if any of its surrounding tiles (or itself) are a part of a match.
     */
    bool hasSequencesProximity(int row, int col) const;

    /**
     * Does a single gravitation step. (drops all rows by 1).
     * @return false If grid is "gravitatized" (no more drops possible)
     */
    bool gravitateBoardStep();

    /**
     * Drops a single line of new tiles to top row of the grid
     * @return true    If any tiles were dropped
     */
    bool dropNewTilesRow();

    /**
     * Performs a move of 2 tiles. 
     * @return true If move was possible (adjacent tiles and non-empty)
     */
    bool swapTiles(int row1, int col1, int row2, int col2);

    /**
     * Checks if any more moves are possible on the board in its current state.
     * This is done by swapping every adjacent tiles in every 2 columns, and checking for that tile if 
     * it has created a match in its proximity (that is, if its immediate adjacent tiles are a part of a match).
     * Following that the same procedure is applies to the rows - every adjacent tiles in every two rows are swapped
     * and same check is applied.
     */
    bool hasMoreMoves();

    /**
    * Finds all sequences on the board and marks them as empty tiles.
    * @return true if any sequence was found, false otherwise.
    */
    bool markAllSequencesOnBoard();

    // The following are currently unused methods that perform the actions directly (and not in "steps")
#if 0
    /**
     * Unused.
     * Checks if the board has any sequences of at least length 3.
     * This is a bit faster than calling markAllSequencesOnBoard,
     * as we do not find the sequences themselves.
     */
    bool hasSequences() const;


    /**
     * Unused.
     * Gets the board to a stable state - finds all the sequences, removes them and gravitates the board,
     * does so over and over again until board has no more sequences.
     */
    void stabilizeBoard();

    /**
     * Unused.
     * Makes a move - swapping between 2 tiles, checking if the board has new sequences.
     * If it does - stabilizes it. Else - swaps back and return false.
     */
    bool makeMove(int row1, int col1, int row2, int col2);

    /**
     * Unused.
     * Actually causes all tiles to drop to new locations when empty tiles are in the board.
     */
    void gravitateBoard();

    /**
     * Unused.
     * Add missing tile from the top to the missing locations.
     */ 
    void dropNewTiles();
#endif

private:
    /// Prevent Copying and Assignment
    BoardModel(const BoardModel&);
    BoardModel& operator=(const BoardModel&);

    /**
    * Checks for all the sequences in the grid.
    * Initializes the sequence collection with all the sequences in the grid.
    * @return true If any sequences were found and the sequence collection is not empty
    */
    bool findAllSequences();

    /**
    * Marks all tiles of the given sequence as empty tiles in the board
    */
    void markSequenceOnBoard(const TileSequence& sequence);

    /**
     * Checks if the cell at [i][j] is the first cell of an horizontal or vertical sequence. 
     * Also handles border cases.
     */
    bool isBeginningOfSequence(int i, int j) const;

    /**
     * Checks if the cell at [i][j] is the last cell of an horizontal or vertical sequence. 
     * Also handles border cases.
     */ 
    bool isEndOfSequence(int i, int j) const;

    /// Board dimensions
    int m_numCols, m_numRows;

    /// Number of available tile types
    int m_numTileTypes;

    /// Represents the 2D grid
    Grid<int> m_grid;

    /// Contains all the horizontal and vertical sequences of length 3 or more in the grid.
    std::vector<TileSequence> m_matchingSequences;
}; // class BoardModel

} // namespace bejeweled

#endif // __Bejeweled_BoardModel_h__
