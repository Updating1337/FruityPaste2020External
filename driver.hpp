#pragma once

#include <winternl.h>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sstream>
#include <locale>
#include <cstdint>
#include <string>

#include <iostream>
#include <sys/types.h>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <TlHelp32.h>

#include "encryption.hpp"
#include "skCrypt.h"

#define secret_t 19782

#define STR_BUFFER_SIZE 64
#define WSTR_BUFFER_SIZE 1024

enum control
{
    read = 111,
    write = 122,
    peb = 133,
    base = 144,
    process_base = 155,
};

struct cmd_t
{
    control code;
    DWORD process_id;
    DWORD key;
    PVOID outbase;
    wchar_t* module_name;

    /*
    * READ/WRITE PROCESS MEMORY.
    */

    PVOID address;
    PVOID value;
    size_t size;

    /* operation success */
    bool success;
};

//class function_t
//{
//private:
//    int64_t(__fastcall* call_driver)(PVOID a1, PVOID a2, PVOID a3, PVOID a4, PVOID a5, PVOID a6);
//public:
//    bool setup()
//    {
//        HMODULE user32 = LoadLibraryA(_("user32.dll").c_str());
//        HMODULE win32u = LoadLibraryA(_("win32u.dll").c_str());
//
//        *(PVOID*)&call_driver = GetProcAddress(win32u, _("NtUserCreateDesktopEx").c_str());
//
//        return call_driver;
//    }
//
//    void call(cmd_t* cmd)
//    {
//        call_driver(cmd, 0, 0, 0, 0, 0);
//    }
//} function;



class Memory
{
public:

    HANDLE handle;
private:

#define call_hook(a) static_cast<uint64_t(_stdcall*)(PVOID)>(hooked_func)(a);


    DWORD process_idd = NULL;
    const char* window_class_name = "";
    const char* window_name = "";

    typedef struct LIGHT_MEMORY
    {
        void* buffer_address;
        UINT_PTR address;
        ULONGLONG size;
        ULONG pid;
        BOOLEAN write;
        BOOLEAN read;
        BOOLEAN req_base;
        BOOLEAN draw_box;
        BOOLEAN draw_line;
        int		r, g, b, x, y, w, h, t;
        void* output;
        const char* module_name;
        ULONG64 base_address;
    }LIGHT_MEMORY;

    void* hooked_func = nullptr;

    int GetPID(const char* process_name)
    {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);


        if (!Process32First(snapshot, &entry) == TRUE)
        {
            return 0;
        }


        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (strcmp(entry.szExeFile, process_name) == 0)
            {
                return (int)entry.th32ProcessID;
            }
        }


        return 0;
    }


