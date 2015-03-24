package applet;

import java.applet.Applet;
import java.applet.AppletContext;
import java.net.MalformedURLException;
import java.net.URL;

public class AppletJavascript extends Applet{
	
	AppletContext a;
	
	@Override
	public void init(){
		a = getAppletContext();
		showStatus("Javascript from Java");}
	
	@Override
	public void start(){
		try {a.showDocument(new URL ("javascript:hello()"));}
		catch (MalformedURLException e) {
			e.printStackTrace();}
		
	}}
