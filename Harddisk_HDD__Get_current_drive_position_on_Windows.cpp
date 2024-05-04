#include <Windows.h>
#include <iostream>

struct StdLargeInteger {
    union {
        struct {
            std::int32_t LowPart;
            std::int32_t HighPart;
        };
        std::int64_t QuadPart;
    };
};

long long int GetDrivePointerPosition(const std::string& drivePath) {
    HANDLE hDrive = CreateFile(drivePath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if (hDrive == INVALID_HANDLE_VALUE) {
        // Error handling: Failed to open drive
        std::cerr << "Error: Failed to open drive" << std::endl;
        return -1; // Or handle the error in another appropriate way
    }

    StdLargeInteger liOfs = { 0 };
    StdLargeInteger liNew = { 0 };
    if (!SetFilePointerEx(hDrive, liOfs, &liNew, FILE_CURRENT)) {
        // Error handling: Failed to get current position
        std::cerr << "Error: Failed to get current position" << std::endl;
        CloseHandle(hDrive);
        return -1; // Or handle the error in another appropriate way
    }

    CloseHandle(hDrive);
    return liNew.QuadPart;
}

int main() {
    std::string drivePath = "\\\\.\\PhysicalDrive0"; // Example: PhysicalDrive0 represents the first physical drive

    long long int drivePosition = GetDrivePointerPosition(drivePath);
    if (drivePosition != -1) {
        std::cout << "Current position within drive: " << drivePosition << std::endl;
    }

    return 0;
}
