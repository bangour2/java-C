
import java.io.IOException;

	public class ThoughtWork_hw1 {
	   public static void main(String[] args) throws IOException {
	      
	     
    	      /*
    	       * for change file path to "C:/Users/bango_000/Downloads/input.txt"
    	       * 
    	       */
		      TrainMap10 g10 = new TrainMap10();
		      TrainMap9 g9 = new TrainMap9();
		      TrainMap8 g8 = new TrainMap8();
    	      TrainMap7 g7 = new TrainMap7();
    	      TrainMap6 g6 = new TrainMap6();
    	      TrainMap1to5 g5 = new TrainMap1to5();

    	        g5.result();
    	        g6.result();
    	        System.out.print("output #7: ");
    	        g7.result("A", "C", 4); 	 
    	        g8.result();
    	        g9.result();
    	        System.out.print("output #10: ");
    	        g10.result("C", "C", 0); }}