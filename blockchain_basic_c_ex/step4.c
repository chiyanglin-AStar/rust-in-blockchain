int modify_block(int block_index, char* new_data, int new_size)
{
    if (block_index >= chain_length || block_index == 0)
    {
        return 0; // Invalid block index
    }

    block_t* block = &blockchain[block_index];
    strncpy(block->data, new_data, new_size);
    block->size = new_size;

    // Recalculate block hash and update subsequent block hashes if necessary
    unsigned char new_hash[SHA256_DIGEST_LENGTH];
    generate_block_hash(block->data, block->size, new_hash);
    memcpy(block->hash, new_hash, SHA256_DIGEST_LENGTH);

    for (int i = block_index + 1; i < chain_length; i++)
    {
        block_t* current_block = &blockchain[i];
        generate_block_hash(current_block->data, current_block->size, current_block->hash);
        memcpy(current_block->hash, current_block->hash, SHA256_DIGEST_LENGTH);
    }

    return 1; // Block modified successfully
}