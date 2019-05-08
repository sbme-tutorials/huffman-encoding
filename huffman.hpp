#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <vector>
#include <utility>
#include <string>
#include <map>
#include <bits/stdc++.h>

struct Node //tree node
{
  uint8_t val; //greyscale value
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
  // double encode_test(std::vector<uint8_t> &input, std::string outputfile);

private:
  std::string intensity = "p2";
  int maxIntensity = 255;
  Node *tree;
  std::vector<uint8_t> input;
  int width = 0, height = 0;
  std::map<uint8_t, float> probability;
  std::map<uint8_t, float>::iterator prob_it;
  std::map<uint8_t, std::vector<uint8_t>> codeTable; //greyscale value : code
  std::map<uint8_t, std::vector<uint8_t>>::iterator codeTable_it;
  std::vector<std::vector<uint8_t>> encoded;
  std::vector<uint8_t> decoded;

  void buildTree();
  void outputEncoded(std::string outputfile);
  void getCodeTable(Node *parent, uint8_t *arr, int index);
  void readInput();
  void convertToBitset();
  int vectorToDecimal(std::vector<uint8_t> v);
};

#endif