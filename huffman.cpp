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
    struct compare
    {
        bool operator()(Node *left, Node *right)

        {
            return (left->p > right->p);
        }
    };
    // Create a min heap & inserts all characters of input data[]
    std::priority_queue<Node *, std::vector<Node *>, compare> minHeap;

    //build heap
    for (auto pixel : probability)
    {
        Node *n = new Node{prob_it->first, prob_it->second, nullptr, nullptr};
        minHeap.push(n);
    }
    while (minHeap.size() != 1)
    {
        Node *left = minHeap.top();
        minHeap.pop();
        Node *right = minHeap.top();
        minHeap.pop();
        Node *parent = new Node;
        parent->p = left->p + right->p;
        parent->left = left;
        parent->right = right;
        minHeap.push(parent);
        tree = parent;
    }
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
    vector<uint8_t> binaryCode(arr, arr + index);
    codeTable[parent->val] = binaryCode;
}

double Huffman::encode(std::string outputfile)
{
    readInput();
    computeProb();
    buildTree();
    double compressionRatio = 0;
    for (auto element : input)
    {
        vector<uint8_t> binaryCode = codeTable[element];
        encoded.push_back(binaryCode);
        compressionRatio += binaryCode.size();
    }
    outputEncoded(outputfile);
    return compressionRatio;
}

void Huffman::outputEncoded(std::string outputfile) //input/output with files
{
    std::string directory = "./encoded/" + outputfile + ".txt";
    std::ofstream myfile;
    myfile.open(directory);
    myfile << intensity << "\n"
           << width << " " << height << " " << maxIntensity << " "
           << encoded.size() << " " << codeTable.size() << std::endl; // print info
    for (auto c : codeTable)
    {
        myfile << (int)c.first << " " << vectorToDecimal(c.second);
    }
    for (auto e : encoded)
    {
        myfile << vectorToDecimal(e) << " ";
    }
    myfile.close();
}

void Huffman::decode(std::string outputfile) // calls outputDecoded()
{
    int sizeOfEncoded;
    int sizeOfTable;
    // first get important data from the file
    string directory = "./decoded/" + outputfile + ".pgm";
    cin >> intensity >> width >> height >> maxIntensity >> sizeOfEncoded >> sizeOfTable;

    // second use this data to decode
    // a) fill the codeWordTable as reversedCodeTable
    map<int, unsigned char> reversedCodeTable;
    for (int i = 0; i < sizeOfTable; i++)
    {
        int codeWordAsInt;
        int temp;
        cin >> temp >> codeWordAsInt;
        reversedCodeTable[codeWordAsInt] = (int)temp;
    }
    //b)fill the decoded vecotr <unsigned char>
    for (int i = 0; i < sizeOfEncoded; i++)
    {
        int temp;
        cin >> temp;
        decoded.push_back(reversedCodeTable[temp]);
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

double Huffman::encode_test(vector<unsigned char> input, std::string outputfile, std::vector<std::vector<uint8_t>> encoded)
{
    this->input = input;
    computeProb();
    buildTree();
    double compressionRatio = 0;
    for (auto element : input)
    {
        vector<uint8_t> binaryCode = codeTable[element];
        encoded.push_back(binaryCode);
        compressionRatio += binaryCode.size();
    }
    for (auto e : encoded)
    {
        for (auto ee : e)
        {
            std::cout << ee;
        }
        std::cout << std::endl;
    }
    return compressionRatio;
}