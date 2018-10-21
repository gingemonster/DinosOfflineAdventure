c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o main.c
REM  the wl-g stuff is here so memcopy works no idea what its doing but it works
REM c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-g_inc_ram=0xD000 -Wl-g_inc_hiram=0xFFA0 -o dinosofflineadventure.gb main.o
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o dinosofflineadventure.gb main.o
del *.o
del *.map
del *.lst
del *.sym
del *.sav

copy /b ..\..\tools\goombacolor_12_14_2014\goomba.gba+dinosofflineadventure.gb goombadinosofflineadventure.gba
copy dinosofflineadventure.gb .\embedjsplayer\dinosofflineadventure.gb
REM..\..\tools\bgbw64\bgb64 -rom dinosofflineadventure.gb
REM..\..\tools\mGBA-0.6.3-win32\mGBA.exe goombadinosofflineadventure.gba