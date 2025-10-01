//
// Created by Oliver Bailey on 18/07/2025.
//

#ifndef BOARDITERATOR_HPP
#define BOARDITERATOR_HPP

#include <cstddef>
#include <iterator>

class Board;
class Piece;

class BoardIterator {
public:
    // Type aliases for standard iterator traits
    using iteratorCategory = std::forward_iterator_tag;
    using valueType = Piece; // The type of element you are iterating over (e.g., int, char, TileType)
    using differenceType = std::ptrdiff_t;
    using pointer = valueType*;
    using reference = valueType*;

    // Constructor
    BoardIterator(Board* boardPtr, int currentRow, int currentCol);

    // Dereference operators
    reference operator*() const;
    pointer operator->() const;

    // Increment operators
    BoardIterator& operator++();    // Pre-increment (++it)
    BoardIterator operator++(int);  // Post-increment (it++)

    // Comparison operators
    bool operator==(const BoardIterator& other) const;
    bool operator!=(const BoardIterator& other) const;

private:
    Board* boardPtr_;
    int currentRow_;
    int currentCol_;
};



#endif //BOARDITERATOR_HPP
