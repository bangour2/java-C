package project_poc;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

import org.dozer.DozerBeanMapper;

public class JavaClient {
	
	private int NUMBER;
	private double AMOUNT;
	private String CURRENCY;
	private static String data;
	private static int port = 1234;
	private static String check;

	public int getNumber(){
		return NUMBER;}
	
	public double getAmount(){
		return AMOUNT;}
	
	public String getCurrency(){
		return CURRENCY;}
	
   public static void main (String [] args) {
   
	   receive("");
	   send(data);}
   
   public static void send(String message){
	   try {
	         ServerSocket srvr = new ServerSocket(port);
	         Socket skt = srvr.accept();
	         
	         System.out.print("Server has connected!\n");
	         PrintWriter out = new PrintWriter(skt.getOutputStream(), true);
	         System.out.print("Sending string: '" + mapping() + "'\n");
	         
	         out.print(message);
	         out.close();
	         skt.close();
	         srvr.close();
	         
	      }
	      catch(Exception e) {
	         System.out.print("Whoops! It didn't work!\n");}}
   

public static void receive(String message){
 try {
       Socket skt = new Socket("localhost", port);
       BufferedReader in = new BufferedReader(new
          InputStreamReader(skt.getInputStream()));
       
       System.out.print("Received string: '");
       message = "";

       while (!in.ready()) {
       message += message + in.readLine() +"\n";} // Read one line and output it

       check = message;
       in.close();
    }
    catch(Exception e) {
       System.out.print("Whoops! It didn't work!\n");}}
   
   public static String mapping(){
	   List<String> mymappings = new ArrayList<String>();
	   mymappings.add("doxer.xml");
	   
	   JavaServer js = new JavaServer();
	   JavaClient jc = new JavaClient();
	   DozerBeanMapper mapper = new DozerBeanMapper(mymappings);
	   mapper.map(js, jc);
	   
	   data = jc.getNumber()+" "+jc.getAmount()+""+jc.getCurrency();	   
	return data;}
}