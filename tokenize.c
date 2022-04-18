#include "9cc.h"


char *user_input;
Token *token;


void error(char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

void error_at(char *loc, char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);

	int pos = loc - user_input;
	fprintf(stderr, "%s\n", user_input);
	fprintf(stderr, "%*s", pos, " ");
	fprintf(stderr, "^ ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

Token *peek(char *s) {
  	if (token->kind != TK_RESERVED || strlen(s) != token->len ||
    	memcmp(token->str, s, token->len))
   		return NULL;
  	return token;
}

bool consume(char *op){
	if (!peek(op))
		return NULL;
	Token *t = token;
	token = token->next;
	return t;
}

bool consume_ident(char *op){
	if (token->kind != TK_IDENT)
		return NULL;
	Token *t = token;
	token = token->next;
	return t;
}




void expect(char *op) {
	if (!peek(op))
 	   error_at(token->str, "'%s'ではありません", op);
 	token = token->next;
}

int expect_number() {
	if (token->kind != TK_NUM)
		error_at(token->str, "数ではありません");
	int val = token->val;
	token = token->next;
	return val;
}

bool at_eof() {
  return token->kind == TK_EOF;
}

Token *new_token(TokenKind kind, Token *cur, char *str, int len) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  tok->len = len;
  cur->next = tok;
  return tok;
}

bool startswitch(char *p, char *q){
	return memcmp(p, q, strlen(q)) == 0;
}

Token *tokenize() {
	char *p = user_input;
	Token head;
	head.next = NULL;
	Token *cur = &head;

	while (*p) {
		if (isspace(*p)) {
			p++;
			continue;
		}
		if (startswitch(p, "==") || startswitch(p, "!=") ||
			startswitch(p, "<=") || startswitch(p, ">=")) {
				cur = new_token(TK_RESERVED, cur, p, 2);
				p += 2;
				continue;
		}

		if (strchr("+-*/()<>", *p)) {
			cur = new_token(TK_RESERVED, cur, p++, 1);
			continue;
		}

		if ('a' <= *p && *p <= 'z'){
			cur = new_token(TK_IDENT, cur, p++, 0);
			cur->len = 1;
			continue;
		}

		if (isdigit(*p)) {
			cur = new_token(TK_NUM, cur, p, 0);
			char *q = p;
			cur->val = strtol(p, &p, 10);
			cur->len = p - q;
			continue;
		}

		error_at(p, "トークナイズできません");
	}

	new_token(TK_EOF, cur, p, 0);
	return head.next;
}