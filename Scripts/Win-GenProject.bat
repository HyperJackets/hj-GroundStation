@echo off

pushd ..\

call ThirdParty\premake\premake5.exe vs2022

popd

pause