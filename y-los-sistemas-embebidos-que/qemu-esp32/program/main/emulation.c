#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "psa/crypto.h"

static const char *TAG = "QEMU_CRYPTO";

// PRUEBA SHA-256 
void probar_sha256(const char *mensaje) {
    uint8_t hash[32];
    size_t hash_len;

    psa_status_t status = psa_hash_compute(
        PSA_ALG_SHA_256,
        (const uint8_t *)mensaje,
        strlen(mensaje),
        hash, sizeof(hash), &hash_len
    );

    if (status == PSA_SUCCESS) {
        ESP_LOGI(TAG, "[SHA-256] OK");
        printf("Hash: ");
        for (size_t i = 0; i < hash_len; i++) printf("%02x", hash[i]);
        printf("\n---------------------------------------------------\n");
    } else {
        ESP_LOGE(TAG, "[SHA-256] Error: %d", status);
    }
}

// PRUEBA AES-128-CBC 
void probar_aes_128(const char *mensaje) {
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_id_t key_id;
    
    // Clave de 128 bits (16 bytes) e IV estático de 16 bytes
    uint8_t key_bytes[16] = {0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34, 0x56, 
        0x78, 0x90, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12}; // 1234567890123456
    uint8_t iv[16]        = {0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 
        0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70}; // abcdefghijklmnop
    
    // El mensaje debe estar alineado a bloques de 16 bytes (padding simple)
    uint8_t plaintext[32] = "tp de sistemas embebidos 2026"; 
    uint8_t ciphertext[64];
    size_t ciphertext_len;

    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_ENCRYPT);
    psa_set_key_algorithm(&attributes, PSA_ALG_CBC_NO_PADDING);
    psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&attributes, 128);

    if (psa_import_key(&attributes, key_bytes, sizeof(key_bytes), &key_id) != PSA_SUCCESS) {
        ESP_LOGE(TAG, "[AES-128] Error al importar clave");
        return;
    }

    psa_status_t status = psa_cipher_encrypt(
        key_id, PSA_ALG_CBC_NO_PADDING,
        plaintext, sizeof(plaintext),
        ciphertext, sizeof(ciphertext), &ciphertext_len
    );

    if (status == PSA_SUCCESS) {
        ESP_LOGI(TAG, "[AES-128] OK");
        printf("Cifrado: ");
        for (size_t i = 0; i < ciphertext_len; i++) printf("%02x", ciphertext[i]);
        printf("\n---------------------------------------------------\n");
    } else {
        ESP_LOGE(TAG, "[AES-128] Error: %d", status);
    }

    psa_destroy_key(key_id);
}

// PRUEBA ECDSA (secp256r1 / NIST P-256) 
void probar_ecdsa(void) {
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_id_t key_id;
    uint8_t hash[32] = {0x01, 0x02, 0x03, 0x04}; // Hash simulado de entrada
    uint8_t signature[64];
    size_t signature_len;

    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_SIGN_HASH);
    psa_set_key_algorithm(&attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
    psa_set_key_type(&attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
    psa_set_key_bits(&attributes, 256);

    // Generar par de claves ECC
    if (psa_generate_key(&attributes, &key_id) != PSA_SUCCESS) {
        ESP_LOGE(TAG, "[ECDSA] Error al generar clave ECC");
        return;
    }

    // Firmar Hash
    psa_status_t status = psa_sign_hash(
        key_id, PSA_ALG_ECDSA(PSA_ALG_SHA_256),
        hash, sizeof(hash),
        signature, sizeof(signature), &signature_len
    );

    if (status == PSA_SUCCESS) {
        ESP_LOGI(TAG, "[ECDSA] Firma OK (Longitud: %u bytes)", signature_len);
        printf("Firma: ");
        for (size_t i = 0; i < signature_len; i++) printf("%02x", signature[i]);
        printf("\n---------------------------------------------------\n");
    } else {
        ESP_LOGE(TAG, "[ECDSA] Error: %d", status);
    }

    psa_destroy_key(key_id);
}

void app_main(void) {
    ESP_LOGI(TAG, "=== ESP32 QEMU ===");
    printf("---------------------------------------------------\n");
    // Inicializar subsistema
    psa_crypto_init();

    vTaskDelay(pdMS_TO_TICKS(1000));

    probar_sha256("Hola criptografía 2026");
    probar_aes_128("Hola criptografía 2026");
    probar_ecdsa();
}