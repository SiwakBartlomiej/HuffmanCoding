#define OUTPUT_ARRAY_LENGTH 256

struct TreeNode {
    int Ascii;
    int Frequency;
    int Parent;
    int LeftChild;
    int RightChild;
    int Visited;
};
typedef struct TreeNode TreeNode;

struct HuffmanNode {
    int Ascii;
    int Frequency;
};
typedef struct HuffmanNode HuffmanNode;

struct EncodedCharacter {
    int Ascii;
    int code[OUTPUT_ARRAY_LENGTH];
};
typedef struct EncodedCharacter EncodedCharacter;

int CompareHuffmanNodes(const void* element1, const void* element2);