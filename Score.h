#ifndef __SCORE_H__
#define __SCORE_H__


#define SCORE_MAGIC_USER	"$"

class Score {
public:
	typedef struct {
		uint32_t points;
		uint32_t time;
		char user[9];
	} Data;

	typedef struct node_s {
		struct node_s *next;
		Data data;
	} Node;

	static void defaults(void);

	static void addToList(Data data);
	static uint32_t getSize(void) { return size; }
	static Node *getList(uint32_t index);
	static Node *sortByPoints(void);
	static Node *sortByTime(void);
	static Node *findByUser(const char *user, uint32_t *index);
	static void freeList(void);

	static int load(const char *filename);
	static int save(const char *filename);

private:
	static Node *root;
	static uint32_t size;
};


#endif /* __SCORE_H__ */
