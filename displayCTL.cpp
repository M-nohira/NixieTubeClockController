#include "displayCtl.h"
#include "lib/wiringpi/wiringPi.h"

#define NIXIE_ON_TIME   600
#define NIXIE_OFF_TIME  400

void DisplayCtl::main(int (*pattern[2])[8],pthread_mutex_t *m)
{
    //GPIO設定関数
    wiringPiSetupGpio();
    pinMode(12,OUTPUT);
    pinMode(16,OUTPUT);
    pinMode(20,OUTPUT);
    pinMode(21,OUTPUT);
    pinMode(23,OUTPUT);
    pinMode(24,OUTPUT);
    pinMode(25,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(17,OUTPUT);
    pinMode(27,OUTPUT);

    //表示用ループ
    do
    {  
        if(0 != pthread_mutex_trylock(m)) //アクセス権限が得られなかった場合はコピーを用いて表示
        {
            UpdateDisplay(_pattern);
            return;
        }

        if(_pattern == *pattern) continue;
        memcpy(_pattern,*pattern,sizeof(*pattern));
        UpdateDisplay(_pattern);

        pthread_mutex_unlock(m);
    }while(true);
}

void DisplayCtl::SetNixie(int num,bool isTube)
{
    if(isTube == false)
    {
        switch(num)
        {
            case 0:
                SetTube(0,1,1,0);
            case 1:
                SetTube(1,0,0,1);
            case 2:
                SetTube(1,0,0,0);
            case 3:
                SetTube(0,1,1,1);
            case 4:
                SetTube(0,0,0,0);
            case 5:
                SetTube(0,0,0,1);
            case 6:
                SetTube(0,0,1,0);
            case 7:
                SetTube(0,0,1,1);
            case 8:
                SetTube(0,1,0,0);
            case 9:
                SetTube(0,1,0,1);
            default:
                SetTube(1,1,1,1);
        }
        return;
    }

    switch(num)
    {
        case 0:
            SetNum(1,1,1,1);
        case 1:
            SetNum(0,0,1,1);
        case 2:
            SetNum(0,0,0,1);
        case 3:
            SetNum(0,0,1,0);
        case 4:
            SetNum(0,0,0,0);
        case 5:
            SetNum(0,1,1,1);
        case 6:
            SetNum(0,1,0,1);
        case 7:
            SetNum(0,1,1,0);
        case 8:
            SetNum(0,1,0,0);
        default:
            SetNum(1,1,1,1);
    }        
    return;
}

void DisplayCtl::SetTube(int bcd1,int bcd2,int bcd3,int bcd4)
{
    digitalWrite(12,bcd1);
    digitalWrite(16,bcd2);
    digitalWrite(20,bcd3);
    digitalWrite(21,bcd4);
}

int SetNum(int bcd1,int bcd2,int bcd3,int bcd4)
{
    digitalWrite(23,bcd1);
    digitalWrite(24,bcd2);
    digitalWrite(25,bcd3);
    digitalWrite(8,bcd4);
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
        delayMicroseconds(NIXIE_ON_TIME);//ON　時間

        //表示を例外を用いて消す
        SetNixie(999,true);
        SetNixie(999,false);

        delayMicroseconds(NIXIE_OFF_TIME); //OFF 時間
    }
}