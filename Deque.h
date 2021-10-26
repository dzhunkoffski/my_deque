#pragma once

#include <initializer_list>
#include <iostream>
#include <algorithm>
#include <memory>

class Block {  // Block, that stores 128 ints inside itself
public:
    std::unique_ptr<std::array<int, 128>> block_data_ = std::make_unique<std::array<int, 128>>();

    long int first_ptr;
    long int last_ptr;

    bool used = false;
    bool is_rev = false;

    Block() {
        for (int i = 0; i < 128; ++i) {
            (*block_data_)[i] = 0;
        }
        first_ptr = 0;
        last_ptr = 0;
    }

    Block(const Block& rhs) = delete;
    Block operator=(const Block&) = delete;
    Block(Block&&) = delete;

    Block operator=(Block&& rhs) = delete;

    size_t GetSize() const {
        if (!used) {
            return 0;
        }

        return last_ptr - first_ptr + 1;
    }

    bool AddNext(int digit) {
        if (used && last_ptr == 127) {  // can't add cos block is full
            return false;
        }

        // Two cases: (1) this block is fresh'n'empty (unused); (2) it used
        if (used == false) {
            used = true;
            is_rev = false;
            last_ptr = 0;
            (*block_data_)[last_ptr] = digit;
        } else {
            ++last_ptr;
            (*block_data_)[last_ptr] = digit;
        }

        return true;
    }

    bool AddPrev(int digit) {
        if (used && first_ptr == 0) {
            return false;
        }

        if (used == false) {
            used = true;
            is_rev = true;
            last_ptr = 127;
            first_ptr = 127;
            (*block_data_)[first_ptr] = digit;
        } else {
            --first_ptr;
            (*block_data_)[first_ptr] = digit;
        }

        return true;
    }

    bool EraseNext() {
        --last_ptr;
        if (last_ptr == -1 || !used) {
            used = false;
            is_rev = false;
            last_ptr = 0;
            return false;
        }

        return true;
    }

    bool ErasePrev() {
        ++first_ptr;
        if (first_ptr == 128 || !used) {
            used = false;
            is_rev = false;
            first_ptr = 127;
            return false;
        }

        return true;
    }
};

class Deque {
public:
    Deque() {
        data_ = new Block[1];
        begin_block_ = 0;
        end_block_ = 0;

        block_size_ = 1;
        capacity_ = 1;
        sz_ = 0;
    }
    Deque(const Deque& rhs) {
        data_ = new Block[1];
        begin_block_ = 0;
        end_block_ = 0;

        block_size_ = 1;
        capacity_ = 1;
        sz_ = 0;

        for (size_t i = 0; i < rhs.sz_; ++i) {
            this->PushBack(rhs[i]);
        }
    }
    Deque(Deque&& rhs) {
        data_ = rhs.data_;
        rhs.data_ = nullptr;
        begin_block_ = std::move(rhs.begin_block_);
        end_block_ = std::move(rhs.end_block_);

        block_size_ = std::move(rhs.block_size_);
        capacity_ = std::move(rhs.capacity_);
        sz_ = std::move(rhs.sz_);
    }
    explicit Deque(size_t size) {
        data_ = new Block[1];
        begin_block_ = 0;
        end_block_ = 0;

        block_size_ = 1;
        capacity_ = 1;

        for (size_t i = 0; i < size; ++i) {
            PushBack(0);
        }
    }

    Deque(std::initializer_list<int> list) {
        data_ = new Block[1];
        begin_block_ = 0;
        end_block_ = 0;

        block_size_ = 1;
        capacity_ = 1;

        for (auto el : list) {
            PushBack(el);
        }
    }

    Deque& operator=(Deque rhs) {
        Swap(rhs);
        return *this;
    }

    void Swap(Deque& rhs) {
        std::swap(this->data_, rhs.data_);
        std::swap(this->begin_block_, rhs.begin_block_);
        std::swap(this->end_block_, rhs.end_block_);
        std::swap(this->block_size_, rhs.block_size_);
        std::swap(this->capacity_, rhs.capacity_);
        std::swap(this->sz_, rhs.sz_);
    }

