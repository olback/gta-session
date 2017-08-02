
#ifndef GTATOGGLE2_VAR_H
#define GTATOGGLE2_VAR_H

#ifdef DEFINE_GLOBALS
#define EXTERN
#else
#define EXTERN extern
#endif

/* ------------------ */

#define btnW 120 // Button/Static width
#define btnH 30 // Button/Static height

static const char name[] = "GTAToggle 2.0";
static const char helpURL[] = "start https://github.com/olback/gta-session/blob/master/README.md";
static const int wWidth = 460;                                                                          // Window width.
static const int wHeight = 160;                                                                         // Window  height.
static const int tabInTime = 5;                                                                         // Time before the process begins. AKA the time you have to tab back in to the game.
static const int sleepTime = 10;                                                                        // Time to block ports. Increase if it doesn't work. Decrease if you get kicked from your session.

static const char script1[] = "@ECHO off\n"
        "netsh advfirewall firewall del rule name=GTAToggle\n"
        "netsh advfirewall firewall add rule name=GTAToggle dir=in action=block protocol=TCP localport=80,443\n"
        "netsh advfirewall firewall add rule name=GTAToggle dir=out action=block protocol=TCP localport=80,443\n"
        "netsh advfirewall firewall add rule name=GTAToggle dir=in action=block protocol=UDP localport=6672,61455,61457,61456,61458\n"
        "netsh advfirewall firewall add rule name=GTAToggle dir=out action=block protocol=UDP localport=6672,61455,61457,61456,61458\n"
        "netsh advfirewall firewall set rule name=GTAToggle new enable=yes\n"
        "exit";

static const char script2[] = "@ECHO OFF\n"
        "netsh advfirewall firewall set rule name=\"GTAToggle\" new enable=no\n"
        "netsh advfirewall firewall del rule name=\"GTAToggle\"\n"
        "exit";

HWND hwndExec;

/* ------------------ */

#endif //GTATOGGLE2_VAR_H
