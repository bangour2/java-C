package applet;

import java.awt.*;
import java.applet.*;
import java.io.PrintWriter;
public class SimpleApplet extends Applet { 
	
	PrintWriter p = new PrintWriter(System.out, true);

	String name;
	int id;
	Integer i;
	
    @Override
	public void init(){
    	name =getParameter("Name");
		try{
		id =Integer.parseInt(getParameter("ID"));}
		
		catch (NumberFormatException e){}
    }
    
    @Override
	public void start(){
    	++id;
		i = new Integer(id);
    }
    
    @Override
	public void stop(){}
    
    @Override
	public void destroy(){}
    
    @Override
	public void paint(Graphics g) { 
		g.drawString(name, 20, 30);
		g.drawString(i.toString(), 20, 40);}
    
    }