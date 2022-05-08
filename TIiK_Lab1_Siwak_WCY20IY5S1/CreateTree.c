#include "structdef.h"
#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable:4996)

TreeNode TreeNodes[512] = { {0} };
int j;

void CreateTree(HuffmanNode symbolFrequency[]) {
	for (int i = 0; i < 512; i++) {
		if (symbolFrequency[i].Frequency > 0
			&& symbolFrequency[i].Ascii != '\0') {
			TreeNodes[j].Ascii = symbolFrequency[i].Ascii;
			TreeNodes[j].Frequency = symbolFrequency[i].Frequency;
			j++;
		}
	}
	int x = -1;
	for(int i = 512 - 1; i >= 0; i--)
	{
		if (symbolFrequency[i].Frequency > 0
			&& symbolFrequency[i].Ascii != '\0') {
			if (i - 1 >= 0) {
				TreeNodes[j].LeftChild = symbolFrequency[i].Ascii;
				TreeNodes[j].RightChild = symbolFrequency[i - 1].Ascii;
				TreeNodes[j].Ascii = x;
				TreeNodes[j].Frequency =
					symbolFrequency[i].Frequency + symbolFrequency[i - 1].Frequency;
			}
			j++;
			symbolFrequency[OUTPUT_ARRAY_LENGTH + j].Ascii = x;
			x--;
			symbolFrequency[OUTPUT_ARRAY_LENGTH + j].Frequency =
				symbolFrequency[i].Frequency + symbolFrequency[i - 1].Frequency;
			i++;

			qsort(symbolFrequency, 512, sizeof(HuffmanNode),
				CompareHuffmanNodes);
			symbolFrequency[i].Ascii = 0;
			symbolFrequency[i].Frequency = 0;
			symbolFrequency[i - 1].Ascii = 0;
			symbolFrequency[i - 1].Frequency = 0;
		}
	}
}

void SaveTreeToFile() {
	FILE* treeFileHandler = fopen("tree.graf", "w");
	int j = -1;
	for (int i = 0; i < 512; i++)
	{
		if (TreeNodes[i].Ascii != 0 || TreeNodes[i].LeftChild != 0 || TreeNodes[i].RightChild != 0) {
			if (TreeNodes[i].Ascii != 0)
				fprintf(treeFileHandler, "%i : %i \t\t Left child: %i \t Right child: %i \n",
					TreeNodes[i].Ascii, TreeNodes[i].Frequency, TreeNodes[i].LeftChild, TreeNodes[i].RightChild);
			else {
				fprintf(treeFileHandler, "%i : %i  \t\t Left child: %i \t Right child: %i \n",
					j, TreeNodes[i].Frequency, TreeNodes[i].LeftChild, TreeNodes[i].RightChild);
				j--;
			}
		}
	}
}

TreeNode* SeekLeftNode(TreeNode* node) {
	int ascii = node->LeftChild;
	int i = 0;
	for (; i < 512; i++)
	{
		if (TreeNodes[i].Ascii == ascii)
			return &TreeNodes[i];
	}

	TreeNode* emptyNode = calloc(1, sizeof(TreeNode));
	return emptyNode;
}

TreeNode* SeekRightNode(TreeNode* node) {
	int ascii = node->RightChild;
	int i = 0;
	for (; i < 512; i++)
	{
		if (TreeNodes[i].Ascii == ascii)
			return &TreeNodes[i];
	}

	TreeNode* emptyNode = calloc(1, sizeof(TreeNode));
	return emptyNode;
}

TreeNode* FindNodeByAscii(int ascii) {
	for (int i = 0; i < 512; i++) {
		if (TreeNodes[i].Ascii == ascii) {
			return &TreeNodes[i];
		}
	}
}

EncodedCharacter codeTable[OUTPUT_ARRAY_LENGTH] = { {0} };

