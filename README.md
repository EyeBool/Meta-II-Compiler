# Meta-II-Compiler

A [Meta II](https://en.wikipedia.org/wiki/META_II) to VALGOL compiler based on Schorre's famous paper "A Syntax-Oriented Compiler Writing Language". The compiler is written in C++11, and uses a recursive descent parser.

## Structure

* `IOUtilities`: An C++11 library to manage input/output for the compiler. Reads from `stdin`, outputs VALGOL code to `stdout`, and errors to `stderr`.
* `MetaII`: A C++11 library to compile Meta II to VALGOL. Uses `IOUtitlies` for input/output.

## References

* D. V. Schorre. 1964. META II: A Syntax-Oriented Compiler Writing Language. In Proceedings of the 1964 19th ACM National Conference (ACM '64). ACM, New York, NY, USA, 41.301-41.3011. DOI=http://dx.doi.org/10.1145/800257.808896
