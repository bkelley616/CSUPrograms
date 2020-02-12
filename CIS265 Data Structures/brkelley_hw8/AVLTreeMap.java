// class for us to implement an AVL BST
public class AVLTreeMap extends AbstractMap {
    private int n;
    private AVLTreeNode root;
    private AVLTreeNode NIL = new AVLTreeNode();
    private AVLNodeComparator comp = new AVLNodeComparator();

    public AVLTreeMap() {
        root = null; // set root to null, i thought nil at first but pseudo code uses if statement to check if null
        n = 0; // the size of the AVL Tree map
    }

    public int size() {
        return n;
    }

    public boolean isEmpty() {
        return n == 0;
    }

    public Object get(Object key) { // get method, to return the value of the key we search for

        boolean foundKey = false; //variable to control while loop
        AVLTreeNode searchNode = root; //start at root with search

        if (key == null) return null; // if the key is null dont bother searching
        while (!foundKey) { // while we dont find the key, keep looking
            if (searchNode == null) return null;// if searchNode (root or other node) is null then return null (cant find)
            int compareKeys = comp.compare(key, searchNode);// check if the key is contained in the searchNode
            if (compareKeys < 0) { // if less then go left
                searchNode = searchNode.getLeft();
            } else if (compareKeys > 0) { // if greater go right
                searchNode = searchNode.getRight();
            } else { // the values are equal so we found the key
                foundKey = true;
            }
        } //return the value of the search node we are on
        return searchNode.getValue();
    }

    /*
    Algorithm 1: AVL Node Insertion Algorithm
Input: key,value,root // parameters
Output: An AVL tree with the new node storing <key,value>

	newnode <--------------- constructor (key,value) //to creat new node
	set both children of newnode to NILs
	compute newnode's height //don’t need to compute because a new nod has a height of 0
	if root == null //empty tree so this node is the root
		root is newnode
		size++
	else // tree is not empty
		insertAVL(root,newnode);
	end if/else statement

     */

    public Object put(Object key, Object value) {
        AVLTreeNode newNode = new AVLTreeNode((String) key, (String) value);
        newNode.setLeft(NIL);
        newNode.setRight(NIL);
        newNode.setH();

        if (root == null) {
            root = newNode;
            n++;
            return root;
        } else {
            insertAVL(root, newNode);
            return newNode;
        }
    }

    /*
    Algorithm 2: Recursive insertAVL
	Input: p( the root of the subtree), newnode
	output: insertion of a newnode to a subtree rooted at p

	if newnode.key == p.key then  // real code cant directly reference key cause its private should be newnode == p, will have tree node comparator. use that. compares key value
		set p's value to newnode's value
		return
	else if (newnode < p) //  use comparator given // in left subtree
		if p.left == NIL //put new node to the left child of p
			p.left <--- newnode
			newnode.parent <---- p
			update p's height
			size++
		else
			insertAVL(P.left ,newNode)
				if p's balance factor < -1
					if newnode < p.left then
						rotateLL at p (p<---rotateLL(p))
					else
						rotateLR at p (p<---rotateLR(p))
					endif
			endif
			update p's height ( can be a new p due to the rotation)
		end if
	else
		if p.right == NIL then
			p.right <---new node
			newnode.parent <----p
			update p's height
			size++
		else
			insertAVL(p.right , newnode)
			if p's bf > 1
				if newnode > p.right then
					rotateRR at p (p<------ rotateRR(p))
				else
					rotateRL at p (p<---- rotateRL(p))
				endif
			endif
			update p's height (can be a new p due to the rotation)
		endif
	endif
     */

    private void insertAVL(AVLTreeNode p, AVLTreeNode node) {
        if (comp.compare(node, p) == 0) {
            p = node;
            return;
        } else if (comp.compare(node, p) < 0) {
            if (p.getLeft() == NIL) {
                p.setLeft(node);
                node.setParent(p);
                p.setH();
                n++;
            } else {
                insertAVL(p.getLeft(), node);
                if (p.calBF() < -1) {
                    if (comp.compare(node, p.getLeft()) < 0) {
                        rotateLL(p);
                    } else {
                        rotateLR(p);
                    }
                }
                p.setH();
            }

        } else {
            if (p.getRight() == NIL) {
                p.setRight(node);
                node.setParent(p);
                p.setH();
                n++;
            } else {
                insertAVL(p.getRight(), node);
                if (p.calBF() > 1) {
                    if (comp.compare(node, p.getRight()) > 0) {
                        p = rotateRR(p);
                    } else {
                        p = rotateRL(p);
                        //rotateRL(p);
                    }
                }
                p.setH();
            }

        }


    }

