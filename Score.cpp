#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif
#include "Global.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "Score.h"


Score::Node *Score::root = NULL;
uint32_t Score::size = 0;



void Score::defaults(void)
{
	for(uint8_t i=0; i < 1; i++) {
		addToList(Data { (uint32_t)(123 + i), (uint32_t)(100 - i), "PAWEL" });
		addToList(Data { (uint32_t)(456 + i*1), (uint32_t)(1000 + i*8), "ANIA" });
		addToList(Data { (uint32_t)(56 + i*3), (uint32_t)(200 + i*8), "BASIA" });
		addToList(Data { (uint32_t)(16 + i*2), (uint32_t)(300 + i*8), "MICHAL" });
		addToList(Data { (uint32_t)(17 + i*3), (uint32_t)(400 + i*8), "LALA" });
		addToList(Data { (uint32_t)(156 + i*3), (uint32_t)(40 + i*8), "KASIA" });
		addToList(Data { (uint32_t)(1056 + i*3), (uint32_t)(60 + i*8), "RYS" });
		addToList(Data { (uint32_t)(367 + i*3), (uint32_t)(4120 + i*8), "PIOTR" });
		addToList(Data { (uint32_t)(367 + i*3), (uint32_t)(4150 + i*8), "TOMEK" });
		addToList(Data { (uint32_t)(367 + i*3), (uint32_t)(4140 + i*8), "OLEK" });
	}
	sortByPoints();
}


void Score::addToList(Data data)
{
	Node *node = (Node *)malloc(sizeof(Node));
	if(node) {
		node->data = data;
		node->next = root;
		root = node;
		size++;
	}
}


Score::Node *Score::getList(uint32_t index)
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


Score::Node *Score::sortByPoints(void)
{
/*
	Node *temp = NULL;
	Node *help = NULL;
	for(temp = root; temp != NULL; temp = temp->next) {
		for(help = temp; help != NULL; help = help->next) {
			if((help->data.points > temp->data.points) || (help->data.points == temp->data.points) && (help->data.time > temp->data.time)) {
				Data data = help->data;
				help->data = temp->data;
				temp->data = data;
			}
		}
	}
*/
	bool again = false;

	do {
		Node *node = root;
		Node *prev = NULL;
		again = false;
		while(node) {
			if(node->next) {
				if((node->data.points < node->next->data.points) || (node->data.points == node->next->data.points) && (node->data.time < node->next->data.time)) {
					if(prev) {
						prev->next = node->next;
						Node *temp = prev->next->next;
						prev->next->next = node;
						node->next = temp;
					} else {
						root = node->next;
						Node *temp = root->next;
						root->next = node;
						node->next = temp;
					}
					again = true;
				}
			}
			prev = node;
			node = node->next;
		}
	} while(again);
	return root;
}


Score::Node *Score::sortByTime(void)
{
	Node *temp = NULL;
	Node *help = NULL;
	for(temp = root; temp != NULL; temp = temp->next) {
		for(help = temp; help != NULL; help = help->next) {
			if((help->data.time > temp->data.time) || (help->data.time == temp->data.time) && (help->data.points > temp->data.points)) {
				Data data = help->data;
				help->data = temp->data;
				temp->data = data;
			}
		}
	}
	return root;
}


Score::Node *Score::findByUser(const char *user, uint32_t *index)
{
	Node *node = sortByPoints();
	uint32_t i = 0;

	while(node) {
		if(!strncmp(node->data.user, user, strlen(user))) {
			break;
		}
		node = node->next;
		i++;
	}
	if(index) {
		*index = i;
	}
	return node;
}


void Score::freeList(void)
{
	while(root) {
		Node *node = root->next;
		free(root);
		root = node;
	}
}


int Score::load(const char *filename)
{
#define MAX_LINE_LENGTH	128
	FILE *file;
	char line[MAX_LINE_LENGTH];

	if ((file = fopen(filename, "rt")) != NULL) {
		uint32_t i = 0;
		int result;

		while(fgets(line, MAX_LINE_LENGTH, file) != NULL) {
			Data data;
			memset(&data, 0, sizeof(data));
			if((result = sscanf(line, "%u %u %8s", &data.points, &data.time, data.user)) >= 2) {
				data.user[sizeof(data.user) - 1] = '\0';
				addToList(data);
				i++;
			}
		}
		fclose(file);
		sortByPoints();
		return i;
	}
	return -1;
}


int Score::save(const char *filename)
{
	FILE* file;

	if ((file = fopen(filename, "wt")) != NULL) {
		Node *node = sortByPoints();
		uint32_t i = 0;

#if defined(GLOBAL_MAX_SCORES_TO_FILE)
		while((i < GLOBAL_MAX_SCORES_TO_FILE) && node) {
#else /* !defined(GLOBAL_MAX_SCORES_TO_FILE) */
		while(node) {
#endif /* !defined(GLOBAL_MAX_SCORES_TO_FILE) */
			if(strncmp(node->data.user, SCORE_MAGIC_USER, strlen(SCORE_MAGIC_USER))) {
				fprintf(file, "%u %u %s\n", node->data.points, node->data.time, node->data.user);
				i++;
			}
			node = node->next;
		}
		fclose(file);
		return i;
	}
	return -1;
}
