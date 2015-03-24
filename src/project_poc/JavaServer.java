package project_poc;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import java.net.ServerSocket;
import java.net.Socket;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;;

public class JavaServer { 
	
	private static int refNumber; 
	private static double amount_;
	private static String curren;
	private static String xml;
	private static int port = 1234;
	private static String check;
	
	public static int getNumber(){
		return refNumber;}
	
	public static double getAmount(){
		return amount_;}
	
	public static String getCurrency(){
		return curren;}

   public static void main (String [] args){
   
	   send(xml);
	   receive("");
	   if(check.length()>0){System.out.print("OK");}
	   else{System.out.print("NOT OK");}}
   
   public static void send(String message){
	   try {
	         ServerSocket srvr = new ServerSocket(port);
	         Socket skt = srvr.accept();
	         
	         System.out.print("Server has connected!\n");
	         PrintWriter out = new PrintWriter(skt.getOutputStream(), true);
	         System.out.print("Sending string: '" + xml() + "'\n");
	         
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
   
   public static String xml(){ 
	   try {
		   
			File fXmlFile = new File("Sample.xml");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
		 
			doc.getDocumentElement().normalize();
			System.out.println("Root element :" + doc.getDocumentElement().getNodeName());
		 
			NodeList nList = doc.getElementsByTagName("REQUEST");
			System.out.println("----------------------------");
		 
			for (int temp = 0; temp < nList.getLength(); temp++) {
		 
				Node nNode = nList.item(temp);
				System.out.println("\nCurrent Element :" + nNode.getNodeName());
		 
				if (nNode.getNodeType() == Node.ELEMENT_NODE) {
		 
					Element eElement = (Element) nNode;
		 
					System.out.println("Number : " + eElement.getElementsByTagName("NUMBER").item(0).getTextContent());
					System.out.println("Amount : " + eElement.getElementsByTagName("AMOUNT").item(0).getTextContent());
					System.out.println("Currency: " + eElement.getElementsByTagName("CURRENCY").item(0).getTextContent());
					
		xml = "<REQUEST>"+"\n"+"<NUMBER>"+eElement.getElementsByTagName("NUMBER").item(0).getTextContent()+"</NUMBER>"+
		"\n"+"<AMOUNT>"+eElement.getElementsByTagName("AMOUNT").item(0).getTextContent()+"</AMOUNT>"+
		"\n"+"<CURRENCY>"+  eElement.getElementsByTagName("CURRENCY").item(0).getTextContent()+"</CURRENCY>"+"\n"+"</REQUEST>";}}
		
		    } catch (Exception e) {e.printStackTrace();}
	   
	   String stx = charactertonumber("N");
	   String etx = charactertonumber("A");
	   int result = Integer.parseInt(stx) ^ Integer.parseInt(etx);
	   xml = "<"+stx+">"+"<NUMBER>,"+"<CURRENCY>,"+"<AMOUNT>"+"<"+etx+">"+"<"+result+">";

	   return xml;}
   
   public static String charactertonumber(String name){
		
		int value = 0;
		String output = "";
		
		name = name.replace(" ", "");
		name = name.toUpperCase();
		
		for(int i = 0; i< name.length(); i++){
		value = Math.abs(65 - (int)(name.charAt(i)));	
		output = output + value + " ";}
		
		return output;}}