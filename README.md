# Linux System Programming - Week 1
A collection of simple C command-line tools with basic error handling and help flags.

## Greeting tool
Compile:
`gcc hello.c -o hello`

Usage:
`./hello`
`./hello [NAME]`
`./hello --help`

## Date tool
Compile:
`gcc -std=c11 -Wall -Wextra date.c -o date_tool`

Usage:
`./date_tool`
`./date_tool Asia/Tokyo`
`./date_tool America/New_York`
`./date_tool --help`

With no time-zone argument, the tool displays the system's local date and time. To display another place's time, provide its IANA time-zone name, as listed in the system's zoneinfo database (usually under `/usr/share/zoneinfo`). The output includes the date, time, time-zone abbreviation, and UTC offset.