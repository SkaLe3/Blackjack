@echo off

echo Bulding project files:
echo SDL2
echo SDL2main
echo Core
echo Blackjack

@echo on
cd ..\Blackjack\
call ..\ThirdParty\premake\premake5.exe vs2022
@echo off

PAUSE
