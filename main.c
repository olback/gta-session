/*
 *  Made by Edwin Svensson.
 *  GitHub: github.com/olback
 *  Twitter: @Mrolback
 *  Licenced under GNU Lesser General Public License v3.0.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mem.h>

char cversion[] = "1.3\n";
char downlURL[] = "github.com/olback/gta-session/releases";
int tabInTime = 5; // Time before the process begins.
int time = 10; // Time before unblocking ports. Change to a higher value if it doesn't work. Change to a lower value if you get kicked.

int main() {

    printf("Checking for updates...\n");
    system("powershell -C \"curl https://raw.githubusercontent.com/olback/gta-session/master/VERSION -OutFile latest-version.txt\"");
    sleep(1);
    int lineNumber = 0;

    static const char filename[] = "latest-version.txt";
    FILE *file = fopen(filename, "r");
    int count = 0;
    if ( file != NULL )
    {
        char line[256]; /* or other suitable maximum line size */
        while (fgets(line, sizeof line, file) != NULL) /* read a line */
        {
            if (count == lineNumber)
            {
                //use line or in a function return it
                //in case of a return first close the file with "fclose(file);"

                if (strcmp(line,cversion) == 0) {
                    printf("Already using latest version.\n");
                } else {
                    printf("Current version: %s",cversion);
                    printf("New version: %s",line);
                    printf("Download the latest version from %s", downlURL);
                }

                break;
            }
            else
            {
                count++;
            }
        }
        fclose(file);
        system("del latest-version.txt");
    }
    else
    {
        printf("Error checking for updates. :(\n");
    }

    printf("Waiting for %d",tabInTime);
    printf(" seconds. Tab back in to the game.\n\n");
    sleep(tabInTime);

    // Removing all old rules named 'GTAToggle'.
    printf("Removing old firewall rules named 'GTAToggle'.\n");
    system("netsh advfirewall firewall del rule name=\"GTAToggle\" > NUL"); // Point output to NUL to suppress output from the command.

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
    printf("Unblocking traffic on these UDP ports: 6672,61455,61457,61456,61458.\n\n");
    system("netsh advfirewall firewall set rule name=\"GTAToggle\" new enable=no > NUL");

    // Clean up.
    printf("Cleaning up.\n");
    system("netsh advfirewall firewall del rule name=\"GTAToggle\" > NUL");

    sleep(2);

    return 0;

}