#include <vector>
#include <random>
#include <deque>
#include <cassert>
#include <iostream>

#include "Deque.h"

void Check(const Deque& actual, const std::vector<int>& expected) {
    assert(actual.Size() == expected.size());
    for (size_t i = 0; i < actual.Size(); ++i) {
        assert(actual[i] == expected[i]);
    }
}

int main() {
    std::cout << "================ TEST1: CONSTRUCTORS ================" << '\n';
    {
        Deque a;
        assert(a.Size() == 0);
    }
    {
        Deque a{1, 2, 3, 4};
        Check(a, std::vector<int>{1, 2, 3, 4});
    }
    {
        Deque a(5);
        Check(a, std::vector<int>(5));
    }
    std::cout << "++++++++ TEST1: PASSED ++++++++" << '\n';

    std::cout << "================ TEST2: BASIC METHODS ================" << '\n';
    {
        Deque a{1, 3, 5};
        Check(a, std::vector<int>{1, 3, 5});

        a.PopBack();
        Check(a, std::vector<int>{1, 3});
        a.PopFront();
        Check(a, std::vector<int>{3});
        a.PushFront(5);
        Check(a, std::vector<int>{5, 3});
        a.PushBack(1);
        Check(a, std::vector<int>{5, 3, 1});

        a.Clear();
        Check(a, std::vector<int>());

        a.PushBack(3);
        Deque b{2, 4};
        a.Swap(b);
        Check(a, std::vector<int>{2, 4});
        Check(b, std::vector<int>{3});
    }
    std::cout << "++++++++ TEST2: PASSED ++++++++" << '\n';

    std::cout << "================ TEST3: OPERATOR [] ================" << '\n';
    {
        Deque a{9, 1, 1};
        a[0] = 1;
        a[1] = 2;
        a[2] = 3;
        Check(a, std::vector<int>{1, 2, 3});
    }
    std::cout << "++++++++ TEST3: PASSED ++++++++" << '\n';

    std::cout << "================ TEST4: REALLOCATIONS ================" << '\n';
    {
        Deque a;
        const int iterations = 1e6;
        std::vector<int*> addr;
        for (int i = 0; i < iterations; ++i) {
            a.PushBack(i);
            addr.push_back(&a[i]);
        }

        for (int i = 0; i < iterations; ++i) {
            assert(*addr[i] == i);
        }

        // adding erase realloc
    }
    std::cout << "++++++++ TEST4: PASSED ++++++++" << '\n';

    std::cout << "================ TEST5: COPY ================" << '\n';
    {
        Deque a;
        Deque b(a);
        b.PushBack(1);
        Check(a, std::vector<int>());
        Check(b, std::vector<int>{1});

        b = b;
        Check(b, std::vector<int>{1});
        a = b;
        Check(a, std::vector<int>{1});

        b = std::move(a);
        Check(b, std::vector<int>{1});
        Deque c(std::move(b));
        Check(c, std::vector<int>{1});

        Deque d{3, 4, 5};
        Deque e(d);
        Check(e, std::vector<int>{3, 4, 5});
        d.Swap(c);
        Check(e, std::vector<int>{3, 4, 5});
        Check(d, std::vector<int>{1});
        Check(c, std::vector<int>{3, 4, 5});
    }
    std::cout << "++++++++ TEST5: PASSED ++++++++" << '\n';

    std::cout << "================= TEST6: STRESS-TEST ================" << '\n';
    {
        const int iterations = 1e6;
        Deque a;
        std::deque<int> b;
        std::mt19937 gen(735675);
        std::uniform_int_distribution<int> dist(1, 5);

        for (int i = 0; i < iterations; ++i) {
            a.PushFront(i);
            b.push_front(i);
        }

        for (int i = 0; i < iterations; ++i) {
            int code = dist(gen);
            int value = gen();
            if (code == 1) {
                a.PushFront(value);
                b.push_front(value);
            } else if (code == 2) {
                a.PushBack(value);
                b.push_back(value);
            } else if (code == 3) {
                a.PopFront();
                b.pop_front();
            } else if (code == 4) {
                a.PopBack();
                b.pop_back();
            } else {
                int index = static_cast<int>(value % a.Size());
                assert(a[index] == b[index]);
            }
        }
    }
    std::cout << "++++++++ TEST6: PASSED ++++++++" << '\n';
}