    /*
    	Algorithm3 AVL LL Rotation
	Input: a subtree rotated at p
	output: a rebalanced AVL subtree rooted at p

	pp <----------- p.parent
	y <------------- p.left
	v <---------------- y.right
	y.parent <----------pp
	if pp == null then
		root <--- y
	else if p==pp/left then
		pp.left <--- y
	else if (p == pp.getLeft())
        pp.setLeft(y);
	else
		pp.right<---y
	endif
	y.right <----p
	p.left <----v
	 v.parent <---- p
	p.parent <-----y
	update p's height
	return y

     */

    private AVLTreeNode rotateLL(AVLTreeNode p) {
        AVLTreeNode pp = p.getParent();
        AVLTreeNode y = p.getLeft();
        AVLTreeNode v = y.getRight();
        y.setParent(pp);
        if (pp == null)
            root = y;
        else if (p == pp.getLeft())
            pp.setLeft(y);
        else
            pp.setRight(y);
        y.setRight(p);
        p.setLeft(v);
        v.setParent(p);
        p.setParent(y);
        p.setH();
        return y;


    }

    /*
    	Algorithm 4 AVL LR Rotation
	Input: A subtree rooted at p
	Output: A rebalanced AVL subtree rooted at p
	y<-------p.left
	x<--------y.right
	s<------x.left
	p.left<----- x
	x.parent <------p
	x.left<---------y
	y.right <---------- s
	y.parent <------x
	s.parent <--------y
	update y's height
	update x's height
	return rotateLL(p)

     */

    private AVLTreeNode rotateLR(AVLTreeNode p) {
        AVLTreeNode y = p.getLeft();
        AVLTreeNode x = y.getRight();
        AVLTreeNode s = x.getLeft();
        p.setLeft(x);
        x.setParent(p);
        x.setLeft(y);
        y.setRight(s);
        y.setParent(x);
        s.setParent(y);
        y.setH();
        x.setH();
        return rotateLL(p);
    }

    //mirror the given methods by switch left with right

    private AVLTreeNode rotateRR(AVLTreeNode p) {
        AVLTreeNode pp = p.getParent();
        AVLTreeNode y = p.getRight();
        AVLTreeNode v = y.getLeft();
        y.setParent(pp);
        if (pp == null)
            root = y;
        else if (p == pp.getRight())
            pp.setRight(y);
        else
            pp.setLeft(y);
        y.setLeft(p);
        p.setRight(v);
        v.setParent(p);
        p.setParent(y);
        p.setH();
        return y;
    }

    //mirror the given methods by switch left with right

    private AVLTreeNode rotateRL(AVLTreeNode p) {
        AVLTreeNode y = p.getRight();
        AVLTreeNode x = y.getLeft();
        AVLTreeNode s = x.getRight();
        p.setRight(x);
        x.setParent(p);
        x.setRight(y);
        y.setLeft(s);
        y.setParent(x);
        s.setParent(y);
        y.setH();
        x.setH();
        return rotateRR(p);
    }

    public Object remove(Object key) {
        return null;
        // remove is not required for this assignment
    }

    //not best way but use global variables to get the correct formatting
    private boolean first = true;
    private String answer = "";

    //plug root into the recursive search method then return the answer
    public String toString() {
        preOrderTraversal(root);
        return answer + "--" ; // i added the -- at the end to follow the sample output exactly
    }


    //recursive method to traverse the AVL tree in preorder format, return the the order
    public void preOrderTraversal(AVLTreeNode node) {
        if (node == NIL) { //if NIL (child node) stop looking
            return;
        }
        if (first){ // check if first that way we dont include "--" in the answer string
            answer += node.getKey();
            first = false;
        } else // else precede the next last name with --
        answer += "--" + node.getKey();

        preOrderTraversal(node.getLeft()); //check left side, once it runs out of left side then check right side. once
        preOrderTraversal(node.getRight()); // it finishes, we will have a global string with the pre-order traversal
    }


}
