#include <cstdint>
#include <iostream>

// CC so bits;

class MyVec
{
  private:
    uint64_t v_size;
    uint64_t v_capacity;
    int *array = nullptr;

    uint64_t calc_capacity(uint64_t n)
    {
        uint64_t r = 1;
        while (r < n)
        {
            r = r << 1;
        }
        return r;
    }

  public:
    MyVec(uint64_t s = 0, int v = 0)
    {
        v_size = s;
        uint64_t cc = calc_capacity(s);
        v_capacity = (cc < 8 ? 8 : cc);
        array = new int[v_capacity];

        for (uint64_t i = 0; i < s; ++i)
        {
            array[i] = v;
        }
    }

    uint64_t size()
    {
        return v_size;
    }

    uint64_t capacity()
    {
        return v_capacity;
    }

    void info()
    {
        std::cout << "size: " << size() << "\n";
        std::cout << "capacity: " << capacity() << "\n";
        std::cout << "vector elements: ";
        for (int i = 0; i < size(); ++i)
        {
            std::cout << array[i] << " ";
        }
        std::cout << "\n";
    }

    int &at(uint64_t i)
    {
        if (i >= 0 && i < size())
        {
            return array[i];
        }
        throw std::out_of_range("Нема елемент со дадениот индекс");
    }

    int &back()
    {
        if (size() > 0)
        {
            return array[size() - 1];
        }
        throw std::out_of_range("Празна е низата, не постои последен елемент");
    }

    void pop()
    {
        if (size() > 1)
        {
            v_size--;
        }
    }

    void push(int v)
    {
        if (capacity() > size())
        {
            array[v_size] = v;
            ++v_size;
            return;
        }
        uint64_t new_capacity = capacity() << 1;
        int *new_array = new int[new_capacity];

        for (uint64_t i = 0; i < capacity(); ++i)
        {
            new_array[i] = array[i];
        }

        new_array[size()] = v;
        ++v_size;
        v_capacity = new_capacity;
        
        delete[] array;
        array = new_array;
    }
};

int main()
{
    MyVec v;
    MyVec v1(10);
    MyVec v2(8, 6);

    v2.info();

    std::cout << v2.at(6) << "\n";
    v2.at(6) = 5;
    v2.at(6) = 11;
    std::cout << v2.at(6) << "\n";
    v2.pop();
    v2.push(13);
    v2.push(19);
    v2.info();
    
}
