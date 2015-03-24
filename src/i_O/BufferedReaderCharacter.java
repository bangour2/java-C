package i_O;
	// Use a BufferedReader to read characters from the console. 
import java.io.*;
	public class BufferedReaderCharacter { 
		public static void main(String args[]) throws IOException { 
			char c; 
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
			System.out.println("Enter characters, 'q' to quit.");
			
			// read characters 
			do { 
				c = (char) br.read(); //character by character
				System.out.println(c); } 
			while(c != 'q');

		}}