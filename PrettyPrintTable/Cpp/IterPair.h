//
// Created by max on 27/09/22.
//

#ifndef PRETTYPRINTJAVA_JAVA_ITERPAIR_H
#define PRETTYPRINTJAVA_JAVA_ITERPAIR_H

#include <iterator>

namespace pretty {

/**
 * This is my first attempt at writing an iterator. <br>
 * This is copied or inspired by from
 * https://en.cppreference.com/w/cpp/iterator/iterator
 */
template<std::forward_iterator T, std::forward_iterator U>
class IterPair {

    struct IterType {
        T left;
        U right;

        IterType(T l, U r) {
            left = l;
            right = r;
        }

        bool operator==(const IterType &rhs) const {
            return left == rhs.left && right == rhs.right;
        }

        bool operator!=(const IterType &rhs) const {
            return !(rhs == *this);
        }
    };


    class iterator : public std::iterator<
            std::input_iterator_tag,    // iterator_category
            IterType                    // value_type
    > {

    private:
        IterPair *parent_;
        IterType iter_ = {leftStart_, rightStart_};


    public:
        explicit iterator(IterPair *parent, IterType in)
                : parent_(parent), iter_(in) {}

        iterator(const iterator &) = default;

        // Pre increment.
        iterator &operator++() {
            bool canIncrement = (iter_.left < parent_->leftEnd_)
                                || (iter_.right < parent_->rightEnd_);

            if (canIncrement) {
                iter_ = {++iter_.left, ++iter_.right};
            } else {
                // I don't know why it does this or why they had it.
                // iter_ = {--iter_.left, --iter_.right};
            }
            return *this;
        }

        // Post increment.
        iterator &operator++(int) {
            iterator retval = *this;
            ++(*this);
            return retval;
        }

        bool operator==(iterator other) const {
            return (other.parent_ == parent_) && (other.iter_ == iter_);
        }

        bool operator!=(iterator other) const {
            return !(*this == other);
        }

        IterType operator*() const {
            return iter_;
        }

    };


private:
    T leftStart_;
    T leftEnd_;
    U rightStart_;
    U rightEnd_;


public:
    IterPair(T leftStart, T leftEnd, U rightStart, U rightEnd)
            : leftStart_(leftStart), leftEnd_(leftEnd), rightStart_(rightStart),
              rightEnd_(rightEnd) {}


    iterator begin() {
        return iterator(this, IterType(leftStart_, rightStart_));
    }

    iterator end() {
        return iterator(this, IterType(leftEnd_, rightEnd_));
    }

};


}



#endif //PRETTYPRINTJAVA_JAVA_ITERPAIR_H
