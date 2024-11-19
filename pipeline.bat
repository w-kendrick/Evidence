@echo off
setlocal

set UNREAL_EDITOR="C:\Program Files\Epic Games\UE_5.3\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
set PROJECT_FILE="C:\Users\willk\Documents\Unreal Projects\Evidence\Evidence.uproject"

%UNREAL_EDITOR% %PROJECT_FILE% -Deterministic -nosplash -Unattended -nopause -nosound -NullRHI -nocontentbrowser -ini:EditorPerProjectUserSettings:[/Script/UnrealEd.LevelEditorPlaySettings]:PlayNetMode=PIE_Client -ExecCmds="Automation RunTests Project.Functional Tests.Tests.Client;quit" -StdOut -LogCmds="Global Warning, LogCheckSubobjects Fatal, LogAutomationController Verbose"

endlocal
@echo on