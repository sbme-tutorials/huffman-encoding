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
  double encode_test(std::vector<unsigned char> input,std::string outputfile, std::vector<std::vector<uint8_t>> encoded);

private:
  std::string intensity = "p2";
  int maxIntensity = 255;
  Node *tree;
  std::vector<unsigned char> input;
  int width = 0, height = 0;
  std::map<unsigned char, float> probability;
  std::map<unsigned char, float>::iterator prob_it;
  std::map<unsigned char, std::vector<uint8_t>> codeTable; //greyscale value : code
  std::map<unsigned char, std::vector<uint8_t>>::iterator codeTable_it;
  std::vector<std::vector<uint8_t>> encoded;
  std::vector<unsigned char> decoded;


  void buildTree();
  void outputEncoded(std::string outputfile);
  void getCodeTable(Node *parent, uint8_t *arr, int index);
  void readInput();
  void convertToBitset();
  int vectorToDecimal(std::vector<uint8_t> v);
};

#endif