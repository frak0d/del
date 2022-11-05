#include <cstdio>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std::literals;

int main(const int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::puts("Usage: del [path] <passes(optional)>");
        return -1;
    }
    if (!fs::exists(argv[1]))
    {
        std::puts("\x1b[1;31mError:\x1b[0;31m Invalid Path!\x1b[0m");
        return -2;
    }
    if (argc > 3)
    {
        std::puts("\x1b[1;33mWarning:\x1b[0;33m Ignoring Extra Arguments.\x1b[0m");
    }
    
    auto path = argv[1];
    auto passes = argc>2 ? argv[2] : "1";
    bool verbose = true;
    
    if (fs::is_directory(path))
    {
        for (auto dir_entry : fs::recursive_directory_iterator(path))
        {
            if (!dir_entry.is_directory())
            {
                auto fpath = dir_entry.path().string();
                if (verbose) std::printf("%s\n", fpath.c_str());
                std::system(("shred -uxzfn "s+passes+" \""+fpath+'"').c_str());
            }
        }
    }
    
    fs::remove_all(path);
}
