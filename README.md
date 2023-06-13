# gf_2q_mult
A demonstration program for finite field arithmetic in $char(\mathbb{F}_q) = 2$ 
## Overview
Binary finite fields provide faster arithmetic on hardware, trading off simplicity provided when working with integer rings $(\mathbb{Z}/p\mathbb{Z})^\times$. It is heavily used in elliptic curve cryptography, however there is debate whether composite curves provide the same level of security as their corresponding prime curve (index calculus, supersingular curves, curves with trace 1, etc).

## Algorithm
![Algorithm](img/1.png)
## Compiling and usage
There is a Makefile attatched to simplify compilation. Run `make build` to compile the program.
```
Usage: ./gf_2q_mult [OPTIONS]
Description:
    Multiply polynomials over GF(2)[x]/p(x)
Options:
  -h, --help               display this help message
  -d <degree>              set the degree of the field
  -a <value>               set the value of a
  -b <value>               set the value of b
  -p <polynomial>          set the irreducible polynomial in hexadecimal
```

## Future features
* Multiplication for all fields $p^q, q \neq 1$. 
* Text truncation
