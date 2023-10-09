#include "clip_file_path.hpp"


// ---------------------------------------------
// Public
// ---------------------------------------------

ClipFilePath::ClipFilePath(const std::vector<std::string>& command_line_args)
  : file_paths_(AnalyseCommandLineArgs_(command_line_args))
{
}

ClipFilePath::~ClipFilePath()
{

}

ClipFilePath::Resutl ClipFilePath::Clipping() const
{
  return ClipFilePath::Resutl::OK;
}

// ---------------------------------------------
// Private
// ---------------------------------------------

std::map<std::string, std::vector<std::string>> ClipFilePath::AnalyseCommandLineArgs_(
  const std::vector<std::string>& command_line_args)
{
  std::map<std::string, std::vector<std::string>> file_paths;

  return file_paths;
}