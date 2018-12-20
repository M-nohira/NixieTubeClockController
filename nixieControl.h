#include <stdio.h>
#include <time.h>
#include <thread>
#include <mutex>


class nixieControl
{
       
    public:
        int pattern[2][8];
        int main();
        void GetDisplayPattern(int order,int tubeNumber,int showNumber);
        void StartUpAnim();
        static void ApplyUpdate();
    private:   
};