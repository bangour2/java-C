package applet;

import java.applet.Applet;
import java.awt.Color;
import java.awt.Graphics;

public class AppletThread extends Applet {

	MyThread m;
	
	@Override
	public void start(){
		m = new MyThread(this);
		m.t.start();
		}
	
	@Override
	public void paint(Graphics g){
		for(int i =1; i<=5; i++){
			g.drawString("AppletThread", 10, 10*i);}
	
		try {Thread.sleep(100);}
		catch (InterruptedException e) {
			e.printStackTrace();}}}

	
	class MyThread implements Runnable{
		Thread t;
		AppletThread ma;
		
    public MyThread(AppletThread ma){
    	this.ma = ma;
    	t = new Thread(this, "mo");
    }
		
	public void run() {
        Color[] co = {Color.green, Color.yellow,
        		Color.BLACK, Color.blue, Color.cyan};		
	   
        for(int i =0; i<5; i++){
        	ma.setBackground(co[i]);
        	
        	try {Thread.sleep(1000);}
			catch (InterruptedException e) {
				e.printStackTrace();}}
	}}
