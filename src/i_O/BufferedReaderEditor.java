package i_O;
	// Use a BufferedReader to read characters from the console. 
import java.io.*;
	public class BufferedReaderEditor { 
		public static void main(String args[]) throws IOException { 
			String c[] =new String[100]; 
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
			System.out.println("Enter characters, 'stop' to quit.");
			
			// read characters 
			for(int i =0; i<100; i++) { 
				c[i] = br.readLine(); //character by character
				if(c[i].equals("stop")) break;
} 
			
			System.out.println("\nHere is your file:");
			// display the lines 
			for(int i=0; i<100; i++) { 
				if(c[i].equals("stop")) break; 
				System.out.println(c[i]); }


		}}