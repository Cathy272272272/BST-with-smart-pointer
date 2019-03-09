# BST-with-smart-pointer
I use unique_ptr to implement BST, because it is convinent to use unique_ptr to implement move constructor. 
As for copy constructor, I use a helper method clone() to make a deep copy for each node.

For example, in my code, I let bst2 deep-copies bst, and insert(0) to bst2, then 0 is found in bst2 but not in bst.
Also, the address of bst.root and bst2.root are different
This indicates that deep-copy is successful, because two objects don't disturb each other.

Move constructor makes a shallow copy of the root and deletes the original pointer.
I make bst3 move-copy bst2, and bst3 can find every keys, but bst2 find none of the keys.
Also, the address of bst3.root is the same as the previous bst2.root, and now bst.root turns into 0x0
This indicates move constructor makes a shallow copy and then make the old pointer becomes a nullptr
