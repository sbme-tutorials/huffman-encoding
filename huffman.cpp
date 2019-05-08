#include "huffman.hpp"
#include <map>
#include <vector>
#include "math.h"
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <queue>
using namespace std;
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

    uint8_t *arr = new uint8_t[maxIntensity + 1]; //arbitrary size 0-255
    getCodeTable(tree, arr, 0);
    delete[] arr;
}

void Huffman::getCodeTable(Node *parent, uint8_t *arr, int index)
{
    if (parent->left)
    {
        arr[index] = 0;
        getCodeTable(parent->left, arr, index + 1);
    }

    if (parent->right)
    {
        arr[index] = 1;
        getCodeTable(parent->right, arr, index + 1);
    }

    if (!(parent->right || parent->left))
    {
        vector<uint8_t> binaryCode(arr, arr + index);
        codeTable[parent->val] = binaryCode;
    }
}

void Huffman::outputEncoded(std::string outputfile) //input/output with files
{
    std::string directory = "./encoded/" + outputfile + ".txt";
    std::ofstream myfile;
    myfile.open(directory);
    myfile << intensity << "\n"
           << width << " " << height << " " << maxIntensity << " " << codeTable.size() << " "; // print info
    for (auto c : codeTable)
    {
        myfile << (int)c.first << " " << vectorToDecimal(c.second) << " ";
    }
    // for (std::map<uint8_t, vector<uint8_t>>::iterator it = codeTable.begin(); it != codeTable.end(); ++it)
    //     std::cout << (int)it->first << " ";

    myfile << endl;
    for (auto e : encoded)
    {
        myfile << vectorToDecimal(e) << " ";
    }
    myfile.close();
}

void Huffman::decode(std::string outputfile) // calls outputDecoded()
{
    int sizeOfTable;
    // first get important data from the file
    string directory = "./decoded/" + outputfile + ".pgm";
    cin >> intensity >> width >> height >> maxIntensity >> sizeOfTable;

    // second use this data to decode
    // a) fill the codeWordTable as reversedCodeTable symbol codeWordAsInt
    map<int, uint8_t> reversedCodeTable;
    for (int i = 0; i < sizeOfTable; i++)
    {
        int codeWordAsInt;
        int symbol;
        cin >> symbol >> codeWordAsInt;
        reversedCodeTable[codeWordAsInt] = (uint8_t)symbol;
    }

    //b)fill the decoded vecotr <uint8_t>
    for (int i = 0; i < width * height; i++)
    {
        int codeWordAsInt;
        cin >> codeWordAsInt;
        decoded.push_back(reversedCodeTable[codeWordAsInt]);
    }
    //ouput the image as decoded file
    ofstream myfile;
    myfile.open(directory);
    myfile << intensity << endl
           << width << " " << height << endl
           << maxIntensity << endl;
    int i = 0;
    for (auto d : decoded)
    {
        if (++i % width == 0)
            myfile << endl;
        myfile << (int)d << " ";
    }
    myfile.close();
}

int Huffman::vectorToDecimal(std::vector<uint8_t> v)
{
    int p = 0;
    int num = 0;
    for (int i = v.size() - 1; i >= 0; i--)
    {
        num += std::pow(2, p) * v[i];
        p++;
    }
    return num;
}

double Huffman::encode(std::string outputfile)
{
    readInput();
    computeProb();
    buildTree();
    double compressionRatio = 0;
    for (auto element : input)
    {
        vector<uint8_t> binaryCode(codeTable[element]);
        encoded.push_back(binaryCode);
        compressionRatio += binaryCode.size();
    }
    outputEncoded(outputfile);
    compressionRatio = (8 * width * height) / compressionRatio;
    return compressionRatio;
}
