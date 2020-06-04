#include "il2cpp-config.h"

#if IL2CPP_TARGET_WINRT || IL2CPP_TARGET_XBOXONE

#include "il2cpp-vm-support.h"
#include "os\Environment.h"
#include "os\Win32\WindowsHelpers.h"
#include "utils\StringUtils.h"
#include "vm\Exception.h"

#include <windows.storage.h>
#include <wrl.h>

using namespace ABI::Windows::Storage;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace il2cpp
{
    using namespace vm;

namespace os
{
#define CSIDL_DESKTOP                   0x0000        // <desktop>
#define CSIDL_PROGRAMS                  0x0002        // Start Menu\Programs
#define CSIDL_PERSONAL                  0x0005        // My Documents
#define CSIDL_FAVORITES                 0x0006        // <user name>\Favorites
#define CSIDL_STARTUP                   0x0007        // Start Menu\Programs\Startup
#define CSIDL_RECENT                    0x0008        // <user name>\Recent
#define CSIDL_SENDTO                    0x0009        // <user name>\SendTo
#define CSIDL_STARTMENU                 0x000b        // <user name>\Start Menu
#define CSIDL_MYMUSIC                   0x000d        // "My Music" folder
#define CSIDL_MYVIDEO                   0x000e        // "My Videos" folder
#define CSIDL_DESKTOPDIRECTORY          0x0010        // <user name>\Desktop
#define CSIDL_DRIVES                    0x0011        // My Computer
#define CSIDL_NETWORK                   0x0012        // Network Neighborhood (My Network Places)
#define CSIDL_NETHOOD                   0x0013        // <user name>\nethood
#define CSIDL_FONTS                     0x0014        // windows\fonts
#define CSIDL_TEMPLATES                 0x0015
#define CSIDL_COMMON_STARTMENU          0x0016        // All Users\Start Menu
#define CSIDL_COMMON_PROGRAMS           0X0017        // All Users\Start Menu\Programs
#define CSIDL_COMMON_STARTUP            0x0018        // All Users\Startup
#define CSIDL_COMMON_DESKTOPDIRECTORY   0x0019        // All Users\Desktop
#define CSIDL_APPDATA                   0x001a        // <user name>\Application Data
#define CSIDL_PRINTHOOD                 0x001b        // <user name>\PrintHood
#define CSIDL_LOCAL_APPDATA             0x001c        // <user name>\Local Settings\Applicaiton Data (non roaming)
#define CSIDL_ALTSTARTUP                0x001d        // non localized startup
#define CSIDL_COMMON_ALTSTARTUP         0x001e        // non localized common startup
#define CSIDL_COMMON_FAVORITES          0x001f
#define CSIDL_INTERNET_CACHE            0x0020
#define CSIDL_COOKIES                   0x0021
#define CSIDL_HISTORY                   0x0022
#define CSIDL_COMMON_APPDATA            0x0023        // All Users\Application Data
#define CSIDL_WINDOWS                   0x0024        // GetWindowsDirectory()
#define CSIDL_SYSTEM                    0x0025        // GetSystemDirectory()
#define CSIDL_PROGRAM_FILES             0x0026        // C:\Program Files
#define CSIDL_MYPICTURES                0x0027        // C:\Program Files\My Pictures
#define CSIDL_PROFILE                   0x0028        // USERPROFILE
#define CSIDL_SYSTEMX86                 0x0029        // x86 system directory on RISC
#define CSIDL_PROGRAM_FILESX86          0x002a        // x86 C:\Program Files on RISC
#define CSIDL_PROGRAM_FILES_COMMON      0x002b        // C:\Program Files\Common
#define CSIDL_PROGRAM_FILES_COMMONX86   0x002c        // x86 Program Files\Common on RISC
#define CSIDL_COMMON_TEMPLATES          0x002d        // All Users\Templates
#define CSIDL_COMMON_DOCUMENTS          0x002e        // All Users\Documents
#define CSIDL_COMMON_ADMINTOOLS         0x002f        // All Users\Start Menu\Programs\Administrative Tools
#define CSIDL_ADMINTOOLS                0x0030        // <user name>\Start Menu\Programs\Administrative Tools
#define CSIDL_CONNECTIONS               0x0031        // Network and Dial-up Connections
#define CSIDL_COMMON_MUSIC              0x0035        // All Users\My Music
#define CSIDL_COMMON_PICTURES           0x0036        // All Users\My Pictures
#define CSIDL_COMMON_VIDEO              0x0037        // All Users\My Video
#define CSIDL_RESOURCES                 0x0038        // Resource Direcotry
#define CSIDL_RESOURCES_LOCALIZED       0x0039        // Localized Resource Direcotry
#define CSIDL_COMMON_OEM_LINKS          0x003a        // Links to All Users OEM specific apps
#define CSIDL_CDBURN_AREA               0x003b        // USERPROFILE\Local Settings\Application Data\Microsoft\CD Burning
#define CSIDL_COMPUTERSNEARME           0x003d        // Computers Near Me (computered from Workgroup membership)

    template<typename T>
    static inline std::string GetAppFolder(T appDataToStorageFolder)
    {
        ComPtr<IApplicationDataStatics> appDataStatics;
        ComPtr<IApplicationData> appData;
        ComPtr<IStorageFolder> appDataFolder;
        ComPtr<IStorageItem> appDataFolderItem;
        HString appDataPath;

        auto hr = RoGetActivationFactory(HStringReference(RuntimeClass_Windows_Storage_ApplicationData).Get(), __uuidof(IApplicationDataStatics), &appDataStatics);
        IL2CPP_VM_RAISE_IF_FAILED(hr, false);

        hr = appDataStatics->get_Current(&appData);
        IL2CPP_VM_RAISE_IF_FAILED(hr, false);

        hr = appDataToStorageFolder(appData.Get(), &appDataFolder);
        IL2CPP_VM_RAISE_IF_FAILED(hr, false);

        hr = appDataFolder.As(&appDataFolderItem);
        IL2CPP_VM_RAISE_IF_FAILED(hr, false);

        hr = appDataFolderItem->get_Path(appDataPath.GetAddressOf());
        IL2CPP_VM_RAISE_IF_FAILED(hr, false);

        unsigned int dummy;
        return utils::StringUtils::Utf16ToUtf8(appDataPath.GetRawBuffer(&dummy));
    }

    static inline std::string GetLocalAppDataFolder()
    {
        return GetAppFolder([](IApplicationData* appData, IStorageFolder** folder) { return appData->get_LocalFolder(folder); });
    }

#if !IL2CPP_TARGET_XBOXONE
    static inline std::string GetRoamingAppDataFolder()
    {
        return GetAppFolder([](IApplicationData* appData, IStorageFolder** folder) { return appData->get_RoamingFolder(folder); });
    }

#endif

    std::string Environment::GetWindowsFolderPath(int32_t folder)
    {
        switch (folder)
        {
#if !IL2CPP_TARGET_XBOXONE
            case CSIDL_APPDATA:
                return GetRoamingAppDataFolder();
#endif

            case CSIDL_LOCAL_APPDATA:
                return GetLocalAppDataFolder();

            default:
                IL2CPP_VM_RAISE_UNAUTHORIZED_ACCESS_EXCEPTION(L"Failed getting the path of a special folder: Access Denied.");
        }

        return std::string();
    }

#if NET_4_0

    bool Environment::Is64BitOs()
    {
#if IL2CPP_TARGET_WINRT
        IL2CPP_VM_NOT_SUPPORTED("Is64BitOs", L"It is not possible to check if the OS is a 64bit OS on the current platform.");
        return false;
#endif
        return true;
    }

#endif
}
}
#endif
