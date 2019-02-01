#include "nixieControl.h"
#include "displayCTL.cpp"

int nixieControl::main()
{
    //std::thread thread_Display(&ApplyUpdate);
    std::thread thread_Display(&DisplayCtl::main,this,*pattern,&m);
    printf("Starting Display Thread...");
    thread_Display.join();
}

///Imcomplete
void nixieControl::GetDisplayPattern(int order, int tubeNumber,int showNumber)
{
    int base[2][8];
    base[0][order] = tubeNumber;
    base[1][order] = showNumber;
    // ....

    
    //
    pthread_mutex_lock(&m);
    memcpy(pattern,base,sizeof(base));
    pthread_mutex_unlock(&m);
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