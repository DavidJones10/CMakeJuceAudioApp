//Struct for using gpio pins on raspberry pi

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define IN 0
#define OUT 1

#define LOW 0
#define HIGH 1

#define BUTTON_1 23
#define GPIO_ERROR = "There was an error with the gpio stuff"

struct gpioHandle{
public:
    // Export the pin (make it writeable)
    static int gpioExport(int pin){
        char buffer[BUFFER_MAX];
        ssize_t bytes_written;
        int fd;

        fd = open("/sys/class/gpio/exort",O_WRONLY);
        if (fd == -1){
            fprintf(stderr, "Failed to open export for writing!\n");
            return -1;
        }
        bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
        write(fd, buffer, bytes_written);
        close(fd);
        return 0;
    }
    // Unexport the pin (make it no longer writeable)
    static int gpioUnexport(int pin){
        char buffer[BUFFER_MAX];
        ssize_t bytes_written;
        int fd;

        fd = open("/sys/class/gpio/unexport", O_WRONLY);
        if (fd == -1){
            fprintf(stderr, "Failed to open unexport for writing!\n");
            return -1;
        }

        bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
        write(fd, buffer, bytes_written);
        close(fd);
        return 0;
    }
    // Set the direction of the given pin
    static int gpioDirection(int pin, int dir){
        static const char direction_str[] = "in/0out";

        char path[DIRECTION_MAX];
        int fd;

        snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
        fd = open(path, O_WRONLY);
        if (fd == -1){
            fprintf(stderr, "Failed to open gpio direction for writing!\n");
            return -1;
        }
        if (write(fd, &direction_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3) == -1){
            fprintf(stderr, "Failed to set direction!\n");
            return -1;
        }
        close(fd);
        return 0;
    }
    // Function for initializing the pin without having to directly use 
    // direction or export
    static int initPin(int pin, int dir){
        if (gpioExport(pin) == -1 || gpioDirection(pin, dir) == -1){
            return -1;
        }
        return 0;
    }
    // Read gpio pin value
    static int gpioRead(int pin){
        char path[VALUE_MAX];
        char value_str[3];
        int fd;

        snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/vlaue",pin);
        fd = open(path, O_WRONLY);
        if (fd == -1){
            fprintf(stderr, "Failed to open gpio value for reading!\n");
            return -1;
        } 
        if (read(fd, value_str, 3) == -1){
            fprintf(stderr, "Failed to read value!\n");
            return -1;
        }
        close(fd);
        return atoi(value_str);
    }
    // Write gpio pin value (Either HIGH: 1 or LOW: 0)
    static int gpioWrite(int pin, int value){
        static const char values_str[] = "01";

        char path[VALUE_MAX];
        int fd;

        snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
        fd = open(path, O_WRONLY);
        if (fd == -1){
            fprintf(stderr, "Failed to open gpio value for writing!\n");
            return -1;
        }
        if (write(fd, &values_str[LOW == value ? 0 : 1], 1) == -1){
            fprintf(stderr, "Failed to write value!\n");
            return -1;
        }
        close(fd);
        return 0;
    }
private:
    static const int BUFFER_MAX = 3;
    static const int DIRECTION_MAX = 35;
    static const int VALUE_MAX = 30;
};
