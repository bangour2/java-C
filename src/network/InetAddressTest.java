package network;

import java.io.IOException;
import java.net.*;
class InetAddressTest { 
	public static void main(String args[]) throws UnknownHostException { 
		InetAddress Address = InetAddress.getLocalHost(); 
		System.out.println(Address); 
		System.out.println(Address.isMulticastAddress());
		System.out.println(Address.isAnyLocalAddress());
		try {
			System.out.println(Address.isReachable(0));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println(Address.isLoopbackAddress());
		System.out.println(Address.isMCGlobal());
		System.out.println(Address.isMCSiteLocal());
		Address = InetAddress.getByName("google.com"); 
		System.out.println(Address); 
		InetAddress SW[] = InetAddress.getAllByName("www.nba.com"); 
		for (int i=0; i<SW.length; i++) System.out.println(SW[i]); 
	   
		System.out.println(InetAddress.getLoopbackAddress());
	} } 
