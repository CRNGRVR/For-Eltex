#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void moveDataAndErase(char *pathDest, char *pathSrc) {

    int destFd;
    int srcFd;
    char buff;

    //  Если файла не было, будет создан; если был - будет усечён
    destFd = open(pathDest, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);

    //  Если файла не было, будет создан
    srcFd = open(pathSrc, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);

    //  Побайтовая перезапись
    while (0 != read(srcFd, &buff, 1)) {
        write(destFd, &buff, 1);
    }
    close(srcFd);

    //  Усечение
    srcFd = open(pathSrc, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
    close(srcFd);
}
