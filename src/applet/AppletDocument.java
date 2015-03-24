package applet;

import java.applet.Applet;
import java.applet.AppletContext;
import java.net.MalformedURLException;
import java.net.URL;


public class AppletDocument extends Applet{
	
	String filename;
	URL path, codeBase;
	AppletContext a;
	
	@Override
	public void init(){
		a = getAppletContext();
		filename = getParameter("File Name");
		codeBase = getCodeBase(); //path to the directory of applet class
		
        try {path = new URL(codeBase.toString() + filename);}
		catch (MalformedURLException e) {
			e.printStackTrace();}}
	
	@Override
	public void start(){
		a.showDocument(path);
	}
}
