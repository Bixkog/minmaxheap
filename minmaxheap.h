#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H
#include <vector>
#include <iostream>
#include <algorithm>

template<typename T>
class minmaxheap
{
    std::vector<T> heap;
    size_t n;

    size_t partnerH(size_t k) const;
    size_t partnerL(size_t k) const;
    bool hasPartner(size_t k) const;
    
    size_t parent(size_t k) const;
    

    struct children
    {
        size_t left;
        size_t right;
    };

    children getChildren(size_t k) const;

    void moveUpH(size_t k);
    void moveUpL(size_t k);
    void moveDownH(size_t k);
    void moveDownL(size_t k);
public:
    minmaxheap();
    minmaxheap(std::vector<T> v);
    void insert(T t);
    T popMax();
    T popMin();
    bool empty();

    friend std::ostream& operator << (std::ostream& out, const minmaxheap& h)
    {
        for(T t : h.heap)
            out << t << " ";
        return out;
    }
};

template<typename T>
minmaxheap<T>::minmaxheap()
: heap(),
    n(0)
{}

template<typename T>
minmaxheap<T>::minmaxheap(std::vector<T> v)
: heap(),
    n(0)
{
    // bottom-up linear creation?
    for(auto e : v)
        insert(e);
}

template<typename T>
void minmaxheap<T>::insert(T t)
{
    heap.push_back(t);
    size_t k = n++;
    if(n == 1) return;
    size_t p = k&1?partnerL(k):partnerH(k);
    if(k&1)
    {
        if(heap[k] > heap[p])
            moveDownL(k);
        else
            moveUpL(k);
    }
    else
    {
        if(heap[k] < heap[p])
            moveDownH(k);
        else
            moveUpH(k);
    }
}

template<typename T>
T minmaxheap<T>::popMax()
{
    T max_el = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    n--;
    moveDownH(0);
    return max_el;
}

template<typename T>
T minmaxheap<T>::popMin()
{
    if(n == 1) return popMax();
    T min_el = heap[1];
    heap[1] = heap.back();
    n--;
    heap.pop_back();
    moveDownL(1);
    return min_el;
}

template<typename T>
bool minmaxheap<T>::empty()
{
    return heap.empty();
}

template<typename T>
void minmaxheap<T>::moveUpH(size_t k)
{
    size_t j;
    do
    {
        j = k;
        size_t p = parent(k);
        if(j > 1 && heap[k] > heap[p])
        {
            k = p;
            std::swap(heap[k], heap[j]);
        }
    }
    while(j != k);
}

template<typename T>
void minmaxheap<T>::moveUpL(size_t k)
{
    size_t j;
    do
    {
        j = k;
        size_t p = parent(k);
        if(j > 1 && heap[k] < heap[p])
        {
            k = p;
            std::swap(heap[k], heap[j]);
        }
    }
    while(j != k);    
}

template<typename T>
void minmaxheap<T>::moveDownH(size_t k)
{
    size_t j;
    do
    {
        j = k;
        children c = getChildren(k);
        if(c.left < n && heap[k] < heap[c.left])
            k = c.left;
        if(c.right < n && heap[k] < heap[c.right])
            k = c.right;
        std::swap(heap[k], heap[j]);
    }
    while(j != k);
    if(!hasPartner(k)) return;
    size_t p = partnerH(k);
    if(heap[k] < heap[p])
    {
        std::swap(heap[k], heap[p]);
        moveUpL(p);
    }
}

template<typename T>
void minmaxheap<T>::moveDownL(size_t k)
{
    size_t j;
    do
    {
        j = k;
        children c = getChildren(k);
        if(c.left < n && heap[k] > heap[c.left])
            k = c.left;
        if(c.right < n)
        {
            if(heap[k] > heap[c.right])
                k = c.right;
        }
        else if(c.left < n)
        {
            size_t p = partnerL(k);
            if(heap[k] > heap[p])
            {
                std::swap(heap[j], heap[p]);
                moveUpH(p);
                return;
            }
        }
        std::swap(heap[j], heap[k]);
    }
    while(j != k);
    if(!hasPartner(k)) return;
    size_t p = partnerL(k);
    if(heap[k] > heap[p])
    {
        std::swap(heap[k], heap[p]);
        moveUpH(p);
    }
}

template<typename T>
typename minmaxheap<T>::children 
minmaxheap<T>::getChildren(size_t k) const
{
    return children{2*(k+1) - (k&1), 2*(k+1) + 2 - (k&1)};
}

template<typename T>
bool minmaxheap<T>::hasPartner(size_t k) const
{
    children c = getChildren(k);
    if((k&1) && (n&1))
    {
        return c.right >= n;
    }
    else
        return c.left >= n;
}

template<typename T>
size_t minmaxheap<T>::partnerL(size_t k) const
{
    size_t base = ((n-1)/2);
    if((n&1) == 1 && k == base - 1 + (base&1))
        return n - 1;
    else
        return k - 1;
}

template<typename T>
size_t minmaxheap<T>::partnerH(size_t k) const
{
    if(k == n - (n&1)) // can only occur when n&1 == 1
    {
        size_t base = k/2;
        return base - 1 + (base&1);
    }
    else
        return k + 1;
}

template<typename T>
size_t minmaxheap<T>::parent(size_t k) const
{
    size_t base = k/2;
    return  base - 2 + (k&1) + (base&1);
}


#endif
