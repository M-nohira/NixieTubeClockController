#include <mutex>
#include <string.h>

class DisplayCtl
{
    public:
    void main(int (*pattern[2])[8] ,pthread_mutex_t *m);
    int UpdateDisplay(int pattern[2][8]);
    void SetNixie(int num,bool isTubeNum);

    void SetTube(int bcd1,int bcd2,int bcd3,int bcd4);
    void SetNum(int bcd1,int bcd2,int bcd3,int bcd4);

    private:
    int _pattern[2][8];
};