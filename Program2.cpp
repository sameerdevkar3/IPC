#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    std::cout << "Program 2 \n";

    char cBuffer[1024] = {0};
    int iFD = 0, iRead = 0;
    std::string Sendbuff;

    while (1)
    {
        iFD = open("/tmp/SenderPipe1", O_RDONLY);
        iRead = read(iFD, cBuffer, 1024);
        close(iFD);
        if (iRead != -1)
            std::cout << "Program 1 : " << cBuffer << "\n";
        memset(cBuffer, 0x00, sizeof(cBuffer));

        std::cout << "Program 2 : ";
        std::cin >> Sendbuff;

        iFD = open("/tmp/SenderPipe2", O_WRONLY);
        write(iFD, Sendbuff.data(), Sendbuff.size());
        close(iFD);
    }
    
    return 0;
}