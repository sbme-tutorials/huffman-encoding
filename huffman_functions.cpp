#include "huffman.hpp"
#include <bits/stdc++.h>
#include <stdlib.h>
// functions definitions here

float Huffman::computeEntropy() // computes entropy and probability of each greyscale value
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
    priority_queue<Node, std::vector<Node>, compare> min_Heap;

    for (int i = 0; i < Huffman::input.size; ++i) //Build Heap
        min_Heap.push(new Node(input[i],probability[input[i]] , nullptr , nullptr);
    // Iterate while size of heap doesn't become 1
    while (min_Heap.size() != 1) {
            // Extract the two minimum
            // freq items from min heap
            Node left = min_Heap.top();
            min_Heap.pop();

            Node right = min_Heap.top();
            min_Heap.pop();

            // Create a new internal node with frequency equal to the sum of the
            // two nodes frequencies. Make the two extracted node as left and right children
            // of this new node. Add this node to the min heap '$' is a special value
            // for internal nodes, not used
            Node top = new Node('$', left.p + right.p);
            top.left = left;
            top.right = right;
            min_Heap.push(top);
    }
    //  The remaining node is the 
    // root node and the tree is complete. 

return   min_Heap.top ;
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
