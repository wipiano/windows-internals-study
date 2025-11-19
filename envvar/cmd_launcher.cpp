#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

int main() {

  std::wstring env1 = L"MY_APP_MODE=Production";
  std::wstring env2 = L"DB_CONNECTION=Localhost";

  std::vector<wchar_t> envBlock;
  envBlock.insert(envBlock.end(), env1.begin(), env1.end());
  envBlock.push_back(L'\0');
  envBlock.insert(envBlock.end(), env2.begin(), env2.end());
  envBlock.push_back(L'\0');

  STARTUPINFOW si = { sizeof(si) };
  PROCESS_INFORMATION pi = { 0 };

  //std::wstring cmd = L"C:\\Windows\\System32\\cmd.exe /k set";
  std::wstring envDump = L"./env_dump.exe";

  BOOL success = CreateProcessW(
    NULL,
    //&cmd[0],
    &envDump[0],
    NULL, NULL,
    FALSE,
    CREATE_UNICODE_ENVIRONMENT | CREATE_NEW_CONSOLE,
    (LPVOID)envBlock.data(),
    NULL,
    &si,
    &pi
  );

  if (success) {
    std::wcout << L"Process started! Check the new window." << std::endl;
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
  } else {
    std::cerr << "Failed to start process. Error: " << GetLastError() << std::endl;
  }

  return 0;
}