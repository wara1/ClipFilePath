#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

/// @brief クリップファイルパス 機能クラス
class ClipFilePath
{
 public:
  /// @brief 結果
  enum class Resutl
  {
    OK,        //!< 成功
    NG,        //!< 失敗
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
  static constexpr const char* const K_NEW_LINE_CODE = "\r\n";

  /// @brief コマンドライン引数解析
  /// @param[in] command_line_args コマンドライン引数
  /// @return ファイルパス
  std::unordered_multimap<std::string, std::string> AnalyseCommandLineArgs_(const std::vector<std::string>& command_line_args);

  /// @brief クリップボードテキスト設定
  /// @param[in] text 設定するテキスト
  /// @return 結果
  /// @retval true 設定成功
  /// @retval false 設定失敗
  bool SetClipboardText_(const std::string& text) const;

  /// @briefテンプレート関数で任意のunordered_multimap型に対応
  /// @param[in] inputMap キー抽出対象の連想配列
  /// @return 重複なしキー値
  template <typename KeyType, typename ValueType>
  std::unordered_set<KeyType> ExtractKeys_(const std::unordered_multimap<KeyType, ValueType>& inputMap) const
  {
    std::unordered_set<KeyType> keys;

    // unordered_multimapの要素をイテレートし、キーをkeysに追加
    for (const auto& pair : inputMap) {
      keys.insert(pair.first);
    }

    return keys;
  }

  const std::unordered_multimap<std::string, std::string> file_paths_;   //!< ファイルパス(パス,ファイル名[複数]の連想配列)
};
