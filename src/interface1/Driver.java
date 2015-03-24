package interface1;

public class Driver{
	    public static void main(String[] args) {
		
		Vehicle output = new Honda();
		Company output2 = new Honda();
		Accord  output3 = new Honda();
		
		System.out.print(output.accelerate(3)
		+"#"+output.brake(1)+"#");
		output2.name();
		
		System.out.print("$"+output3.cost(25));}
	    
	    	    	
}