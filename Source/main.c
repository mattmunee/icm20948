#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

/* main.c */
int main(int argc, char *argv[]) {
    printf("Hello\n");

    int file;
    int adapter_nr = 0; /* probably dynamically determined */
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0) {
        /* ERROR HANDLING; you can check errno to see what went wrong */
        printf("Error Opening I2C Interface\n");
        return(1);
    }

    return 0;
}
