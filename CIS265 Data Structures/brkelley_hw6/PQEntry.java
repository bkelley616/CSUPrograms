//class to serve as concrete implementation of each entry in the priority queue, its the type of data the queue will hold
//a key value as an integer and a value as a string
public class PQEntry {
    private Integer key;
    private String value;

    public PQEntry() { this(-1,null);}

    public PQEntry (Integer k, String v) {
        this.key = k;
        this.value = v;
    }

    public Integer getKey() {return key;}
    public String getValue() {return value;}
    public void setkey(Integer k) {key =k;}
    public void setValue (String v) {value =v;}

}
