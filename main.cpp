#include "huffman.hpp"

int main(int argc, char *argv[])
{
    // To encode: ./a.exe -encode output_file_name < ./data/omaha.pgm
    Huffman H;
    int indexArgv = 1; // 0 is the exe
    if (indexArgv < argc && std::string(argv[indexArgv]) == "-encode")
    {
        indexArgv++;
        std::string encodedFileName;
        if (indexArgv < argc)
        {
            encodedFileName = std::string(argv[indexArgv]);
            H.encode(encodedFileName);
            indexArgv++;
        }
        else
        {
            encodedFileName = "output";
            H.encode(encodedFileName);
        }
    }
    else if (indexArgv < argc && std::string(argv[indexArgv]) == "-decode")
    {
        indexArgv++;
        std::string decodedFileName;
        if (indexArgv < argc)
        {
            decodedFileName = std::string(argv[indexArgv]);
            H.decode(decodedFileName);
            indexArgv++;
        }
        else
        {
            decodedFileName = "output";
            H.decode(decodedFileName);
        }
    }
    return 0;
}