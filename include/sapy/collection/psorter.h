#pragma once

#include <functional>
#include "sapy/collection/pcomparer.h"

namespace sapy{

namespace collection{

template <typename T>
class PSorter {
private:
    PComparer<T> cmp_;

    // 默认比较函数
    bool defaultCompare(const T& a, const T& b) const {
        return a < b;
    }

    // 获取比较函数
    bool compare(const T& a, const T& b) const {
        return cmp_ ? cmp_(a, b) : defaultCompare(a, b);
    }

    // 快速排序的递归实现
    void quickSort(PIteratorInterface<T> begin, PIteratorInterface<T> end) const {
        if (begin != end) {
            PIteratorInterface<T> pivot = partition(begin, end);
            quickSort(begin, pivot);
            quickSort(++pivot, end);
        }
    }

    // 快速排序的分区函数
    PIteratorInterface<T> partition(PIteratorInterface<T> begin, PIteratorInterface<T> end) const {
        PIteratorInterface<T> pivot = begin;
        PIteratorInterface<T> i = begin;
        PIteratorInterface<T> j = begin + 1;

        while (j != end) {
            if (compare(*j, *pivot)) {
                ++i;
                std::swap(*i, *j);
            }
            ++j;
        }
        std::swap(*i, *pivot);
        return i;
    }

    // 归并排序的递归实现
    void mergeSort(PIteratorInterface<T> begin, PIteratorInterface<T> end) const {
        if (begin != end && begin + 1 != end) {
            PIteratorInterface<T> mid = begin + (end - begin) / 2;
            mergeSort(begin, mid);
            mergeSort(mid, end);
            merge(begin, mid, end);
        }
    }

    // 归并排序的合并函数
    void merge(PIteratorInterface<T> begin, PIteratorInterface<T> mid, PIteratorInterface<T> end) const {
        std::vector<T> temp;
        PIteratorInterface<T> i = begin;
        PIteratorInterface<T> j = mid;

        while (i != mid && j != end) {
            if (compare(*i, *j)) {
                temp.push_back(*i);
                ++i;
            } else {
                temp.push_back(*j);
                ++j;
            }
        }

        while (i != mid) {
            temp.push_back(*i);
            ++i;
        }

        while (j != end) {
            temp.push_back(*j);
            ++j;
        }

        for (const T& val : temp) {
            *begin = val;
            ++begin;
        }
    }

    // 堆排序的实现
    void heapSort(PIteratorInterface<T> begin, PIteratorInterface<T> end) const {
        std::vector<T> temp(begin, end);
        std::make_heap(temp.begin(), temp.end(), [this](const T& a, const T& b) {
            return compare(a, b);
        });
        std::sort_heap(temp.begin(), temp.end(), [this](const T& a, const T& b) {
            return compare(a, b);
        });

        for (const T& val : temp) {
            *begin = val;
            ++begin;
        }
    }

public:
    PSorter()
        : cmp_(nullptr) {}
    PSorter(PComparer<T> cmp)
        : cmp_(cmp) {}

    // 快速排序
    void quickSort(PIteratorInterface<T> begin, PIteratorInterface<T> end) {
        quickSort(begin, end);
    }

    // 归并排序
    void mergeSort(PIteratorInterface<T> begin, PIteratorInterface<T> end) {
        mergeSort(begin, end);
    }

    // 堆排序
    void heapSort(PIteratorInterface<T> begin, PIteratorInterface<T> end) {
        heapSort(begin, end);
    }

    // 默认排序（使用快速排序）
    void sort(PIteratorInterface<T> begin, PIteratorInterface<T> end) {
        quickSort(begin, end);
    }
};

}
}