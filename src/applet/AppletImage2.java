package applet;
import java.util.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

public class AppletImage2 extends JFrame //java.applet.Applet implements Runnable
{
	//thread
	static int total = 10;
	static int time;
	String name;
	 Random r = new Random();
	 
	 
	  //drawImage
	 Image image;
	 
	 //layout
	 JPanel jp = new JPanel();
	 JLabel jl = new JLabel();

	
        
		//applet and frame
		public void init()
	    {
	       add(new Button("One"));
	       add(new Button("Two"));
	     }
	   @Override
	public Dimension preferredSize()
	    {
	       return new Dimension(300,100);
	    }
	   
	   //drawline
	   public AppletImage2()
	   {
		  // JFrame jframe = new JFrame("My JFrame Title");
		   this.setTitle("drawImage&Line");
		   this.setSize(450,350);
		   this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);   
		   this.setVisible(true);
		   
		   
		   //jp.setLayout(new FlowLayout());
		   jp.setLayout(new FlowLayout(1, 100, 100));
		   
		   JButton b1 = new JButton("a");
		   jp.add(b1);
		   jp.add(new JButton("b"));
		   jp.add(new JButton("c"));
		   jp.add(new Button("d"));
		   
		   //jp.setLayout(new BorderLayout());
		   jl.add(new JLabel("text only label"));
		   //jp.add(jl, BorderLayout.EAST);
		   
		   
		   b1.addActionListener(new ActionListener(){

			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				JOptionPane.showMessageDialog(null, "wasup");
			}});
		   
		   add(jl);
		   add(jp);
		   
		   
		   
	   }
	   
	   //drawline, drawimage
	   @Override
	public void paint(Graphics g)
	   {   
		   g.setColor(Color.BLUE);
		   g.drawLine(0, 200, 400, 200);
		   
		   ImageIcon i = new ImageIcon("image/Document1.png");
		   image = i.getImage();
		   g.drawImage(image, 200, 200, null);
		   
		   g.setColor(Color.GREEN);
		   g.drawString("wasupp", 150, 100);
	   }
	   
	   //main
	   public static void main(String[] args)
		{
	
			//frame, applet
			 Frame f = new Frame("Button");
		      AppletImage2 ex = new AppletImage2();
		      ex.init();
		      f.add("Center", ex);
		      f.pack();
		      f.show();   
	
		}}		   