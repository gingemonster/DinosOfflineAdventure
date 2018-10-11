c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o main.c
REM  the wl-g stuff is here so memcopy works no idea what its doing but it works
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-g_inc_ram=0xD000 -Wl-g_inc_hiram=0xFFA0 -o chromedino.gb main.o
del *.o
del *.map
del *.lst
del *.sym
REM..\..\tools\bgbw64\bgb64 -rom chromedino.gb