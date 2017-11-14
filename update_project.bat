@cd %~dp0
@premake5 vs2015

@mkdir bin\x86
@xcopy /Y third_party\sdl2\lib\x86\*.dll bin\x86

@mkdir bin\x64
@xcopy /Y third_party\sdl2\lib\x64\*.dll bin\x64

@pause
