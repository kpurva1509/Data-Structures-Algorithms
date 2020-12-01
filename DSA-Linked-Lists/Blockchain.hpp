#include "headers.hpp"
#include "Node.hpp"
#include "DoublyLinkedList.hpp"
#include "GenericLinkedList.hpp"
#include "GenericListVisitor.hpp"
#include <stdexcept>
#include "hash.hpp"

using namespace std;

/* Utility functions */

void print_hex(const char *label, const uint8_t *v, size_t len) {
    size_t i;

    printf("%s: ", label);
    for (i = 0; i < len; ++i) {
        printf("%02x", v[i]);
    }
    printf("\n");
}

string getMerkleRoot(const vector<string> &merkle) {
    printf("\nFinding Merkle Root.... \n");
    if (merkle.empty())
        return "";
    else if (merkle.size() == 1) {
        return sha256(merkle[0]);
    }

    vector<string> new_merkle = merkle;

    while (new_merkle.size() > 1) {
        if (new_merkle.size() % 2 == 1)
            new_merkle.push_back(merkle.back());

        vector<string> result;

        for (int i = 0; i < new_merkle.size(); i += 2) {
            string var1 = sha256(new_merkle[i]);
            string var2 = sha256(new_merkle[i + 1]);
            string hash = sha256(var1 + var2);
            // printf("---hash(hash(%s), hash(%s)) => %s\n",new_merkle[0].c_str(),new_merkle[1].c_str(),hash.c_str());
            result.push_back(hash);
        }
        new_merkle = result;
    }
    return new_merkle[0];
}

pair<string, string> findHash(int index, string prevHash, vector<string> &merkle) {
    string header = to_string(index) + prevHash + getMerkleRoot(merkle);
    unsigned int nonce;
    for (nonce = 0; nonce < 100000; nonce++) {
        string blockHash = sha256(header + to_string(nonce));
        if (blockHash.substr(0, 2) == "00") {
            // cout << "nonce: " << nonce;
            // cout << "header: " << header;
            return make_pair(blockHash, to_string(nonce));
            break;
        }
    }
    return make_pair("fail", "fail");
}

class Block {
    int index;
    std::string data;
    std::string prevHashed;
    std::string blockHash;
    std::string nonce;
    std::vector<std::string> merkle;

public:

    Block(int _index, std::string _prevHashed, std::string blockHash, std::string _nonce, std::vector<std::string>& data);
    std::string getPreviousHash();
    std::string getHash();
    int getIndex();
    std::vector<std::string> getData();

    std::string toString();

};

Block::Block(int _index, std::string _prevHashed, std::string blockHash, std::string _nonce, std::vector<std::string> &data){
    this->index = _index;
    this->prevHashed = _prevHashed;
    this->blockHash = blockHash;
    this->nonce = _nonce;
    this->merkle = data;
}

std::string Block::getPreviousHash(){
    return this->prevHashed;
}

std::string Block::getHash(){
    return this->blockHash;
}

int Block::getIndex(){
    return  this->index;
}  

std::vector<std::string> Block::getData(){
    return this->merkle;
}

std::string Block::toString(){
    std::ostringstream oss;
    for (std::vector<std::string>::iterator it = merkle.begin(); it != merkle.end(); it++){
        if(it++ != merkle.end()){
            oss << *it << ", ";
        } else oss << *it;
    }
    oss << "---------------------\n\n";
    oss << "Block index: " << index;
    oss << "\nBlock hash: " << blockHash;
    oss << "\nPrevious hash: " << prevHashed;
    oss << "\n";
    oss << "---------------------\n\n";
    return oss.str();
}

class Blockchain{
    std::vector<std::unique_ptr<Block>> blockchain;
public:
    Blockchain(int genesis=1);
    void addBlock(int _index, std::string _prevHashed, std::string blockHash, std::string _nonce, std::vector<std::string> &data);
    std::unique_ptr<Block>& getBlock(int _index);
    std::string getLatestBlockHash();
    int getSize();
};

Blockchain::Blockchain(int genesis){
    if(genesis == 0){
        std::vector<std::string> vec;
        vec.push_back("Genesis Block");
        auto hash_nonce_pair = findHash(0, string("00000000000000"), vec);

        this->blockchain.push_back(std::make_unique<Block>(0, string("00000000000000"), hash_nonce_pair.first, hash_nonce_pair.second, vec));
        printf("Created blockchain!\n");
    }
}

void Blockchain::addBlock(int _index, std::string _prevHashed, std::string blockHash, std::string _nonce, std::vector<std::string> &data){
    string header = to_string(_index) + _prevHashed + getMerkleRoot(data) + _nonce;
    if(!sha256(header).compare(blockHash) && blockHash.substr(0,2)== "00" && _index == blockchain.size()){
        printf("Block hashes match --- Adding Block %s \n", blockHash.c_str());
        this->blockchain.push_back(std::make_unique<Block>(_index, _prevHashed, blockHash, _nonce, data));
        return;
    }
    cout << "Hash doesn't match criteria\n";
}

std::unique_ptr<Block>& Blockchain::getBlock(int _index) {
    for (int i = 0; i < blockchain.size(); i++){
        if(blockchain[i]->getIndex() == _index){
            return blockchain[i];
        }
    }
    return std::unique_ptr<Block>();
}

std::string Blockchain::getLatestBlockHash(){
    return blockchain[blockchain.size() - 1]->getHash();
}

int Blockchain::getSize(){
    return blockchain.size();
}
