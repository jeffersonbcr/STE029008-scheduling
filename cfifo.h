#ifndef __CFIFO_H__
#define __CFIFO_H__

template <typename T, int N>
class CircularFifo
{
public:
    CircularFifo()
    {
        head = 0;
        for (int i = 0; i < N; i++)
        {
            buffer[i] = 0;
        }
        head = N - 1;
    }

    ~CircularFifo()
    {
    }

    void enqueue(T data)
    {
        head = (head+1) % N;
        buffer[head] = data;
    }
    T get(int pos)
    {
       return buffer[pos];
    }


    T getLast()
    {
        return buffer[head];
    }

private:
    T buffer[N];
    int head;
};

#endif