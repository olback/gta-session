/*
 *  Made by Edwin Svensson.
 *  GitHub: github.com/olback
 *  Twitter: @Mrolback
 *  Licenced under Creative Commons v3.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int tabInTime = 5; // Time before the process begins.
int time = 10; // Time before unblocking ports. Change to a higher value if it doesn't work. Change to a lower value if you get kicked.

int main() {

    system("cls"); // Clear command prompt.

    printf("Waiting for %d",tabInTime);
    printf(" seconds. Tab back in to the game.\n\n");
    sleep(tabInTime);

    // Removing all old rules named 'GTAToggle'.
    printf("Removing old firewall rules named 'GTAToggle'.\n");
    system("netsh advfirewall firewall del rule name=\"GTAToggle\" > NUL");

    // Adding rules named 'GTAToggle'.
    printf("Adding firewall rules named 'GTAToggle'\n\n");
    system("netsh advfirewall firewall add rule name=\"GTAToggle\" dir=in action=block protocol=TCP localport=80,443 > NUL");
    system("netsh advfirewall firewall add rule name=\"GTAToggle\" dir=out action=block protocol=TCP localport=80,443 > NUL");
    system("netsh advfirewall firewall add rule name=\"GTAToggle\" dir=in action=block protocol=UDP localport=6672,61455,61457,61456,61458 > NUL");
    system("netsh advfirewall firewall add rule name=\"GTAToggle\" dir=out action=block protocol=UDP localport=6672,61455,61457,61456,61458 > NUL");
    system("netsh advfirewall firewall set rule name=\"GTAToggle\" new enable=no > NUL");

    // Block ports.
    printf("Blocking traffic on these TCP ports: 80,443.\n");
    printf("Blocking traffic on these UDP ports: 6672,61455,61457,61456,61458.\n\n");
    system("netsh advfirewall firewall set rule name=\"GTAToggle\" new enable=yes > NUL");

    // Wait before unblocking ports.
    printf("Waiting for %d",time);
    printf(" seconds.\n\n");
    sleep(time);

    // Unblocking ports.
    printf("Unblocking traffic on these TCP ports: 80,443.\n");
    printf("Unblocking traffic on these UDP ports: 6672,61455,61457,61456,61458.\n");
    system("netsh advfirewall firewall set rule name=\"GTAToggle\" new enable=no > NUL");

    return 0;

}