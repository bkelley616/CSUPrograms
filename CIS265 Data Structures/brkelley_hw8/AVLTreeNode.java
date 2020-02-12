//AVL Tree Node to be used in our implementation of Tree Map
public class AVLTreeNode extends MapEntry {
    private int height;
    private AVLTreeNode parent;
    private AVLTreeNode left;
    private AVLTreeNode right;

    public AVLTreeNode() { // dummy node
        super();
        height = -1;
        parent = null;
        left = null;
        right = null;
    }

    public AVLTreeNode(String key, String value) { // valid node
        super(key, value);
        height = 0;
        parent = null;
        left = null;
        right = null;
    }

    private int max(int l, int r) {
        if (l < r)
            return r;
        return l;
    }

    public AVLTreeNode getLeft() {return left;}
    public AVLTreeNode getRight() {return right;}
    public AVLTreeNode getParent() {return parent;}
    public int getH() {return height;}
    public void setLeft(AVLTreeNode l) {left = l;}
    public void setRight(AVLTreeNode r) {right = r;}
    public void setParent(AVLTreeNode p) {parent = p;}
    public void setH() {height = max(left.getH(), right.getH()) + 1;}
    public int calBF() {
        return this.right.getH() - this.left.getH();
    }
}
