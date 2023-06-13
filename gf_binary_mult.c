#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <getopt.h>

void print_help(char* appl_name) {
    printf("Usage: %s [OPTIONS]\n", appl_name);
    printf("Description:\n\tMultiply polynomials over GF(2)[x]/p(x)\n");
    printf("Options:\n");
    printf("  -h, --help               display this help message\n");
    printf("  -d, <degree>             set the degree of the field\n");
    printf("  -a, <value>              set the value of a\n");
    printf("  -b, <value>              set the value of b\n");
    printf("  -p, <poly>               set the irreducible polynomial in hexadecimal\n");
}

typedef struct {
	uint64_t q; // Degree
	uint64_t poly; // Irreducible polynomial
} gf_t;

gf_t* gf_init(uint64_t qi, uint64_t polyi) {
	gf_t* field = malloc(sizeof(gf_t));
	field->q = qi;
	field->poly = polyi;

	return field;
}

uint64_t gf_mul(gf_t* field, uint64_t a, uint64_t b) {
	uint64_t rop = 0;
	while (b > 0) {
		if (b & 1) {
			rop ^= a;
		}
		a <<= 1;
		if (a & (1ULL << field->q)) {
			a ^= field->poly;
		}
		b >>= 1;
	}

	return rop;
}

void polynomial_representation(uint64_t polynomial) {
	uint8_t h_degree = 0;
	uint64_t pcopy = polynomial;
	while (pcopy > 0) {
		pcopy >>= 1;
		h_degree++;
	}

	for (int i = 0; i < h_degree; i++) {
		if (polynomial & (1 << i)) {
			printf("x^%d + ", i);
		}
	}
	printf(" 0\n"); // Sloppy, but works :-)
}

int main(int argc, char* argv[]) {
//	assert(argc >= 4);
	uint64_t a = 0, b = 0, degree = 0, polynomial = 0;

	int opt;
	struct option options[] = {
		{"help", no_argument, 0, 'h'},
		{NULL, required_argument, 0, 'd'},
		{NULL, required_argument, 0, 'a'},
		{NULL, required_argument, 0, 'b'},
		{NULL, required_argument, 0, 'p'},
		{0, 0, 0, 0}
	};

	while ((opt = getopt_long(argc, argv, "hd:a:b:p:", options, NULL)) != -1) {
		switch (opt) {
			case 'h':
				print_help(argv[0]);
				return 0;
			case 'd':
				degree = strtoul(optarg, NULL, 0);
				break;
			case 'a':
				a = strtoul(optarg, NULL, 0);
				break;
			case 'b':
				b = strtoul(optarg, NULL, 0);
				break;
			case 'p':
				polynomial = strtoul(optarg, NULL, 16);
				break;
			default:
				print_help(argv[0]);
				return 1;
		}
	}
	
	gf_t* gf_2q = gf_init(degree, polynomial);
	uint64_t result = gf_mul(gf_2q, a, b);
	printf("0x%lX * 0x%lX = 0x%lX\n", a, b, result);
	polynomial_representation(result);

	free(gf_2q);
	return 0;
}
