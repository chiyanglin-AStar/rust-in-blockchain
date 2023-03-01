use crypto::digest::Digest;
use crypto::sha2::Sha256;
use std::collections::LinkedList;


// Define a struct to represent a block in the blockchain
struct Block {
    index: u32,
    data: String,
    timestamp: u64,
    previous_hash: String,
    hash: String,
}

// Generate the hash for a block
fn generate_block_hash(data: &str, previous_hash: &str, timestamp: u64) -> String {
    let mut hasher = Sha256::new();
    hasher.input_str(data);
    hasher.input_str(previous_hash);
    hasher.input_str(&timestamp.to_string());
    hasher.result_str()
}

fn main() {
    println!("Hello, world!");
}


// Step 1: Create the genesis block
let genesis_block = Block {
    index: 0,
    data: "Hello, blockchain!".to_owned(),
    timestamp: 1234567890,
    previous_hash: "0000000000000000000000000000000000000000000000000000000000000000".to_owned(),
    hash: "".to_owned(),
};

let mut blockchain = LinkedList::new();
blockchain.push_back(genesis_block);

// Step 2: Add blocks to the blockchain
let previous_block = blockchain.back().unwrap();
let new_block = Block {
    index: previous_block.index + 1,
    data: "This is a new block.".to_owned(),
    timestamp: 1234567891,
    previous_hash: previous_block.hash.clone(),
    hash: "".to_owned(),
};

let new_block_hash = generate_block_hash(&new_block.data, &new_block.previous_hash, new_block.timestamp);
new_block.hash = new_block_hash.clone();

blockchain.push_back(new_block);

// Step 3: Verify the integrity of the blockchain
let mut is_valid = true;
let mut previous_hash = "0000000000000000000000000000000000000000000000000000000000000000".to_owned();
for block in blockchain.iter() {
    if block.previous_hash != previous_hash {
        is_valid = false;
        break;
    }
    let block_hash = generate_block_hash(&block.data, &block.previous_hash, block.timestamp);
    if block.hash != block_hash {
        is_valid = false;
        break;
    }
    previous_hash = block.hash.clone();
}

if is_valid {
    println!("Blockchain is valid.");
} else {
    println!("Blockchain is invalid.");
}

// Step 4: Modify a block in the blockchain
let block_to_modify = blockchain.front_mut().unwrap();

block_to_modify.data = "New data for the genesis block.".to_owned();

let modified_block_hash = generate_block_hash(&block_to_modify.data, &block_to_modify.previous_hash, block_to_modify.timestamp);
block_to_modify.hash = modified_block_hash;
