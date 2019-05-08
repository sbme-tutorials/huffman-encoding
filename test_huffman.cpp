#include "huffman.hpp"

int main(int argc, char *argv[])
{
    To encode file named (./run -encode < ./data/omaha.pgm)
    Huffman H;
    int indexArgv = 1; // 0 is the exe
    if (indexArgv < argc && std::string(argv[indexArgv]) == "-encode")
    {
        indexArgv++;
        // ./run -encode encoded_file_name < ./data/omaha.pgm
        std::string encodedFileName;
        if (indexArgv < argc)
        {
            indexArgv++;
            H.encode(encodedFileName);
            encodedFileName = std::string(argv[indexArgv]);
            H.encode(encodedFileName);
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
            indexArgv++;
            decodedFileName = std::string(argv[indexArgv]);
            H.decode(decodedFileName);
        }
        else
        {
            decodedFileName = "output";
            H.decode(decodedFileName);
        }
    }
    else if (indexArgv < argc && std::string(argv[indexArgv]) == "-entropy")
    {
    }
    return 0;
    huffman coding test

}