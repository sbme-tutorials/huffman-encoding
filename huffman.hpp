#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <vector>
#include <utility>
#include <string>
#include <map>

struct Node //tree node
{
  unsigned char val; //greyscale value
  float p;           //probability
  Node *left = nullptr;
  Node *right = nullptr;
};

class Huffman
{
<<<<<<< HEAD
  public:
    float computeProb();
    double encode();
    void decode();

  private:
    Node *tree;
    std::vector<unsigned char> input;
    int width = 0, height = 0;
    std::map<unsigned char, unsigned long long > probability;
    std::map<unsigned char, std::string> codeTable; //greyscale value : code
    std::vector<std::string> encoded;
    std::vector<unsigned char> decoded;

    void readInput();
    void buildTree();
    void printEncoded();
    void printDecoded();
    void getCodeTable();
    void printCodeTable();
=======
public:
  float computeProb();
  int encode();
  void decode();

private:
  Node *tree;
  std::vector<unsigned char> input;
  int width = 0, height = 0;
  std::vector<Symbol> probability;
  std::map<unsigned char, std::string> codeTable; //greyscale value : code
  std::vector<unsigned int> encoded;
  std::vector<unsigned char> decoded;

  void readInput();
  void buildTree();
  void printEncoded();
  void printDecoded();
>>>>>>> 954872dcd11c88de7054247aef6efeb4117970c0
};

#endif