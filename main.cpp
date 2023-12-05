#include <fstream>
#include <memory>
#include <string>

#include "deviant_llvm.h"
#include "user_input.h"

std::string readFile(const std::string& fileName) {
  std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::ate);

  std::ifstream::pos_type fileSize = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  std::vector<char> bytes(fileSize);
  ifs.read(bytes.data(), fileSize);

  return std::string(bytes.data(), fileSize);
}

int main(int argc, char* argv[]) {
  deviant::UserInput user_input;
  bool handle_file = user_input.handleUserInput(argc, argv);

  if (!handle_file)
    return 1;

  std::string program(readFile(user_input.getFilename()));
  deviant::DeviantLLVM vm;
  vm.execute(program);

  return EXIT_SUCCESS;
}