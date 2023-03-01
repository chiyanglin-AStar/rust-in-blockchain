use chrono::Utc;
use serde::{Deserialize, Serialize};
use serde_json::{json, Value};
use sha2::{Digest, Sha256};

#[derive(Serialize, Deserialize, Debug)]
struct Block {
    index: u32,
    timestamp: i64,
    data: String,
    prev_hash: String,
    hash: String,
}

fn calculate_hash(index: u32, timestamp: i64, data: &str, prev_hash: &str) -> String {
    let mut hasher = Sha256::new();
    hasher.update(index.to_string().as_bytes());
    hasher.update(timestamp.to_string().as_bytes());
    hasher.update(data.as_bytes());
    hasher.update(prev_hash.as_bytes());
    format!("{:x}", hasher.finalize())
}

fn create_genesis_block() -> Block {
    let timestamp = Utc::now().timestamp();
    let data = "Hello, world!".to_owned();
    let prev_hash = "0000000000000000000000000000000000000000000000000000000000000000".to_owned();
    let hash = calculate_hash(0, timestamp, &data, &prev_hash);
    Block { index: 0, timestamp, data, prev_hash, hash }
}

fn create_block(data: String, prev_hash: String, last_block: &Block) -> Block {
    let index = last_block.index + 1;
    let timestamp = Utc::now().timestamp();
    let hash = calculate_hash(index, timestamp, &data, &prev_hash);
    Block { index, timestamp, data, prev_hash, hash }
}

fn is_valid_new_block(new_block: &Block, prev_block: &Block) -> bool {
    if prev_block.index + 1 != new_block.index {
        return false;
    }
    if prev_block.hash != new_block.prev_hash {
        return false;
    }
    if calculate_hash(new_block.index, new_block.timestamp, &new_block.data, &new_block.prev_hash) != new_block.hash {
        return false;
    }
    true
}

fn is_valid_chain(chain: &[Block]) -> bool {
    for i in 1..chain.len() {
        if !is_valid_new_block(&chain[i], &chain[i-1]) {
            return false;
        }
    }
    true
}

fn main() {
    let mut blockchain = vec![create_genesis_block()];

    let block1 = create_block("Data for block 1".to_owned(), blockchain[0].hash.clone(), &blockchain[0]);
    blockchain.push(block1);

    let block2 = create_block("Data for block 2".to_owned(), blockchain[1].hash.clone(), &blockchain[1]);
    blockchain.push(block2);

    println!("Blockchain: {:?}", blockchain);

    let valid = is_valid_chain(&blockchain);
    println!("Is valid chain? {}", valid);

    let json_chain: Value = json!(blockchain);
    println!("JSON representation:\n{}", serde_json::to_string_pretty(&json_chain).unwrap());
}