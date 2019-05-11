#include "huffman.hpp"
#include <map>
#include <vector>
#include "math.h"
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <queue>
// functions definitions here

void Huffman::readInput()
{
    std::cin >> intensity >> width >> height >> maxIntensity;
    for (int i = 0; i < width * height; i++)
    {
        int temp;
        std::cin >> temp;
        input.push_back(temp);
    }
}

float Huffman::computeProb() // computes entropy and probability of each greyscale value
{
    unsigned long long pixels = input.size(); // total number of pixels in the pic
    float entropy = 0;
    for (auto value : input) // for loop to calculate frequency of each greyscale value
    {
        probability[value]++;
    }
    // divide the frequency over total
    // number of pixels to get probability
    for (auto &value : probability)
    {
        value.second = value.second / (float)pixels;
        entropy += value.second * log2(value.second); //entropy formula
    }
    return -1 * entropy;
}

void Huffman::buildTree()
{
    struct Compare
    {
        bool operator()(Node *a, Node *b)
        {
            return (a->p > b->p);
        }
    };
    // Create a min heap & inserts all characters of input data[]
    std::priority_queue<Node *, std::vector<Node *>, Compare> minHeap;
    //build heap
    for (auto pixel : probability)
    {
        Node *n = new Node{pixel.first, pixel.second, nullptr, nullptr};
        minHeap.push(n);
    }
    Node *parent;
    while (minHeap.size() != 1)
    {
        Node *left = minHeap.top();
        minHeap.pop();
        Node *right = minHeap.top();
        minHeap.pop();
        parent = new Node;
        parent->p = left->p + right->p;
        parent->left = left;
        parent->right = right;
        minHeap.push(parent);
    }
    tree = parent;

    char arr[255];
    getCodeTable(tree, arr, 0);
}

void Huffman::getCodeTable(Node *parent, char *arr, int index)
{
    if (parent->left)
    {
        arr[index] = '0';
        getCodeTable(parent->left, arr, index + 1);
    }

    if (parent->right)
    {
        arr[index] = '1';
        getCodeTable(parent->right, arr, index + 1);
    }

    if (!(parent->right || parent->left))
    {
        arr[index] = '\0';
        std::string binaryCode(arr, arr + index + 1);
        codeTable[parent->val] = binaryCode;
    }
}
void Huffman::encode(std::string outputFile)
{
    readInput();
    computeProb();
    buildTree();
    sizeOfEncoded = 0;
    for (auto element : input)
    {
        if (codeTable.find(element) != codeTable.end())
        {
            std::string binaryCode = codeTable[element];
            encoded+=binaryCode;
            sizeOfEncoded += binaryCode.length();
        }
    }
    outputEncoded(outputFile);
}

void Huffman::outputEncoded(std::string outputFile)
{
    std::string directory = "./encoded/" + outputFile + ".txt";
    std::ofstream myFile;
    myFile.open(directory);
    myFile << intensity << "\n"
           << width << " " << height << " " << maxIntensity << " "
           << codeTable.size() << " " << sizeOfEncoded << " "; // print info
    for (auto c : codeTable)
    {
        myFile << (int)c.first << " " << c.second << " " << std::endl;
    }
    for (auto e : encoded)
    {
        myFile << e;
    }
    myFile.close();
}

void Huffman::decode(std::string outputFile) // calls outputDecoded()
{
    int sizeOfTable = 0;
    // get important data from the file
    std::string directory = "./decoded/" + outputFile + ".pgm";
    std::cin >> intensity >> width >> height >> maxIntensity >> sizeOfTable >> sizeOfEncoded;

    // fill the codeWordTable as reversedCodeTable symbol codeWordAsInt
    std::map<std::string, uint8_t> reversedCodeTable;
    for (int i = 0; i < sizeOfTable; i++)
    {
        std::string codeWord;
        int symbol;
        std::cin >> symbol >> codeWord;
        reversedCodeTable[codeWord] = (uint8_t)symbol;
    }
    std::string str = "";
    for (int i = 0; i < sizeOfEncoded; i++)
    {
        char c;
        std::cin >> c;
        str += c;
        if (reversedCodeTable.find(str) != reversedCodeTable.end())
        {
            decoded.push_back(reversedCodeTable[str]);
            str = "";
        }
    }
    std::ofstream myFile;
    myFile.open(directory);
    myFile << intensity << std::endl
           << width << " " << height << std::endl
           << maxIntensity << std::endl;
    int i = 0;
    for (auto d : decoded)
    {
        if (i++ % width == 0)
            myFile << std::endl;
        myFile << (int)d << " ";
    }
    myFile.close();
}

