#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__


template<typename T, bool ORDERED = false, bool RELATIVE = false, typename T_ORDER = char>
class LinkedList
{
public:
    struct Element
    {
        Element *next, *prev;
        T data;
        T_ORDER rank;
    };
    

    LinkedList() : head(0), tail(0), _size(0) {}
    ~LinkedList() {}

    void insert(T _data, T_ORDER _rank = 0)
    {
        if (_size == 0)
        {
            insert_first(_data, _rank);
        }
        else
        {
            if (ORDERED)
            {
                insert_ordered(_data, _rank);
            }
            else
            {
                insert_tail(_data, _rank);
            }
        }
        _size++;
    }

    T get(int i)
    {
        Element * el = head;
        while(i--)
            el = el->next;
        return el->data;
    }

    T remove_head()
    {
        T aux = head->data;
        Element *old_head = head;
        if (head->next != 0) head->next->prev = head->prev;
        head = head->next;
        delete old_head;
        _size--;
        return aux;
    }

    T_ORDER update_head_rank(T_ORDER upd)
    {
        if (_size == 0) return -1;
        
        if (upd > head->rank)
            head->rank = 0;
        else
            head->rank -= upd;

        return head->rank;
    }

    int size() { return _size; }

private:
    void insert_first(T _data, T_ORDER _rank)
    {
        // db_uart.puts("insert_first\n");

        Element *el = new Element();
        el->data = _data;
        el->rank = _rank;
        el->prev = 0;
        el->next = 0;
        head = el;
        tail = el;
    }

    void insert_ordered(T _data, T_ORDER _rank)
    {
        // db_uart.puts("insert_ordered\n");
        
        Element *nxt = head;
        while((nxt != 0) && (_rank > nxt->rank))
        {
            if (RELATIVE) _rank -= nxt->rank;
            nxt = nxt->next;
        }
        if (nxt == 0)
        {
            insert_tail(_data, _rank);
            return;
        }

        Element *el = new Element();
        el->data = _data;
        el->rank = _rank;

        if(nxt->prev != 0)
        {
            el->prev = nxt->prev;
            el->next = nxt;

            nxt->prev->next = el;
            nxt->prev = el;
        } 
        else
        {
            nxt->prev = el;
            el->prev = 0;

            el->next = nxt;
            head = el;
        }
        if(RELATIVE) nxt->rank -= _rank;
    }

    void insert_tail(T _data, T_ORDER _rank)
    {
        Element *el = new Element();
        el->data = _data;
        el->rank = _rank;
        el->prev = tail;
        el->next = 0;
        tail->next = el;
        tail = el;
    }

    Element *head, *tail;
    int _size;
};


#endif //__LINKEDLIST_H__