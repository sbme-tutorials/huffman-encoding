#include "huffman.hpp"
#include <map>
#include <vector>
#include "math.h"
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
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

double Huffman::encode()
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
    return compressionRatio;
}

void Huffman::decode() // calls printDecoded()
{
}


void Huffman::buildTree()
{ 
    // Create a min heap & inserts all characters of input data[]
    std::priority_queue<Node,std::greater> minHeap;
    //build heap
    for (auto pixel : probability)
    {
        minHeap.push(new Node {pixel,probability[pixel] , nullptr , nullptr});
    }
    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
            // Extract the two minimum
            // freq items from min heap
            Node left = minHeap.top();
            minHeap.pop();
            Node right = minHeap.top();
            minHeap.pop();
            // Create a new internal node with frequency equal to the sum of the
            // two nodes frequencies. Make the two extracted node as left and right children
            // of this new node. Add this node to the min heap '$' is a special value
            // for internal nodes, not used
            Node parent = new Node('$', left.p + right.p,left,right);
            minHeap.push(parent);
    }
    //  The remaining node is the 
    // root node and the tree is complete. 
    tree = parent;
    unsigned char arr[1000]; //arbitrary size
    getCodeTable(tree,arr,0);
}

void Huffman::getCodeTable(Node *parent, unsigned char *arr, int index)
{
    if (parent->left)
    {
        arr[index] = '0';
        getCodeTable(parent->left,arr,index+1);
    }
    
    if (parent->right)
    {
        arr[index] = '1';
        getCodeTable(parent->right,arr,index+1);
    }
    std::vector<unsigned char> binaryCode(arr, arr + index);
    codeTable[parent->val] = binaryCode;
}

// ifstream myfile;
// myfile.open();
// myfile >> 
void Huffman::readInput()
{
  int width = 0, height = 0;
  std::string intensity;
  int maxIntensity;
  int c;
  cin >> intensity >> width >> height >> maxIntensity;
  for (int i = 0; i < width * height; i++)
  {
    int temp;
    cin >> temp;
    msg.push_back(temp);
  }    
}
//./hw_p3 -encode
void Huffman::printEncoded()
{
}

void Huffman::printDecoded(std::string outputfile) //input/output with files
{
    string directory = "./output/" + outputfile + ".pgm";
    ofstream myfile;
    myfile.open(directory);
    //print file specs width, heigth
    //print size of table code words && table of codewords
    for(auto e: decoded) {
      myfile << (int)e << " ";
    }
    myfile.close();
}


