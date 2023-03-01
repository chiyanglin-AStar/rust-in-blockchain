#  Blockchain Basic steps

here is a simplified example of how SHA is used to implement a blockchain:

## step 1

Generate a Hash for Each Block: For each block in the blockchain, a unique and unalterable hash value is generated using the SHA-256 algorithm. This hash value is calculated based on the contents of the block, including the transaction data and a previous hash value from the previous block in the chain.

## Step 2
Verify Block Integrity: When a new block is added to the blockchain, its hash value is compared to the previous hash value in the chain to ensure that it has not been tampered with or altered. If the hash value matches, the new block is considered valid and is added to the chain. If the hash value does not match, the block is rejected and the chain remains unchanged.

## Step 3
Verify Chain Integrity: Each block in the blockchain contains a reference to the previous block's hash value, which creates a chain of blocks that are all linked together. This creates a secure and unalterable ledger of all the transactions that have occurred on the blockchain. Any attempt to alter or tamper with the data in a block would cause the hash value of that block to change, which would invalidate the entire chain.

## Step 4 
Mining: To add a new block to the blockchain, a "mining" process is used to solve a complex mathematical puzzle that requires significant computational power. Once the puzzle is solved, the new block is added to the chain and the miner is rewarded with a cryptocurrency.

In summary, SHA is a critical component of blockchain technology as it ensures the integrity and authenticity of the data stored on the blockchain. By using SHA to generate unique and unalterable hash values for each block in the chain, the blockchain can create a secure and tamper-proof ledger of all transactions.