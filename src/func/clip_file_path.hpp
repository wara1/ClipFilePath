#pragma once

#include <vector>
#include <map>
#include <string>

/// @brief クリップファイルパス 機能クラス
class ClipFilePath
{
 public:
  /// @brief 結果
  enum class Resutl
  {
    OK,       //!< 成功
    ERROR,    //!< 失敗
  };

  /// @brief コンストラクタ
  /// @param[in] command_line_args コマンドライン引数
  ClipFilePath(const std::vector<std::string>& command_line_args);

  /// @brief デストラクタ
  ~ClipFilePath();

  /// @brief クリッピング
  /// @return 結果
  /// @retval Resutl::OK 成功
  /// @retval Resutl::NG 失敗
  Resutl Clipping() const;

 private:
  /// @brief コマンドライン引数解析
  /// @param[in] command_line_args コマンドライン引数
  /// @return ファイルパス
  std::map<std::string, std::vector<std::string>> AnalyseCommandLineArgs_(const std::vector<std::string>& command_line_args);

  const std::map<std::string, std::vector<std::string>> file_paths_;   //!< ファイルパス(パス,ファイル名[複数]の連想配列)
};
