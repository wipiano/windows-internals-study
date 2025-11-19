#include <windows.h>
#include <iostream>
#include <string_view>
#include <fcntl.h>
#include <io.h>

int main() { 
  _setmode(_fileno(stdout), _O_U16TEXT);
  LPWCH envBlock = GetEnvironmentStringsW();

  if (envBlock == NULL) {
    std::wcout << "Error: 環境変数ブロックが読み込めませんでした．" << std::endl;
    return 1;
  }

  std::wcout << L"--- 環境変数メモリブロックのダンプを開始します ---" << std::endl;

  LPWCH current = envBlock;

  while (*current != L'\0') {
    std::wstring_view envVar(current);
    std::wcout << envVar << std::endl;

    current += envVar.length() + 1;
  }

  std::wcout << L"--- ダンプ終了 ---" << std::endl;

  FreeEnvironmentStringsW(envBlock);
  
  std::wcout << L"\n終了するにはなにかキーを押してください..." << std::endl;
  std::wcin.get();
  return 0;
}