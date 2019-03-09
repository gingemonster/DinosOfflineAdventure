c:\gbdk\bin\lcc -Wa-l -Wf-ba0 -c -o savestate.o savestate.c
c:\gbdk\bin\lcc -Wa-l -c -o main.o main.c
c:\gbdk\bin\lcc -Wl-yt3 -Wl-yo4 -Wl-ya4 -o dinosofflineadventure.gb main.o savestate.o
del *.o
del *.map
del *.lst
del *.sym
del *.sav

REM copy /b ..\..\tools\goombacolor_12_14_2014\goomba.gba+dinosofflineadventure.gb goombadinosofflineadventure.gba
copy dinosofflineadventure.gb .\embedjsplayer\dinosofflineadventure.gb
REM..\..\tools\bgbw64\bgb64 -rom dinosofflineadventure.gb
REM..\..\tools\mGBA-0.6.3-win32\mGBA.exe goombadinosofflineadventure.gba