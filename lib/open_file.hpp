#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::fstream open_file(const std::string &filePath);

std::stringstream read_file(const std::fstream &file);

std::vector<std::string> split(const std::stringstream &stringstream,
                               const std::string &delim = "\n");
