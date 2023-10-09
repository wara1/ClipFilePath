#include <windows.h>
#include <algorithm>

#include "clip_file_path.hpp"

// ---------------------------------------------
// Public
// ---------------------------------------------

ClipFilePath::ClipFilePath(const std::vector<std::wstring>& command_line_args)
  : file_paths_(AnalyseCommandLineArgs_(command_line_args))
{
}

ClipFilePath::~ClipFilePath()
{
}

ClipFilePath::Resutl ClipFilePath::Clipping() const
{
  Resutl ret = Resutl::NG;

  std::wstring clipping_text;

  std::unordered_set<std::wstring> keys = ExtractKeys_(file_paths_);
  for (const auto& key : keys)
  {
    clipping_text += L"<" + key + L">" + K_NEW_LINE_CODE;

    const auto key_iterators = file_paths_.equal_range(key);

    std::for_each(key_iterators.first, key_iterators.second, [&clipping_text](std::pair<std::wstring, std::wstring> map_data) {
        clipping_text += L"・" + map_data.second + K_NEW_LINE_CODE;
      }
    );
  }

  if (SetClipboardText_(clipping_text))
  {
    ret = Resutl::OK;
  }

  return ret;
}

// ---------------------------------------------
// Private
// ---------------------------------------------

std::unordered_multimap<std::wstring, std::wstring> ClipFilePath::AnalyseCommandLineArgs_(
  const std::vector<std::wstring>& command_line_args)
{
  std::unordered_multimap<std::wstring, std::wstring> file_paths;

  if (1U < command_line_args.size())
  {
    // ソート
    std::vector<std::wstring> temp_file_paths(++command_line_args.begin(), command_line_args.end());
    std::sort(temp_file_paths.begin(), temp_file_paths.end());

    // パスとファイル名分離/設定
    for (const auto& file_path : temp_file_paths)
    {
      std::wstring directory;
      std::wstring fine_name;
      
      const size_t found = file_path.find_last_of(L"/\\");   // 最後のスラッシュまたはバックスラッシュを探して、パスを分割する
      if (found != std::wstring::npos) {
        directory = file_path.substr(0, found);
        fine_name = file_path.substr(found + 1);

        file_paths.emplace(directory, fine_name);           // 結果へ格納
      }
    }
  }

  return file_paths;
}

bool ClipFilePath::SetClipboardText_(const std::wstring& text) const
{
  bool ret = false;

  if ((!text.empty()) && OpenClipboard(nullptr)) {
    // クリップボードをクリア
    EmptyClipboard();

    // 文字列をクリップボードに設定
    HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, (text.length() + 1) * sizeof(wchar_t));
    if (hClipboardData != nullptr) {
      wchar_t* pchData = static_cast<wchar_t*>(GlobalLock(hClipboardData));
      if (pchData != nullptr) {
        wcscpy_s(pchData, text.length() + 1, text.c_str());
        GlobalUnlock(hClipboardData);
        SetClipboardData(CF_UNICODETEXT, hClipboardData);
      }
    }

    CloseClipboard();
    ret = true;
  }

  return ret;
}
