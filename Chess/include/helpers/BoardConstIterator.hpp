//
// Created by Oliver Bailey on 18/07/2025.
//

#ifndef BOARDCONSTITERATOR_HPP
#define BOARDCONSTITERATOR_HPP

#include <cstddef>
#include <iterator>

class Board;
class Piece;

class BoardConstIterator {
public:
    // Type aliases for standard iterator traits
    using iteratorCategory = std::forward_iterator_tag;
    using valueType = Piece; // The type of element you are iterating over (e.g., int, char, TileType)
    using differenceType = std::ptrdiff_t;
    using pointer = const valueType*;
    using reference = const valueType*;

    // Constructor
    BoardConstIterator(const Board* boardPtr, int currentRow, int currentCol);

    // Dereference operators
    reference operator*() const;
    pointer operator->() const;

    // Increment operators
    BoardConstIterator& operator++();    // Pre-increment (++it)
    BoardConstIterator operator++(int);  // Post-increment (it++)

    // Comparison operators
    bool operator==(const BoardConstIterator& other) const;
    bool operator!=(const BoardConstIterator& other) const;

private:
    const Board* boardPtr_;
    int currentRow_;
    int currentCol_;
};



#endif //BOARDCONSTITERATOR_HPP
