Windows has always offered support to help developers localize their applications. An application can get country-specific information from various functions.

*****The basics of characters - ASCII, MBCS/DBCS, Unicode*****

SBCS(Single Byte Character Set): All characters are one byte long. A single zero byte marks end of sbcs string.
e.g. ASCII

Q) How they are stored in memory. example the name "Bob"

42  6F  62  00 

B   o   b   EOS


MBCS(Multi Byte Character Set) or DBCS(Double Byte Character Set): Some characters are one byte long and some are more than one byte long. Supports Japanese kanji which require multi-byte.
A single zero byte is marked as an end of string.
e.g. UTF-8

Q) How they are stored in memory. example the name "nihongo"
93 FA  96 7B  8C EA  00 

LB TB  LB TB  LB TB  EOS

LB-> Leading byte TB-> Trailing Byte


Unicode or Wide Character: All characters are two byte long. Terminated by two zero byte.
e.g. UTF-16

Q) How they are stored in memory. example the name "Bob"
42 00  6F 00  62 00  00 00 

B       o      b      EOS

Note: While using Microsoft Visual Studio, Right Click project properties -> Configuration Properties - General
Character Set -> Use Multi Byte Chracter Set

While the above setting is used, and we define char x[] = "Hello" (6 byte)is taken as a MBCS type. Else this string would be taken as a unicode.

A unicode string is defined as wchar_t x[] = "Hello".
If we wanted to represent an ASCII charater in unicode format we can use the prefix "L". char x[] = L"Hello" (12 byte, 6 wide character).

Sometimes it becomes difficult to monitor if its unicode or mbcs.
Hence we could make use of below method

#ifdef UNICODE
typedef wchar_t TCHAR; //wchar_t is a wide character
#else
typedef char TCHAR;
#endif

Since Windows NT, all Windows versions are built from the ground up using Unicode. That is, all the core
functions for creating windows, displaying text, performing string manipulations, and so forth require
Unicode strings. If you call any Windows function passing it an ANSI string (a string of 1-byte characters),
the function first converts the string to Unicode and then passes the Unicode string to the operating
system. If you are expecting ANSI strings back from a function, the system converts the Unicode string to
an ANSI string before returning to your application. All these conversions occur invisibly to you.


Translating Strings Between Unicode and ANSI

int MultiByteToWideChar(
UINT uCodePage,
DWORD dwFlags,
PCSTR pMultiByteStr,
int cbMultiByte,
PWSTR pWideCharStr,
int cchWideChar);

int WideCharToMultiByte(
UINT uCodePage,
DWORD dwFlags,
PCWSTR pWideCharStr,
int cchWideChar,
PSTR pMultiByteStr,
int cbMultiByte,
PCSTR pDefaultChar,
PBOOL pfUsedDefaultChar);

*Attached a code file that demonstrates the usage of above function.

Use string safe handling functions.
It is highly recommend that your application always use Unicode strings.
