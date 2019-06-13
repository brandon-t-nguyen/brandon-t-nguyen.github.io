#include <stdio.h>
#include <stdint.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * display memory
 * Prints out a 32-bit value at the provided address
 * Example usage:
 *     dm <address>
 *     dm 0x10000000
 */
int main(int argc, char ** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Provide address: dm <address>\n");
        return 1;
    }

    void * addr = NULL;
    uint32_t val = 0xDEADBEEF;

    sscanf(argv[1], "%p", &addr);

    int fd = open("/dev/mem", O_RDONLY, S_IRUSR);
    if (fd == -1) {
        fprintf(stderr, "Could not open /dev/mem: do you have permissions?\n");
        return 2;
    }
    off_t offset = (off_t) (uintptr_t) addr;
    lseek(fd, offset, SEEK_SET);
    read(fd, &val, sizeof(uint32_t));
    printf("[%p] = 0x%08x\n", addr, val);

    return 0;
}
