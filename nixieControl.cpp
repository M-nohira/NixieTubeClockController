#include "nixieControl.h"
#include "displayCTL.cpp"

int nixieControl::main()
{
    std::thread thread_Display(&ApplyUpdate);
    printf("Starting Display Thread...");
    thread_Display.join();
}

///Imcomplete
void nixieControl::GetDisplayPattern(int order, int tubeNumber,int showNumber)
{
    pattern[0][order] = tubeNumber;
    pattern[1][order] = showNumber;
}

void nixieControl::StartUpAnim()
{
    
}

void nixieControl::ApplyUpdate()
{
    
}



/*time_t t_time;
    time(&t_time);
    tm tms;
    tms = *localtime(&t_time);
    printf("%d:%d'%d \r\n",tms.tm_hour,tms.tm_min,tms.tm_sec);*/