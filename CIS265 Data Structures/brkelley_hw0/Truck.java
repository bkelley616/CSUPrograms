public class Truck extends LandVehicle {

    public Truck() {
        // your implementation

        this("Truck's overloaded constructor is invoked.");
        System.out.println("Truck's no-arg constructor is invoked.");

    }

    public Truck(String s) {
        // your implementation
        System.out.println(s);
    }
}