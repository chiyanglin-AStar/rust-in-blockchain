//use hex_literal::hex;
use sha2::{Sha256, Digest};

//use Sha512::{Digest, Sha256};

fn mine(block_number: u32, transactions: &str, previous_hash: &str, difficulty: usize) {
    let mut nonce: u32 = 0;
    loop {
        let block_data = format!("{}{}{}{}", block_number, transactions, previous_hash, nonce);
        let mut hasher = Sha256::new();
        hasher.update(block_data.as_bytes());
        let block_hash = hasher.finalize();

        if block_hash[..difficulty] == [0; 32][..difficulty] {
            println!("Block mined! Nonce: {}, Hash: {:x}", nonce, block_hash);
            return;
        }

        nonce += 1;
    }
}

fn main() {
    let block_number = 12345;
    let transactions = "Transaction data...";
    let previous_hash = "0000000000000000000000000000000000000000000000000000000000000000";
    let difficulty = 5;

    mine(block_number, transactions, previous_hash, difficulty);
}