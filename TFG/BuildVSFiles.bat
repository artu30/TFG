rmdir /s/q Binaries
del TFG.sln
"C:\Program Files\Epic Games\UE_4.19\Engine\Binaries\DotNET\UnrealBuildTool.exe" -projectfiles -project="%cd%\TFG.uproject" -game -rocket -progress