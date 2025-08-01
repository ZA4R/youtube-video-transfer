#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>


// original approach using C I/O didn't work bc mtp is a protocol rather than part of the filesystem
// liunx creates a virtual filesystem that provides access to the connected device
// this program first dynamically finds the (first) mtp device and then using 

std::string exec(const char* cmd) {
    /*
    std::unique_ptr handles the allocationa and deallocation of heap memory
    decltype(&pclose); decltype() gets the type of the argument, &pclose is a function pointer to the address of pclose, this produces a warning but it can be ignored
    popen executes the system command and returns the output
    */
   std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
   
   if (!pipe) {
    throw std::runtime_error("execution of \"" + std::string(cmd) + "\" failed");
   }

   char buffer[128];
   std::string result = "";

   while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
    result += buffer;
   }
   
   return result;
}

int main(void) {
    std::string base_mtp;
    try {
        // finds mtp path using gnome io cmds
        std::string list_result = exec("gio mount -l");
        size_t result_position = list_result.find("mtp://");

        if (result_position == std::string::npos) {
            std::cerr << "Unable to find mount point\n";
            return 1;
        }

        size_t end_of_result_pos = list_result.find("\n", result_position);

        if (end_of_result_pos == std::string::npos) {
            std::cerr << "Unable to find mount point end line char\n";
            return 1;
        }

        std::string mtp_uri = list_result.substr(result_position, end_of_result_pos - result_position);

        // uses uri to get base path to mtp within virtual file system
        std::string info_cmd = "gio info \"" + mtp_uri + "\"";
        std::string info_result = exec(info_cmd.c_str());

        // "local path: " may also be "local-path: "
        // check your specific device by running the commands in a terminal
        size_t info_res_pos = info_result.find("local path: ");

        if (info_res_pos == std::string::npos) {
            std::cerr << "Unable to find local-path: \n";
            return 1;
        }

        size_t path_start = info_res_pos + 12; // +12 to exclude "local-path: "
        size_t path_end = info_result.find("\n", path_start);

        if (path_end == std::string::npos) {
            std::cerr << "Unable to find local-path end line char \n";
            return 1;
        }

        base_mtp = info_result.substr(path_start, path_end - path_start);



    } catch (const std::exception& e) {
        std::cerr << std::string("Error occured during pathfinding: ") + e.what() << std::endl;
        return 1;
    }
    

    if (base_mtp.empty()) {
        std::cerr << "No path found" << std::endl;
        return 1;
    }

    // specific path on phone that I want to copy
    const std::string phone_path = "/Phone/DCIM/YouTube";

    // destination I chose for my uses
    const std::string des = "/home/dunk/Youtube/current";
    
    // -r (recursive) flag copies all contents within directory rather than a single file
    std::string copy_cmd = "cp -r \"" + base_mtp + phone_path + "\" \"" + des + "\"";

    int cmd_result = std::system(copy_cmd.c_str());

    if (cmd_result == 0) {
        std::cout << "File transfer successful" << std::endl;
        return 0;
    } else {
        std::cout << "Copy function was unsuccessful" << std::endl;
        return 1;
    }
}
