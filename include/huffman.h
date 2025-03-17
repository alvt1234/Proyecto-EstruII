#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <queue>
#include <unordered_map>
#include <vector>

// Estructura para el nodo del arbol Huffman
struct HuffmanNode {
    char data;
    unsigned freq;
    HuffmanNode *left, *right;
    
    HuffmanNode(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// Comparador para la cola de prioridad
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

class HuffmanCompression {
private:
    std::unordered_map<char, std::string> huffmanCodes;
    
    // Función para generar codigos Huffman
    void generateCodes(HuffmanNode* root, std::string str);
    
    // Función para construir el arbol Huffman
    HuffmanNode* buildHuffmanTree(std::string text);
    
    // Funcion para liberar memoria del árbol
    void destroyTree(HuffmanNode* node);

public:
    HuffmanCompression();
    ~HuffmanCompression();
    
    // Comprime una cadena de texto
    std::string compress(const std::string& text);
    
    // Descomprime una cadena comprimida
    std::string decompress(const std::string& compressedText, const std::unordered_map<char, std::string>& codes);
    
    // Obtiene los códigos Huffman
    std::unordered_map<char, std::string> getCodes() const;
};

#endif // HUFFMAN_H
