# Check if homebrew is installed
if [[ $(command -v brew) == "" ]]; then
    echo "Homebrew missing"
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    echo "Homebrew installed"
fi

# Check if gbdk is installed
if [[ $(brew ls --versions mistydemeo/formulae/gbdk) == "" ]]; then
    echo "gbdk missing"
    brew tap mistydemeo/formulae
    brew install --HEAD mistydemeo/formulae/gbdk
    echo "gbdk installed"
fi

lcc -Wa-l -Wf-ba0 -c -o savestate.o savestate.c 2> /dev/null
lcc -Wa-l -c -o main.o main.c 2> /dev/null
lcc -Wl-yt3 -Wl-yo4 -Wl-ya4 -o dinosofflineadventure.gb main.o savestate.o

echo "dinosofflineadventure.gb successfully builded"

open dinosofflineadventure.gb