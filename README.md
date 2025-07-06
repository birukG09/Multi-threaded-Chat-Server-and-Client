# AES-256 File Encryption & Decryption Tool

## Description
Encrypt and decrypt files with AES-256 using a password via CLI.

## Requirements
- Crypto++ library installed

## Build and Run
```bash
g++ encrypt.cpp -o encrypt -lcryptopp
./encrypt encrypt plaintext.txt ciphertext.bin mypassword
./encrypt decrypt ciphertext.bin decrypted.txt mypassword
