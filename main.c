#include "9cc.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "引数の個数が正しくありません\n");
		return 1;
	}
	user_input = argv[1];
	token = tokenize(user_input);
	Node *node = program(); 

	// codegen(node);
	// program();
	codegen(node);
	return 0;
}