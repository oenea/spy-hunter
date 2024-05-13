#ifndef __FILE_LIST_H__
#define __FILE_LIST_H__

#include "dirent.h"



#define MAX_FILENAME_SIZE	50


class FileList {
public:
	typedef struct node_s {
		struct node_s *next;
		char filename[MAX_FILENAME_SIZE];
	} Node;

	FileList(const char *sufix, const char *directory = ".")
	{
		struct dirent *entry;
		DIR *dir;

		if(dir = opendir(directory)) {
			size = 0;
			while((entry = readdir(dir)) != NULL) {
				int len1 = (int)strlen(entry->d_name);
				int len2 = (int)strlen(sufix);
				if((len1 >= len2) && (!strncmp(&entry->d_name[len1 - len2], sufix, len2))) {
					Node *node = (Node *)malloc(sizeof(Node));
					if(node) {
						strncpy(node->filename, entry->d_name, MAX_FILENAME_SIZE);
						node->filename[MAX_FILENAME_SIZE - 1] = '\0';
						node->next = root;
						root = node;
						size++;
					}
				}
			}
			closedir(dir);
		}
	}

	~FileList(void)
	{
		while(root) {
			Node *node = root->next;
			free(root);
			root = node;
		}
	}

	uint32_t getSize(void)
	{
		return size;
	}

	Node *getList(uint32_t index)
	{
		Node *node = root;
		uint32_t i = 0;
		while(node) {
			if(i == index) {
				return node;
			}
			node = node->next;
			i++;
		}
		return NULL;
	}

private:
	Node *root = nullptr;
	uint32_t size = 0;
};


#endif /* __FILE_LIST_H__ */
