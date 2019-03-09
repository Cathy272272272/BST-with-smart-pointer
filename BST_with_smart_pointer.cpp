// From http://www.cprogramming.com/tutorial/lesson18.html 
//I implement both copy constructor and move constructor.
//Copy constructor makes a deep copy, for example, I let bst2 deep-copies bst, and insert(0) to bst2, then 0 is found in bst2 but not in bst.
//Also, the address of bst.root and bst2.root are different
//This indicates that deep-copy is successful, because two objects don't disturb each other.
//Move constructor makes a shallow copy and deletes the original pointer.
//I make bst3 move-copy bst2, and bst3 can find every keys, but bst2 find none of the keys.
//Also, the address of bst3.root is the same as the previous bst2.root, and now bst.root turns into 0x0
//This indicates move constructor makes a shallow copy and then make the old pointer becomes a nullptr
#include<iostream>
#include<memory>
using namespace std;
struct node
{
  private:
  	int key_value;
  	unique_ptr<struct node> left;
  	unique_ptr<struct node> right;  
  public:
  	node(int value):key_value(value),left(nullptr),right(nullptr){}
  	node(int value, unique_ptr<node> l, unique_ptr<node> r):key_value(value),left(move(l)),right(move(r)){}
  	int getKeyValue(){
	  return key_value;
  	}
  	node * getLeft(){
	  return left.get();
  	}
  	node * getRight(){
	  return right.get();
  	} 
  	void setLeftKey(int key){
		unique_ptr<node> newNode = make_unique<node>(key);
		this->left = move(newNode);
	}
	void setRightKey(int key){
		unique_ptr<node> newNode = make_unique<node>(key);
		this->right = move(newNode);
	}	
};

class btree
{
    public:
		btree() { 
			root = NULL;
		}
		//copy constructor, deep copy
		btree(btree& tree)
		{
  			root = move(clone(tree.root.get()));
		}
		//move constructor, shallow copy and make the original pointer points to nullptr
		btree(btree && tree){
			root =  move(tree.root);
		}
		void insert(int key) {
			if (root.get() != nullptr){
				insert(key, root.get());
			}
			else
			{			
				unique_ptr<node> newNode = make_unique<node>(key);
				root = move(newNode);
			}
		}
		node * search(int key) {
			node * tmp = search(key, root.get());
			if ( tmp ) return tmp;
			cout << "couldn't find " << key << endl;
			return nullptr;
		}
		void printRootAddress(){
			cout << root.get() << endl;
		}
    private:
		unique_ptr<node> clone(node * ptr)
		{
  			if (ptr)
  			{
				unique_ptr<node> newnode = make_unique<node>(ptr->getKeyValue(), clone(ptr->getLeft()), clone(ptr->getRight()));
    			return newnode;
  			}
  			return nullptr;
		}
		void insert(int key, node * leaf) {
			if (key < leaf->getKeyValue())
			{
				cout << leaf->getLeft() << (nullptr == leaf->getLeft()) << endl;
				if (leaf->getLeft() != nullptr)
					insert(key, leaf->getLeft());
				else
				{
					leaf->setLeftKey(key);
				}
			}
			else if (key >= leaf->getKeyValue())
			{
				cout << leaf->getRight() << (nullptr == leaf->getRight()) << endl;
				if (leaf->getRight() != nullptr)
					insert(key, leaf->getRight());
				else
				{
					leaf->setRightKey(key);
				}
			}
		}
		node * search(int key, node * leaf) {
			if (leaf != nullptr)
			{
				if (key == leaf->getKeyValue()){
					cout << "find " << leaf->getKeyValue() << "\n";
					return leaf;
				}
				if (key < leaf->getKeyValue())
					return search(key, leaf->getLeft());
				else
					return search(key, leaf->getRight());
			}
			else return nullptr;
		}
		unique_ptr<node> root;
};
int main()
{
    btree bst;
    bst.insert(13);
    bst.insert(3);
    bst.insert(5);
    bst.insert(31);
	cout << "Simple test: \n";
	bst.search(13);
    bst.search(3);
    bst.search(5);
    bst.search(31);
	//using copy constructor
	btree bst2 = bst;
	bst2.insert(0);
	cout << "\n\nCopy constructor test: \n";
	cout << "bst result: \n";
	bst.search(0);
	bst.search(13);
    bst.search(3);
    bst.search(5);
    bst.search(31);
	cout << "bst's address: ";
	bst.printRootAddress();
	cout << "bst2 result: \n";
	bst2.search(0);
	bst2.search(13);
    bst2.search(3);
    bst2.search(5);
    bst2.search(31);
	cout << "bst2's address: ";
	bst2.printRootAddress();
	//using move constructor
	btree bst3 = move(bst2);
	cout << "\n\nMove constructor test: \n";
	cout << "bst3 result: \n";
	bst3.search(0);
	bst3.search(13);
    bst3.search(3);
    bst3.search(5);
    bst3.search(31);
	cout << "bst3's address: ";
	bst3.printRootAddress();
	cout << "\nbst2 result: \n";
	bst2.search(0);
	bst2.search(13);
    bst2.search(3);
    bst2.search(5);
    bst2.search(31);
	cout << "bst2's address: ";
	bst2.printRootAddress();
    return 0;

//Below is the output:
// Simple test: 
// find 13
// find 3
// find 5
// find 31


// Copy constructor test: 
// bst result: 
// couldn't find 0
// find 13
// find 3
// find 5
// find 31
// bst's address: 0x7fe166c029e8
// bst2 result: 
// find 0
// find 13
// find 3
// find 5
// find 31
// bst2's address: 0x7fe166c02a28


// Move constructor test: 
// bst3 result: 
// find 0
// find 13
// find 3
// find 5
// find 31
// bst3's address: 0x7fe166c02a28

// bst2 result: 
// couldn't find 0
// couldn't find 13
// couldn't find 3
// couldn't find 5
// couldn't find 31
// bst2's address: 0x0
}




