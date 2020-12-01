#include<iostream>
#include<vector>
#include<map>
#include<functional>
#include<algorithm>
#include<memory>
#include<list>
#include<string>
#include<fstream>
#include<sstream>

using std::cout;
using std::endl;

const double loadFactor = 1.5;

class Hashtable{

private:

	// dynamically allocate the number of buckets required as per the incoming data
	int buckets;
	// "adjacency list" of the hash mappings
	// each list is a linked list of the entries from the dataset mapped to a bucket in the hash function
	std::list<int> *hashchains;

protected:

	double evaluateLoad() const {
		double currentLoad = getCurrentTotalHashtableEntries()/buckets;
		return currentLoad;
	}

	int getCurrentTotalHashtableEntries() const {
		int sum = 0;
		for(int i = 0; i < buckets; i++)
			sum += hashchains[i].size();
		return sum;
	}

	int getCurrentBucketSize() {
		return buckets;
	}

	void resetBucketSize() {
		this->buckets *= 2;
	}

public:

	//default parameterless constructor
	Hashtable(): buckets(0), hashchains(nullptr){}

	// parameterized constructor
	Hashtable(const int& buckets){
		this->buckets = buckets;
		hashchains = new std::list<int>[buckets];
	}

	// copy constructor
	Hashtable(const Hashtable& rhs){

		this->buckets = rhs.buckets;

		for(int i = 0; i < rhs.buckets; i++)
			hashchains[i].assign(rhs.hashchains[i].begin(), rhs.hashchains[i].end());
	}

	// copy assignment operator
	const Hashtable& operator=(const Hashtable& rhs){

		this->buckets = rhs.buckets;

		// delete the old dynamically allocated list array
		delete [] hashchains;

		hashchains = new std::list<int>[rhs.buckets];

		for(int i = 0; i < rhs.buckets; i++)
			hashchains[i].assign(rhs.hashchains[i].begin(), rhs.hashchains[i].end());

		return *this;
	}

	int hashFunction(int element) const {
		return element%buckets;
	}

	void addElement(const int& element) {

		// check for the load factor of the current hashtable
		if(evaluateLoad() > loadFactor)
			resetBucketSize();

		int hashPosition = hashFunction(element);
		hashchains[hashPosition].push_back(element);
	}

	void deleteElement(int element) {
		int hashPosition = hashFunction(element);
		auto it = find(hashchains[hashPosition].begin(), hashchains[hashPosition].end(), element);

		if(it != hashchains[hashPosition].end())
			hashchains[hashPosition].erase(it);
		else
			cout << "Element not in the list..." << endl;
	}

	int elementLookup(int element) const {
		int hashPosition = hashFunction(element);
		auto it = find(hashchains[hashPosition].begin(), hashchains[hashPosition].end(), element);

		if(it != hashchains[hashPosition].end())
			return *it;
		else {
			cout << "Element not in the list..." << endl;
			return -1;
		}
	}

};

int main(){

}
