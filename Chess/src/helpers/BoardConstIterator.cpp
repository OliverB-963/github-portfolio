//
// Created by Oliver Bailey on 18/07/2025.
//

#include "helpers/BoardConstIterator.hpp"

#include "Board.hpp"

BoardConstIterator::BoardConstIterator(const Board *boardPtr, const int currentRow, const int currentCol)
    : boardPtr_(boardPtr), currentRow_(currentRow), currentCol_(currentCol){}

BoardConstIterator &BoardConstIterator::operator++() {
    if (currentCol_ >= 7) {
        currentCol_ = 0;
        currentRow_++;
    }
    else currentCol_++;

    return *this;
}

BoardConstIterator BoardConstIterator::operator++(int) {
    const BoardConstIterator temp = *this;
    ++(*this);
    return temp;
}

bool BoardConstIterator::operator==(const BoardConstIterator &other) const {
    return boardPtr_ == other.boardPtr_
        && currentRow_ == other.currentRow_
        && currentCol_ == other.currentCol_;
}

bool BoardConstIterator::operator!=(const BoardConstIterator &other) const {
    return !(*this == other);
}

BoardConstIterator::reference BoardConstIterator::operator*() const {
    return boardPtr_->getPiece(currentRow_, currentCol_);
}

BoardConstIterator::pointer BoardConstIterator::operator->() const {
    return boardPtr_->getPiece(currentRow_, currentCol_);
}
