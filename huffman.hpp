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
  double encode(std::string outputfile);
  void decode(std::string outputfile);

private:
  Node *tree;
  std::vector<unsigned char> input;
  int width = 0, height = 0;
  std::map<unsigned char, float> probability;
  std::map<unsigned char, float>::iterator prob_it;
  std::map<unsigned char, std::string> codeTable; //greyscale value : code
  std::map<unsigned char, std::string>> ::iterator codeTable_it;
  std::vector<std::string>> encoded;
  std::vector<unsigned char> decoded;

  void buildTree();
  void outputEncoded(std::string outputfile);
  void outputDecoded(std::string outputfile);
  void getCodeTable(Node *parent, char *arr, int index);
  void readInput(std::string file);
  void convertToBitset();
};

#endif