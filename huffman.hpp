#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <vector>
#include <utility>
#include <string>
#include <map>

struct Node //tree node
{
  uint8_t val; //greyscale value
  float p;     //probability
  Node *left = nullptr;
  Node *right = nullptr;
};

class Huffman
{
public:
  float computeProb();
  void encode(std::string outputFile);
  void decode(std::string inputFile, std::string outputFile);

private:
  std::string to_decode ="";
  int width = 0;
  int height = 0 ;
  int maxIntensity = 255;
  std::string intensity = "P2";
  Node *tree;
  std::vector<uint8_t> input;
  std::map<uint8_t, float> probability;
  std::map<uint8_t, std::string> codeTable;
  std::string encoded;
  unsigned long long sizeOfEncoded = 0;
  std::vector<uint8_t> decoded;
  std::vector<uint8_t> packed;

  void buildTree();
  void outputEncoded(std::string outputFile);
  void getCodeTable(Node *parent, char *arr, int index);
  void readInput();
  void bitPacking();
};

#endif