#ifndef __FIFO_H__
#define __FIFO_H__
 
template <typename T, int N>
class FIFO
{
public:
   enum FIFO_Erros_t 
   {
       FIFO_ERROR_FULL = -2,
       FIFO_ERROR_EMPTY = -1,
       FIFO_SUCCESS = 0
   };
   FIFO()
   {
       clear();
   }
   ~FIFO(){}
   FIFO_Erros_t enqueue(T data)
   {
       if (size() >= capacity())
       { 
           return FIFO_ERROR_FULL;
       }
       buffer[tail] = data;
       tail = (tail + 1) % N; 
       count++;
 
       return FIFO_SUCCESS;
   }
   FIFO_Erros_t dequeue(T *data) 
   {
       if (size() == 0)
       { 
           return FIFO_ERROR_EMPTY;
       }
       * data = buffer[head];
       head = (head + 1) % N;
       count--;
       return FIFO_SUCCESS;
   }
   void clear()
   {
       count = 0;
       head = 0;
       tail = 0;
   }
   unsigned int size() { return count; }
   const unsigned int capacity() { return N; }
 
private:
   T buffer[N];
   int head, tail, count;
};
 
#endif
