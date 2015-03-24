package i_O;
	// Use a BufferedReader to read characters from the console. 
import java.io.*;
	public class BufferedReaderString { 
		public static void main(String args[]) throws IOException { 
			String c; 
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
			System.out.println("Enter characters, 'stop' to quit.");
			
			// read characters 
			do { 
				c = br.readLine(); //character by character
				System.out.println(c); } 
			while(!c.equals("stop"));

		}}