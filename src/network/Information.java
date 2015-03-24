package network;
import java.net.*; import java.io.*;
public class Information {
	// Demonstrate Sockets. 
 public static void main(String args[]) throws Exception {
	 int c;
 
	// Create a socket connected to internic.net, port 43. 
	 Socket s = new Socket("google.com", 8080);
	// Obtain input and output streams. 
	 InputStream in = s.getInputStream(); 
	 OutputStream out = s.getOutputStream();
	// Construct a request string.
	 
	 //str = (expression) ? value if true : value if false
	 String str = (args.length == 0 ? "osborne.com" : args[0]) + "\n"; 
	 // Convert to bytes. 
	 byte buf[] = str.getBytes();
	// Send request.
	 out.write(buf);
	// Read and display response. 
	 while ((c = in.read()) != -1) { 
		 System.out.print((char) c); } 
	 s.close();
	}
	}
