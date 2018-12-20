#include <mutex>
#include <string.h>

class DisplayCtl
{
    public:
    void main(int (*pattern[2])[8]);
    int UpdateDisplay(int pattern[2][8]);
    void SetNixie(int num,bool isTubeNum);

    void SetArray(int a,int b,int c,int d);
    private:
    int _pattern[2][8];
};