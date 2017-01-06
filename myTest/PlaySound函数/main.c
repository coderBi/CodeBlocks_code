#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    printf("Hello world!\n");
    PlaySound("Windows Logon Sound.wav",NULL,SND_FILENAME|SND_SYNC);
    //MessageBeep(3);
    return 0;
}
