//
// Created by Oliver Bailey on 18/07/2025.
//

#include "helpers/BoardIterator.hpp"

#include "Board.hpp"

BoardIterator::BoardIterator(Board *boardPtr, const int currentRow, const int currentCol)
    : boardPtr_(boardPtr), currentRow_(currentRow), currentCol_(currentCol){}

BoardIterator &BoardIterator::operator++() {
    if (currentCol_ >= 7) {
        currentCol_ = 0;
        currentRow_++;
    }
    else currentCol_++;

    return *this;
}

BoardIterator BoardIterator::operator++(int) {
    const BoardIterator temp = *this;
    ++(*this);
    return temp;
}

bool BoardIterator::operator==(const BoardIterator &other) const {
    return boardPtr_ == other.boardPtr_
        && currentRow_ == other.currentRow_
        && currentCol_ == other.currentCol_;
}

bool BoardIterator::operator!=(const BoardIterator &other) const {
    return !(*this == other);
}

BoardIterator::reference BoardIterator::operator*() const {
    return boardPtr_->getPiece(currentRow_, currentCol_);
}

BoardIterator::pointer BoardIterator::operator->() const {
    return boardPtr_->getPiece(currentRow_, currentCol_);
}
