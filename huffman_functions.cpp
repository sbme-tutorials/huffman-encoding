#include "huffman.hpp"
#include <bits/stdc++.h>
// functions definitions here

float Huffman::computeProb() // computes entropy and probability of each greyscale value
{
}

int Huffman::encode() // calls reaInput() , computeEntropy(), buildTree() , printEncoded()
{
}

void Huffman::decode() // calls printDecoded()
{
}

void Huffman::buildTree()
{
    // Create a min heap & inserts all characters of data[]
    priority_queue<Node, vector<Node>, value_compare> min_Heap;

    for (int i = 0; i < input.size; ++i) //Build Heap
        min_Heap.push(new Node(value[i],p[i] , nullptr , nullptr);
    // Iterate while size of heap doesn't become 1
    while (min_Heap.size() != 1) {
            // Extract the two minimum
            // freq items from min heap
            left = min_Heap.top();
            min_Heap.pop();

            right = min_Heap.top();
            min_Heap.pop();

            // Create a new internal node with frequency equal to the sum of the
            // two nodes frequencies. Make the two extracted node as left and right children
            // of this new node. Add this node
            // to the min heap '$' is a special value
            // for internal nodes, not used
            top = new MinHeapNode('$', left->freq + right->freq);
            top->left = left;
            top->right = right;
            min_Heap.push(top);
    }
    //  The remaining node is the 
    // root node and the tree is complete. 

return   min_Heap.top ; 
    
}

void Huffman::readInput()
{
}

void Huffman::printEncoded()
{
}

void Huffman::printDecoded()
{
}