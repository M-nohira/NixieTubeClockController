#include "displayCtl.h"


void DisplayCtl::main(int (*pattern[2])[8])
{
    do
    {  
        if(_pattern == *pattern) continue;
        memcpy(_pattern,*pattern,sizeof(*pattern));
        UpdateDisplay(_pattern);
    }while(true);
}

void DisplayCtl::SetNixie(int num,bool isTubeNum)
{
    if(isTubeNum == false)
    {
        switch(num)
        {
            case 0:
                SetArray(0,1,1,0);
            case 1:
                SetArray(1,0,0,1);
            case 2:
                SetArray(1,0,0,0);
            case 3:
                SetArray(0,1,1,1);
            case 4:
                SetArray(0,0,0,0);
            case 5:
                SetArray(0,0,0,1);
            case 6:
                SetArray(0,0,1,0);
            case 7:
                SetArray(0,0,1,1);
            case 8:
                SetArray(0,1,0,0);
            case 9:
                SetArray(0,1,0,1);
            default:
                SetArray(1,1,1,1);
        }
        return;
    }

    switch(num)
    {
        case 0:
            SetArray(1,1,1,1);
        case 1:
            SetArray(0,0,1,1);
        case 2:
            SetArray(0,0,0,1);
        case 3:
            SetArray(0,0,1,0);
        case 4:
            SetArray(0,0,0,0);
        case 5:
            SetArray(0,1,1,1);
        case 6:
            SetArray(0,1,0,1);
        case 7:
            SetArray(0,1,1,0);
        case 8:
            SetArray(0,1,0,0);
        default:
            SetArray(1,1,1,1);
    }        
    return;
}

void DisplayCtl::SetArray(int a,int b,int c,int d)
{
    int ret[4] = {1,1,1,1};//TODO 直接GPIOを制御する予定
    ret[0] = a;
    ret[1] = b;
    ret[2] = c;
    ret[3] = d;

    //return ret;
}

int DisplayCtl::UpdateDisplay(int pattern[2][8])
{
    for(int cnt = 0; cnt < 8;cnt++)
    {
        //表示するニキシー管に通電
        SetNixie(pattern[0][cnt],true);
        //表示する文字をGNDの接続      
        SetNixie(pattern[1][cnt],false);

        //ゴースト現象回避のために調整する必要アリ


        SetNixie(999,true);
        SetNixie(999,false);
    }
}