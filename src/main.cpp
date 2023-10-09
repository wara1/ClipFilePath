#include <cstdint>
#include <cstdlib>
#include <vector>
#include <string>

#include "clip_file_path.hpp"

/// @brief コマンドラインパラメータ
std::vector<std::string> K_COMMAND_LINE_ARGS;

/// @brief メイン関数
/// @return 実行結果
/// @retval EXIT_SUCCESS 成功
/// @retval EXIT_FAILURE 失敗
int32_t main(const int32_t argc, const char const *argv[])
{
  int32_t ret = EXIT_SUCCESS;

  for (int32_t idx = 0; idx < argc; idx++)
  {
    K_COMMAND_LINE_ARGS.push_back(argv[idx]);
  }

  ClipFilePath clip_file_path(K_COMMAND_LINE_ARGS);

  ClipFilePath::Resutl clipRestul = clip_file_path.Clipping();
  if (ClipFilePath::Resutl::OK != clipRestul)
  {
    ret = EXIT_FAILURE;
  }

  return ret;
}