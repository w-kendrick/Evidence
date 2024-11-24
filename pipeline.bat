@echo off
setlocal

set UNREAL_EDITOR="C:\Program Files\Epic Games\UE_5.3\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
set PROJECT_FILE="C:\Users\willk\Documents\Unreal Projects\Evidence\Evidence.uproject"

echo ================================================================================================================================================
echo Running tests in perfect network conditions
echo ================================================================================================================================================

%UNREAL_EDITOR% %PROJECT_FILE% -Deterministic -nosplash -Unattended -nopause -nosound -NullRHI -nocontentbrowser -ini:EditorPerProjectUserSettings:[/Script/UnrealEd.LevelEditorPlaySettings]:PlayNetMode=PIE_ListenServer -ExecCmds="Automation RunTests Project.Functional Tests.Tests;quit" -StdOut -LogCmds="Global Warning, LogCheckSubobjects Fatal, LogAutomationController Verbose"

echo ================================================================================================================================================
echo Running tests with 5% packet loss
echo ================================================================================================================================================

%UNREAL_EDITOR% %PROJECT_FILE% -Deterministic -nosplash -Unattended -nopause -nosound -NullRHI -nocontentbrowser -ini:Engine:[PacketSimulationSettings]:PktLoss=5 -ini:EditorPerProjectUserSettings:[/Script/UnrealEd.LevelEditorPlaySettings]:PlayNetMode=PIE_ListenServer -ExecCmds="Automation RunTests Project.Functional Tests.Tests;quit" -StdOut -LogCmds="Global Warning, LogCheckSubobjects Fatal, LogAutomationController Verbose"

echo ================================================================================================================================================
echo Running tests with 100ms packet lag
echo ================================================================================================================================================

%UNREAL_EDITOR% %PROJECT_FILE% -Deterministic -nosplash -Unattended -nopause -nosound -NullRHI -nocontentbrowser -ini:Engine:[PacketSimulationSettings]:PktLag=100 -ini:EditorPerProjectUserSettings:[/Script/UnrealEd.LevelEditorPlaySettings]:PlayNetMode=PIE_ListenServer -ExecCmds="Automation RunTests Project.Functional Tests.Tests;quit" -StdOut -LogCmds="Global Warning, LogCheckSubobjects Fatal, LogAutomationController Verbose"

echo ================================================================================================================================================
echo Running tests with 5% packet loss and 100ms packet lag
echo ================================================================================================================================================

%UNREAL_EDITOR% %PROJECT_FILE% -Deterministic -nosplash -Unattended -nopause -nosound -NullRHI -nocontentbrowser -ini:Engine:[PacketSimulationSettings]:PktLag=100,PktLoss=5 -ini:EditorPerProjectUserSettings:[/Script/UnrealEd.LevelEditorPlaySettings]:PlayNetMode=PIE_ListenServer -ExecCmds="Automation RunTests Project.Functional Tests.Tests;quit" -StdOut -LogCmds="Global Warning, LogCheckSubobjects Fatal, LogAutomationController Verbose"


endlocal
@echo on