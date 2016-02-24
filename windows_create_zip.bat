@echo off
set TEMPDIR=HW7Submit

rem Delete stuff...
del /q %TEMPDIR%.zip
rmdir /s /q Debug
rmdir /s /q Release
del /q /A:H *.suo
del /q *.sdf
del /q *.user

rem Make directories...
mkdir %TEMPDIR%\%TEMPDIR%
mkdir %TEMPDIR%\%TEMPDIR%\StanfordCPPLib
mkdir %TEMPDIR%\%TEMPDIR%\Mac.xcodeproj

rem Copy...
xcopy * %TEMPDIR%\%TEMPDIR%
xcopy /s StanfordCPPLib %TEMPDIR%\%TEMPDIR%\StanfordCPPLib
xcopy /s Mac.xcodeproj %TEMPDIR%\%TEMPDIR%\Mac.xcodeproj

rem Make the zip
echo Set objArgs = WScript.Arguments > _zipIt.vbs
echo InputFolder = objArgs(0) >> _zipIt.vbs
echo ZipFile = objArgs(1) >> _zipIt.vbs
echo set fso = CreateObject("Scripting.FileSystemObject") >> _zipIt.vbs
echo fso.CreateTextFile(ZipFile, True).Write "PK" ^& Chr(5) ^& Chr(6) ^& String(18, vbNullChar) >> _zipIt.vbs
echo dim curDir >> _zipIt.vbs
echo curDir = fso.GetAbsolutePathName(".") >> _zipIt.vbs
echo Set objShell = CreateObject("Shell.Application") >> _zipIt.vbs
echo Set source = objShell.NameSpace(curDir ^& "\" ^& InputFolder).Items  >> _zipIt.vbs
echo objShell.NameSpace(curDir  ^& "\" ^& ZipFile).CopyHere(source)  >> _zipIt.vbs
echo wScript.Sleep 15000 >> _zipIt.vbs

CScript  _zipIt.vbs  %TEMPDIR%  %TEMPDIR%.zip

rmdir /s /q %TEMPDIR%
del /q *.vbs
