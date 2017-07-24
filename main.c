/*
 *  Made by Edwin Svensson.
 *  GitHub: github.com/olback
 *  Twitter: @Mrolback
 *  Licenced under GNU Lesser General Public License v3.0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mem.h>
#include <windows.h>

static const char cversion[] = "1.7dev\n";                                      // Current version.
static const char downlURL[] = "github.com/olback/gta-session/releases\n\n";    // Link to the latest release.
static const int tabInTime = 5;                                                 // Time before the process begins. AKA the time you have to tab back in to the game.
static const int time = 10;                                                     // Time to block ports. Increase if it doesn't work. Decrease if you get kicked from your session.

int main() {

    // Set window title.
    SetConsoleTitle("GTAToggle");

    /* Check for updates */
    /* A nicer way to check for updates wouldn't hurt... */
    printf("Checking for updates...\n");
    system("powershell -C \"curl https://raw.githubusercontent.com/olback/gta-session/master/VERSION -OutFile latest-version\"");
    static const char filenameLV[] = "latest-version";
    FILE *latest_version = fopen(filenameLV, "r");
    if (latest_version != NULL) {
        char line[256]; /* or other suitable maximum line size */
        while (fgets(line, sizeof line, latest_version) != NULL) { /* read a line */
            if (strcmp(line, cversion) == 0) {

                // Close file.
                fclose(latest_version);

                // Remove latest-version.
                int del_lv = remove("latest-version");
                if (del_lv != 0) {
                    printf("Error removing latest-version.");
                }
                printf("Already using latest version.\n\n");

            } else {

                // Close file.
                fclose(latest_version);

                // Remove latest-version.
                int del_lv = remove("latest-version");
                if (del_lv != 0) {
                    printf("Error removing latest-version.");
                }

                printf("New version available.\n");
                printf("Download the latest version from %s", downlURL);

            }

            break;
        }

    } else {

        printf("Error checking for updates. :(\n");
    }

    /* Wait X amount of seconds for the user to tab back in to GTA */
    printf("Waiting for %d seconds. Tab back in to the game.\n\n", tabInTime);
    sleep(tabInTime);

    /* Removing all old rules named 'GTAToggle'. */
    printf("Removing old firewall rules named 'GTAToggle'.\n");
    system("netsh advfirewall firewall del rule name=\"GTAToggle\" > NUL"); // Point output to NUL to suppress output from the command.

    /* Adding rules named 'GTAToggle'. */
    printf("Adding firewall rules named 'GTAToggle'.\n\n");
    system("netsh advfirewall firewall add rule name=\"GTAToggle\" dir=in action=block protocol=TCP localport=80,443 > NUL");
    system("netsh advfirewall firewall add rule name=\"GTAToggle\" dir=out action=block protocol=TCP localport=80,443 > NUL");
    system("netsh advfirewall firewall add rule name=\"GTAToggle\" dir=in action=block protocol=UDP localport=6672,61455,61457,61456,61458 > NUL");
    system("netsh advfirewall firewall add rule name=\"GTAToggle\" dir=out action=block protocol=UDP localport=6672,61455,61457,61456,61458 > NUL");
    system("netsh advfirewall firewall set rule name=\"GTAToggle\" new enable=no > NUL");

    /* Block ports. */
    printf("Blocking network traffic on these TCP ports: 80,443.\n");
    printf("Blocking network traffic on these UDP ports: 6672,61455,61457,61456,61458.\n\n");
    system("netsh advfirewall firewall set rule name=\"GTAToggle\" new enable=yes > NUL");

    /* Wait before unblocking ports. */
    printf("Waiting for %d", time);
    printf(" seconds.\n\n");
    sleep(time);

    /* Unblocking ports. */
    printf("Unblocking network traffic on these TCP ports: 80,443.\n");
    printf("Unblocking network traffic on these UDP ports: 6672,61455,61457,61456,61458.\n\n");
    system("netsh advfirewall firewall set rule name=\"GTAToggle\" new enable=no > NUL");

    /* Clean up. */
    printf("Cleaning up.\n");
    system("netsh advfirewall firewall del rule name=\"GTAToggle\" > NUL");

    sleep(2);

    return 0;
}