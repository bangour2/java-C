package xy_plot;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;

import javax.swing.JFrame;
import javax.swing.JPanel;


public class GraphingData extends JPanel{
	int[] data = {21, 14, 18, 03};
    final int PAD = 4;

	public static void main(String[] args) {
      JFrame f = new JFrame();
      f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      f.add(new GraphingData());
      f.setSize(400,400);
      f.setLocation(200, 200);
      f.setVisible(true);
      

	}
	
	@Override
	protected void paintComponent(Graphics g){
		super.paintComponent(g);
		
		Graphics2D g2 = (Graphics2D) g;
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		
		int w = getWidth();
		int h = getHeight();
		
		g2.draw(new Line2D.Double(PAD, PAD, PAD, h-PAD)); //draw ordinate
		g2.draw(new Line2D.Double(PAD, h-PAD, w-PAD, h-PAD)); //draw abcissa
		
		double xInc = (double)(w-2*PAD)/(data.length-1);
		double scale = (h - 2*PAD)/getMax();
		
		g2.setPaint(Color.red); //mark data points
		for(int i =0; i< data.length; i++){
			double x = PAD + i*xInc;
			double y = h- PAD - scale*data[i];
			
			g2.fill(new Ellipse2D.Double(x-2, y-2, 4, 4));
		}}

	private double getMax() {
        int max = -Integer.MAX_VALUE;
        for(int i = 0; i< data.length; i++){
        	if(data[i] > max) max = data[i];
        }
		return max;
	}}