public:

    int process_id;

    void set_pid(const char* class_name, const char* _window_name)
    {
        GetWindowThreadProcessId(FindWindowA(class_name, _window_name), &process_idd);

        window_class_name = class_name;
        window_name = _window_name;
    }

    DWORD get_pid()
    {
        return process_idd;
    }

    bool is_driver_mapped()
    {
        cmd_t cmd{};
        cmd.key = secret_t;
        cmd.code = control::base;
        cmd.process_id = GetCurrentProcessId();

        cmd.module_name = const_cast<wchar_t*>(L"win32u.dll");

        //function.call(&cmd);

        return cmd.outbase;
    }


    bool Attach(const char* proc_name)
    {
        hooked_func = GetProcAddress(LoadLibraryA(skCrypt("win32u.dll")), skCrypt("NtGdiDdDDISignalSynchronizationObject")); 
        if (!hooked_func)return 0;

        this->process_id = GetPID(proc_name);


        if (this->process_id == 0)
        {
            return false;
        }


        HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, this->process_id);

        if (handle == INVALID_HANDLE_VALUE)
        {
            return false;
        }


        this->handle = handle;

        return true;
    }

    bool Detach()
    {
        CloseHandle(this->handle);
        this->handle = INVALID_HANDLE_VALUE;
        return true;
    }

    template <typename T>
    T read_chain(std::uint64_t address, std::vector<std::uint64_t> chain)
    {
        uint64_t cur_read = address;

        for (size_t r = 0; r < chain.size() - 1; ++r)
            cur_read = this->Read<std::uint64_t>(cur_read + chain[r]);

        return this->Read<T>(cur_read + chain[chain.size() - 1]);
    }

    template<typename Type>
    Type ReadChain(uint64_t address, std::vector<uint64_t> chain)
    {
        uint64_t current = address;
        for (int i = 0; i < chain.size() - 1; i++)
        {
            current = this->Read<uint64_t>(current + chain[i]);
        }
        return this->Read<Type>(current + chain[chain.size() - 1]);
    }


    uintptr_t ReadChain2(uintptr_t base, const std::vector<uintptr_t>& offsets) {
        uintptr_t result = this->Read<uintptr_t>(base + offsets.at(0));
        for (int i = 1; i < offsets.size(); i++) {
            result = this->Read<uintptr_t>(result + offsets.at(i));
        }
        return result;
    }

    bool read2(UINT_PTR address, void* buffer, SIZE_T size)
    {

        LIGHT_MEMORY instructions;
        instructions.read = TRUE;
        instructions.write = FALSE;
        instructions.req_base = FALSE;

        instructions.pid = process_id;
        instructions.size = size;
        instructions.address = address;
        instructions.draw_box = FALSE;
        instructions.draw_line = FALSE;
        instructions.output = buffer;

        call_hook(&instructions);


        return true;

    }

    std::string read_string(UINT_PTR String_address, SIZE_T size, bool esp_driver = false)
    {
        std::unique_ptr<char[]> buffer(new char[size]);
        read2(String_address, buffer.get(), size);
        return std::string(buffer.get());
    }

    std::wstring read_wstring(UINT_PTR String_address, SIZE_T size, bool esp_driver = false)
    {
        const auto buffer = std::make_unique<wchar_t[]>(size);
        read2(String_address, buffer.get(), size * 2);
        return std::wstring(buffer.get());
    }

    std::wstring read_wstr(uintptr_t address)
    {
        wchar_t buffer[1024 * sizeof(wchar_t)];
        read2(address, &buffer, 1024 * sizeof(wchar_t));
        return std::wstring(buffer);
    }

    const char* read_str(uintptr_t address, int size = 64)
    {
        std::unique_ptr<char[]> buffer(new char[size]);
        read2(address, buffer.get(), size);
        return buffer.get();
    }

    bool write(uint64_t address, LPVOID buffer, size_t size)
    {
        LIGHT_MEMORY instructions;
        instructions.read = FALSE;
        instructions.write = TRUE;
        instructions.req_base = FALSE;

        instructions.pid = process_id;
        instructions.size = size;
        instructions.address = address;
        instructions.buffer_address = buffer;
        instructions.draw_box = FALSE;
        instructions.draw_line = FALSE;
        call_hook(&instructions);

        return true;
    }

    template<typename type>
    bool Write(uint64_t address, type to_write)
    {
        type buffer = to_write;
        return this->write(address, &buffer, sizeof(buffer));
    }

    bool Read(UINT_PTR address, void* buffer, SIZE_T size)
    {

        LIGHT_MEMORY instructions;
        instructions.read = TRUE;
        instructions.write = FALSE;
        instructions.req_base = FALSE;

        instructions.pid = process_id;
        instructions.size = size;
        instructions.address = address;
        instructions.draw_box = FALSE;
        instructions.draw_line = FALSE;
        instructions.output = buffer;

        call_hook(&instructions);


        return true;

    }


    template<class T>
    T Read(UINT_PTR address, bool secondary = false)
    {
        T buffer;
        this->Read(address, &buffer, sizeof(buffer));


        return buffer;
    }


    std::string ReadASCII(uint64_t address)
    {

        char buffer[1024];


        this->Read(address, &buffer, 1024);


        return std::string(buffer);
    }




    std::string ReadMonoString(uint64_t address)
    {

        char buffer[512];


        address = this->Read<uint64_t>(address);


        this->Read(address, buffer, 512);


        return buffer;
    }


    std::wstring ReadUnicode(uint64_t address)
    {

        wchar_t buffer[1024 * sizeof(wchar_t)];


        this->Read(address, &buffer, 1024 * sizeof(wchar_t));


        return std::wstring(buffer);
    }


    std::string ReadNative(uint64_t address)
    {

        char buffer[1024];


        this->Read(this->Read<uint64_t>(address), &buffer, 1024);


        return std::string(buffer);
    }



    uint64_t GetModuleBase(const char* module_name)
    {
        LIGHT_MEMORY instructions;
        instructions.read = FALSE;
        instructions.write = FALSE;
        instructions.req_base = TRUE;

        instructions.pid = process_id;
        instructions.module_name = module_name;
        instructions.draw_box = FALSE;
        instructions.draw_line = FALSE;
        call_hook(&instructions);

        return instructions.base_address;
    }

    bool draw_box(int x, int y, int w, int h, int r, int g, int b, int t) {

        LIGHT_MEMORY instructions;
        instructions.write = FALSE;
        instructions.read = FALSE;
        instructions.req_base = FALSE;
        instructions.draw_line = FALSE;
        instructions.draw_box = TRUE;


        instructions.x = x;
        instructions.y = y;
        instructions.w = w;
        instructions.h = h;


        instructions.t = t;


        instructions.r = r;
        instructions.g = g;
        instructions.b = b;

        call_hook(&instructions);

        return true;

    }

    bool draw_line(int x, int y, int w, int h, int r, int g, int b, int t) {

        LIGHT_MEMORY instructions;
        instructions.write = FALSE;
        instructions.read = FALSE;
        instructions.req_base = FALSE;
        instructions.draw_box = FALSE;
        instructions.draw_line = TRUE;


        instructions.x = x;
        instructions.y = y;
        instructions.w = w;
        instructions.h = h;


        instructions.t = t;


        instructions.r = r;
        instructions.g = g;
        instructions.b = b;

        call_hook(&instructions);

        return true;

    }


    uint64_t IL2CPPScan(const char* class_name)
    {
        uint64_t base = this->GetModuleBase("GameAssembly.dll");

        IMAGE_DOS_HEADER dos_header = this->Read<IMAGE_DOS_HEADER>(base);
        IMAGE_SECTION_HEADER data_header = this->Read<IMAGE_SECTION_HEADER>(base + dos_header.e_lfanew + sizeof(IMAGE_NT_HEADERS64) + (3 * 40));
        IMAGE_SECTION_HEADER next_section = this->Read<IMAGE_SECTION_HEADER>(base + dos_header.e_lfanew + sizeof(IMAGE_NT_HEADERS64) + (4 * 40));
        DWORD data_size = next_section.VirtualAddress - data_header.VirtualAddress;


        if (strcmp((char*)data_header.Name, ".data"))
        {
            return 0;
        }


        for (uint64_t offset = data_size; offset > 0; offset -= 8)
        {
            char klass_name[0x100] = { 0 };
            auto klass = this->Read<uint64_t>(base + data_header.VirtualAddress + offset);
            if (klass == 0) { continue; }
            auto name_pointer = this->Read<uint64_t>(klass + 0x10);
            if (name_pointer == 0) { continue; }
            this->Read(name_pointer, klass_name, sizeof(klass_name));
            if (!strcmp(klass_name, class_name))
            {
                return klass;
            }
        }

        return 0;
    }
} driver;

//extern Memory* driver;