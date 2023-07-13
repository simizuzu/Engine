chcp 65001
@echo off

echo バッチ処理を開始します

echo フォルダ生成開始
cd %~dp0lib\External\
md lib
cd %~dp0lib\External\lib\
md debug
echo フォルダ生成終了

echo libファイル生成するためのvcpkg生成開始
call %~dp0lib\External\vcpkg\bootstrap-vcpkg.bat
echo libファイル生成するためのvcpkg生成終了

echo libファイル生成開始
cd %~dp0lib\External\vcpkg

START /wait vcpkg.exe install imgui[core,dx12-binding,win32-binding]:x64-windows-static 
echo imgui終了

START /wait vcpkg.exe install directxtex:x64-windows-static
echo directxTex終了

START /wait vcpkg.exe install assimp:x64-windows-static 
echo assimp終了

START /wait vcpkg.exe install nlohmann-json:x64-windows-static
echo nlohmann-json終了

START /wait vcpkg.exe install directx-headers:x64-windows-static
echo directx-Headers終了

echo libファイル生成終了

echo 生成ファイル移動開始
cd %~dp0lib\External\vcpkg\installed\x64-windows-static\lib
move *.lib %~dp0lib\External\lib
move pkgconfig %~dp0lib\External\lib

cd %~dp0lib\External\vcpkg\installed\x64-windows-static\debug\lib
move *.lib %~dp0lib\External\lib\debug
move pkgconfig %~dp0lib\External\lib\debug

cd %~dp0lib\External\vcpkg\installed\x64-windows-static
move include %~dp0lib\External\
echo 生成ファイル移動終了

echo バッチ処理が終了しました

pause