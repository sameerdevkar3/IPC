#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    std::cout << "Program 1 \n";
    int iRes1 = 0,iRes2 = 0, iFD = 0,iRead = 0;
    std::string sBuffer;
    char cBuffer[1024] = {0};

    iRes1 = mkfifo("/tmp/SenderPipe1", 0777);
    iRes2 = mkfifo("/tmp/SenderPipe2", 0777);

    if (iRes1 == -1 && iRes2 == -1)
    {
        std::cout << "Sender Pipe can't Create \n";
        std::cout << strerror(errno) << "\n";
        return 0;
    }

    while (1)
    {
        iFD = open("/tmp/SenderPipe1", O_WRONLY);
        std::cout << "Program 1 : ";
        std::cin >> sBuffer;

        write(iFD, sBuffer.data(), sBuffer.size());
        close(iFD);
        
        iFD = open("/tmp/SenderPipe2", O_RDONLY);
        iRead = read(iFD,cBuffer,1024);
        close(iFD);
        if(iRead != -1)
            std::cout << "Program 2 : " << cBuffer << "\n";
        memset(cBuffer,0x00,sizeof(cBuffer));
    }

    return 0;
}