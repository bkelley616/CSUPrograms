
// concrete ArrayList Priority Queue that will be used to compare performance
public class ALPQueue extends AbstractPQueue {

    private IList list ;//= new ArrayList();
    public ALPQueue() {super();}
    public ALPQueue(int cap) { //needed to add this line or change the default size to 5000 to work
        super();
        list = new ArrayList(cap);
        }
    public ALPQueue( EntryComparator comp) { super(comp);}
    public int size() { return list.size(); }

    public PQEntry insert(Integer key, String value) {
        PQEntry newest = new PQEntry (key, value);
        try {
            list.add ( list.size(), newest);
        } catch ( OutOfRangeException e) {
            System.out.println("OutOfRange");
        }

            return newest;
        }

        private int findMin() {
            int min=0;
            if (size() == 1) return min;
            try {
                for (int i = 1; i < list.size(); i++)
                    if (compare((PQEntry) list.get(min), (PQEntry) list.get(i)) > 0)
                        min = i;
            } catch (OutOfRangeException e) {
                System.out.println("OutOfRange Exception");
            }
            return min;
        }

        public PQEntry min() {
            if(isEmpty()) return null;
            PQEntry answer = null;
            try {
                answer = (PQEntry) list.get(findMin());
            } catch (OutOfRangeException e) {
                System.out.println("OutOfRange");
            }
            return answer;
        }

        public PQEntry removeMin() {
            if(isEmpty()) return null;
            PQEntry answer = null;
            try {
                answer = (PQEntry) list.remove(findMin());
            } catch (OutOfRangeException e) {
                System.out.println("OutOfRange");
            }
            return answer;
        }

    }
