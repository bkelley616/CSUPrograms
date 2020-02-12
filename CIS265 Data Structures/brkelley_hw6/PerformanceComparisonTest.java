
// class to test and compare the performance between an ArrayList based priority queue
// and a HeapQueue based priority queue

public class PerformanceComparisonTest {

    public static void main(String[] args) {

        //initialize each type of priorityQueue to hold 5000 had to add another constructor to each to be able to input
        //the capacity
        ALPQueue arrayListPriorityQueue = new ALPQueue(5000);
        HeapPQueue heapPriorityQueue = new HeapPQueue(5000);

        //construct random integer array to serve as keys
        int[] keyValues = new int[5000];
        for (int i = 0; i < keyValues.length; i++) {
            keyValues[i] = (int) (Math.random()*1000);
        }

        //calculate insertion time for ALPQueue
        long ALPQueueInsertBeforeTime = System.currentTimeMillis();
        for (int i = 0; i < 5000; i++) {
            arrayListPriorityQueue.insert(keyValues[i], "CIS" + keyValues[i]);
        }
        long ALPQueueInsertAfterTime = System.currentTimeMillis();
        long ALPQueueInsertTime = ALPQueueInsertAfterTime - ALPQueueInsertBeforeTime;

        //calculate the remove time for ALPQueue
        long ALPQueueRemoveBeforeTime = System.currentTimeMillis();
        for (int i = 0; i < 5000; i++) {
            arrayListPriorityQueue.removeMin();
        }
        long ALPQueueRemoveAfterTime = System.currentTimeMillis();
        long ALPQueueRemoveTime = ALPQueueRemoveAfterTime - ALPQueueRemoveBeforeTime;

        //calculate the insertion time for HeapPQueue
        long HeapPQueueInsertBeforeTime = System.currentTimeMillis();
        for (int i = 0; i < 5000; i++) {
            heapPriorityQueue.insert(keyValues[i], "CIS" + keyValues[i]);
        }
        long HeapPQueueInsertAfterTime = System.currentTimeMillis();
        long HeapPQueueInsertTime = HeapPQueueInsertAfterTime - HeapPQueueInsertBeforeTime;

        //Calculate the removal time for HeapPQueue
        long HeapPQueueRemoveBeforeTime = System.currentTimeMillis();
        for (int i = 0; i < 5000; i++) {
            heapPriorityQueue.removeMin();
        }
        long HeapPQueueRemoveAfterTime = System.currentTimeMillis();
        long HeapPQueueRemoveTime = HeapPQueueRemoveAfterTime - HeapPQueueRemoveBeforeTime;

        //Format and output results
        System.out.println("ALPQueue:\ninsert 5000 entries " + ALPQueueInsertTime + " ms\nremove 5000 entries: " + ALPQueueRemoveTime + " ms\n");
        System.out.println("HeapPQueue:\ninsert 5000 entries " + HeapPQueueInsertTime + " ms\nremove 5000 entries: " + HeapPQueueRemoveTime + " ms");



    }
}
