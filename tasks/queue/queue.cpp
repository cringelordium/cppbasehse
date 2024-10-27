#include "queue.h"

Node::Node(int32_t value, Node* next) : value(value), next(next) {
}

Queue::Queue() : front_(nullptr), tail_(nullptr), size_(0) {
}

Queue::~Queue() {

    Clear();
}

void Queue::Push(int32_t value) {

    Node* node = new Node(value, nullptr);

    ++size_;

    if (tail_ == nullptr) {

        front_ = node;

        tail_ = node;
    } else {

        tail_->next = node;

        tail_ = node;
    }
}

void Queue::Pop() {

    if (!Empty()) {

        Node* node = front_;

        front_ = front_->next;

        --size_;

        delete node;  //  clear

        if (front_ == nullptr) {

            tail_ = front_;
        }
    }
}

int32_t Queue::Front() const {

    if (!Empty()) {

        return front_->value;
    }

    return 0;
}

int32_t Queue::Size() const {

    return size_;
}

void Queue::Clear() {

    while (front_ != nullptr) {

        Pop();
    }
}

bool Queue::Empty() const {

    if (size_ == 0) {

        return true;
    }

    return false;
}
