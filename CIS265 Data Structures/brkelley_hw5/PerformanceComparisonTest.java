
//class to test the difference between each queue type in seconds
//then calculates the percent difference
public class PerformanceComparisonTest {

    // simple method to make output easier to understand and read by converting to seconds
    public static double convertToSeconds (long milliSec) {
        return milliSec /  1000.0;
    }

    // method to calculate the percent difference between the two times
    public static double percentDifference (long slowerTime, long fasterTime) {
        return ((slowerTime - fasterTime)/((slowerTime+fasterTime)/2.0))*100;
    }



    public static void main(String[] args) {

        int numberOfOperations = 50000; // variable for number of operations , can be easily changed to test higher number of operations

        //create each type of array and set capacity to 10,000
        //**Linked list doesn't have CAP**
        ArrayQueue arrayQueue = new ArrayQueue(10000);
        LLQueue llQueue = new LLQueue();



        // add 5,000 random values to each queue
        for (int i = 0; i < 5000; i++) {

            double randomValue = Math.random();
            try{arrayQueue.add(randomValue);}
            catch (QueueFullException exception){}
            llQueue.add(randomValue);

        }


        //calculate time to perform operations for array based queue
        long arrayQueueStart = System.currentTimeMillis();

        for (int i = 0; i < numberOfOperations; i++) {
            double randomValue = Math.random();
            arrayQueue.remove();
            try{arrayQueue.add(randomValue);}
            catch (QueueFullException exception){}
        }

        long arrayQueueEnd = System.currentTimeMillis();
        long arrayQueueTime = (arrayQueueEnd - arrayQueueStart);


        //calculate time to perform operations for array based queue
        long llQueueStart = System.currentTimeMillis();

        for (int i = 0; i < numberOfOperations; i++) {
            double randomValue = Math.random();
            llQueue.remove();
            llQueue.add(randomValue);
        }

        long llQueueEnd = System.currentTimeMillis();
        long llQueueTime = (llQueueEnd - llQueueStart);


        System.out.println(numberOfOperations + " enqueue-dequeue operations were performed on each Queue\n");
        System.out.println("Array Queue Time: " + convertToSeconds(arrayQueueTime) + " seconds");
        System.out.println("Linked List Queue Time: " + convertToSeconds(llQueueTime) + " seconds\n");

        //determine what queue is quicker and get the percent difference and format the output
        if (arrayQueueTime > llQueueTime)
            System.out.println("Linked List Queue is " + String.format("%.1f",percentDifference(arrayQueueTime,llQueueTime)) + " % faster than Array Queue (" + (convertToSeconds(arrayQueueTime-llQueueTime)) + " seconds)");
        else if (arrayQueueTime < llQueueTime)
            System.out.println("Array Queue is " + String.format("%.1f",percentDifference(llQueueTime,arrayQueueTime))+ " % faster than Linked List Queue (" + (convertToSeconds(llQueueTime-arrayQueueTime)) + " seconds)");
        else
            System.out.println("Both Queue types took the same amount of time");


    }
}
