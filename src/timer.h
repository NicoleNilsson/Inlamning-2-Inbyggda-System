#ifndef __TIMER_H
#define __TIMER_H

class Timer{
public:
    Timer(){
        timerSetup();
    }

    void compASetUp(const uint16_t &compATimeInterval);
    void compBSetUp(const uint16_t &compBTimeInterval);

private:
    void timerSetup(void);
};

#endif //__TIMER_H