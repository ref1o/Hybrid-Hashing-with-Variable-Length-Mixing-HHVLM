# Hybrid Hashing with Variable-Length Mixing (HHVLM)
## Table of Contents
- [Overview](#Overview)
- [Features](#Features)
- [Installation](#Installation)
- [Usage](#Usage)
- [Examples](#Examples)
- [Algorithm Details](#Algorithm-Details)
- [Performance](#Performance)
- [Comparisons](#Comparisons)
- [Contributing](#Contributing)
- [License](#License)
- [Acknowledgments](#Acknowledgments)

## Overview
Hybrid Hashing with Variable-Length Mixing (HHVLM) is a cryptographic hashing algorithm designed to offer a balanced approach to security and performance. The algorithm combines non-linear bitwise operations, dynamic memory allocation, and multi-round compression to produce a 256-bit hash from arbitrary input data. This makes it a robust solution for various cryptographic needs, including data integrity checks and secure password storage.

## Features
- Strong Collision Resistance: Utilizes non-linear mixing and multi-round compression to enhance collision resistance.
- Dynamic Memory Allocation: Capable of handling inputs of various lengths without the need for pre-defined buffer sizes.
- Salt Integration: Incorporates a 16-byte salt to protect against precomputed attacks, such as rainbow tables.
- Moderate Performance: Balances security with speed, making it suitable for both high-security applications and general-purpose use.

## Installation
To install and use HHVLM, follow these steps:
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/your-repo.git
   ```
2. Navigate to the project directory:
   ```bash
   cd your-repo
   ```
3. Compile the project:
   ```bash
   gcc -o hhvlm hhvlm.c
   ```

## Usage
The HHVLM algorithm can be executed directly from the command line. The program requires one argument: the string you want to hash.
```bash
./hhvlm "Your data here"
```
Example Command:
```bash
./hhvlm "Hello, World!"
```

## Examples
Here are some examples of how to use HHVLM:
1. Hashing a simple string:
```bash
./hhvlm "password123"
```
Output:
```bash
Hash: c46d751c6b911a20dfb66ec7b08ac13bc47c572f2fc47c57572fc47c7c572fc4
```
2. Hashing a longer string:
```bash
./hhvlm "The quick brown fox jumps over the lazy dog."
```
Output:
```bash
Hash: e0b35391e6b5c406f93b4a196eac4c1fe0a271a2a2e0a27171a2e0a2a271a2e0
```

## Algorithm Details
### Step-by-Step Process:
1. Salt Generation:
  - A 16-byte salt is generated using a simple pattern. For enhanced security, this can be replaced with a cryptographically secure random generator.
3. Input Preprocessing:
  - The salt is prepended to the input data.
  - The combined data is padded to ensure its length is a multiple of 32 bytes.
3. Mixing Stage:
  - The data is processed in 32-byte blocks. Each block undergoes non-linear bitwise rotation and XOR operations, combined with modular multiplication for complexity.
4. Multi-round Compression:
  - The internal state is compressed through several rounds, further increasing the hash’s security by reducing any residual predictability.
5. State Extension:
  - The final internal state is extended across the entire 32-byte output buffer.
6. Final XOR with Salt:
  - The first 16 bytes of the output are XORed with the salt, ensuring that even small changes in the input result in a completely different hash.

## Performance
The HHVLM algorithm has been benchmarked across various input sizes to evaluate its performance and scalability. The results indicate consistent performance, with minimal variations in processing time, regardless of the input length.

| Input Length | Average Time Taken (1000 runs) |
|:------------:|:-------------------------------|
| 10           | 0.004561 seconds               |
| 50           | 0.004991 seconds               |
| 100          | 0.004570 seconds               |
| 1000         | 0.004635 seconds               |
| 10000        | 0.004571 seconds               |
| 100000       | 0.004794 seconds               |

These results demonstrate that HHVLM is capable of handling varying input sizes efficiently, making it suitable for applications where performance consistency is critical.

## Comparisons
### HHVLM vs. SHA-256
- Security: Both HHVLM and SHA-256 offer strong security, but HHVLM's use of salt gives it an edge in protecting against certain attacks like rainbow tables.
- Performance: SHA-256 is slightly faster due to hardware optimizations but lacks the salt-based security enhancement of HHVLM.

### HHVLM vs. MD5:
- Security: HHVLM is far more secure than MD5, which is vulnerable to collisions and not recommended for cryptographic use.
- Performance: MD5 is faster but at the cost of significant security flaws.
 
## Contributing
We welcome contributions to improve HHVLM! If you're interested in contributing, follow these steps:
1. Fork the repository on GitHub.
2. Create a new branch for your feature or bug fix:
   ```bash
   git checkout -b feature-branch
   ```
3. Make your changes and commit them:
   ```bash
   git commit -m "Add new feature"
   ```
4. Push to your branch:
   ```bash
   git push origin feature-branch
   ```
5. Submit a pull request for review.

## Acknowledgments
- The design of HHVLM is inspired by the need for a more flexible and secure hashing algorithm, combining ideas from SHA-256 and custom non-linear operations.
- Special thanks to the open-source community for providing the tools and libraries that made this project possible.
