#include "stack.h"

Stack::Stack() : head_(nullptr), size_(0) {
}

Stack::~Stack() {

    Clear();
}

void Stack::Push(int32_t value) {

    Node* node = new Node(value, head_);

    head_ = node;

    ++size_;
}

void Stack::Pop() {

    if (!Empty()) {

        Node* node = head_;
        head_ = node->previous;

        delete node;  //  clearing the memory

        --size_;
    }
}

int32_t Stack::Top() const {

    if (!Empty()) {

        return head_->value;
    }

    return 0;
}

int32_t Stack::Size() const {

    return size_;
}

void Stack::Clear() {

    while (head_ != nullptr) {

        Pop();
    }
}

bool Stack::Empty() const {

    if (!size_) {

        return true;
    }

    return false;
}
