package applet;

import java.applet.Applet;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.io.PrintWriter;

import javax.swing.ImageIcon;

public class AppletImage extends Applet{
	PrintWriter p = new PrintWriter(System.out, true);
	Image image;
	
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
    	 g.setColor(Color.BLUE);
		   g.drawLine(0, 200, 400, 200);
		   
		   ImageIcon i = new ImageIcon("image/Document1.png");
		   image = i.getImage();
		   g.drawImage(image, 200, 200, null);
		   
		   g.setColor(Color.GREEN);
		   g.drawString("wasupp", 150, 100);}
}
