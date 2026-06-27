#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include "communicator.h"

void configurePort(int fd) {
    struct termios tty;

    // Get the current configuration of the serial port
    if (tcgetattr(fd, &tty) != 0) {
        perror("Error from tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Set the baud rate for both input and output
    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);

    // Configure the serial port
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8 data bits
    tty.c_iflag &= ~IGNBRK; // Ignore break condition
    tty.c_lflag = 0;          // No local modes
    tty.c_oflag = 0;          // No output processing
    tty.c_cc[VMIN] = 1;     // Read at least 1 character
    tty.c_cc[VTIME] = 0;    // No timeout

    tty.c_cflag |= (CLOCAL | CREAD);    // Enable receiver and set local mode
    tty.c_cflag &= ~(PARENB | PARODD);  // Disable parity
    tty.c_cflag &= ~CSTOPB;             // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;            // No hardware flow control

    // Apply the configuration
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error from tcsetattr");
        exit(EXIT_FAILURE);
    }
}

std::string getComp() {
    const char* portName = "/dev/ttyACM0";
    char buffer[255];
    int fd;

    // Open the serial port
    fd = open(portName, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        return "Error opening port";
    }

    // Configure the port
    configurePort(fd);

    // Clear any data in the input buffer
    if (tcflush(fd, TCIFLUSH) != 0) {
        close(fd);
        return "Error flushing input buffer";
    }

    // std::cout << "Listening on " << portName << " at 115200 baud...\n";
    std::string res = "";
    do {
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer

        // Read data from the serial port
        int bytesRead = read(fd, buffer, sizeof(buffer) - 1); // Fixed `sizeof(0)` to `sizeof(buffer)`
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; // Null-terminate the string
            for (int i = 0; i < bytesRead; i++) {
                if (buffer[i] == '\n') {
                    close(fd); // Close the serial port
                    return res;
                }
                else res += buffer[i];
            }
        } else if (bytesRead < 0) {
            std::cout << "Error reading from serial port";
            break;
        }
    } while (true);

    std::cout << "closed file";
    close(fd); // Close the serial port
    return "zero";
}

