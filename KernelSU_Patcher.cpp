// KernelSU_Patcher.cpp: 定义应用程序的入口点。
//

#include "KernelSU_Patcher.h"

using namespace std;

int main(int argc, char* argv[])
{
	std::vector<std::string> arguments;
	for (int i = 0; i < argc; i++) {
		arguments.push_back(argv[i]);
	}
	if (argc != 3 && argc != 4) {
		std::cout << "Usage:" << arguments[0] << " [KernelSU] [Boot] [Output]" << std::endl << std::endl;
		std::cout << "[KernelSU]\t" << "Path to the AnyKernel3-type KernelSU package." << std::endl;
		std::cout << "[Boot]\t\t" << "Path to the boot image that needs to be patched." << std::endl;
		std::cout << "[Output]\t" << "Optional, path to the folder where the output should be saved." << std::endl;
	}
	else if ((argc == 3 && isPathValid(arguments[1]) && isPathValid(arguments[2])) || (argc == 4 && isPathValid(arguments[1]) && isPathValid(arguments[2]) && isPathValid(arguments[3]))) {
		execute(SEVEN_ZIP + " x -y \"" + arguments[1] + "\" Image");
		execute(MAGISKBOOT + " unpack \"" + arguments[2] + "\"");
		std::remove("kernel");
		std::filesystem::rename("Image", "kernel");
		execute(MAGISKBOOT + " repack \"" + arguments[2] + "\"");
		execute(MAGISKBOOT + " cleanup");
		if (argc == 4) {
			rename("new-boot.img", std::string(arguments[3] + "\\new-boot.img").c_str());
		}
	}
	else {
		std::cerr << "无效路径" << std::endl;
		return 1;
	}

	return 0;
}