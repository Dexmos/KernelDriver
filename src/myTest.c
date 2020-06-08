#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char str[150];
    char *str2 = strdup("Hello word!");
    int fp = open("/dev/Epitech_driver", O_RDWR);
    int w = write(fp, str2, strlen(str2));
    int result = read(fp, &str, 150);

    printf("(%i)\n", w);
    printf("[%i]\n", result);
    printf("{%s}\n", str);
    return 0;
}