void CreateCodeTable() {
	int j = 0;
	int i = 512 - 1;
	TreeNode* currentNode = calloc(1, sizeof(TreeNode));

	for (; i >= 0; i--)
	{
		if (TreeNodes[i].Frequency != 0)
			break;
	}
	int alreadyVisited[OUTPUT_ARRAY_LENGTH] = { {0} };
	int h = 0;
	int visited = 0;
	int leftSubtree = 1;
	int k = 0;
	while (h < 256) { 
		if (leftSubtree) {
			while (currentNode->LeftChild != 0 && currentNode->RightChild != 0) {
				if (currentNode->LeftChild != 0) {
					for (int i = 0; i < OUTPUT_ARRAY_LENGTH; i++) {
						if (currentNode->LeftChild == alreadyVisited[i]) {
							visited = 1;
							break;
						}
					}
					if (!visited) {
						currentNode = SeekLeftNode(currentNode);
						codeTable[h].code[j] = 0;
						if (currentNode->Ascii > 0)
						codeTable[h].Ascii = currentNode->Ascii;
					}
				}
				if (currentNode->RightChild != 0 && visited == 1) {
					currentNode = SeekRightNode(currentNode);
					codeTable[h].code[j] = 1;
					if (currentNode->Ascii > 0)
					codeTable[h].Ascii = currentNode->Ascii;
				}
				visited = 0;

				int dontVisitParentNode = 0;
				for (int i = 0; i < 512; i++)
				{
					if (currentNode->LeftChild == alreadyVisited[i]
						&& alreadyVisited[i] != 0) {
						dontVisitParentNode++;
					}
					if (currentNode->RightChild == alreadyVisited[i]
						&& alreadyVisited[i] != 0) {
						dontVisitParentNode++;
					}
				}

				if (dontVisitParentNode == 2) {
					if (k < 256)
					alreadyVisited[k] = currentNode->Ascii;
					k++;
				}

				j++;
			}
		}
		else {
			while (currentNode->LeftChild != 0 && currentNode->RightChild != 0) {
				if (currentNode->RightChild != 0) {
					for (int i = 0; i < OUTPUT_ARRAY_LENGTH; i++) {
						if (currentNode->RightChild == alreadyVisited[i]) {
							visited = 1;
							break;
						}
					}
					if (!visited) {
						currentNode = SeekRightNode(currentNode);
						codeTable[h].code[j] = 1;
						if(currentNode->Ascii > 0)
						codeTable[h].Ascii = currentNode->Ascii;
					}
				}
				if (currentNode->LeftChild != 0 && visited == 1) {
					currentNode = SeekLeftNode(currentNode);
					codeTable[h].code[j] = 0;
					if (currentNode->Ascii > 0)
					codeTable[h].Ascii = currentNode->Ascii;
				}
				visited = 0;

				int dontVisitParentNode = 0;
				for (int i = 0; i < OUTPUT_ARRAY_LENGTH; i++)
				{
					if (currentNode->LeftChild == alreadyVisited[i]
						&& alreadyVisited[i] != 0) {
						dontVisitParentNode++;
					}
					if (currentNode->RightChild == alreadyVisited[i]
						&& alreadyVisited[i] != 0) {
						dontVisitParentNode++;
					}
				}

				if (dontVisitParentNode == 2) {
					if (k < 256)
					alreadyVisited[k] = currentNode->Ascii;
					k++;
				}

				j++;
			}
		}


		codeTable[h].code[j] = 9;

		if (codeTable[h].code[j - 1] == 1) {
			leftSubtree = 0;
		}

		if(k<256)
		alreadyVisited[k] = currentNode->Ascii;
		j = 0;
		k++;
		h++;

		currentNode->LeftChild = TreeNodes[i].LeftChild;
		currentNode->RightChild = TreeNodes[i].RightChild;
		currentNode->Ascii = TreeNodes[i].Ascii;
		currentNode->Frequency = TreeNodes[i].Frequency;
	}
}

void WriteCodeTableToFile() {
	FILE* outputFilePointer = fopen("code.table", "w");
	if (outputFilePointer == NULL)
		exit(1);

	for (int i = 0; i < OUTPUT_ARRAY_LENGTH; i++) {
		if (codeTable[i].Ascii > 0) {
			fprintf(outputFilePointer, "%i (%c)\t", codeTable[i].Ascii,
				codeTable[i].Ascii);
			int j = 0;
			while(codeTable[i].code[j] != 9){
				fprintf(outputFilePointer, "%i", codeTable[i].code[j]);
				j++;
			}
			fprintf(outputFilePointer, "\n");
		}
	}
}