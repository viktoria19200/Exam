#include <windows.h>
#include <iostream>

int main() {
    HANDLE hInputFile = CreateFile(
        L"input.txt",               
        GENERIC_READ,               
        0,                          
        NULL,                       
        OPEN_EXISTING,              
        FILE_ATTRIBUTE_NORMAL,      
        NULL                        
    );

    if (hInputFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Помилка при відкритті input.txt: " << GetLastError() << std::endl;
        return 1;
    }

    
    HANDLE hOutputFile = CreateFile(
        L"output.txt",              
        GENERIC_WRITE,              
        0,                          
        NULL,                       
        CREATE_ALWAYS,              
        FILE_ATTRIBUTE_NORMAL,      
        NULL                        
    );

    if (hOutputFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Помилка при відкритті output.txt: " << GetLastError() << std::endl;
        CloseHandle(hInputFile);
        return 1;
    }

    const DWORD bufferSize = 1024;
    char buffer[bufferSize];
    DWORD bytesRead, bytesWritten;

    
    while (true) {
        
        if (!ReadFile(hInputFile, buffer, bufferSize, &bytesRead, NULL)) {
            std::cerr << "Помилка при читанні файлу: " << GetLastError() << std::endl;
            break;
        }

        if (bytesRead == 0) {
           
            break;
        }

        
        if (!WriteFile(hOutputFile, buffer, bytesRead, &bytesWritten, NULL)) {
            std::cerr << "Помилка при записі файлу: " << GetLastError() << std::endl;
            break;
        }

        if (bytesRead != bytesWritten) {
            std::cerr << "Не всі дані були записані!" << std::endl;
            break;
        }
    }

    
    CloseHandle(hInputFile);
    CloseHandle(hOutputFile);

    std::cout << "Операція завершена успішно!" << std::endl;
    return 0;
}