    void PushBack(int value) {
        if (!data_[end_block_].AddNext(value)) {
            // check for full buffer
            if (IsFull()) {
                Reserve(capacity_ * 2);
            }
            end_block_ = Next(end_block_);
            ++block_size_;
            data_[end_block_].AddNext(value);
        }

        ++sz_;
    }

    void PopBack() {
        if (!data_[end_block_].EraseNext()) {
            if (block_size_ < (capacity_ / 2)) {
                Reserve(capacity_ / 2);
            }
            --block_size_;
            end_block_ = Prev(end_block_);
        }

        --sz_;
    }

    void PushFront(int value) {
        if (!data_[begin_block_].AddPrev(value)) {
            if (IsFull()) {
                Reserve(capacity_ * 2);
            }
            begin_block_ = Prev(begin_block_);
            ++block_size_;
            data_[begin_block_].AddPrev(value);
        }

        ++sz_;
    }

    void PopFront() {
        if (!data_[begin_block_].ErasePrev()) {
            if (block_size_ < (capacity_ / 2)) {
                Reserve(capacity_ / 2);
            }
            --block_size_;
            begin_block_ = Next(begin_block_);
        }

        --sz_;
    }

    int& operator[](size_t ind) {
        size_t curr_block =
                ((data_[begin_block_].first_ptr + ind) / 128 + begin_block_) % capacity_;
        size_t curr_cell = (data_[begin_block_].first_ptr + ind) % 128;

        return (*data_[curr_block].block_data_)[curr_cell];
    }

    int operator[](size_t ind) const {
        size_t curr_block =
                ((data_[begin_block_].first_ptr + ind) / 128 + begin_block_) % capacity_;
        size_t curr_cell = (data_[begin_block_].first_ptr + ind) % 128;

        return (*data_[curr_block].block_data_)[curr_cell];
    }

    size_t Size() const {
        return sz_;
    }

    size_t BlockSize() const {
        return block_size_;
    }

    void Clear() {
        delete[] data_;
        data_ = new Block[1];
        begin_block_ = 0;
        end_block_ = 0;

        block_size_ = 1;
        capacity_ = 1;

        sz_ = 0;
    }

    ~Deque() {
        delete[] data_;
    }

    void Reserve(size_t new_size) {
        Block* expanded_data = new Block[new_size];
        size_t i = 0;
        size_t now_block = begin_block_;
        while (true) {
            if (now_block == end_block_) {
                expanded_data[i].block_data_ = std::move(data_[now_block].block_data_);
                expanded_data[i].first_ptr = data_[now_block].first_ptr;
                expanded_data[i].last_ptr = data_[now_block].last_ptr;
                expanded_data[i].used = data_[now_block].used;
                expanded_data[i].is_rev = data_[now_block].is_rev;
                break;
            } else {
                expanded_data[i].block_data_ = std::move(data_[now_block].block_data_);
                expanded_data[i].first_ptr = data_[now_block].first_ptr;
                expanded_data[i].last_ptr = data_[now_block].last_ptr;
                expanded_data[i].used = data_[now_block].used;
                expanded_data[i].is_rev = data_[now_block].is_rev;

                ++i;
                now_block = Next(now_block);
            }
        }

        delete[] data_;
        data_ = std::move(expanded_data);
        capacity_ = new_size;
        begin_block_ = 0;
        end_block_ = i;  // maybe i - 1
    }

    size_t Next(size_t it) {
        return (it + 1) % capacity_;
    }

    size_t Prev(size_t it) {
        if (it == 0) {
            return capacity_ - 1;
        }

        return (it - 1) % capacity_;
    }

    bool IsFull() {
        return capacity_ == block_size_;
    }

private:
    Block* data_;

    size_t begin_block_;
    size_t sz_ = 0;
    size_t end_block_;

    size_t block_size_ = 0;
    size_t capacity_ = 0;
};
