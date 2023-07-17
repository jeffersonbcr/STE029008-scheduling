#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Observer
{
public:
    //Observer();
    virtual ~Observer() {}

    virtual void update(int val){}
};

#endif // __OBSERVER_H__