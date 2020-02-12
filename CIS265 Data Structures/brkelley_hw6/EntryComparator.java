import java.util.Comparator;

public class EntryComparator implements Comparator {
    public int compare ( Object a, Object b) {
        int aKey = ((PQEntry)a).getKey();
        int bKey = ((PQEntry)b).getKey();
        return aKey-bKey;
    }

}
