#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <vector>
#include <utility>
#include <string>
#include <map>
#include <bits/stdc++.h>

struct Node //tree node
{
  unsigned char val; //greyscale value
  float p;           //probability
  Node *left = nullptr;
  Node *right = nullptr;
};

class Huffman
{
  public:
    float computeProb();
    double encode();
    void decode();
    void readInput(std::string);

private:
  Node *tree;
  std::vector<unsigned char> input;
  std::vector<unsigned char> pixelsArray ;
  int width = 0, height = 0;
  std::map<unsigned char , float> probability;
  std::map<unsigned char , float>::iterator prob_it;
  std::map<unsigned char, std::bitset<100> > codeTable; //greyscale value : code
  std::map<unsigned char, std::bitset<100> >::iterator codeTable_it;
  std::vector<std::bitset<100>> encoded;
  std::vector<unsigned char> decoded;

    void buildTree();
    void outputEncoded(std::string outputfile);
    void outputDecoded(std::string outputfile);
    void getCodeTable(Node *parent, std::bitset<100> arr, int index);
};

#endif