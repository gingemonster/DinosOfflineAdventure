c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o chromedino.gb main.o
del *.o
del *.map
del *.lst
del *.sym
REM..\..\tools\bgbw64\bgb64 -rom chromedino.gb