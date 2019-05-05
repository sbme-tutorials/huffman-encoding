#include "huffman.hpp"

int main(int argc, char *argv[]) // calls encode() , decode() and computeProb() 
{
    Huffman H;
    H.readInput(argv[1]);
    H.encode();
    return 0;
}

