#include "../include/huffman.h"
#include <iostream>

HuffmanCompression::HuffmanCompression() {}

HuffmanCompression::~HuffmanCompression() {}

void HuffmanCompression::generateCodes(HuffmanNode* root, std::string str) {
    if (!root)
        return;
    
    // Si es un nodo hoja
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = str;
    }
    
    generateCodes(root->left, str + "0");
    generateCodes(root->right, str + "1");
}

HuffmanNode* HuffmanCompression::buildHuffmanTree(std::string text) {
    // Contar frecuencias
    std::unordered_map<char, unsigned> freq;
    for (char c : text) {
        freq[c]++;
    }
    
    // Crear cola de prioridad
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;
    
    // Crear nodos hoja y agregarlos a la cola
    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    
    // Construir el árbol Huffman
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        
        HuffmanNode* newNode = new HuffmanNode('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        
        pq.push(newNode);
    }
    
    return pq.top();
}

void HuffmanCompression::destroyTree(HuffmanNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

std::string HuffmanCompression::compress(const std::string& text) {
    // Construir árbol Huffman
    HuffmanNode* root = buildHuffmanTree(text);
    
    // Generar códigos Huffman
    huffmanCodes.clear();
    generateCodes(root, "");
    
    // Comprimir el texto
    std::string compressedText = "";
    for (char c : text) {
        compressedText += huffmanCodes[c];
    }
    
    // Liberar memoria
    destroyTree(root);
    
    return compressedText;
}

std::string HuffmanCompression::decompress(const std::string& compressedText, 
                                          const std::unordered_map<char, std::string>& codes) {
    // Invertir el mapa de códigos
    std::unordered_map<std::string, char> reverseCodes;
    for (const auto& pair : codes) {
        reverseCodes[pair.second] = pair.first;
    }
    
    std::string decompressedText = "";
    std::string currentCode = "";
    
    for (char bit : compressedText) {
        currentCode += bit;
        if (reverseCodes.find(currentCode) != reverseCodes.end()) {
            decompressedText += reverseCodes[currentCode];
            currentCode = "";
        }
    }
    
    return decompressedText;
}

std::unordered_map<char, std::string> HuffmanCompression::getCodes() const {
    return huffmanCodes;
}
