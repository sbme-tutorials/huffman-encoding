#include "huffman.hpp"
#include <map>
#include <vector>
#include "math.h"
#include <algorithm>
#include <iostream>

// functions definitions here

float Huffman::computeProb() // computes entropy and probability of each greyscale value
{
    unsigned long long pixels = input.size(); //total number of pixels in the pic
    float entropy = 0;
    for (auto value : input) //for loop to calculate frequency of each greyscale value
    {
        probability[value]++;
    }
    //divide the frequency over total
    //number of pixels to get probability
    for (auto &value : probability)
    {
        value.second = value.second / (float)pixels;
        entropy += value.second * log2(value.second); //entropy formula
    }
    return -1 * entropy;
}

double Huffman::encode() // calls reaInput() , computeEntropy(), buildTree() , printEncoded()
{
    readInput();
    computeProb();
    buildTree();
    double compressionRatio = 0;
    for (auto element : input)
    {
        std::string code = codeTable[element];
        encoded.push_back(code);
        compressionRatio += code.size();
    }
    printEncoded();
    printCodeTable();
    return compressionRatio;
}

void Huffman::decode() // calls printDecoded()
{
}

void Huffman::buildTree()
{
}

void Huffman::getCodeTable()
{
}


void Huffman::readInput()
{
}

void Huffman::printEncoded()
{
}

void Huffman::printDecoded() //input/output with files
{
}

void Huffman::printCodeTable()
{
}
