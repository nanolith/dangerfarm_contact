% Practical Bounded Model Checking
% Justin Handville
% June 15, 2024

## What is Bounded Model Checking?

- An abstract interpretation technique that checks the correctness of
  finite-state systems within bounds.
- For instance, loops and recursion are unrolled to only a certain number of
  iterations, with assertions to check that these iterations are not exceeded.
- All program state, and all possible inputs or outputs of functions, are
  specified using a SAT (Satisfiability) solver or an SMT (Satisfiability Modulo
  Theories) solver.

## Steps for Model Checking a C Program with CBMC

- The C source file and headers are parsed to form an AST.
- This AST is annotated with rules and assertions from the source program are
  captured.
- These rules check for errors such as UAF, buffer overruns, integer overflow /
  underflow, or bad interpretation of data stored in memory.
- This AST with annotations is transformed into an intermediate represention
  known as GOTO.
- This intermediate representation is compiled into a SMT solver program.
- The SMT solver program looks for counter-examples that would fail the rules
  and assertions defined.

## What about other languages like Rust or C++?

- Rust is covered by kani, which is a tool that transforms Rust MIR into GOTO.
- C++ has not gotten as much love after C++11.
- llvm2goto is a tool adapted from an academic project that could be extended to
  support modern C++.
- So far, llvm2goto lacks some support for modern LLVM intrinsics and
  instructions, and needs to be updated with respect to modern GOTO.

## Limitations

- Bounded model checking works best function by function.
- Deep recursion or looping can quickly overwhelm model checking.
- Software needs to be written in an idiomatic style that makes model checking
  easier.
- In many cases, using helper macros and _shadow methods_ (defined later), it is
  possible to port existing software to this style.
- ``formal methods lite''. This is not verifying output from the compiler, that
  the CPU does not have vulnerabilities, or that the specification being built
  is sound.
- Model checking is part of the engineering toolbox to be used in addition to
  other techniques. Think defense in depth.

## Non-determinism in Model Checking

- A non-deterministic value is one that is ``unset'', like a wildcard.
- The solver can use these wildcards when trying to find a failing
  counter-example.
- For instance, if we assert that all outputs for the function `f` are valid,
  and if the input `x` to function `f` is non-deterministic, and `f`
  computes $1 / (x - 5)$, then the solver could choose `x` as $5$ to find a
  divide-by-zero counter-example.

## Practical Development Process

- Use macros / compile-time options to create model assertions.
- Build up function contracts and data structure / class invariants.
- Model check individual functions, replacing called functions with _shadow
  methods_.
- Audit function contracts as part of code review, and capture them as reusable
  functions where possible.
- Build reporting to determine what percentage of code is covered by model
  checks and what specific code should be covered by model checks.

## Shadow Methods

- A shadow method upholds and checks the function contract of the function it
  shadows.
- It uses nondeterministic behavior to return every possible output
  from the function.
- It simulates expected side-effects in a way that can be externally verified.

## Unix Shadow Examples

- `open` allocates a valid descriptor on success, which we can use later on.
- `close` verifies that the descriptor is open and frees this descriptor.
- `read` verifies the descriptor, returns a random number of bytes between the
  total requested and 0, optionally setting the data read with nondeterministic
  values, or return -1 and set `errno` to a nondeterministic value based on the
  range of possible errors it can set.

## Example: Heap Corruption in Serialized Variable Length String

- Program reads a data structure with a variable-length string from a
  descriptor.
- It reads the size, then attempts to compute the total size to allocate and
  read.
- Model checking finds an interesting counter-example.

## Example: Avoiding OSC Sequences in Abitrary UTF-8 on a Terminal.

- We ``constructively prove'' a function that filters potentially harmful UTF-8
  sequences from a string, which could be used to inject operating system
  command sequences into a terminal.
- This demonstrates how model checking programs are a bit different than unit
  tests.

## Example: Resource Leak in Error Flow

- We examine a function that uses the classic ``goto fail'' pattern for handling
  an error flow.
- However, the model checker can find subtle errors.

## Example: Use-After-Free in Error Flow

- Another ``goto fail'' pattern.
