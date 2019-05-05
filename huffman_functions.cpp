#include "huffman.hpp"
#include <map>
#include <vector>
#include "math.h"
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <queue>
// functions definitions here

void Huffman::readInput(std::string)
{
    //./test.cpp -encode > eath.pgm
    std::string intensity;
    unsigned char maxIntensity;
    std::cin >> intensity >> width >> height >> maxIntensity;
    for (int i = 0; i < width * height; i++)
    {
        unsigned char temp;
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
struct compare
{
    bool operator()(Node *left, Node *right)

    {
        return (left->p > right->p);
    }
};
void Huffman::buildTree()
{
    // Create a min heap & inserts all characters of input data[]
    std::priority_queue<Node*, std::vector<Node*>, compare> minHeap;

    //build heap
    for (auto pixel : probability)
    {
        Node* n = new Node{prob_it->first, prob_it->second, nullptr, nullptr};
        minHeap.push(n);
    }
    while (minHeap.size() != 1)
    {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();
        Node* parent = new Node;
        parent->p =left->p + right->p;
        parent->left= left;
        parent->right =right;
        minHeap.push(parent);
        tree = parent;
    }
    std::bitset<100> arr; //arbitrary size
    getCodeTable(tree, arr, 0);
}
void Huffman::getCodeTable(Node *parent, std::bitset<100> arr, int index)
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
    codeTable[parent->val] = arr;
    //add line
}

double Huffman::encode()
{
    //readInput();
    computeProb();
    buildTree();
    double compressionRatio = 0;
    for (auto element : input)
    {
        std::bitset<100> binaryCode = codeTable[element];
        encoded.push_back(binaryCode);
        compressionRatio += binaryCode.size();
    }
    outputEncoded("encoded_text");
    return compressionRatio;
}

void Huffman::outputEncoded(std::string outputfile) //input/output with files
{
    std::string intensity;
    unsigned char maxIntensity;
    std::string directory = "./output/" + outputfile + ".txt";
    std::ofstream myfile;
    myfile.open(directory);
    myfile << intensity << std::endl
           << width << height << std::endl
           << maxIntensity << std::endl << encoded.size();

    for (auto e : encoded)
    {
        myfile << e;
    }
    
    myfile << std::endl
           << "codeTable:" << std::endl;
    for (auto e : codeTable)
    {
        myfile << codeTable_it->first << ":" << codeTable_it->second;
    }
    myfile.close();
}

/*void Huffman::decode() // calls outputDecoded()
{
    //./test.cpp -encode > eath.pgm
    std::string intensity;
    unsigned char maxIntensity;
    int size;
    std::cin >> intensity >> width >> height >> maxIntensity >> size;
    for (int i = 0; i < size ; i++)
    {
        std::bitset<100> temp;
        if (temp == )
        std::cin >> temp;
        input.push_back(temp);
    }
}

void Huffman::outputDecoded(std::string outputfile) //input/output with files
{
    std::string intensity;
    unsigned char maxIntensity;
    std::string directory = "./output/" + outputfile + ".pgm";
    std::ofstream myfile;
    myfile.open(directory);
    //print file specs width, heigth
    //print size of table code words && table of codewords
    myfile << intensity << std::endl
           << width << height << std::endl
           << maxIntensity;
    for (auto e : decoded)
    {
        myfile << e << " ";
    }
    myfile.close();
}*/
