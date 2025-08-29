bin\flex.exe -o src/iec61131.l.cpp src/iec61131.l
bin\bison.exe --defines=src/iec61131.y.hpp -o src/iec61131.y.cpp src/iec61131.y

xcopy "src/location.hh" "include/deci/location.hh" /R /C /F /y