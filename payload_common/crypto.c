#include <openssl/evp.h>
#include <string.h>

void aes_encrypt(unsigned char *plaintext, int plainlen, unsigned char *key, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, key, NULL);
    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plainlen);
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    EVP_CIPHER_CTX_free(ctx);
}